#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <p32xxxx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

/*this file is for handeling interutps*/

void user_isr(void){
    
    if(IFS0 & 0x1){
        IFS0CLR = 0x1;
        
        
        
    }
    
}
