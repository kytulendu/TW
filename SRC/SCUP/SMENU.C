/*
* ============================================================================
* SMENU.C
*
* Select menu
* ============================================================================
*/

#include <stdio.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\kbdcode.h"
#include "..\common\tutil1.h"

#include "smenu.h"

int smenu( register int p_x, register int p_y, int p_number, char *p_message[], int *p_curmenu ) {
	int i;
	int c, length;
	char fmt[7];

	length = find_menu_len( p_number, p_message );
	sprintf( fmt, "%%-%ds", length );
	/*
	scrndx = savescrn( p_x - 1, p_y - 1, p_x + 1 + length, p_y + p_number + 1 );
	*/
	for ( i = 0; i < p_number; i++ ) {
		dispprintf( p_x, p_y + i, NORMALATTR, fmt, p_message[i] );
	}
	i = *p_curmenu - 1;
	dispprintf( p_x, p_y + i, REVERSEATTR, fmt, p_message[i] );
	_rectangle( p_x * 8 - 2, p_y * 20 + 2, ( p_x + length - 1 ) * 8 + 9, ( p_y + p_number ) * 20 + 5 );
	for ( ;; ) {
		c = ebioskey( 0 );
		switch ( c ) {
		case UPKEY:
			dispprintf( p_x, p_y + i, NORMALATTR, fmt, p_message[i] );
			i = ( i ) ? i - 1 : p_number - 1;
			dispprintf( p_x, p_y + i, REVERSEATTR, fmt, p_message[i] );
			break;
		case DNKEY:
			dispprintf( p_x, p_y + i, NORMALATTR, fmt, p_message[i] );
			i = ( i != p_number - 1 ) ? i + 1 : 0;
			dispprintf( p_x, p_y + i, REVERSEATTR, fmt, p_message[i] );
			break;
		case ESCKEY:
		case RETKEY:
			/*
			resscrn( scrndx, p_x - 1, p_y - 1, p_x + 1 + length, p_y + p_number + 1 );
			*/
			*p_curmenu = i + 1;
			return( c );
		}
	}
}

unsigned int find_menu_len( register int p_number, char *p_message[] ) {
	register unsigned int length;
	size_t i;
	char **m;

	length = thaistrlen( p_message[0] );
	for ( m = p_message + 1; m < p_message + p_number; m++ ) {
		if ( ( i = thaistrlen( *m ) ) > length ) {
			length = i;
		}
	}
	return length;
}
