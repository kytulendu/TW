#include "..\common\cwtype.h"
#include "..\common\grphc.h"
#include "..\common\ccommon.h"

#include "tutil1.h"

int thaistrlen( char *thaist ) {
	register int count = 0;

	while ( *thaist ) {
		if ( whatlevel( *thaist ) == MIDDLE ) {
			count++;
		}
		thaist++;
	}
	return( count );
}
