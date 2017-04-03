/* mipslabdata.c
   This file compiled 2015 by F Lundevall
   from original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


char textbuffer2[512];
uint8_t thematrix[32][128];

const uint8_t const scorezero[8][8] = {
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 0, 0, 1, 1},
	{1, 1, 1, 0, 0, 1, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
};

const uint8_t const scoreone[8][8] = {
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0},
};

const uint8_t const scoretwo[8][8] = {
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0},
};

const uint8_t const scorethree[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 0, 0},
};

const uint8_t const paddle1[6][3] = {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
};

const uint8_t const paddle2[6][3] = {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
};

const uint8_t const ball[2][2] = {
	{1, 1},
    {1, 1},
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
	1, 2, 4, 8, 16, 32, 64, 128
};

const uint8_t const welcome[] = {
0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0x10, 0x08, 0x08, 0x04,
0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20,
0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0x1C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x1C, 0xE0, 0x00,
0x00, 0x00, 0x00, 0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
0x00, 0x00, 0x07, 0x38, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x38, 0x07, 0x00, 0x00, 0x00, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF8, 0x00,
0x00, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0x01, 0x06, 0x18, 0x06, 0x01, 0x00, 0x00, 0x07, 0xF8,
0x00, 0x00, 0x00, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x0E, 0x70, 0x80, 0x70, 0x0C, 0x03, 0x00, 0x03, 0x0C, 0x70, 0x80,
0x70, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x18, 0x20, 0x40, 0x80, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x20, 0x18, 0x04, 0x00, 0x00, 0x01, 0x06, 0x18, 0x20,
0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x20, 0x18, 0x06, 0x01, 0x00,
0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x3F, 0xC0, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};


const uint8_t const lightning [] = {
0x02, 0x04, 0x04, 0x09, 0x09, 0x11, 0x11, 0x22, 0x22, 0x42, 0x42, 0x84, 0x84, 0x84, 0x04, 0x08,
0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80,
0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x70, 0x80, 0x00, 0x00, 0x00,
0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x20, 0x20, 0x40,
0x40, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80,
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x04, 0x05, 0x06, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x40, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80,
0x80, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x0B, 0x0C, 0x00, 0x01, 0x01, 0x01,
0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x04,
0x08, 0x10, 0x10, 0x20, 0x2E, 0x72, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x20, 0x40, 0x40,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x38, 0xC0, 0x00, 0x00, 0x01, 0x01, 0x01,
0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x20, 0x20,
0x20, 0x21, 0x41, 0x42, 0x42, 0x84, 0x84, 0x88, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80,
0x80, 0x00, 0x02, 0x04, 0x04, 0x08, 0x08, 0x1C, 0x04, 0x08, 0x08, 0x10, 0x00, 0x80, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x17, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04,
0x04, 0x05, 0x05, 0x0A, 0x0A, 0x0C, 0x14, 0x18, 0x18, 0x10, 0x30, 0x20, 0x00, 0x00, 0x00, 0x01,
0x01, 0x02, 0x02, 0x04, 0x04, 0x0F, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00
};


const uint8_t const tohoho[]={
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x03,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x02,0x00,0x00,0x60,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x06,0x00,0x00,0x20,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xe0,0x1f,0xfc,0x00,
0x0c,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0x08,0x00,0x00,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0x30,0x00,0x00,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0x20,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0x20,0x0f,0x80,0x04,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0x40,0x7e,0xf0,0x06,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,
0xc1,0xcc,0x9c,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xe0,0x1f,0xfc,0x01,
0x87,0x18,0xc6,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x01,
0x0c,0x12,0x43,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x03,
0x08,0x12,0x41,0x82,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x02,
0x18,0x12,0x40,0xc2,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x02,
0x10,0x1a,0x40,0xc2,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x02,
0x1c,0x08,0x40,0x82,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x02,
0x07,0x0c,0xc3,0x82,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x03,
0x01,0xf7,0x86,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x01,
0x00,0x1f,0xfc,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x01,
0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x01,
0x80,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x80,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0xc0,0x00,0x00,0x06,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x60,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x30,0x00,0x00,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x10,0x00,0x00,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x18,0x00,0x00,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x0c,0x00,0x00,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x06,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x03,0x80,0x00,0xe0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,
0x00,0xe0,0x00,0xc0,0x00,0x00,0x00,0x00
};

const uint8_t const reflexp1[]={
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
	0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

const uint8_t const reflexp2[]={
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

const uint8_t const reflexp3[]={
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

const uint8_t const reflexp4[]={
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
};