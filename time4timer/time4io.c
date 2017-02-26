#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw (void)
{
	volatile int retur = PORTD;
	retur = retur >> 8;
	retur &= 0xf;
	return (retur);
}


int getbtns (void)
{
	volatile int retur = PORTD;
	retur = retur >> 5;
	retur &= 0x7;
	return (retur);
}