/*
* ============================================================================
* TUTIL2.C
*
* Updated: Suttipong Kanakakorn
*          Wed  08-02-1989  09:52:44
*          Sun  08-06-1989  11:24:52
* ============================================================================
*/

#include <stdlib.h>

#include "..\common\cwtype.h"
#include "..\common\common.h"
#include "..\common\cscrn.h"

#include "tutil2.h"

unsigned int linearcolumn( unsigned char *p_textstream, unsigned int p_thaiCol, font_attr *p_attr ) {
	register unsigned int logiccol = 0;	/* logical column (physical), column is origin 0. */
	*p_attr = NORMALATTR;
	while ( ( p_thaiCol > 0 ) && ( *p_textstream != '\0' ) ) {
		if ( whatlevel( *p_textstream ) == MIDDLE ) {
			if ( *p_textstream < 32 ) {
				togglefont( p_attr, *p_textstream );
			} else {
				if ( ( *p_attr & ENLARGEATTR ) == ENLARGEATTR ) {
					p_thaiCol--;
				}
				if ( p_thaiCol > 0 ) {
					p_thaiCol--;
				}
			}
		}
		p_textstream++;
		logiccol++;
	}
	if ( *p_textstream != MIDDLE ) {
		while ( whatlevel( *( p_textstream++ ) ) != MIDDLE ) {
			logiccol++;
		}
	}
	return( logiccol );
}

void arabictothai( char *p_string ) {
	while ( *p_string != '\0' ) {
		if ( ( *p_string >= '0' ) && ( *p_string <= '9' ) ) {
			*p_string = *p_string | 0xf0;
		}
		p_string++;
	}
}
