/**
*   keyboard function that different between cuprint.exe and cw.exe
*   Suttipong Kanakakorn Mon  08-07-1989  00:18:41
*/

#include <stdio.h>

#include "..\common\cwtype.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\grphc.h"

#include "global.h"

#include "kbd.h"

void waitkbd( unsigned int x, unsigned int y ) {
	register unsigned int i;

	setcurpos( x, y, thaimode );
	while ( !keypressed( ) ) {
		for ( i = 0; !keypressed( ) && i < 1200; i++ );
		setcurpos( x, y, thaimode );
		for ( i = 0; !keypressed( ) && i < 1200; i++ );
		setcurpos( x, y, thaimode );
	}
	setcurpos( x, y, thaimode );
}

int readkbd( void ) {
	register unsigned int c;

	c = ebioskey( 0 );
	if ( thaimode ) {
		return( thaikey( c ) );
	} else {
		return( c );
	}
}
