#include <ctype.h>

#include "..\tctype.h"
#include "..\thai.h"

#include "global.h"
#include "routine.h"

/** Thai English Cut Routine
*
*   Programmer  :   Subun Yenjaichon
*   Date Written :  Saturday, 7 May, 1988 9:53:12 AM
*   Last Updated :  Saturday, 7 May, 1988 9:53:28 AM
*/

unsigned char *ThaiEngCutRtn( unsigned char *TempIndx ) {
	unsigned char *TempIndxm1 = TempIndx - 1;

	if ( ( isthai( *TempIndx ) && isalpha( *TempIndxm1 ) ) || ( isthai( *TempIndxm1 ) && isalpha( *TempIndx ) ) ) {
		return( TempIndxm1 ); /* cut before thai and after English */
	}
	return ( FAIL );
}
