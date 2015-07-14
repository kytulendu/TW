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

unsigned int linearcolumn( char *textstream, unsigned int thaicol, font_attr *font ) {
	register unsigned int logiccol = 0;	/* origin 0 */
	*font = 0;
	while ( ( thaicol > 0 ) && ( *textstream != '\0' ) ) {
		if ( whatlevel( *textstream ) == MIDDLE ) {
			if ( *textstream < 32 ) {
				togglefont( font, *textstream );
			} else {
				if ( ( *font & ENLARGEATTR ) == ENLARGEATTR ) {
					thaicol--; 
				}
				if ( thaicol > 0 ) {
					thaicol--; 
				}
			}
		}
		textstream++;
		logiccol++;
	}
	if ( *textstream != MIDDLE ) {
		while ( whatlevel( *( textstream++ ) ) != MIDDLE ) {
			logiccol++;
		}
	}
	return( logiccol );
}
