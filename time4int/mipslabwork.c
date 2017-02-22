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

char textstring[] = "text, more text, and even more text!";

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
		IFS(0) = 0;
	}
	else if (IFS(0) & 0x8000)
		{
			/*volatile int sw3 = PORTD;
			sw3 = sw3 >> 10;
			sw3 &= 0x1;*/
			bindis++;
			PORTE = bindis;
			IFS(0) = 0;
		}

	//return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	*trise = *trise & 0xff00; // 1111 1111 0000 0000
	//*porte = *porte & 0x0;
	PORTE = 0x0;
	TRISD |= 0x7f0;
	INTCON = 0x8; // high flank on swith 3 (rising edge)

	IPC(3) = 0x1c000000;			// external interrupt 3


	T2CON = 0x60;
	PR2 = TMR2PERIOD;

	TMR2 = 0;
	T2CONSET = 0x8000;
	IPC(2) = 0x1c;
	IEC(0) = 0x8100;			//lade till bit för INT3, tidigare 0x100
	enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
	prime = nextprime(prime);
	display_string(0, itoaconv(prime));
	display_update();
}

						/*porte = *porte & 0x0;
  if (bindis = 256)
  {
	  bindis = 0;
  }
  //delay( 1000 );
    int b = getbtns();
  if (b > 0)
  {
	  int s = getsw();
	  switch (b)
	  {
		  case 1:
		  mytime &= 0xff0f;
		  s = s << 4;
		  mytime |= s;
		  break;

		  case 2:
		  mytime &= 0xf0ff;
		  s = s << 8;
		  mytime |= s;
		  break;

		  case 4:
		  mytime &= 0x0fff;
		  s = s << 12;
		  mytime |= s;
		  break;

		  case 3: 			// minst och mellersta
		  mytime &= 0xf00f;
		  s = s << 4;
		  mytime |= s;
		  s = s << 4;
		  mytime |= s;
		  break;

		  case 6:			// högsta och mellersta
		  mytime &= 0x00ff;
		  s = s << 8;
		  mytime |= s;
		  s = s << 4;
		  mytime |= s;
		  break;

		  case 5:			// högsta och minsta
		  mytime &= 0x0f0f;
		  s = s << 4;
		  mytime |= s;
		  s = s << 8;
		  mytime |= s;
		  break;

		  case 7:			// samtliga
		  mytime &= 0x000f;
		  s = s << 4;
		  mytime |= s;
		  s = s << 4;
		  mytime |= s;
		  s = s << 4;
		  mytime |= s;
		  break;
	  }
  }
  if(IFS(0) & 0x100)
  {
	    if (timeoutcounter == 100)
  {
	  timeoutcounter = 0;
    Test time-out event flag

  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  bindis++;
  *porte = bindis;
  display_image(96, icon);
  }
  timeoutcounter++;
  IFS(0) = 0; /* Reset all event flags (crude!)
  }
} */
