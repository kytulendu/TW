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

void soundnoise( unsigned int p_freq, unsigned int p_duration ) { }
void errorsound( void ) { }

#else

/** Delay for duration given.
*  \param[in]  p_duration   time to delay in millisecond. */
void biosdelay( long p_duration );

void soundnoise( unsigned int p_freq, unsigned int p_duration ) {
    sound( p_freq );
    /* we can't use delay() because it call dos, so it is not reentrant */
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

void biosdelay( long p_duration ) {
    long i;

    i = biostime( 0, 0 );
    p_duration = i + 182L * p_duration / 10000L;
    if ( p_duration == i ) {
        p_duration++;
    }

    do {
        i = biostime( 0, 0 );
    } while ( i < p_duration );
}

#endif
