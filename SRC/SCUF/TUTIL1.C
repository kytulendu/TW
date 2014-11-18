/*
* ============================================================================
* TUTIL1.C 15 Fri  08-25-1989  21:41:55
* ============================================================================
*/

#include "..\common\cwtype.h"
#include "..\common\grphc.h"
#include "..\common\ccommon.h"

unsigned int thaistrlen( char thaist[] ) {
	register unsigned int index = 0, count = 0;
	char curfont = 0;
	while ( thaist[index] != '\0' ) {
		if ( whatlevel( thaist[index] ) == MIDDLE ) {
			count++;
			if ( ( curfont & ENLARGEATTR ) == ENLARGEATTR ) {
				count++;
			}
		}
		index++;
	}
	return( count );
}
