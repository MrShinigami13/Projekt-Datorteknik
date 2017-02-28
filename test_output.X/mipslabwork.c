/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
#include "header.h" /* Declatations for these labs */

volatile int * trise = (volatile int *) 0xbf886100;
volatile int * porte = (volatile int *) 0xbf886110;

#define TMR2PERIOD ((80000000 / 64) / 100)

int bindis = 0;
int mytime = 0x5957;
int timeoutcounter = 0;
char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  if (IFS0 & 0x100)
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
    else if (IFS0 & 0x80) // int1
      {

        labwork();		// behöver ha ett kort delay av någon form för att inte göra flera loopar
        volatile int sw1 = PORTD;
        sw1 = sw1 >> 8;
        sw1 &= 0x1;
        if(sw1 == 0){
          IFS0 &= ~0x80;

        }
        display_score(96,scorezero);
        bindis++;
        PORTE = bindis;

      }
      else if (IFS0 & 0x800) // int2
        {
          labwork();
          volatile int sw2 = PORTD;
          sw2 = sw2 >> 9;
          sw2 &= 0x1;
          if(sw2 == 0){
            IFS0 &= ~0x800;

          }
          display_score(96,scoreone);
          bindis++;
          PORTE = bindis;

        }
        else if (IFS0 & 0x8000) //int3
          {

            labwork();
            volatile int sw3 = PORTD;
            sw3 = sw3 >> 10;
            sw3 &= 0x1;
            if(sw3 == 0){
              IFS0 &= ~0x8000;

            }

            display_score(96,scoretwo);
            bindis++;
            PORTE = bindis;

          }
          else if (IFS0 & 0x80000) // int4
            {

              labwork();
              volatile int sw4 = PORTD;
              sw4 = sw4 >> 11;
              sw4 &= 0x1;
              if(sw4 == 0){
                IFS0 &= ~0x80000;

              }
              display_score(96,scorethree);
              bindis++;
              PORTE = bindis;

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
	INTCON = 0x1E; // high flank on swith 3 (rising edge)

	IPC1 = 0x1c000000;			// external interrupt 1
	IPC2 = 0x1c000000;			// external interrupt 2
	IPC3 = 0x1c000000;			// external interrupt 3
	IPC4 = 0x1c000000;			// external interrupt 4


	T2CON = 0x60;
	PR2 = TMR2PERIOD;

	TMR2 = 0;
	T2CONSET = 0x8000;
	IPC2 = 0x1c;
	//IEC(0) = 0x8100;			//lade till bit för INT3, tidigare 0x100 fungerande
	IEC0 = 0x88980; // för interrupts sw1-4 och timer2
	enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  time2string( textstring, mytime );
  display_string( 3, textstring );
  //display_update();
  //tick( &mytime );
  //bindis++;
  //*porte = bindis;
  //display_image(0, font);
  display_image(96,icon );
  display_update();
}
