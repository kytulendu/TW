#include "tctype.h"
#include "thai.h"

#include "global.h"
#include "routine.h"

/** Programmer   : Subun Yenjaichon
*   Date Written : Wednesday, 11 May, 1988 4:02:08 PM
*   Last Updated : Saturday, 14 May, 1988 9:39:42 AM
*/

unsigned char *SaraAirRtn( register unsigned char *TempIndx ) {
	register short i;
	unsigned char *TempIndxp1 = TempIndx + 1;
	unsigned char *TempIndxm1 = TempIndx - 1;
	unsigned char *TempIndxp2 = TempIndx + 2;
	unsigned char *TempIndxm2 = TempIndx - 2;

	short SoreSeoTableLen = 6;								/* 7 - 1 */
	static char ToreTaharnWd[] = "��§";
	static char ShoreChangWd[] = "��ǧ";
	static char *SoreSeoTable[] = {
		"������", "�����", "�ᵹ�", "�᡹����", "�᡹��", "���", "��ŧ"
	};

	if ( TempIndxp1 <= RightMargin && findchar( *( TempIndxp2 ), "�������" ) ) {
		return( TempIndxp1 );								/* cut after following consonant */
	}

	if ( TempIndxp2 <= RightMargin && isttnl( *TempIndxp2 ) &&
		findchar( *( TempIndx + 3 ), "�������" ) ) {
		return( TempIndxp2 );								/* cut after tonal mark */
	}

	/* check exception words */
	switch ( *TempIndxm1 ) {
	case ShoreChang:
		if ( !( nstrcmp( ShoreChangWd, TempIndxm1 ) ) ) {
			return( TempIndxm2 );							/* cut before consonant */
		}
		return( TempIndxm1 );								/* cut before SaraAir */
	case ToreTaharn:
		if ( !( nstrcmp( ToreTaharnWd, TempIndxm1 ) ) ) {
			return( TempIndxm2 );							/* cut before consonant */
		}
		return( TempIndxm1 );
	case SoreSeo:
		for ( i = 0; i <= SoreSeoTableLen; ++i ) {
			if ( !( nstrcmp( SoreSeoTable[i], TempIndxm1 ) ) ) {
				return( TempIndxm2 );						/* cut before consonant */
			}
		}
		return( TempIndxm1 );								/* cut before SaraAir */
	}
	return( TempIndxm1 );									/* cut before Sara Air */
}
