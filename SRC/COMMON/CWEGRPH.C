/*
* ============================================================================
* EGA/VGA/MCGA graphics module for CW 1.20
*
* Kraisorn  Liansee
* Date:      04/21/1988
* Updated:   04/21/1988
*
* Updated: Suttipong Kanakakorn
* Mon  07-31-1989  19:03:13
* Tue  08-22-1989  01:53:19
* ============================================================================
*/

#include <dos.h>

#include "cwgrphc.h"
#include "grdetect.h"

/** Set EGA/VGA/MCGA Graphic Card to graphic mode */
void ega_setgraph( void ) {
	union REGS inregs, outregs;

	if ( scrmode == VGA ) {
		/*inregs.x.ax = 0x12;*/			/* 640 x 480 16 color graphic mode on VGA display */
		inregs.x.ax = 0x11;
	} else if ( scrmode == MCGA ) {
		inregs.x.ax = 0x11;			/* 640 x 480 monochrome graphic mode on MCGA display */
	} else if ( scrmode == EGA64 || scrmode == EGA ) {
		inregs.x.ax = 0x10;			/* 640 x 350 4 or 16 color graphic mode on EGA display */
	} else {						/* scrmode == EGAMONO */
		inregs.x.ax = 0x0F;			/* 640 x 350 monochrome graphic mode on EGA monochrome display */
	}

	int86( 0x10, &inregs, &outregs );

	outportb( 0x03C4, 0x02 );		/* CGA, EGA, VGA sequencer index */
	if ( scrmode != EGAMONO ) {
		outportb( 0x03C5, 0x0F );	/* CGA, EGA, VGA sequencer */
	} else {
		outportb( 0x03C5, 0x03 );	/* use 2 plain only on mode 0F */
	}
}

/** Set EGA/VGA/MCGA Graphic Card to text mode */
void ega_settext( void ) {
	union REGS inregs, outregs;

	inregs.x.ax = 3;					/* 80x25 16 color text mode */
	int86( 0x10, &inregs, &outregs );
}

/** Find offest of pixel x, y by use the following formula
*   ( High_byte * y ) + ( x / 8 )  where High_byte = 640 / 8 = 80 */
unsigned int ega_offset( register unsigned int x, register unsigned int y ) {
	return ( ( 80 * y ) + ( x / 8 ) );
}
