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

#define TMR2PERIOD ((80000000 / 64) / 100)

#define HSYNC_MASK 0x01
#define VSYNC_MASK 0x02

#define PADDLE_LENGTH 6
#define BALL_LENGTH 2

#define MINX 3
#define MAXX 123
#define MINY 9
#define MAXY 30

int start = 0;
int paddle1_x = 0;
int paddle1_y = 16;
int paddle2_x = 124;
int paddle2_y = 16;
int ball_x = 62;
int ball_x_speed = 1;
int ball_y = 20;
int ball_y_speed = 0;
int ball_speed = 0;
int player1score = 0;
int player2score = 0;
int playerwin = 0;
int startgame = 0;

volatile int sw1, sw2, sw3, sw4;


void _isr( void )
{
	return;
}

/* Lab-specific initialization goes here */
void labinit( void ) {
    *trise = *trise & 0xff00; // 1111 1111 0000 0000

	PORTE = 0x0;
	TRISD |= 0x7f0; // va |=
	enable_interrupt();
    LATEbits.LATE4 = 1;
}

void gameplay_paddle(void) {
    update_switches();
	if (sw1 == 1 && (paddle2_y < 24)){
		paddle2_y++;
	} else if ( sw2 == 1 && (paddle2_y > 8)){
		paddle2_y--;
	}
	if (sw3 == 1 && (paddle1_y < 24)){
		paddle1_y++;
	} else if ( sw4 == 1 && (paddle1_y > 8)){
		paddle1_y--;
	}		
}

void gameplay_ball(void) {
  // vertical motion of the ball, just invert the vertical component if
  // it gets to the top or bottom of the screen.
    ball_y = ball_y + ball_y_speed;
    if (ball_y > MAXY){
        ball_y = MAXY;
    }
    else if (ball_y < MINY){
        ball_y = MINY;
    }
    if((ball_y >= (MAXY - BALL_LENGTH)) && (ball_x <= 108) && (ball_x >= 18)) {
        ball_y_speed = -(random() % (2) + (1));
        ball_x_speed = ((random() % (5) + (1)) - (random() % (5) + (1)));
    } else if ((ball_y <= MINY)  && (ball_x <= 108) && (ball_x >= 18)) {
        ball_y_speed = (random() % (2) + (1));
        ball_x_speed = ((random() % (5) + (1)) - (random() % (5) + (1)));
    } else if (ball_y >= (MAXY - BALL_LENGTH)){
        ball_y_speed = -ball_y_speed;
    } else if (ball_y <= MINY){
        ball_y_speed = -ball_y_speed;
    }
    ball_y = ball_y + ball_y_speed;

  // horizontal motion of the ball.  Need to decide if it hit a bat or not
    ball_x = ball_x + ball_x_speed;

    if(ball_x >= MAXX) {
        int k;
        if ((ball_y >= paddle2_y) && (ball_y <= (paddle2_y +6))){
            k = 1;
        }
		if(k == 1 ) {
            // ball hit bat2
            ball_x_speed = -(random() % (5) + (2));          // just reflect it for now
            // this makes it bounce off up or down the screen depending on
            // where you hit it
            ball_y_speed = ((random() % (2) + (1)) - (random() % (2) + (1)));
            ball_x = MAXX + ball_x_speed;
			k = 0;
        } else {
            explosion_anim(2);
            // player 2 missed the ball, increment player 1's score
            player1score++;
            // reset the ball to the centre of the screen player 1 serves
            ball_y_speed = 0;
            ball_x_speed = 0;
            ball_x = 62 + ball_x_speed;
            ball_y = 20 + ball_y_speed;
			playerwin = 1;           
        }
    } else if(ball_x <= MINX) {
        int paddle1_col, k;
        paddle1_col = paddle1_y;
        if ((ball_y >= paddle1_col) && (ball_y <= (paddle1_col +6))){
            k = 1;
        }
		if(k == 1 ) {
            // ball hit bat1
            ball_x_speed = (random() % (5) + (2));
            ball_y_speed = ((random() % (2) + (1)) - (random() % (2) + (1)));
            ball_x = MINX + ball_x_speed;
            k = 0;
        } else {
            explosion_anim(1);
            // player 1 missed the ball, give player 2 the points and serve
            player2score++;
            ball_y_speed = 0;
            ball_x_speed = 0;
            ball_x = 62 + ball_x_speed;
            ball_y = 20 + ball_y_speed;
			playerwin = 2;
        }
    }
}


/* This function is called repetitively from the main program */
void labwork( void ) {
	int delay = 0;
    int i;
    //volatile int sw1, sw2, sw3, sw4;
    
    while(player1score == 3 || player2score == 3 || startgame == 0) { // press sw to start loop
    // delay innan man kollar sw?
        if(startgame == 0){
            while(delay<60){
                display_matrix(0, reflexplogga);
                delay++;
            }
            delay = 0;
            while ( delay < 60){
                display_matrix(0, reflexploggatext);
                delay++;
            }
            delay = 0;
            
            update_switches();
            if (sw1 == 1 || sw2 == 1 ||sw3 == 1 || sw4 == 1){
                startgame = 1;
            }                   
        } else if(player1score == 3){
            while(delay<10){
                display_matrix(0, player1win);
                delay++;
            }
            delay = 0;

            update_switches();
            if (sw3 == 1 || sw4 == 1){
                player1score = 0;
                player2score = 0;
                startgame = 0;
                start = 0;
            }                   
        } else if(player2score == 3){
            while(delay<10){
                display_matrix(0, player2win);
                delay++;
            }
            delay = 0;

            update_switches();
            if (sw1 == 1 || sw2 == 1){
                player1score = 0;
                player2score = 0;
                startgame = 0;
                start = 0;
            }                  
        }
    }
    while ( player1score != 3 && player2score != 3){
        clear_matrix();
        clear_textbuffer2();

        ui_to_matrix();
        ball_to_matrix();
        paddle1_to_matrix();
        paddle2_to_matrix();
        score_to_matrix();
        matrix_to_textbuffer();
        display_matrix(0, textbuffer2);
        if (start == 0){      
			gamestart();
            start = 1;
        }
        gameplay_paddle();
		while ( playerwin == 1){
			ball_x_speed = 0;
            
            update_switches();
            if (sw3 == 1 || sw4 == 1){
				ball_x_speed = 2;
				playerwin = 0;
                paddle1_x = 0;
                paddle1_y = 16;
                paddle2_x = 124;
                paddle2_y = 16;
            }
		}
		while ( playerwin == 2){
            ball_x_speed = 0;
            
            update_switches();
            if (sw1 == 1 || sw2 == 1){
				ball_x_speed = -2;
				playerwin = 0;
                paddle1_x = 0;
                paddle1_y = 16;
                paddle2_x = 124;
                paddle2_y = 16;
			}
		} 
		if (delay == 2){
			gameplay_ball();
			delay = 0;
		}
		delay++; 
    }
	/*if (player1score == 3){	
	}
	else if (player2score == 3){	
	}*/
}

void gamestart(void) {
	//ball_x++;
    ball_x = ball_x + ball_x_speed;
    ball_y = 20;
	player1score = 0;
	player2score = 0;
    paddle1_x = 0;
    paddle1_y = 16;
    paddle2_x = 124;
    paddle2_y = 16; 
}

