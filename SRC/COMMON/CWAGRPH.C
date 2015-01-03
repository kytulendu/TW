/*
* ============================================================================
* AT&T graphics module for CW 1.20
*
* Kraisorn  Liansee
* Date:      04/21/1988
* Updated:   04/21/1988
* ============================================================================
*/

#include <dos.h>

void asetgraph( void ) {
	union REGS inregs, outregs;

	inregs.x.ax = 0x40;					/* 640x400 2 color AT&T 6300 */
	int86( 0x10, &inregs, &outregs );

	/*
	outportb( 0x03C4, 0x02 );
	outportb( 0x03C5, 0x0F );
	*/
}

void asettext( void ) {
	union REGS inregs, outregs;

	inregs.x.ax = 3;					/* 80x25 16 color text mode */
	int86( 0x10, &inregs, &outregs );
}

unsigned int aoffset( register unsigned int x, register unsigned int y ) {
	return ( 0x2000 * ( y % 4 ) + 80 * ( y / 4 ) + x / 8 );
}
