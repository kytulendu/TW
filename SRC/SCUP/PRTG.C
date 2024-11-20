/*
* ============================================================================
* PRTG.C
*
* Updated: Suttipong Kanakakorn
* Tue  08-08-1989  23:50:08
*  - Group constants in a file, add function prototype
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#include "..\common\cwtype.h"

#include "cuptype.h"
#include "global.h"
#include "funcmac.h"

#include "cpi.h"
#include "prncntrl.h"
#include "prtutil.h"
#ifdef WANT_TO_USE_GRAPH
#include "pic.h"
#endif

#include "prtg.h"

/* function prototype */

void print_picture( char *p_buffer );

/** Print data in buffer.
*   include left-right trim functions to fasten
*   graphic print. In text mode the printer print
*   nothing when it reaches blank (' '). */
void PrintBuffer9pin( unsigned char *p_buffer );
int ltrim( unsigned char *p_line, int p_left, int p_right );
int rtrim( unsigned char *p_line, int p_left, int p_right );

#ifdef WANT_TO_USE_GRAPH
void print_picture( char *p_buffer ) {
    extern int grp_ready;
    extern char *print_buffer_pointer;
    grp_ready = NO;
    print_buffer_pointer = p_buffer;
    read_picture_file( );
}
#endif

void PrintBuffer9pin( unsigned char *p_buffer ) {
    extern int maxdot;
    register int i;
    int left, right, length;
    charwidth( p_buffer );              /* alternate character width in cpi.obj */
    left = ltrim( p_buffer, 0, maxdot );
    right = rtrim( p_buffer, 0, maxdot );
    for ( i = 0; i < left; i++ ) {
        putp( ' ' );                    /* text mode */
    }
    length = right - ( left * 24 );
    if ( length != 0 ) {
        PrinterSetGraphicMode9pinQuadrupleDensity( length );
        for ( i = 0; i < length; i++ ) {
            putp( p_buffer[( left * 24 ) + i] );    /* graphic (bit image) print */
        }
    }
}

/* modify by Suttipong Kanakakorn Tue  08-29-1989  13:08:36 */
void PrintThree9pin( void ) {
    extern int linespace;
    /* FX    : 24 */
    /* LX,LQ : 20 */
    extern int nlqmode;
    extern int maxdot;
    extern char *bupper1;
    extern char *bupper2;
    extern char *bmiddle1;
    extern char *bmiddle2;
    extern char *bbelow1;
    extern char *bbelow2;
    char *print_pointer[6];
#ifdef WANT_TO_USE_GRAPH
    extern int pic_print;
    extern int grp_ready;
    extern int dot_per_line;
    char *temp_buffer;
#endif
    int i, j, spleft;
    print_pointer[0] = bupper1;
    print_pointer[1] = bupper2;
    print_pointer[2] = bmiddle1;
    print_pointer[3] = bmiddle2;
    print_pointer[4] = bbelow1;
    print_pointer[5] = bbelow2;
    if ( nlqmode == 1 ) {
        for ( i = 0; i < 6; i++ ) {
#ifdef WANT_TO_USE_GRAPH
            if ( pic_print == NO ) {
#endif
                PrintBuffer9pin( print_pointer[i] );
                if ( ( i % 2 ) == 0 ) {
                    PrinterLineFeed216inch( 1 );
                } else {
                    if ( i == 5 ) {                         /* After finish line */
                        if ( extbarprinting ) {
                            spleft = linespace;
                            while ( spleft > 24 ) {
                                PrinterLineFeed216inch( 23 );
                                PrintBuffer9pin( extbar1 ); /* More table line */
                                PrinterLineFeed216inch( 1 );
                                PrintBuffer9pin( extbar2 );
                                spleft -= 24;
                            }
                            PrinterLineFeed216inch( spleft );
                        } else {
                            PrinterLineFeed216inch( linespace );
                        }
                    } else {
                        PrinterLineFeed216inch( 23 );
                    }
                }
#ifdef WANT_TO_USE_GRAPH
            } else { /* picprint == yes */
                switch ( dot_per_line ) {
                case 1:
                    if ( i % 2 == 0 ) {
                        PrintBuffer9pin( print_pointer[i] );
                        PrinterLineFeed216inch( 1 );
                    } else {
                        /* print_picture( print_pointer[i] ); */
                        PrintBuffer9pin( print_pointer[i] );
                        PrinterLineFeed216inch( 23 );
                    }
                    break;
                case 2:
                    print_picture( print_pointer[i] );
                    PrintBuffer9pin( print_pointer[i] );
                    if ( ( i % 2 ) == 0 ) {
                        PrinterLineFeed216inch( 1 );
                    } else {
                        PrinterLineFeed216inch( 23 );
                    }
                    break;
                case 3:
                    print_picture( print_pointer[i] );
                    PrintBuffer9pin( print_pointer[i] );
                    switch ( i % 2 ) {
                    case 0:
                        PrinterLineFeed216inch( 1 );
                        break;
                    case 1:
                        PrinterLineFeed216inch( 1 );
                        temp_buffer = ( char * ) calloc( 6600, sizeof( char ) );
                        print_picture( temp_buffer );
                        PrintBuffer9pin( temp_buffer );
                        PrinterLineFeed216inch( 22 );
                        free( temp_buffer );
                        break;
                    }
                    break;
                }
            }
#endif
        }
    } else {
        for ( i = 1; i < 6; i += 2 ) {
            for ( j = 0; j < maxdot; j++ ) {
                *( print_pointer[i] + j ) |= *( print_pointer[i - 1] + j );
            }
#ifdef WANT_TO_USE_GRAPH
            if ( ( pic_print == YES ) && ( dot_per_line == 1 ) ) {
                print_picture( print_pointer[i] );
            }
#endif
            PrintBuffer9pin( print_pointer[i] );
            if ( i == 5 ) {
                PrinterLineFeed216inch( linespace );
            } else {
                PrinterLineFeed216inch( 24 );
            }
        }
    }
}

int ltrim( unsigned char *p_line, int p_left, int p_right ) {
    register int i;
    i = p_left;
    while ( p_line[i] == 0 ) {
        i++;
        if ( i >= p_right - 1 ) {
            return( p_left );
        }
    }
    return( ( int ) ( i / 24 ) );
}

int rtrim( unsigned char *p_line, int p_left, int p_right ) {
    register int i;
    i = p_right - 1;
    while ( p_line[i] == 0 ) {
        i--;
        if ( i <= p_left ) {
            return( p_left );
        }
    }
    return( i + 1 );
}
