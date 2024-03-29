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
		//time2string(textstring, mytime);
		//display_string(3, textstring);
    //display_update();
    //OledMoveTo(paddle2_x,paddle2_y);
    //OledPutBmp(2,8,paddle2);
    //display_paddle(paddle1_x,paddle1_y,paddle1);
    //display_paddle(paddle2_x,paddle2_y,paddle2);

		tick(&mytime);
		}
		timeoutcounter++;
		IFS0 &= ~0x100;
	}
	/*else if (IFS0 & 0x8000) //original
		{
			volatile int sw3 = PORTD;
			sw3 = sw3 >> 10;
			sw3 &= 0x1;
			bindis++;
			PORTE = bindis;
			labwork();
			if(sw3 == 0){
				IFS0 &= ~0x8000;

			}

		}*/
    /*
		else if (IFS0 & 0x80) // int1
			{

			//	labwork();		// behöver ha ett kort delay av någon form för att inte göra flera loopar
				volatile int sw1 = PORTD;
				sw1 = sw1 >> 8;
				sw1 &= 0x1;
				if(sw1 == 0){
					IFS0 &= ~0x80;

				}
				bindis++;
				PORTE = bindis;
				//display_score(48, 0, scorezero);

			}
			else if (IFS0 & 0x800) // int2
				{
					//labwork();
					volatile int sw2 = PORTD;
					sw2 = sw2 >> 9;
					sw2 &= 0x1;
					bindis++;
					PORTE = bindis;
					if(sw2 == 0){
						IFS0 &= ~0x800;

					}
					//display_score(48, 0, scoreone);

				}
				else if (IFS0 & 0x8000) //int3
					{
						//labwork();
						volatile int sw3 = PORTD;
						sw3 = sw3 >> 10;
						sw3 &= 0x1;
						bindis++;
						PORTE = bindis;
						if(sw3 == 0){
							IFS0 &= ~0x8000;

						}
						//display_score(48, 0, scoretwo);

					}
					else if (IFS0 & 0x80000) // int4
						{
							//labwork();
							volatile int sw4 = PORTD;
							sw4 = sw4 >> 11;
							sw4 &= 0x1;
							bindis++;
							PORTE = bindis;
							if(sw4 == 0){
								IFS0 &= ~0x80000;

							}


							//display_score(48, 0, scorethree);

						} */


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
    

/*	// output controll (hardware PWM)
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
 * */
/* behöver skrivas om FIXME
	ConfigIntTimer2((T2_INT_ON | T2_INT_PRIOR_3));
  ConfigIntTimer3((T3_INT_ON | T3_INT_PRIOR_3));
  ConfigIntTimer4((T4_INT_ON | T4_INT_PRIOR_4));
  ConfigIntTimer5((T5_INT_ON | T5_INT_PRIOR_5));
*/
	//T2CON = 0x60;
    T2CONbits.ON = 1;
	PR2 = TMR2PERIOD;
    

	TMR2 = 0;
	//T2CONSET = 0x8000;
//	IPC(2) = 0x1c;
	//IEC(0) = 0x8100;			//lade till bit för INT3, tidigare 0x100 fungerandome
	//IEC0 = 0x88980; // för interrupts sw1-4 och timer2
    //IEC0 = 0x100;
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
    int i = 0;
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
  
            while (i == 0)
            {
                display_string(0, "   Doge-Pong     ");
                display_string(1, "   press anykey     ");
                display_string(2, "   to start        ");
                display_string(3, "                ");
                display_update();
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
                            if(sw1||sw2||sw3||sw4)
                                i = 1;
            }
            gameplay();

	//display_string(0, itoaconv(prime));
    //display_image(96,icon);
	//display_update();
  // OledMoveTo(paddle2_x,paddle2_y);
   //OledPutBmp(2,8,paddle2);
	
  //isplay_image(paddle1_x,paddle1);
}

void gameplay() {
    int i = 0;
    int player1score = 0;
    int player2score = 0;
    int oledlek = 46;
    int oledlek2 = 4;
    while(player1score == 0 && player2score == 0)
    {
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
  display_image((oledlek-oledlek2),icon2);
    display_image(oledlek,icon);
    oledlek +=oledlek2;
    if(oledlek <= 8 && sw4)
        oledlek2 = +4;
    else if(oledlek > 96 && sw1)
        oledlek2 = -4;
    else if(oledlek <= 8)
        player2score = 1;
    else if (oledlek > 96)
        player1score = 1;
    
    }
   while (i == 0)
            {
                display_string(0, "Game Over");
                if(player1score == 1)
                display_string(1, "player1 win");
                else if(player2score == 1)
                display_string(1, "player2 win");
                display_string(2, "press anykey");
                display_string(3, "to return");
                display_update();
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
                            if(sw1||sw2||sw3||sw4)
                                i = 1;
            }
}
