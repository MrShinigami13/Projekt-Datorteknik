
#include <p32xxxx.h>
#include "OledDriver.h"
#include "mipslab.h"


extern int		xcoOledCur;
extern int		ycoOledCur;
extern char *	pbOledCur;
extern char		rgbOledBmp[];

extern int		bnOledCur;
extern char		clrOledCur;
extern char *	pbOledPatCur;


void	OledMoveDown();
void	OledMoveUp();
void	OledMoveRight();
void	OledMoveLeft();

int		OledClampXco(int xco);
int		OledClampYco(int yco);



void OledMoveTo(int xco, int yco)
	{

	/* Clamp the specified coordinates to the display surface
	*/
	xco = OledClampXco(xco);
	yco = OledClampYco(yco);

	/* Save the current position.
	*/
	xcoOledCur = xco;
	ycoOledCur = yco;

	/* Compute the display access parameters corresponding to
	** the specified position.
	*/
	pbOledCur = &rgbOledBmp[((yco/8) * ccolOledMax) + xco];
	bnOledCur = yco & 7;

}

/* ------------------------------------------------------------ */
/***	OledGetPos
**
**	Parameters:
**		pxco	- variable to receive x coordinate
**		pyco	- variable to receive y coordinate
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Fetch the current graphics drawing position
*/

void
OledGetPos(int * pxco, int * pyco)
	{

	*pxco = xcoOledCur;
	*pyco = ycoOledCur;

}


/* ------------------------------------------------------------ */
/***	OledPutBmp
**
**	Parameters:
**		dxco		- width of bitmap
**		dyco		- height of bitmap
**		pbBits		- pointer to the bitmap bits	
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This routine will put the specified bitmap into the display
**		buffer at the current location.
*/

void
OledPutBmp(int dxco, int dyco, char * pbBits)
	{
	int		xcoLeft;
	int		xcoRight;
	int		ycoTop;
	int		ycoBottom;
	char *	pbDspCur;
	char *	pbDspLeft;
	char *	pbBmpCur;
	char *	pbBmpLeft;
	int		xcoCur;
	char	bDsp;
	char	bBmp;
	char	mskEnd;
	char	mskUpper;
	char	mskLower;
	int		bnAlign;
	int		fTop;
	char	bTmp;

	/* Set up the four sides of the destination rectangle.
	*/
	xcoLeft = xcoOledCur;
	xcoRight = xcoLeft + dxco;
	if (xcoRight >= ccolOledMax) {
		xcoRight = ccolOledMax - 1;
	}

	ycoTop = ycoOledCur;
	ycoBottom = ycoTop + dyco;
	if (ycoBottom >= crowOledMax) {
		ycoBottom = crowOledMax - 1;
	}

	bnAlign = ycoTop & 0x07;
	mskUpper = (1 << bnAlign) - 1;
	mskLower = ~mskUpper;
	pbDspLeft = &rgbOledBmp[((ycoTop/8) * ccolOledMax) + xcoLeft];
	pbBmpLeft = pbBits;
	fTop = 1;

	while (ycoTop < ycoBottom) {
		/* Combine with a mask to preserve any upper bits in the byte that aren't
		** part of the rectangle being filled.
		** This mask will end up not preserving any bits for bytes that are in
		** the middle of the rectangle vertically.
		*/
		if ((ycoTop / 8) == ((ycoBottom-1) / 8)) {
			mskEnd = ((1 << (((ycoBottom-1)&0x07)+1)) - 1);
		}
		else {
			mskEnd = 0xFF;
		}
		if (fTop) {
			mskEnd &= ~mskUpper;
		}
											
		xcoCur = xcoLeft;
		pbDspCur = pbDspLeft;
		pbBmpCur = pbBmpLeft;

		/* Loop through all of the bytes horizontally making up this stripe
		** of the rectangle.
		*/
		if (bnAlign == 0) {
			while (xcoCur < xcoRight) {
				*pbDspCur = (*pfnDoRop)(*pbBmpCur, *pbDspCur, mskEnd);
				xcoCur += 1;
				pbDspCur += 1;
				pbBmpCur += 1;
			}
		}
		else {
			while (xcoCur < xcoRight) {
				bBmp = ((*pbBmpCur) << bnAlign);
				if (!fTop) {
					bBmp |= ((*(pbBmpCur - dxco) >> (8-bnAlign)) & ~mskLower);
				}
				bBmp &= mskEnd;
				*pbDspCur = (*pfnDoRop)(bBmp, *pbDspCur, mskEnd);
				xcoCur += 1;
				pbDspCur += 1;
				pbBmpCur += 1;
			}
		}

		/* Advance to the next horizontal stripe.
		*/
		ycoTop = 8*((ycoTop/8)+1);
		pbDspLeft += ccolOledMax;
		pbBmpLeft += dxco;
		fTop = 0;

	}

}



/* ------------------------------------------------------------ */
/***	OledMoveUp
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Updates global variables related to current position on the
**		display.
*/

void
OledMoveUp()
	{

	/* Go up one bit position in the current byte.
	*/
	bnOledCur -= 1;

	/* If we have gone off the end of the current byte
	** go up 1 page.
	*/
	if (bnOledCur < 0) {
		bnOledCur = 7;
		pbOledCur -= ccolOledMax;
		/* If we have gone off of the top of the display,
		** go back down.
		*/
		if (pbOledCur < rgbOledBmp) {
			pbOledCur += ccolOledMax;
		}
	}
}

/* ------------------------------------------------------------ */
/***	OledMoveDown
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Updates global variables related to current position on the
**		display.
*/

void
OledMoveDown()
	{

	/* Go down one bit position in the current byte.
	*/
	bnOledCur += 1;

	/* If we have gone off the end of the current byte,
	** go down one page in the display memory.
	*/
	if (bnOledCur > 7) {
		bnOledCur = 0;
		pbOledCur += ccolOledMax;
		/* If we have gone off the end of the display memory
		** go back up a page.
		*/
		if (pbOledCur >= rgbOledBmp+cbOledDispMax) {
			pbOledCur -= ccolOledMax;
		}
	}
}

/* ------------------------------------------------------------ */
/***	OledMoveLeft
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Updates global variables related to current position on the
**		display.
*/

void
OledMoveLeft()
	{

	/* Are we at the left edge of the display already
	*/
	if (((pbOledCur - rgbOledBmp) & (ccolOledMax-1)) == 0) {
		return;
	}

	/* Not at the left edge, so go back one byte.
	*/
	pbOledCur -= 1;

}

/* ------------------------------------------------------------ */
/***	OledMoveRight
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Updates global variables related to current position on the
**		display.
*/

void
OledMoveRight()
	{

	/* Are we at the right edge of the display already
	*/
	if (((pbOledCur-rgbOledBmp) & (ccolOledMax-1)) == (ccolOledMax-1)) {
		return;
	}

	/* Not at the right edge, so go forward one byte
	*/
	pbOledCur += 1;

}



/* ------------------------------------------------------------ */
/***	OledClampXco
**
**	Parameters:
**		xco		- x value to clamp
**
**	Return Value:
**		Returns clamped x value
**
**	Errors:
**		none
**
**	Description:
**		This routine forces the x value to be on the display.
*/

int
OledClampXco(int xco)
	{
	if (xco < 0) {
		xco = 0;
	}
	if (xco >= ccolOledMax) {
		xco = ccolOledMax-1;
	}

	return xco;

}

/* ------------------------------------------------------------ */
/***	OledClampYco
**
**	Parameters:
**		yco		- y value to clamp
**
**	Return Value:
**		Returns clamped y value
**
**	Errors:
**		none
**
**	Description:
**		This routine forces the y value to be on the display.
*/

int
OledClampYco(int yco)
	{
	if (yco < 0) {
		yco = 0;
	}
	if (yco >= crowOledMax) {
		yco = crowOledMax-1;
	}

	return yco;

}