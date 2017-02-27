/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

volatile int * trise = (volatile int *) 0xbf886100;
//volatile int * porte = (volatile int *) 0xbf886110;


#define TMR2PERIOD ((80000000 / 64) / 100)

#define HSYNC_MASK 0x01
#define VSYNC_MASK 0x02

/*T2CON = 0x60;
#define TMR2PERIOD ((80000000 / 64) / 10)

#if TMR2PERIOD > 0xffff
#error "Timer_period_is_too_big."
#endif

PR2 = TMR2PERIOD;

TMR2 = 0; */

//T2CONSET = 0x8000;
int prime = 1234567;
int timeoutcounter = 0;
int bindis = 0;
int mytime = 0x5957;
int paddle1_x = 0;
int paddle1_y = 12;
int paddle2_x = 126;
int paddle2_y = 12;
int ball_x = 62;
int ball_y = 14;
int ball_speed = 0;
int player1score = 0;
int player2score = 0;

char textstring[] = "text, more text, and even more text!";

unsigned int rand (void)
{
   static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}

/* Interrupt Service Routine */
void user_isr( void )
{
	if (IFS(0) & 0x100)
	{
		if (timeoutcounter == 100)
		{
		timeoutcounter = 0;
		time2string(textstring, mytime);
		display_string(3, textstring);
		display_update();
		tick(&mytime);
		}
		timeoutcounter++;
		IFS(0) &= ~0x100;
	}
	/*else if (IFS(0) & 0x8000) //original
		{
			volatile int sw3 = PORTD;
			sw3 = sw3 >> 10;
			sw3 &= 0x1;
			bindis++;
			PORTE = bindis;
			labwork();
			if(sw3 == 0){
				IFS(0) &= ~0x8000;

			}

		}*/
		else if (IFS(0) & 0x80) // int1
			{

				labwork();		// behöver ha ett kort delay av någon form för att inte göra flera loopar
				volatile int sw1 = PORTD;
				sw1 = sw1 >> 8;
				sw1 &= 0x1;
				if(sw1 == 0){
					IFS(0) &= ~0x80;

				}
				bindis++;
				PORTE = bindis;
				display_score(48, 0, scorezero);

			}
			else if (IFS(0) & 0x800) // int2
				{
					labwork();
					volatile int sw2 = PORTD;
					sw2 = sw2 >> 9;
					sw2 &= 0x1;
					bindis++;
					PORTE = bindis;
					if(sw2 == 0){
						IFS(0) &= ~0x800;

					}
					display_score(48, 0, scoreone);

				}
				else if (IFS(0) & 0x8000) //int3
					{
						labwork();
						volatile int sw3 = PORTD;
						sw3 = sw3 >> 10;
						sw3 &= 0x1;
						bindis++;
						PORTE = bindis;
						if(sw3 == 0){
							IFS(0) &= ~0x8000;

						}
						display_score(48, 0, scoretwo);

					}
					else if (IFS(0) & 0x80000) // int4
						{
							labwork();
							volatile int sw4 = PORTD;
							sw4 = sw4 >> 11;
							sw4 &= 0x1;
							bindis++;
							PORTE = bindis;
							if(sw4 == 0){
								IFS(0) &= ~0x80000;

							}

							display_paddle(126,paddle_y, paddle);
						paddle_y++;
						if(paddle_y > 32)
						{
							paddle_y = 0;
						}
							display_score(48, 0, scorethree);

						}



	//return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	*trise = *trise & 0xff00; // 1111 1111 0000 0000
	//*porte = *porte & 0x0;
	PORTE = 0x0;
	TRISD |= 0x7f0; // va |=
	INTCON = 0x1E; // high flank on swith 3 (rising edge)

	IPC(1) = 0x1c000000;			// external interrupt 1
	IPC(2) = 0x1c00001c;			// external interrupt 2 och timer 2
	IPC(3) = 0x1c000000;			// external interrupt 3
	IPC(4) = 0x1c000000;			// external interrupt 4


	// output controll (hardware PWM)
	OC1CON = 0x0000;
	OC1R = 0x083a;
	OC1RS = 0x083a;
	OC1CON = 0x0006;
	PR2 = 0x08A6;

	// enable the timer interrupts for doing the ball and bats and h_sync
	//IFS0CLR = _IFS0_T2IF_MASK | _IFS0_T3IF_MASK | _IFS0_T4IF_MASK | _IFS0_T5IF_MASK;
	LATDSET = HSYNC_MASK | VSYNC_MASK;
	// enable the timers and output compare
	T2CONSET = 0x8000;
	T3CONSET = 0x8000;
	T4CONSET = 0x8000;
	T5CONSET = 0x8000;
	OC1CONSET = 0x8000;

	// set up the parallel port to drive the colour dac
	PMAEN = 0;
	PMMODE = 0x23FF;
	PMCON = 0x8000;
/* behöver skrivas om FIXME
	ConfigIntTimer2((T2_INT_ON | T2_INT_PRIOR_3));
  ConfigIntTimer3((T3_INT_ON | T3_INT_PRIOR_3));
  ConfigIntTimer4((T4_INT_ON | T4_INT_PRIOR_4));
  ConfigIntTimer5((T5_INT_ON | T5_INT_PRIOR_5));
*/
	T2CON = 0x60;
	PR2 = TMR2PERIOD;

	TMR2 = 0;
	T2CONSET = 0x8000;
//	IPC(2) = 0x1c;
	//IEC(0) = 0x8100;			//lade till bit för INT3, tidigare 0x100 fungerande
	IEC(0) = 0x88980; // för interrupts sw1-4 och timer2
	enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

	//display_string(0, itoaconv(prime));
	display_update();
	//display_image(96,icon);
}

void gameplay() {

  // read the two paddle controllers and set the two bat postitions
									//bat1 = analogRead(0) / 3 + 50;	här skriver vi input för ms
									//bat2 = analogRead(1) / 3 + 50;

  // vertical motion of the ball, just invert the vertical component if
  // it gets to the top or bottom of the screen.
  ball += ball_y_dir;
  if(ball >= (MAXY - BALL_LENGTH)) {
    ball_y_dir *= (lfsr113_Bits() % (-10) + (-1));
	ball_x_dir *= (lfsr113_Bits() % (10) + (-10));
  } else if (ball <= MINY) {
    ball_y_dir *= (lfsr113_Bits() % (-10) + (-1));
	ball_x_dir *= (lfsr113_Bits() % (10) + (-10));
  }

  // horizontal motion of the ball.  Need to decide if it hit a bat or not
  ball_x += ball_x_dir;
  if(ball_x >= MAXX) {
    if((ball > bat2-BALL_LENGTH) && (ball < (bat2 + BAT_LENGTH))) {
      // ball hit bat2
      ball_x_dir *= (lfsr113_Bits() % (-10) + (-1));          // just reflect it for now
      // this makes it bounce off up or down the screen depending on
      // where you hit it
      ball_y_dir *= (lfsr113_Bits() % (10) + (-10));
    } else {
      // player 2 missed the ball, increment player 1's score
      player1_score++;
      // reset the ball to the centre of the screen player 1 serves
      ball_x_dir = 3;
      ball_y_dir = 0;
      ball_x = (MAXX - MINX) / 2 + MINX;
      ball = 13;
    }
  } else if(ball_x <= MINX) {
    if((ball > bat1-BALL_LENGTH) && (ball < (bat1 + BAT_LENGTH))) {
      // ball hit bat1
      ball_x_dir *= (lfsr113_Bits() % (-10) + (-1));
      ball_y_dir *= (lfsr113_Bits() % (10) + (-10));
    } else {
      // player 1 missed the ball, give player 2 the points and serve
      player2_score++;
      ball_x_dir = -3;
      ball_y_dir = 0;
      ball_x = (MAXX - MINX) / 2 + MINX;
      ball = 13;
    }
  }
  // see which of the players score to show this time
  if(p % 2) {
    // enable player 1's 7seg display and disable player 2's
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    // drive the score onto player 1's display
    sevenseg(player1_score);
  } else {
    // enable player 2's 7seg display and disable player 2's
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    // drive the score onto player 2's display
    sevenseg(player2_score);
  }
  // toggle the lsb of p to alternate who gets the score next time
  p^=1;
  // delay a bit before the next position update
  delay(10);
}