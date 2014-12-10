/*
* ============================================================================
* EGA/VGA graphics module for CW 1.20
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
void esetgraph( void ) {
	union REGS inregs, outregs;

	if ( scrmode == VGA ) {
		inregs.x.ax = 0x11;			/* 640 x 480 graphic on vga display */
	} else if ( scrmode == EGA64 || scrmode == EGA ) {
		inregs.x.ax = 0x10;			/* 640 x 350 graphic on ega display */
	} else {
		inregs.x.ax = 0x0F;			/* 640 x 350 mono-graphic on mono display */
	}

	int86( 0x10, &inregs, &outregs );

	outportb( 0x03C4, 0x02 );
	if ( scrmode != EGAMONO ) {
		outportb( 0x03C5, 0x0F );
	} else {
		outportb( 0x03C5, 0x03 );	/* use 2 plain only on mode 0F */
	}
}

/** Set EGA/VGA/MCGA Graphic Card to text mode by call
*   BIOS routine INT 10h */
void esettext( void ) {
	union REGS inregs, outregs;

	inregs.x.ax = 3;					/* 16 color text mode */
	int86( 0x10, &inregs, &outregs );	/* text mode */
}

/** Find offest of pixel x, y we use the following formula
*   ( High_byte * y ) + ( x / 8 )  where High_byte = 640 / 8 = 80 */
unsigned eoffset( register unsigned int x, register unsigned int y ) {
	return ( ( 80 * y ) + ( x / 8 ) );
}
