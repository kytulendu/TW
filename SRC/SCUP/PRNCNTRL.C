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

void putp( unsigned int p_character ) {
    /*
    union REGS regs;
    regs.h.ah = 0;
    regs.h.al = p_character;
    regs.h.dh = 0;
    regs.h.dl = 0;
    intr( 0x17, &regs, &regs );
    */
    biosprint( 0, p_character, 0 );
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

void PrinterSetFormLenghtInch( register unsigned int p_lenght ) {
    putp( ESC );
    putp( 'C' );
    putp( 0 );
    putp( p_lenght );
}

void PrinterSkipLine( register int p_lines ) {
    for ( ; p_lines > 0; p_lines-- ) {
        putp( CR );
        putp( LF );
    }
}

void PrinterFormFeed( void ) {
    putp( FF );
}

void PrinterLineFeed( register unsigned int p_lines ) {
    putp( CR );
    if ( p_lines == 0 ) {
        return;
    }
    putp( ESC );
    putp( 'J' );
    putp( p_lines );
}

void PrinterMasterSelectMode( register unsigned int p_mode ) {
    putp( ESC );
    putp( '!' );
    putp( p_mode );
}

void PrinterSetGraphicMode9pinQuadrupleDensity( register unsigned int p_density ) {
    putp( ESC );
    putp( 'Z' );
    putp( p_density % 256 );
    putp( p_density / 256 );
}

void PrinterSetGraphicMode24pinTripleDensity( register unsigned int p_density ) {
    putp( ESC );
    putp( '*' );
    putp( 39 );
    putp( p_density % 256 );
    putp( p_density / 256 );
}

void PrinterSet10cpi( void ) {
    putp( ESC );
    putp( 'P' );
}
