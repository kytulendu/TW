/*
* ============================================================================
* GETSTR.C 15 JAN 89
*
* Updated : Suttipong Kanakakorn
*           Wed  08-02-1989  09:52:44
* ============================================================================
*/

#include <string.h>
#include <dir.h>

#include "const.h"
#include "cwtype.h"
#include "cwgrphc.h"
#include "common.h"
#include "cscrn.h"
#include "kbd.h"
#include "ekbd.h"
#include "kbdcode.h"
#include "sound.h"
#include "tutil1.h"
#include "var.h"

#include "getstr.h"

int getstring( unsigned char *p_textstr, int p_x, int p_y, size_t p_maxlen, font_attr p_attr, strtype p_mode ) {
    int inkey;
    int key;
    size_t oldlen;
    size_t temp;
    unsigned char keepchar = '\0';

    oldlen = strlen( p_textstr );
    dispblank( p_x, p_y, p_maxlen, p_attr );
    dispstrhgc( p_textstr, p_x, p_y, p_attr );
    waitkbd( p_x + thaistrlen( p_textstr ), p_y );

    switch ( p_mode ) {
    case THAIENG:
        inkey = readkbd( );
        break;
    case NUMBER:
    case ONEORTWO:
    case ENGLISH:
        inkey = ebioskey( 0 );
        break;
    case ENGUPCASE:
        inkey = ebioskey( 0 );
        key = inkey & 0xff;
        if ( ( key >= 'a' ) && ( key <= 'z' ) ) {
            inkey = key - ( 'a' - 'A' );
        }
        break;
    }

    switch ( inkey ) {
    case CNTRL_H:
    case BSKEY:
    case CNTRL_S:
    case LEKEY:
    case CNTRL_M:
    case RETKEY:
        break;
    default:
        key = inkey & 0xff;
        if ( p_mode == NUMBER ) {
            if ( ( key < '0' ) || ( key > '9' ) ) {
                break; 
            }
        }
        if ( p_mode == ONEORTWO ) {
            if ( ( key != '1' ) && ( key != '2' ) ) {
                break; 
            }
        }
        if ( ( inkey & 0xff ) >= 32 ) {
            p_textstr[0] = '\0';
            dispblank( p_x, p_y, p_maxlen, p_attr );
        }
        break;
    }

    for ( ;; ) {
        switch ( inkey ) {
        case CNTRL_M:
        case RETKEY:
            return( YES );
        case CNTRL_U:
            return( NO );              /* Abort */
        case ESCKEY:
            return( ESCKEY );
        case UPKEY:
            return( UPKEY );
        case DNKEY:
            return( DNKEY );
        case CNTRL_H:
        case BSKEY:
        case LEKEY:
        case CNTRL_S:
            temp = strlen( p_textstr );
            if ( temp != 0 ) {
                if ( temp < oldlen ) {
                    p_textstr[temp] = keepchar;
                }
                keepchar = p_textstr[temp - 1];
                p_textstr[temp - 1] = '\0';
                dispblank( p_x, p_y, p_maxlen, p_attr );
                dispstrhgc( p_textstr, p_x, p_y, p_attr );
            }
            break;
        case RIKEY:
        case CNTRL_D:
            temp = strlen( p_textstr );
            if ( ( temp < oldlen ) && ( temp < p_maxlen ) ) {
                p_textstr[temp] = keepchar;
                keepchar = p_textstr[temp + 1];
                p_textstr[temp + 1] = '\0';
                dispblank( p_x, p_y, p_maxlen, p_attr );
                dispstrhgc( p_textstr, p_x, p_y, p_attr );
            }
            break;
        case CNTRL_Y:
            if ( strlen( p_textstr ) < oldlen ) {
                p_textstr[strlen( p_textstr )] = keepchar;
            }
            keepchar = p_textstr[0];
            p_textstr[0] = '\0';
            dispblank( p_x, p_y, p_maxlen, p_attr );
            break;
        case CNTRL_R:
            if ( strlen( p_textstr ) < oldlen ) {
                p_textstr[strlen( p_textstr )] = keepchar;
                dispblank( p_x, p_y, p_maxlen, p_attr );
                dispstrhgc( p_textstr, p_x, p_y, p_attr );
            }
            break;

        case F10KEY:
            thaimode = !thaimode;
            break;

        default:
            inkey = ( inkey & 0xff );
            if ( p_mode == NUMBER ) {
                if ( ( inkey < '0' ) || ( inkey > '9' ) ) {
                    break; 
                }
            }
            if ( p_mode == ONEORTWO ) {
                if ( ( inkey != '1' ) && ( inkey != '2' ) ) {
                    break; 
                }
            }
            if ( inkey >= 32 && strlen( p_textstr ) < p_maxlen ) {
                if ( whatlevel( inkey ) == MIDDLE ) {
                    p_textstr[strlen( p_textstr ) + 1] = '\0';
                    p_textstr[strlen( p_textstr )] = inkey;
                    oldlen = strlen( p_textstr );
                    dispblank( p_x, p_y, p_maxlen, p_attr );
                    dispstrhgc( p_textstr, p_x, p_y, p_attr );
                } else {
                    if ( ( strlen( p_textstr ) != 0 ) &&
                        ( whatlevel( inkey ) > whatlevel( p_textstr[strlen( p_textstr ) - 1] ) ) &&
                        ( inkey != HUNAKADMITO ) ) {
                        p_textstr[strlen( p_textstr ) + 1] = '\0';
                        p_textstr[strlen( p_textstr )] = inkey;
                        oldlen = strlen( p_textstr );
                        dispblank( p_x, p_y, p_maxlen, p_attr );
                        dispstrhgc( p_textstr, p_x, p_y, p_attr );
                    } else {
                        errorsound( );
                    }
                }
            }
            break;
        }

        waitkbd( p_x + thaistrlen( p_textstr ), p_y );

        switch ( p_mode ) {
        case THAIENG:
            inkey = readkbd( );
            break;
        case NUMBER:
        case ONEORTWO:
        case ENGLISH:
            inkey = ebioskey( 0 );
            break;
        case ENGUPCASE:
            inkey = ebioskey( 0 );
            key = inkey & 0xff;
            if ( ( key >= 'a' ) && ( key <= 'z' ) ) {
                inkey = key - ( 'a' - 'A' );
            }
            break;
        }
    }
}

int getname( char *p_textstr, int p_x, int p_y, size_t p_maxlen, font_attr p_attr ) {
    int i;
    char drv[MAXDRIVE + 1];
    char dir[MAXDIR + 1];
    char name[MAXFILE + 1];
    char ext[MAXEXT + 1];
    char textstr[80];

    do {
        i = getstring( p_textstr, p_x, p_y, p_maxlen, p_attr, ENGUPCASE );
    } while ( ( i != YES ) && ( i != ESCKEY ) && ( i != NO ) );

    if ( i == YES ) {
        fnsplit( p_textstr, drv, dir, name, ext );
        fnmerge( textstr, drv, dir, name, ext );
        if ( strcmp( p_textstr, textstr ) != 0 ) {
            errorsound( );
            blockmsg( 5 );
            dispstrhgc( "ชื่อแฟ้มข้อมูลผิดพลาด ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 13, 5, REVERSEATTR );
            while ( ebioskey( 0 ) != ESCKEY );
            return( ESCKEY );
        }
    }
    return( i );
}
