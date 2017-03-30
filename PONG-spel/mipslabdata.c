/* mipslabdata.c
   This file compiled 2015 by F Lundevall
   from original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

	 #include <stdint.h>   /* Declarations of uint_32 and the like */
	 #include <stdio.h>
	 #include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
	 #include "mipslab.h"  /* Declatations for these labs */
	 #include <xc.h>
char textbuffer[4][16];
uint8_t thematrix[32][128];


const uint8_t const icon[] = {  // doge
	255, 255, 255, 255, 255, 255, 127, 187,
	68, 95, 170, 93, 163, 215, 175, 95,
	175, 95, 175, 95, 223, 111, 175, 247,
	59, 237, 242, 254, 171, 254, 1, 255,
	255, 255, 15, 211, 109, 58, 253, 8,
	178, 77, 58, 199, 122, 197, 242, 173,
	242, 237, 186, 215, 40, 215, 41, 214,
	35, 175, 91, 212, 63, 234, 149, 111,
	171, 84, 253, 252, 254, 253, 126, 184,
	195, 52, 201, 22, 225, 27, 196, 19,
	165, 74, 36, 146, 72, 162, 85, 8,
	226, 25, 166, 80, 167, 216, 167, 88,
	106, 149, 161, 95, 135, 91, 175, 87,
	142, 123, 134, 127, 134, 121, 134, 121,
	132, 59, 192, 27, 164, 74, 177, 70,
	184, 69, 186, 69, 254, 80, 175, 217,
};


const int scorezero[8][8] = {
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{1, 1, 1, 0, 0, 1, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 0, 0}
};

const int scoreone[8][8] = {
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0}
};

const int scoretwo[8][8] = {
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0}
};

const int scorethree[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 0, 0}
};

const int paddle1[6][3] = {
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
};

const int paddle2[6][3] = {
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
};

const int ball[2][2] = {
	1, 1, 1, 1,
};


const uint8_t const test[] = {
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
	128, 64, 32, 16, 8, 4, 2, 1,
	1, 2, 4, 8, 16, 32, 64, 128,
};