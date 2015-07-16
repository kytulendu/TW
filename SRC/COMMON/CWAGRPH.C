/*
* ============================================================================
* AT&T 6300/Olivetti M24 graphics module for CW 1.20.
*
* Kraisorn  Liansee
* Date:      04/21/1988
* Updated:   04/21/1988
* ============================================================================
*/

#include <dos.h>

/** Set AT&T 6300 / Olivetti M24 Graphic Card to graphic mode */
void att_setgraph( void ) {
	union REGS inregs, outregs;

	inregs.x.ax = 0x40;					/* 640x400 2 color AT&T 6300 */
	int86( 0x10, &inregs, &outregs );
}

/** AT&T 6300 / Olivetti M24 Graphic Card to text mode */
void att_settext( void ) {
	union REGS inregs, outregs;

	inregs.x.ax = 3;					/* 80x25 16 color text mode */
	int86( 0x10, &inregs, &outregs );
}

/** Find offest of pixel x, y by use the following formula
*   0x2000 * ( y % 4 ) + 80 * ( y / 4 ) + ( x / 8 ) ) */
int att_offset( register int x, register int y ) {
	return ( 0x2000 * ( y % 4 ) + 80 * ( y / 4 ) + ( x / 8 ) );
}
