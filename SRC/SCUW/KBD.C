/*
* ============================================================================
* KBD.C
*
* Keyboard function that different from COMMON\KBD.C
* Update: Suttipong Kanakakorn
*         Thu  08-03-1989  16:54:04
*         Sun  08-06-1989  00:19:22
* ============================================================================
*/

#include <dir.h>

#include "..\common\cwgrphc.h"
#include "..\common\cwtype.h"
#include "..\common\var.h"
#include "..\common\kbdcode.h"
#include "..\common\ekbd.h"
#include "..\common\cscrn.h"
#include "..\common\common.h"

#include "const.h"
#include "var.h"

#include "kbd.h"

int last_menu_on = 0;

void waitkbd( unsigned int x, unsigned int y ) {
	register unsigned int i;

	setcurpos( x, y, thaimode );
	while ( !keypressed( ) ) {
		for ( i = 0; !keypressed( ) && i < 1200; i++ );
		setcurpos( x, y, thaimode );
		for ( i = 0; !keypressed( ) && i < 1200; i++ );
		setcurpos( x, y, thaimode );
		if ( !last_menu_on )
			dispstrhgc( ( ebioskey( 2 ) & 0x10 ) ? "สร้างตาราง" : "         ",
			70, 2, BOLDATTR );
	}
	setcurpos( x, y, thaimode );
}

int changekey( int key ) {
	if ( ( ebioskey( 2 ) & 0x10 ) != 0 ) {    /* table ? */
		switch ( key & 0xff00 ) {
		case SHIFT_7_NP & 0xff00:
			key = 0x98;
			break;
		case SHIFT_8_NP & 0xff00:
			key = 0x91;
			break;
		case SHIFT_9_NP & 0xff00:
			key = 0x99;
			break;
		case GRAY_MINUS & 0xff00:
			key = 0x95;
			break;
		case SHIFT_4_NP & 0xff00:
			key = 0x93;
			break;
		case SHIFT_5_NP & 0xff00:
			key = 0x96;
			break;
		case SHIFT_6_NP & 0xff00:
			key = 0x92;
			break;
		case GRAY_PLUS & 0xff00:
			key = 0x8f;
			break;
		case SHIFT_1_NP & 0xff00:
			key = 0x9a;
			break;
		case SHIFT_2_NP & 0xff00:
			key = 0x90;
			break;
		case SHIFT_3_NP & 0xff00:
			key = 0x9b;
			break;
		}
	}
	return( key & 0xff );
}

int readkbd( void ) {
	unsigned int c;
	c = ebioskey( 0 );
	if ( thaimode && ( ( c & 0xff00 ) < 0x4700 ) ) {       /* Ignore Keypad */
		c = thaikey( c );
	}
	return( c );
}

int alt_char_map( int c ) {
	int k;
	switch ( c ) {
	case ALTA: k = 0x80;
		break;
	case ALTB: k = 0x81;
		break;
	case ALTC: k = 0x88;
		break;
	case ALTD: k = 0x87;
		break;
	case ALTE: k = 0x85;
		break;
	case ALTF: k = 0x9e;
		break;
	case ALTH: k = 0x9f;
		break;
	case ALTI: k = 0x84;
		break;
	case ALTJ: k = 0xdf;
		break;
	case ALTN: k = 0xfa;
		break;
	case ALTO: k = 0x83;
		break;
	case ALTQ: k = 0x8c;
		break;
	case ALTR: k = 0x86;
		break;
	case ALTS: k = 0x8b;
		break;
	case ALTT: k = 0x89;
		break;
	case ALTU: k = 0x8e;
		break;
	case ALTV: k = 0xfb;
		break;
	case ALTY: k = 0x82;
		break;
	default: k = -1;
		break;
	}
	return ( k );
}

void dispkey( register unsigned int p_key ) {
	dispstrhgc( "   ", wind.col, 2, NORMALATTR );
	if ( ( p_key & 0xff ) < 32 ) {
		prchar( '^', 0, wind.col, REVERSEATTR );
		prchar( ( p_key & 0xff ) + 0x40, 0, wind.col + 1, REVERSEATTR );
	}
}