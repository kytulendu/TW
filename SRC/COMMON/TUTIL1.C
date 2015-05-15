#include "cwtype.h"
#include "common.h"
#include "cscrn.h"

#include "tutil1.h"

unsigned int thaistrlen( register unsigned char *p_thaistring ) {
	register int count = 0;
	font_attr curfont = 0;

	while ( *p_thaistring ) {
		if ( whatlevel( *p_thaistring ) == MIDDLE ) {
			if ( *p_thaistring < 32 ) {		/* if is control code */
				togglefont( &curfont, *p_thaistring );
			} else {
				count++;
				if ( ( curfont & ENLARGEATTR ) == ENLARGEATTR ) {
					count++;
				}
			}
		}
		p_thaistring++;
	}
	return( count );
}
