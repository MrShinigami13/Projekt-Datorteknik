
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdio.h>
// constants for the size of game elements
#define BAT_LENGTH 20
#define BALL_LENGTH 6

#define BAT_COL 0xF 	
#define BALL_COL 0xF

#define MINX 0
#define MAXX 255
#define MINY 14
#define MAXY 64

#define HSYNC_MASK 0x01
#define VSYNC_MASK 0x02

// global variables
int scanline;	// counts the screen scanline
int bat1;		// position of player 1's bat in scanlines
int bat2;		// position of player 2's bat in scanlines
int ball;		// vertical position of the bat in  scanlines
int ball_x;	// horizontal position of the ball
int ball_x_dir;	// direction and speed of the ball in X axis
int ball_y_dir;	// direction and speed of the ball in Y axis
int player1_score;	// player 1 score
int player2_score;	// player 2 score
int p;		// keep track of which player's score is displayed

unsigned int lfsr113_Bits (void)
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

void setup() {
  
  // initialise the global variables
  scanline=0;		// start at the top of the screen

  bat1 = 13;	// start bat1 in the middle of the screen
  bat2 = 13;
 
  ball = 13;		// start in centre like a serve

  ball_x = 60;	// somewhere near the middle of the screen
  ball_x_dir = 3;	// start with a diagonal direction
  ball_y_dir = 0;
  
  TRISECLR = 0xff;
  TRISDCLR = HSYNC_MASK | VSYNC_MASK;  

  // Set up output control (hardware PWM)
  OC1CON = 0x0000;
  OC1R = 0x083a;
  OC1RS = 0x083a;
  OC1CON = 0x0006;
  PR2 = 0x08A6;
  //PR3 = 0xFFFF;
  LATDSET = HSYNC_MASK | VSYNC_MASK;

  // enable the timer interrupts for doing the ball and bats and h_sync
  IFS0CLR = _IFS0_T2IF_MASK | _IFS0_T3IF_MASK | _IFS0_T4IF_MASK | _IFS0_T5IF_MASK;
  
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

  //pinMode(3, OUTPUT);
  // set up output on digital pin 5 for the V_SYNC signal
  //pinMode(5, OUTPUT);
    //pinMode(13, OUTPUT);
  //digitalWrite(13, LOW);
  ConfigIntTimer2((T2_INT_ON | T2_INT_PRIOR_3));
  ConfigIntTimer3((T3_INT_ON | T3_INT_PRIOR_3));
  ConfigIntTimer4((T4_INT_ON | T4_INT_PRIOR_4));
  ConfigIntTimer5((T5_INT_ON | T5_INT_PRIOR_5));
  // set up output on digital pin 13 for debug

  
  // digital pins 11 and 12 are the enable lines for the two
  // 7seg displays
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  
  // digital pins 34-40 are the bits for the 7seg
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  
  delay(3000);
  //mConfigIntCoreTimer((CT_INT_OFF));
  // start displaying player 1 first
  p = 0;
}

void sevenseg(int score) {
  // base 10 seven segment driver with arduino abstraction
  score = score % 10;	// make sure the number is between 0 and 9
}

void gameplay() {

  // read the two paddle controllers and set the two bat postitions
									//bat1 = analogRead(0) / 3 + 50;	här skriver vi input för ms
									//bat2 = analogRead(1) / 3 + 50;

  // vertical motion of the ball, just invert the vertical component if
  // it gets to the top or bottom of the screen.
  ball += ball_y_dir;
  if(ball >= (MAXY - BALL_LENGTH)) {
    ball_y_dir *= (lfsr113_Bits() % (-10) + (-1));
	ball_x_dir *= (lfsr113_Bits() % (10) + (-10));
  } else if (ball <= MINY) {
    ball_y_dir *= (lfsr113_Bits() % (-10) + (-1));
	ball_x_dir *= (lfsr113_Bits() % (10) + (-10));
  }

  // horizontal motion of the ball.  Need to decide if it hit a bat or not
  ball_x += ball_x_dir;
  if(ball_x >= MAXX) {
    if((ball > bat2-BALL_LENGTH) && (ball < (bat2 + BAT_LENGTH))) {
      // ball hit bat2
      ball_x_dir *= (lfsr113_Bits() % (-10) + (-1));          // just reflect it for now
      // this makes it bounce off up or down the screen depending on
      // where you hit it
      ball_y_dir *= (lfsr113_Bits() % (10) + (-10));
    } else {
      // player 2 missed the ball, increment player 1's score
      player1_score++;
      // reset the ball to the centre of the screen player 1 serves
      ball_x_dir = 3;
      ball_y_dir = 0;
      ball_x = (MAXX - MINX) / 2 + MINX;
      ball = 13;
    }
  } else if(ball_x <= MINX) {
    if((ball > bat1-BALL_LENGTH) && (ball < (bat1 + BAT_LENGTH))) {
      // ball hit bat1
      ball_x_dir *= (lfsr113_Bits() % (-10) + (-1));
      ball_y_dir *= (lfsr113_Bits() % (10) + (-10));
    } else {
      // player 1 missed the ball, give player 2 the points and serve
      player2_score++;
      ball_x_dir = -3;
      ball_y_dir = 0;
      ball_x = (MAXX - MINX) / 2 + MINX;
      ball = 13;
    }
  }
  // see which of the players score to show this time
  if(p % 2) {
    // enable player 1's 7seg display and disable player 2's
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    // drive the score onto player 1's display
    sevenseg(player1_score);
  } else {
    // enable player 2's 7seg display and disable player 2's
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    // drive the score onto player 2's display
    sevenseg(player2_score);
  }
  // toggle the lsb of p to alternate who gets the score next time
  p^=1;
  // delay a bit before the next position update
  delay(10);
}

// interrupt functions have to be C functions
#ifdef __cplusplus
extern "C" {
#endif

/* Timer 2 interrupt, priority 3
    This interrupt is triggered at the end of the h_sync period i.e. the
    beginning of each scanline.  This sets up the interrupts to draw
    the two bats and the ball if they appear on this scan line. */
void __ISR(_TIMER_2_VECTOR, IPL3AUTO) scanline_handler(void) {
  //volatile int i=0;
  //digitalWrite(13, HIGH);
  // reset the three timer counters so that each interrupt occurs
  // from the same point on the screen
  TMR3 = 0;
  TMR4 = 0;
  TMR5 = 0;
  // keep track of how far down the screen we've got
  scanline++;
  if(scanline == 2) {
    // the V_SYNC signal is active low for the first 2 lines so set it high here
    LATDSET = VSYNC_MASK;
  } else if((scanline > 12) && (scanline < 492)) {
    // this is the visible screen area
    if((scanline > ball) && (scanline < (ball + BALL_LENGTH))) {
      // if the ball is on this scanline then set the interrupt to occur at
      // the right time on the line
      PR4 = 0x170 + ball_x;
    } else {
      // if it isn't on this scanline, set the interrupt to happen after the
      // end of the scanline (will never happen so the ball won't draw)
      PR4 = 0xFFFF;
    }
    if((scanline > bat1) && (scanline < (bat1 + BAT_LENGTH))) {
      // if bat1 is on the scanline enable the interrupt
      PR3 = 0x130;
    } else {
      PR3 = 0xFFFF;
    }
    if((scanline > bat2) && (scanline < (bat2 + BAT_LENGTH))) {
      // if bat2 is on the scanline enable the interrupt
      PR5 = 0x660;
    } else {
      PR5 = 0xFFFF;
    }
  } else if(scanline==525) {
    // once at the end of the screen set the V_SYNC low
    LATDCLR = VSYNC_MASK;
    scanline = 0;
  }
  // make sure all the timer interrupt flags are clear and ready to trigger
  // again
  IFS0CLR = _IFS0_T2IF_MASK | _IFS0_T3IF_MASK | _IFS0_T4IF_MASK | _IFS0_T5IF_MASK;
}

/* TIMER_3 draws bat1, and has priority 3 */
void __ISR(_TIMER_3_VECTOR, IPL3AUTO) pixel_handler(void) {
  // The parallel master port has been set up with enough wait states to 
  // get the width of the bat right, so just write to it and close the interrupt
  PMDIN = BAT_COL;
  // to make sure this interrupt doesn't occur again in this scanline the
  // period is set to maximum which won't occur again until after the next
  // h_sync interrupt
  PR3 = 0xFFFF;
  IFS0CLR = _IFS0_T3IF_MASK;
}

/* TIMER_4 interupt draws the ball and has a higher priority
    (can pre-empt the timer 3 interrupt to draw the ball as close
    to the bat as possible) */
void __ISR(_TIMER_4_VECTOR, IPL4AUTO) ball_handler(void) {
  PMDIN = BALL_COL;
  PR4 = 0xFFFF;
  IFS0CLR = _IFS0_T4IF_MASK;
}

/* TIMER_5 draws the second bat but has a higher priority than
    the ball so can draw it close to the ball. */
void __ISR(_TIMER_5_VECTOR, IPL5AUTO) bat2_handler(void) {
  PMDIN = BAT_COL;
  PR5 = 0xFFFF;
  IFS0CLR = _IFS0_T5IF_MASK;
}

#ifdef __cplusplus
}
#endif