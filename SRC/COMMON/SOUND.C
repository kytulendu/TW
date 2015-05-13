/*
* ============================================================================
* SOUND.C 15 JAN 89
* Updated : Suttipong Kanakakorn
*           Sun  08-06-1989  18:30:55
*           Mon  10-23-1989  23:18:49
* ============================================================================
*/

#include <bios.h>
#include <dos.h>

#include "sound.h"

#ifdef NOSOUND

void soundnoise( int p_freq, int p_duration ) { }
void errorsound( void ) { }

#else

void biosdelay( long millisecs );

void soundnoise( int p_freq, int p_duration ) {
	sound( p_freq );
	biosdelay( ( long ) p_duration );
	nosound( );
}

void errorsound( void ) {
	/* soundnoise( C * 2, 300 ); */
	soundnoise( C, 40 );
	soundnoise( D, 40 );
	soundnoise( E, 40 );
	soundnoise( F, 40 );
	soundnoise( G, 40 );
	soundnoise( A, 40 );
	soundnoise( B, 40 );
	soundnoise( C * 2, 40 );
}

/* we can not use delay() because it call dos, so it is not reentrant */
void biosdelay( long millisecs ) {
	long i;

	i = biostime( 0, 0 );
	millisecs = i + 182L * millisecs / 10000L;
	if ( millisecs == i ) {
		millisecs++;
	}

	do {
		i = biostime( 0, 0 );
	} while ( i < millisecs );
}

#endif
