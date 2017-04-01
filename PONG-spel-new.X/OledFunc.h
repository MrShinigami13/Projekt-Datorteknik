#if !defined(OLEDGRPH_H)
#define	OLEDGRPH_H

void	OledMoveTo(int xco, int yco);
void	OledGetPos(int * pxco, int * pyco);

void	OledGetBmp(int dxco, int dyco, uint8_t * pbBmp);
void	OledPutBmp(int dxco, int dyco, uint8_t * pbBmp);

#endif