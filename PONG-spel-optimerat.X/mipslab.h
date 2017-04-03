/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
#include <stdint.h>

#define	cbOledDispMax	512		//max number of bytes in display buffer

#define	ccolOledMax		128		//number of display columns
#define	crowOledMax		32		//number of display rows
#define	cpagOledMax		4		//number of display memory pages

void display_image(int x, const uint8_t *data);
void display_screen(int x, const uint8_t *data);
void display_matrix(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
void gameplay(void);
void gamestart(void);
uint8_t spi_send_recv(uint8_t data);

void ball_to_matrix(void);
void paddle1_to_matrix(void);
void paddle2_to_matrix(void);
void score_to_matrix(void);
void ui_to_matrix(void);
void matrix_to_textbuffer(void);
void clear_matrix(void);


/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
void labinit(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );
void enable_interrupt(void);

extern int paddle1_x;
extern int paddle1_y;
extern int paddle2_x;
extern int paddle2_y;
extern int ball_x;
extern int ball_y;
extern int ball_x_speed;
extern int ball_y_speed;
extern int ball_speed;
extern int player1score;
extern int player2score;

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
extern const uint8_t const icon2[128];
extern const uint8_t const test[128*8];
extern const uint8_t const welcome[128*8];
extern const uint8_t const lightning[128*8];
extern const uint8_t const tohoho[128*8];
extern const uint8_t const tohoho2[128*8];
extern const uint8_t const reflexp1[128*8];
extern const uint8_t const reflexp2[128*8];
extern const uint8_t const reflexp3[128*8];
extern const uint8_t const reflexp4[128*8];
// Declar bitmap array containing score numbers

extern const uint8_t const scorezero[8][8];
extern const uint8_t const scoreone[8][8];
extern const uint8_t const scoretwo[8][8];
extern const uint8_t const scorethree[8][8];
extern const uint8_t const paddle1[6][3];
extern const uint8_t const paddle2[6][3];
extern const uint8_t const ball[2][2];


/* Declare text buffer for display output */
extern char textbuffer[4][128];
extern char textbuffer2[512];
extern uint8_t thematrix[32][128];


/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
/* Written as part of i/o lab: getbtns, getsw */
int getbtns(void);
int getsw(void);
