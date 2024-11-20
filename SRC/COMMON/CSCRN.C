/*
* ============================================================================
* Common screen utility
*
* Suttipong Kanakakorn
* Sun  08-06-1989  09:35:17
* ============================================================================
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#include "cwtype.h"
#include "cwgrphc.h"
#include "ekbd.h"
#include "sound.h"
#include "common.h"

#include "cscrn.h"

void _line( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd/*, int p_color*/ ) {
    /** Draw line using Bresenham's line algorithm.
     *  author Zingl Alois
     *  code from http://members.chello.at/~easyfilter/bresenham.html */
    int dx = abs( p_xEnd - p_xStart ), sx = p_xStart < p_xEnd ? 1 : -1;
    int dy = -abs( p_yEnd - p_yStart ), sy = p_yStart < p_yEnd ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    for ( ;; ) {
        _putpixel( p_xStart, p_yStart/*, p_color*/ );
        if ( p_xStart == p_xEnd && p_yStart == p_yEnd ) {
            break;
        }

        e2 = 2 * err;
        if ( e2 >= dy ) { /* e_xy + e_x > 0 */
            err += dy; p_xStart += sx;
        }

        if ( e2 <= dx ) { /* e_xy + e_y < 0 */
            err += dx; p_yStart += sy;
        }
    }
}

void _rectangle( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd/*, p_color*/ ) {
    _line( p_xStart, p_yStart, p_xEnd, p_yStart/*, p_color*/ );
    _line( p_xStart, p_yStart, p_xStart, p_yEnd/*, p_color*/ );
    _line( p_xStart, p_yEnd, p_xEnd, p_yEnd/*, p_color*/ );
    _line( p_xEnd, p_yStart, p_xEnd, p_yEnd/*, p_color*/ );
}

void dispstrhgc( unsigned char *p_string, int p_xPos, int p_yPos, font_attr p_attr ) {
    while ( ( *p_string != '\0' ) && ( p_xPos < 90 ) ) {
        if ( *p_string < 32 ) {
            togglefont( &p_attr, *p_string );
        } else {
            if ( whatlevel( *p_string ) == MIDDLE ) {
                prchar( *p_string, p_attr, p_xPos, p_yPos );
                if ( ( p_attr & ENLARGEATTR ) == ENLARGEATTR ) {
                    p_xPos++;
                }
                p_xPos++;
            } else {
                if ( ( p_attr & ENLARGEATTR ) == ENLARGEATTR ) {
                    if ( p_xPos >= 2 ) {
                        prchar( *p_string, p_attr, p_xPos - 2, p_yPos );
                    }
                } else {
                    if ( p_xPos >= 1 ) {
                        prchar( *p_string, p_attr, p_xPos - 1, p_yPos );
                    }
                }
            }
        }
        p_string++;
    }
}

void dispprintf( int p_xPos, int p_yPos, font_attr p_attr, char *p_format, ... ) {
    va_list argptr;
    unsigned char tstring[240];

    va_start( argptr, p_format );
    vsprintf( tstring, p_format, argptr );
    va_end( argptr );
    dispstrhgc( tstring, p_xPos, p_yPos, p_attr );
}

void dispblank( int p_xPos, int p_yPos, size_t p_count, font_attr p_attr ) {
    p_count++;
    while ( p_count-- ) {
        prchar( ' ', p_attr, p_xPos++, p_yPos );
    }
}

void togglefont( font_attr *p_curfont, font_code p_code ) {
    if ( p_code == ONELINECODE ) {
        *p_curfont = *p_curfont ^ ONELINEATTR;
    }
    if ( p_code == SUPERCODE ) {
        *p_curfont = *p_curfont ^ SUPERATTR;
    }
    if ( p_code == SUBCODE ) {
        *p_curfont = *p_curfont ^ SUBATTR;
    }
    if ( p_code == ITALICCODE ) {
        *p_curfont = *p_curfont ^ ITALICATTR;
    }
    if ( p_code == BOLDCODE ) {
        *p_curfont = *p_curfont ^ BOLDATTR;
    }
    if ( p_code == TWOLINECODE ) {
        *p_curfont = *p_curfont ^ TWOLINEATTR;
    }
    if ( p_code == ENLARGECODE ) {
        *p_curfont = *p_curfont ^ ENLARGEATTR;
    }
}

void framebox( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd, int p_attr ) {
    register int i;
    register int j;

    i = p_xStart;
    prchar( ' ', p_attr, i++, p_yStart );
    prchar( '˜', p_attr, i, p_yStart );
    for ( i++, j = p_xEnd - 1; i < j; i++ ) {
        prchar( '•', p_attr, i, p_yStart );
    }
    prchar( '™', p_attr, i++, p_yStart );
    prchar( ' ', p_attr, i, p_yStart );

    for ( j = p_yStart + 1; j < p_yEnd; j++ ) {
        for ( i = p_xStart; i <= p_xEnd; i++ ) {
            prchar( ' ', p_attr, i, j );
        }
        prchar( '–', p_attr, p_xEnd - 1, j );
        prchar( '–', p_attr, p_xStart + 1, j );
    }
    i = p_xStart;
    prchar( ' ', p_attr, i++, p_yEnd );
    prchar( 'š', p_attr, i, p_yEnd );
    for ( i++, j = p_xEnd - 1; i < j; i++ ) {
        prchar( '•', p_attr, i, p_yEnd );
    }
    prchar( '›', p_attr, i++, p_yEnd );
    prchar( ' ', p_attr, i, p_yEnd );
}

void blockmsg( int p_linePos ) {
    framebox( 5, p_linePos - 1, ( 5 + 69 ) + shrink_factor, p_linePos + 1, REVERSEATTR );
}

void showerrno( void ) {
    errorsound( );
    blockmsg( 5 );
    switch ( errno ) {
    case ENOENT:
        dispstrhgc( "ËÒá¿éÁ¢éÍÁÙÅäÁè¾º ! ¡´»ØèÁã´æà¾×èÍ·Ó§Ò¹µèÍ...", ( 7 + center_factor ) + 15, 5, REVERSEATTR );
        break;
    case ENOMEM:
        dispstrhgc( "Ë¹èÇÂ¤ÇÒÁ¨ÓäÁè¾Í ! ¡´»ØèÁã´æà¾×èÍ·Ó§Ò¹µèÍ...", ( 14 + center_factor ) + 8, 6, REVERSEATTR );
        break;
    default:
        framebox( 13 + center_factor, 4, ( 13 + center_factor ) + 54, 7, REVERSEATTR );
        dispstrhgc( "à¡Ô´¤ÇÒÁ¼Ô´¾ÅÒ´ÀÒÂã¹ÃÐºº !", ( 14 + center_factor ) + 15, 5, REVERSEATTR );
        dispstrhgc( sys_errlist[errno], ( 14 + center_factor ) + 15, 6, REVERSEATTR );
    }
    ebioskey( 0 );
}

unsigned char *savescrn( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd ) {
    unsigned char *scrnindex;
    scrnindex = ( unsigned char * ) malloc( ( p_xEnd - p_xStart + 1 ) * ( p_yEnd - p_yStart + 1 ) * 20 );
    if ( scrnindex == NULL ) {
        savepic( );
        errorsound( );
        blockmsg( 5 );
        dispstrhgc( "Ë¹èÇÂ¤ÇÒÁ¨ÓäÁè¾Í ! ¡´»ØèÁã´æà¾×èÍ·Ó§Ò¹µèÍ...", ( 14 + center_factor ) + 8, 6, REVERSEATTR );
        ebioskey( 0 );
        return( NULL );
    }

    ( *getwind_ptr )( p_xStart, p_yStart, ( p_yEnd - p_yStart + 1 ) * 20, ( p_xEnd - p_xStart + 1 ), scrnindex );
    return( scrnindex );
}

void resscrn( unsigned char *p_scrnindex, int p_xStart, int p_yStart, int p_xEnd, int p_yEnd ) {
    if ( p_scrnindex == NULL ) {
        retpic( );
        return;
    }
    ( *putwind_ptr )( p_xStart, p_yStart, ( p_yEnd - p_yStart + 1 ) * 20, ( p_xEnd - p_xStart + 1 ), p_scrnindex );
    free( p_scrnindex );
}
