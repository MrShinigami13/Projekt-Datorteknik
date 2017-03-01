/* 
 * File:   newmain.c
 * Author: oskar
 *
 * Created on February 28, 2017, 1:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic32mx.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int bindis = 0;
    PORTE = 0x0;
    TRISE = 0xff00;
    
    while(1){
        bindis++;
		PORTE = bindis;
    }
    
    
    return (EXIT_SUCCESS);
}

