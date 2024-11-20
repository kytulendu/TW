/*
* ============================================================================
* FONTMSG.C
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\cwgrphc.h"
#include "..\common\cscrn.h"
#include "..\common\dir.h"
#include "..\common\ekbd.h"
#include "..\common\getstr.h"
#include "..\common\tutil1.h"

#include "fed.h"
#include "key.h"

#include "fontmsg.h"

extern int center_x, center_y;

int existfile( char *pname );

int existfile( char *pname ) {
    int fd;
    if ( ( fd = open( pname, O_RDONLY ) ) == -1 ) {
        return 0;
    } else {
        close( fd );
    }
    return !0;
}

void put_box( int x1, int y1, int x2, int y2 ) {
    char *buff;
    x1 += align; x2 += align;
    if ( ( buff = ( char* ) malloc( imagesize( x1, y1, x2, y2 ) ) ) == NULL ) {
        settext( );
        puts( "Error: Not enough memory." );
        exit( EXIT_FAILURE );
    }
    getimage( x1, y1, x2, y2, buff );
    putimage( x1, y1, buff, XOR_PUT );
    free( buff );
    x1 -= align; x2 -= align;
    _rectangle( x1, y1, x2, y2 );
    _rectangle( x1 + 2, y1 + 2, x2 - 2, y2 - 2 );
}

int fontnamebox( char *pname, int creat ) {
    int ret;
    savepic( );
    put_box( 9 * 8 - 4, 5 * 20, 20 * 8 + 22 * 8 + 4, 6 * 20 + 7 );
    dispstrhgc( "ãÊèª×èÍá¿éÁ --> ", 9, 5, REVERSEATTR );
    getname( pname, 21, 5, 20, REVERSEATTR );
    if ( !creat ) {
        if ( !existfile( pname ) ) {
            if ( pname[0] == '\0' ) {
                strcpy( pname, "*.*" );
            }
            ret = ( selectfile( pname ) == NO ) ? ESC : RET;
        } else {
            ret = RET;
        }
    }
    retpic( );
    return ret;
}

void error_message( char *prompt ) {
    savepic( );

    put_box( center_x - 16 * thaistrlen( prompt ) / 2 - 5, 8 * 20 - 20,
        center_x + 16 * thaistrlen( prompt ) / 2 + 3, 8 * 20 + 7 );
    dispstrhgc( prompt, 40 - thaistrlen( prompt ) + herc_align, 7, ENLARGEATTR | REVERSEATTR );
    bioskey( 0 );
    retpic( );
}

int _waitkbd( int x, int y );

int _waitkbd( int x, int y ) {
    register unsigned int i;
    while ( !keypressed( ) ) {
        for ( i = 0; !keypressed( ) && i < 6000; i++ );
        setcurpos( x, y, 0 );
    }
    return getch( );
}

int prompter( char *ans, int x, int y, char attr );

int prompter( char *ans, int x, int y, char attr ) {
    int k;
    dispstrhgc( ans, x, y, attr );
    while ( !strchr( "yYnN\r\x1b", ( k = _waitkbd( x, y ) ) ) );
    dispstrhgc( ans, x, y, attr );
    return toupper( k );
}

int immediatebox( int x, int y, char *str, char *ans ) {
    static char buff[100];
    int ret;
    savepic( );
    strcpy( buff, str );
    strcat( buff, "    " );
    put_box( x * 8 - 4, y * 20,
        x * 8 + 8 * thaistrlen( buff ) + 4, y * 20 + 27 );
    dispstrhgc( buff, x, y, REVERSEATTR );
    ret = ( prompter( ans, x + thaistrlen( buff ) - 2, y, REVERSEATTR ) );
    retpic( );
    if ( ret == '\r' ) {
        ret = toupper( *ans );
    }
    switch ( ret ) {
    case 'Y':
        return 1;
    case 'N':
        return 0;
    case  27:
        return -1;
    }
}
