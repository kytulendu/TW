/*
* ============================================================================
* PRNCNTRL.C
*
* control printer.
* 9 May 1989
* Programmer : Mr. Prasart Topitumatukhun
* Updated    : Suttipong Kanakakorn
*  - increse speed and add function prototype
* ============================================================================
*/

#include <dos.h>
#include <bios.h>

#include "const.h"
#include "cuptype.h"

#include "prncntrl.h"

void putp( unsigned c ) {
	/*
	union REGS regs;
	regs.h.ah = 0;
	regs.h.al = c;
	regs.h.dh = 0;
	regs.h.dl = 0;
	intr( 0x17, &regs, &regs );
	*/
	biosprint( 0, c, 0 );
}

int PrinterReadstatus( void ) {
	/*
	union REGS regs;
	regs.h.ah = 0x02;
	regs.h.al = 0;
	regs.h.dh = 0;
	regs.h.dl = 0;
	return( int86( 0x17, &regs, &regs ) );
	*/
	return( biosprint( 2, 0, 0 ) );
}

void PrinterInitialize( void ) {
	putp( ESC );
	putp( '@' );
}

void PrinterSetFormLenghtInch( register unsigned n ) {
	putp( ESC );
	putp( 'C' );
	putp( 0 );
	putp( n );
}

void PrinterSkipLine( register int n ) {
	for ( ; n > 0; n-- ) {
		putp( CR );
		putp( LF );
	}
}

void PrinterFormFeed( void ) {
	putp( FF );
}

void PrinterLineFeed( register unsigned n ) {
	putp( CR );
	if ( n == 0 ) {
		return;
	}
	putp( ESC );
	putp( 'J' );
	putp( n );
}

void PrinterMasterSelectMode( register unsigned n ) {
	putp( ESC );
	putp( '!' );
	putp( n );
}

void PrinterSetGraphicMode9pinQuadrupleDensity( register unsigned n ) {
	putp( ESC );
	putp( 'Z' );
	putp( n % 256 );
	putp( n / 256 );
}

void PrinterSetGraphicMode24pinTripleDensity( register unsigned n ) {
	putp( ESC );
	putp( '*' );
	putp( 39 );
	putp( n % 256 );
	putp( n / 256 );
}

void PrinterSet10cpi( void ) {
	putp( ESC );
	putp( 'P' );
}
