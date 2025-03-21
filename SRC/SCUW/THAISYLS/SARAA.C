#include "thai.h"

#include "global.h"
#include "routine.h"

/** Programmer   : Subun Yenjaichon
*   Date Written : Monday, 16 May, 1988 9:40:59 AM
*   Last Updated : Monday, 16 May, 1988 9:41:26 AM
*/

unsigned char *SaraARtn( unsigned char *TempIndx ) {
    register short i;
    unsigned char *TempIndxm1 = TempIndx - 1;
    unsigned char *TempIndxm2 = TempIndx - 2;
    short SoreSeoAlen = 17;                                 /* 18 - 1 */
    short OrAngAlen = 7;                                    /* 8 - 1 */
    short MoreMarAlen = 2;                                  /* 3 - 1 */

    static unsigned char *SoreSeoTableA[] = {
        "������", "������", "������", "������", "���", "���", "�൪��", "���", "����",
        "���", "����", "���", "�໡", "�໹", "�൵", "�൷", "�൹", "��Ź"
    };

    static unsigned char *OrAngTableA[] = {
        "�๨", "�๡ѵ�", "����ԡѹ", "����ԡ�",
        "�������", "��Ǩ�", "����", "�๶"
    };

    static unsigned char *MoreMarTableA[] = {
        "����ѡ���", "����ѡ��", "�����"
    };

    static unsigned char ToreTongAEx[] = "���";
    static unsigned char JoreJarnAEx[] = "���";
    static unsigned char PoreParnAEx[] = "�๨�";

    switch ( *TempIndxm1 ) {
    case SoreSeo:
        for ( i = 0; i <= SoreSeoAlen; ++i ) {
            if ( !( nstrcmp( SoreSeoTableA[i], TempIndxm1 ) ) ) {
                return( TempIndxm2 ); /* found cut before leading-consonant */
            }
        }
        break;

    case OrAng:
        for ( i = 0; i <= OrAngAlen; ++i ) {
            if ( !( nstrcmp( OrAngTableA[i], TempIndxm1 ) ) ) {
                return( TempIndxm2 ); /*found cut before leading-consonant */
            }
        }
        break;

    case MoreMar:
        for ( i = 0; i <= MoreMarAlen; ++i ) {
            if ( !( nstrcmp( MoreMarTableA[i], TempIndxm1 ) ) ) {
                return( TempIndxm2 );                       /*found cut before leading-consonant */
            }
        }
        break;

    case PoreParn:
        if ( !( nstrcmp( PoreParnAEx, TempIndxm1 ) ) ) {
            return( TempIndxm2 );                           /* found cut before leading-consonant */
        }
        return( TempIndxm1 );                               /* cut before SaraA */

    case ToreTong:
        if ( !( nstrcmp( ToreTongAEx, TempIndxm1 ) ) ) {
            return( TempIndxm2 );                           /* found cut before leading-consonant */
        }
        break;

    case JoreJarn:
        if ( !( nstrcmp( JoreJarnAEx, TempIndxm1 ) ) ) {
            return( TempIndxm2 );                           /* found cut before leading-consonant */
        }
        break;

    default:
        return( TempIndxm1 );                               /* cut before SaraA */
    }
    return( TempIndxm1 );                                   /* cut before SaraA */
}
