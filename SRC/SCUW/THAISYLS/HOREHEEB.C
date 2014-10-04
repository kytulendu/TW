#include "..\tctype.h"
#include "..\thai.h"

#include "global.h"
#include "routine.h"

/**
*   Module Name : HorHeebRtn
*   Programmer  : Subun yenjaichon
*   Date Written    : Friday, 20 May, 1988 2:04:06 PM
*   Last Updated    :
*   parameter   : TempIndx (pointer to unsigned char)
*   return value    : pointer that pointer to cut pointer.
*/

unsigned char *HorHeebRtn( unsigned char *TempIndx ) {
	unsigned char *TempIndxm1 = TempIndx - 1;
	unsigned char *TempIndxp1 = TempIndx + 1;

	if ( istcon( *TempIndxm1 ) ) {
		switch ( *TempIndxm1 ) {
		case KoreKwai:
		case MoreMar:
		case SoreSeo:
			return( FAIL );
		case ToreTaharn:
			if ( *TempIndxp1 != SaraR ) {
				return( TempIndxm1 ); /* cut before HorHeeb */
			}
			break;
		case RoreReo:
		case OrAng:
			if ( *TempIndxp1 != HunAkad ) {
				return( TempIndxm1 ); /* cut before HorHeeb */
			}
			break;
		case PoreParn:
			if ( *TempIndxp1 != SaraU && *TempIndxp1 != SaraUU ) {
				return( TempIndxm1 ); /* cut before HorHeeb */
			}
			break;
		default:
			return( TempIndxm1 );
		}
	}
	return( FAIL );
}
