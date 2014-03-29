#include <ctype.h>

#include "..\tctype.h"
#include "..\thai.h"

#include "global.h"

#include "mainsyls.h"

/** SYL_SEP (Syllable Separation)
*
*   Parameters   : lm   (Left Limit to search for cut point)
*                  eot  (End Of Text)
*                  rm   (Right Margin)
*   Function     : Find the location of the given text to be separated
*   Return       : Pointer to that location (Real Right Margin)
*
*   Author       : Tanat Chirakarn
*                  Subun Yenjaichon
*
*   Date Written : Friday, 6 May, 1988 8:38:18 AM
*   Last Update  : Thueday, 19 May, 1988 10:07:31 AM
*/

/** The Main Function Thai Syllable Separate that will return
*   the Real Right Margin
*/

/* Function name must be capital letter for asm call */

unsigned char *FINDCUT( unsigned char *lm, unsigned char *eot, unsigned char *rm ) {
	register unsigned char  *CutPt;

	LeftLimit = lm;
	EndOfText = eot;
	RightMargin = rm;

	/*  Back searching to find cut point until left limit */

	if ( isbpunc( *( RightMargin + 1 ) ) || istspmk( *( RightMargin + 1 ) ) ) {
		--RightMargin;
	}
	for ( Indx = RightMargin; Indx >= LeftLimit; --Indx ) {
		if ( ( CutPt = ThaiEngCutRtn( Indx ) ) != NULL ) {
			return( ( CutPt >= LeftLimit ) ? CutPt : NULL );
		} else if ( ( CutPt = ( *FuncPtr[*Indx] )( Indx ) ) != NULL ) {
			if ( CutPt >= LeftLimit && CutPt <= RightMargin
				&& !isfpunc( *CutPt ) && !isbpunc( *( CutPt + 1 ) )
				&& !istspmk( *( CutPt + 1 ) ) ) {
				return ( CutPt );
			}
		}
	}
	return( RightMargin );		/* Reach LeftLimit, return RightMargin */
}