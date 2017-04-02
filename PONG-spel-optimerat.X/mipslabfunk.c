/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

/* Declare a helper function which is local to this file */
static void num32asc( char * s, int );

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}


uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {


        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000);
LATEbits.LATE1 = 1;
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
}


void display_screen(int x, const uint8_t *data) {
	int i, j;

	
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i); // var i best�mmer vilken rad som ska skrivas till
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
      
		DISPLAY_CHANGE_TO_DATA_MODE;
    for(i = 0; i < 4; i++) {
		for(j = 0; j < 128; j++)
			spi_send_recv(data[i*128 + j]);
	}
    return;
}
void display_screen_inv(int x, const uint8_t *data) {
	int i, j;

	
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i); // var i best�mmer vilken rad som ska skrivas till
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
      
		DISPLAY_CHANGE_TO_DATA_MODE;
    for(i = 0; i < 4; i++) {
		for(j = 0; j < 128; j++)
			spi_send_recv(~data[i*128 + j]);
	}
    return;
}
void display_matrix(int x, const uint8_t *data) {
	int i, j;

	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i); // var i best�mmer vilken rad som ska skrivas till
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 128; j++)
			spi_send_recv(data[i*128 + j]);
	}
    return;
}

 //---------------------------------------------------------------------------


void ball_to_matrix(void){
int i,j;
	for(i = 0; i< 2 ; i++){
	
        for(j = 0; j< 2 ; j++){
            thematrix[(ball_y)+i][(ball_x)+j] = ball[i][j];

        }
    }

}
void paddle1_to_matrix(void){
int i,j;
	for(i = 0; i< 6 ; i++){
	

	
        for(j = 0; j< 3 ; j++){
            thematrix[paddle1_y+i][j] = paddle1[i][j];

        }
    }

}
void paddle2_to_matrix(void){
int i,j;
	for(i = 0; i< 6 ; i++){
	
        for(j = 0; j< 3 ; j++){
            thematrix[paddle2_y+i][124+j] = paddle2[i][j];

        }
    }

}
void score_to_matrix(void){
int i,j;

if(player1score == 0) {
	for(i = 0; i< 8 ; i++){
		
        for(j = 0; j< 8 ; j++){
            thematrix[i][32+j] = scorezero[i][j];

        }
    }
}
else if (player1score == 1){
      for(i = 0; i< 8 ; i++){
		
        for(j = 0; j< 8 ; j++){
            thematrix[i][32+j] = scoreone[i][j];

        }
    }
}
else if(player1score == 2){
    
    for(i = 0; i< 8 ; i++){
			
        for(j = 0; j< 8 ; j++){
            thematrix[i][32+j] = scoretwo[i][j];

        }
    }
}
else if(player1score == 3){
	for(i = 0; i< 8 ; i++){
		
        for(j = 0; j< 8 ; j++){
            thematrix[i][32+j] = scorethree[i][j];

        }
    }

}
if(player2score == 0) {
	for(i = 0; i< 8 ; i++){
		
        for(j = 0; j< 8 ; j++){
            thematrix[i][96+j] = scorezero[i][j];

        }
    }
}
else if(player2score == 1){
	for(i = 0; i< 8 ; i++){

        
        for(j = 0; j< 8 ; j++){
            thematrix[i][96+j] = scoreone[i][j];

        }
    }
}
else if(player2score == 2){
	for(i = 0; i< 8 ; i++){

        for(j = 0; j< 8 ; j++){
            thematrix[i][96+j] = scoretwo[i][j];

        }
    }
}
else if(player2score == 3){
	for(i = 0; i< 8 ; i++){

        for(j = 0; j< 8 ; j++){
            thematrix[i][96+j] = scorethree[i][j];

        }
    }

}


}
void ui_to_matrix(void) {
	int i,j;
	for (i = 0; i < 9; i++)
	{
		thematrix[i][64] = 1;
	}
	for (j = 0; j < 128; j++)
	{
		thematrix[8][j] = 1;
	}
}
void clear_matrix(void) {
	int i,j;
	for (i = 0; i < 32; i++)
	{

	for (j = 0; j < 128; j++)
	{
		thematrix[i][j] = 0;
	}
}
}
void clear_textbuffer2(void) {
	int i;
	for (i = 0; i < 512; i++)
	{
        textbuffer2[i] = 0;
	
}
}

void  SetBit(int z , int w , int k)
   {

      int pos = k;      //gives the corresponding bit position in A[i]

      unsigned char flag = 1;   // flag = 0000.....00001

      flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)

	  textbuffer2[(z*128) + w] = textbuffer2[(z*128) + w] | flag;      // Set the bit at the k-th position in A[i]

   }

void  ClearBit( int z , int w,  int k )
      {
         textbuffer2[(z*128) + w] &= ~(1 << (k));
      }

void matrix_to_textbuffer(void){

		
			int i,j;
		  int w = 0;
		  int z = 0;
		  int k = 0;
		  for(j =0; j<32;j++){
		    if (j > 7 && j < 16) {
		      z = 1;
		    } else if (j > 15 && j < 24) {
		      z = 2;
		    } else if (j > 23 && j < 32) {
		      z = 3;
		    }
		    for(i = 0; i<128;i++){
				

		          if (k>7){
		            k = 0;
		          }
		        int e = thematrix[j][i]; // byt namn till passande
		        if (e ==1){
		          SetBit(z,i,k);
		        }
		        else{
		         // ClearBit(z,i,k);
		        }


		      }

		    
		   k++;
		  }
		  

} //---------------------------------------------------------------------------
