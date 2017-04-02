/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdio.h>
#include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <xc.h>

volatile int * trise = (volatile int *) 0xbf886100;
//volatile int * porte = (volatile int *) 0xbf886110;


#define TMR2PERIOD ((80000000 / 64) / 100)

#define HSYNC_MASK 0x01
#define VSYNC_MASK 0x02

#define PADDLE_LENGTH 2
#define BALL_LENGTH 4

#define PADDLE_COL 0xF
#define BALL_COL 0xF

#define MINX 0
#define MAXX 128
#define MINY 9
#define MAXY 32

/*T2CON = 0x60;
#define TMR2PERIOD ((80000000 / 64) / 10)

#if TMR2PERIOD > 0xffff
#error "Timer_period_is_too_big."
#endif

PR2 = TMR2PERIOD;

TMR2 = 0; */

//T2CONSET = 0x8000;
int start = 0;
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

unsigned int random (void)
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

void _isr( void )
{
    LATEbits.LATE3 = 1;
	if (IFS0 & 0x100)
	{
		if (timeoutcounter == 100)
		{
		timeoutcounter = 0;


		tick(&mytime);
		}
		timeoutcounter++;
		IFS0 &= ~0x100;
	}


	return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{


	*trise = *trise & 0xff00; // 1111 1111 0000 0000
	//*porte = *porte & 0x0;
	PORTE = 0x0;
	TRISD |= 0x7f0; // va |=
	/*INTCON = 0x1E; // high flank on swith 3 (rising edge)

	IPC1 = 0x1c000000;			// external interrupt 1
	IPC2 = 0x1c00001c;			// external interrupt 2 och timer 2
	IPC3 = 0x1c000000;			// external interrupt 3
	IPC4 = 0x1c000000;			// external interrupt 4

*/

    INTCONbits.INT1EP = 1;
    INTCONbits.INT2EP = 1;
    INTCONbits.INT3EP = 1;
    INTCONbits.INT4EP = 1;



    T2CONbits.ON = 1;
	PR2 = TMR2PERIOD;


	TMR2 = 0;

    IEC0bits.INT1IE = 0x1;
    IEC0bits.INT2IE = 0x1;
    IEC0bits.INT3IE = 0x1;
    IEC0bits.INT4IE = 0x1;
    IFS0bits.INT1IF = 0x0;
    IFS0bits.INT2IF = 0x0;
    IFS0bits.INT3IF = 0x0;
    IFS0bits.INT4IF = 0x0;
    IEC0bits.T2IE = 0x1;
    IFS0bits.T2IF = 0x0;


	enable_interrupt();
    //interrupts();

    LATEbits.LATE4 = 1;


}

/* This function is called repetitively from the main program */
void labwork( void )
{
    /*int i = 0;
   volatile int sw1 = PORTD;
			sw1 = sw1 >> 8;
			sw1 &= 0x1;
   volatile int sw2 = PORTD;
			sw2 = sw2 >> 9;
			sw2 &= 0x1;
   volatile int sw3 = PORTD;
			sw3 = sw3 >> 10;
			sw3 &= 0x1;
    volatile int sw4 = PORTD;
			sw4 = sw4 >> 11;
			sw4 &= 0x1;

            if(sw1 == 1){
              display_screen(0, test);
            }
            else{*/

              clear_matrix();
              ui_to_matrix();
              ball_to_matrix();
              paddle1_to_matrix();
              paddle2_to_matrix();
              score_to_matrix();
              matrix_to_textbuffer();
              display_matrix(0, textbuffer2);
			  if (start == 0){
			  gamestart();
			  } else{
			  gameplay();
			  start = 1;}
            


}

void gamestart() {
	ball_x++;
	player1score = 0;
	player2score = 0;
}

void gameplay() {
	volatile int sw1 = PORTD;
			sw1 = sw1 >> 8;
			sw1 &= 0x1;
   volatile int sw2 = PORTD;
			sw2 = sw2 >> 9;
			sw2 &= 0x1;
   volatile int sw3 = PORTD;
			sw3 = sw3 >> 10;
			sw3 &= 0x1;
    volatile int sw4 = PORTD;
			sw4 = sw4 >> 11;
			sw4 &= 0x1;
			
			if (sw1 == 1){
					paddle2_y++;
			}
			else if ( sw2 == 1){
				paddle2_y--;
			}
			
			if (sw3 == 1){
					paddle1_y++;
			}
			else if ( sw4 == 1){
				paddle1_y--;
			}

  // read the two paddle controllers and set the two bat postitions
									//bat1 = analogRead(0) / 3 + 50;	här skriver vi input för ms
									//bat2 = analogRead(1) / 3 + 50;

  // vertical motion of the ball, just invert the vertical component if
  // it gets to the top or bottom of the screen.
  ball_y += ball_y;
  if(ball_y >= (MAXY - BALL_LENGTH)) {
    ball_y *= (random() % (-10) + (-1));
	ball_x *= (random() % (10) + (-10));
  } else if (ball_y <= MINY) {
    ball_y *= (random() % (10) + (1));
	ball_x *= (random() % (10) + (-10));
  }

  // horizontal motion of the ball.  Need to decide if it hit a bat or not
  ball_x += ball_x;
  if(ball_x >= MAXX) {
    if((ball_y > paddle2_y - BALL_LENGTH) && (ball_y < (paddle2_y + PADDLE_LENGTH))) {
      // ball hit bat2
      ball_x *= (random() % (-10) + (-1));          // just reflect it for now
      // this makes it bounce off up or down the screen depending on
      // where you hit it
      ball_y *= (random() % (10) + (-10));
    } else {
      // player 2 missed the ball, increment player 1's score
      player1score++;
      // reset the ball to the centre of the screen player 1 serves
      ball_x = 62;
      ball_y = 14;
      //ball_x = (MAXX - MINX) / 2 + MINX;
      //ball = 13;
    }
  } else if(ball_x <= MINX) {
    if((ball_y > paddle1_y - BALL_LENGTH) && (ball_y < (paddle1_y + PADDLE_LENGTH))) {
      // ball hit bat1
      ball_x *= (random() % (10) + (1));
      ball_y *= (random() % (10) + (-10));
    } else {
      // player 1 missed the ball, give player 2 the points and serve
      player2score++;
      ball_x = 62;
      ball_y = 14;
      //ball_x = (MAXX - MINX) / 2 + MINX;
      //ball = 13;
    }
  }

  // toggle the lsb of p to alternate who gets the score next time
 // p^=1;
  // delay a bit before the next position update
  //delay(10);


}
