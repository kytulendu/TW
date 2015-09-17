/*
* ============================================================================
* EGA/VGA/MCGA graphics module for CW 1.20.
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

#include <stdlib.h>
#include <string.h>
#include <dos.h>

#include "cwgrphc.h"
#include "grdetect.h"

/** Find offset of pixel x, y by use the following formula
*   ( High_byte * y ) + ( x / 8 )  where High_byte = 640 / 8 = 80 */
int ega_offset( register int x, register int y ) {
	return ( ( 80 * y ) + ( x / 8 ) );
}
/*
void ega_prchar( unsigned char p_char, int p_attr, int p_x, int p_y ) {

}

void ega_prblank( int p_x, int p_y ) {

}

void ega_setcurpos( int p_x, int p_y, int p_thaimode ) {

}
*/
void ega_putpixel( int p_x, int p_y ) {
	unsigned char far *vram = ( unsigned char far * ) 0xa0000000UL;

	/* calculate which bit to modify */
	unsigned char bit = ( unsigned char ) ( 0x80 >> ( p_x & 7 ) );

	/* set the value on VRAM */
	vram[ega_offset( p_x, p_y )] |= bit;
}

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

void ega_savepic( void ) {
	unsigned char far *vram = ( unsigned char far * ) 0xa0000000UL;

	memcpy( screen_buffptr, vram, 38400U );	/* 38400 = (640*480)/8 */
}

void ega_retpic( void ) {
	unsigned char far *vram = ( unsigned char far * ) 0xa0000000UL;

	memcpy( vram, screen_buffptr, 38400U );	/* 38400 = (640*480)/8 */
}

void ega_clsall( void ) {
	unsigned char far *vram = ( unsigned char far * ) 0xa0000000UL;

	memset( vram, 0, 38400U );	/* 38400 = (640*480)/8 */
}
/*
void ega_clsgraph( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd ) {

}

void ega_clrline( int p_x1, int p_y1, int p_x2 ) {

}

void ega_prakeaw( void ) {

}

void ega_getwind( int p_x1, int p_x2, int p_linecount, int p_bytecount, unsigned char *p_buffer ) {

}

void ega_putwind( int p_x1, int p_x2, int p_linecount, int p_bytecount, unsigned char *p_buffer ) {

}
*/
