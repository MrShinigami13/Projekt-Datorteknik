/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */

#define	cbOledDispMax	512		//max number of bytes in display buffer

#define	ccolOledMax		128		//number of display columns
#define	crowOledMax		32		//number of display rows
#define	cpagOledMax		4		//number of display memory pages

void display_image(int x, const uint8_t *data);
void display_score(int x, int y, const uint8_t *data);
void display_paddle1(int x, int y, const uint8_t *data);
void display_paddle2(int x, int y, const uint8_t *data);
void display_ball(int x, int y, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );


extern int		xcoOledCur;
extern int		ycoOledCur;
extern char *	pbOledCur;

extern int		bnOledCur;
extern char		clrOledCur;
extern char *	pbOledPatCur;


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

extern int paddle1_x;
extern int paddle1_y;
extern int paddle2_x;
extern int paddle2_y;
extern int ball_x;
extern int ball_y;
extern int ball_speed;
extern int player1score;
extern int player2score;

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
// Declar bitmap array containing score numbers
extern const uint8_t const scorezero[8];
extern const uint8_t const scoreone[8];
extern const uint8_t const scoretwo[8];
extern const uint8_t const scorethree[8];
extern const uint8_t const paddle1[2];
extern const uint8_t const paddle2[2];
extern const uint8_t const ball[4];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

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


#if !defined(OLEDGRPH_H)
#define	OLEDGRPH_H

void	OledMoveTo(int xco, int yco);
void	OledGetPos(int * pxco, int * pyco);

void	OledGetBmp(int dxco, int dyco, uint8_t * pbBmp);
void	OledPutBmp(int dxco, int dyco, uint8_t * pbBmp);

#endif