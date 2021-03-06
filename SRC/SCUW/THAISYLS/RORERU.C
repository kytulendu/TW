#include "thai.h"

#include "global.h"
#include "routine.h"

/** Programmer   : Subun Yenjaichon
*   Date Written : Monday, 16 May, 1988 10:55:24 AM
*   Last Updated : Monday, 16 May, 1988 10:55:48 AM
*/

unsigned char *RoreRuRtn( unsigned char *TempIndx ) {
	unsigned char *TempIndxm1 = TempIndx - 1;
	short i;
	short RoreRuWdCnt = 7;									/* 8 - 1 */
	static unsigned char *RoreRuWd[] = {
		"ġ��", "Ĵ�", "Ĵ�", "Ī�", "Ĥ�Ƿ", "ķ��", "���", "ķ���", "ķ��"
	};

	if ( !( findchar( *TempIndxm1, "����������" ) ) ) {
		return( TempIndxm1 );								/* cut before RoreRu */
	} else {												/* possible leading consonants is found, do */
		if ( *TempIndxm1 == PoreParn && !( nstrcmp( "�ġ��", TempIndxm1 ) ) ) {
			return( TempIndx - 2 );							/* cut before �ġ�� */
		}
		for ( i = 0; i <= RoreRuWdCnt; ++i ) {
			if ( !( nstrcmp( RoreRuWd[i], TempIndx ) ) ) {
				return( TempIndxm1 );						/* if found, cut before RoreRu */
			}
		}
		return( TempIndx - 2 );								/* cut before possible leading consonants */
	}
}
