/*
* ============================================================================
* Extended keyboard routine
*
* Written: Suttipong Kanakakorn
*          Thu  08-03-1989  16:59:05
* ============================================================================
*/

#include <bios.h>

#include "cwtype.h"
#include "common.h"
#include "var.h"

#include "ekbd.h"

#define KBUFSIZE 128

static int ebioskey_buf[KBUFSIZE];
static int keyb_head = 0;
static int keyb_tail = 0;

int ebioskey( register int p_cmd ) {
    register int keycode;
    if ( p_cmd == 0 ) {
        if ( keyb_head == keyb_tail ) {
            return ( bioskey( 0 ) );
        }

        keycode = ebioskey_buf[keyb_head++];
        if ( keyb_head == KBUFSIZE ) {
            keyb_head = 0;
        }
        return( keycode );
    }
    return ( bioskey( p_cmd ) );
}

void placekey( register int p_key ) {
    ebioskey_buf[keyb_tail++] = p_key;
    if ( keyb_tail == KBUFSIZE ) {
        keyb_tail = 0;
    }

}

int keypressed( void ) {
    if ( keyb_head == keyb_tail ) {
        return( asm_keypressed( ) );
    }
    return( YES );
}
