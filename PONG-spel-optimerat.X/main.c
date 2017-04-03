/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015 by F Lundevall

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */





// PIC32MX320F128H Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_24         // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>





int main(void) {


   TRISEbits.TRISE0 = 0;
   TRISEbits.TRISE1 = 0;
   TRISEbits.TRISE2 = 0;
   TRISEbits.TRISE3 = 0;
   TRISEbits.TRISE4 = 0;
   TRISEbits.TRISE5 = 0;
   TRISEbits.TRISE6 = 0;
  // Set pin RF0 to 1 (3.3v)
  LATEbits.LATE0 = 1;


	/* Set up peripheral bus clock */
        /* OSCCONbits.PBDIV = 1; */
        OSCCONCLR = 0x100000; /* clear PBDIV bit 1 */
	OSCCONSET = 0x080000; /* set PBDIV bit 0 */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

    LATEbits.LATE5 = 1;
	display_init();


	labinit(); /* Do any lab-specific initialization */
    
    int delay = 0;
        int i;
        while(delay<100000){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
             
        }
        delay = 0;
        
        for(i = 0; i<128;i++){
        while(delay<50000){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
        }
        delay = 0;
        display_matrix(i, welcome); // display welcome scroll
    }
       
        for (i= 0; i<3; i++){
		while (delay<5){
			display_matrix(0, lightning1);
		delay++;}
		while (delay<10){
			display_matrix(0, lightning2);
		delay++;}
		while (delay<15){
			display_matrix(0, lightning3);
		delay++;}
		while (delay<20){
			display_matrix(0, lightning4);
		delay++;}
		while (delay<25){
			display_matrix(0, lightning5);
		delay++;}
		while (delay<30){
			display_matrix(0, lightning6);
		delay++;}
		while (delay<35){
			display_matrix(0, lightning7);
		delay++;}
		while (delay<40){
			display_matrix(0, lightning8);
		delay++;}
		while (delay<45){
			display_matrix(0, lightning9);
		delay++;}
		while (delay<50){
			display_matrix(0, lightning10);
		delay++;}
		while (delay<55){
			display_matrix(0, lightning11);
		delay++;}
		while (delay<60){
			display_matrix(0, lightning12);
		delay++;}
		while (delay<65){
			display_matrix(0, lightning13);
		delay++;}
		while (delay<70){
			display_matrix(0, lightning14);
		delay++;}
		while (delay<75){
			display_matrix(0, lightning15);
		delay++;}
		delay = 0;
	i++;}
        delay = 0;
        
        while(delay<500){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
            display_matrix(0, tohoho);
            display_matrix(0, tohoho2);
        }
        delay = 0;
        
        while(delay<10){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
             display_matrix(0, reflexp1);
        }
        delay = 0;
        while(delay<10){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
             display_matrix(0, reflexp2);
        }
        delay = 0;
        while(delay<10){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
             display_matrix(0, reflexp3);
        }
        delay = 0;
        while(delay<10){ // delay på 50000 är läsbart men inte för långsamt
            delay++;
             display_matrix(0, reflexp4);
        }
        delay = 0;
        
    

	while(1)
	{
        
	  labwork(); /* Do lab-specific things again and again */

	}
	return 0;
}
