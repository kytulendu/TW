#include "tctype.h"
#include "thai.h"

#include "global.h"
#include "routine.h"

/** Programmer   : Subun Yenjaichon
*   Date Written : Wednesday, 11 May, 1988 10:08:10 AM
*   Last Updated : Monday, 16 May, 1988 4:26:17 PM
*/

unsigned char *SaraORtn( register unsigned char *TempIndx ) {
    register short i;
    unsigned char *TempIndxm1 = TempIndx - 1;
    short SoreSeoTbLen = 6;                                 /* 7 - 1 */
    short OrAngTbLen = 8;                                   /* 9 - 1 */
    short MoreMarTbLen = 6;                                 /* 7 - 1 */
    short NoreNooTbLen = 1;                                 /* 2 - 1 */
    short ShoreChangTbLen = 3;                              /* 4 - 1 */
    static char *SoreSeoTable[] = { "�����", "����", "����", "�����", "�⵹", "�⤻", "���᡹" };
    static char *OrAngTable[] = { "�⳷��", "��ä��", "�����", "�⹪�", "����", "�����", "�����", "�����", "��ȡ" };
    static char *MoreMarTable[] = { "����з֡", "����ʾ", "������", "�����", "���ʶ", "���Ҿ", "�⹸���" };
    static char *NoreNooTable[] = { "��º��", "��ô�" };
    static char *ShoreChangTable[] = { "��ź�", "��Ÿ�", "����", "���" };
    static char ToreTaharnWord[] = "����";
    static char RoreReoWord[] = "��˰ҹ";
    static char YoreYakWord[] = "���";
    static char KorKaiWord[] = "����";

    switch ( *( TempIndxm1 ) ) {
    case SoreSeo:                                           /* ����� ���� ���� ����� �⵹ �⤻ ���᡹*/
        for ( i = 0; i <= SoreSeoTbLen; ++i ) {
            if ( !( nstrcmp( SoreSeoTable[i], TempIndxm1 ) ) ) {
                return( TempIndx - 2 );                     /* cut before consonant that before Sara O */
            }
        }
        return( TempIndxm1 );                               /* cut before sara O */

    case OrAng:                                             /* �⳷�� ��ä�� ����� �⹪� ���� ����� ����� ����� ��ȡ*/
        for ( i = 0; i <= OrAngTbLen; ++i ) {
            if ( !( nstrcmp( OrAngTable[i], TempIndxm1 ) ) ) {
                return( TempIndx - 2 );                     /* cut before consonant that before Sara O */
            }
        }
        return( TempIndxm1 );                               /* cut before sara O */

    case MoreMar:                                           /* ����з֡, ����ʾ,������,����,���ʶ */
        for ( i = 0; i <= MoreMarTbLen; ++i ) {
            if ( !( nstrcmp( MoreMarTable[i], TempIndxm1 ) ) ) {
                return( TempIndx - 2 );                     /* cut before consonant that before Sara O */
            }
        }
        return( TempIndxm1 );                               /* cut before sara O */

    case NoreNoo:                                           /* ��º�� ��ô� */
        if ( !( nstrcmp( "���", TempIndxm1 ) ) && !( istlvwl( *( TempIndx - 2 ) ) ) ) {
            if ( !( isttnl( *( TempIndx + 2 ) ) ) ) {
                return( TempIndx - 2 );                     /*cut before NoreNoo */
            }
        }
        for ( i = 0; i <= NoreNooTbLen; ++i ) {
            if ( !( nstrcmp( NoreNooTable[i], TempIndxm1 ) ) ) {
                return( TempIndx - 2 );                     /* cut before consonant that before Sara O */
            }
        }
        return( TempIndxm1 );                               /* cut before sara O */

    case ShoreChang:                                        /* ��ź� ��Ÿ� ���� ��� */
        for ( i = 0; i <= ShoreChangTbLen; ++i ) {
            if ( !( nstrcmp( ShoreChangTable[i], TempIndxm1 ) ) ) {
                return( TempIndx - 2 );                     /* cut before consonant that before Sara O */
            }
        }
        return( TempIndxm1 );                               /* cut before sara O */

    case ToreTaharn:                                        /* ���� */
        if ( nstrcmp( ToreTaharnWord, TempIndxm1 ) ) {
            return( TempIndxm1 );                           /* cut before sara O */
        } else {
            return( TempIndx - 2 );                         /* cut before consonant that before Sara O */
        }

    case RoreReo:                                           /* ��˰ҹ */
        if ( nstrcmp( RoreReoWord, TempIndxm1 ) ) {
            return( TempIndxm1 );                           /* cut before sara O */
        } else {
            return( TempIndx - 2 );                         /* cut before consonant that before Sara O */
        }

    case YoreYak:                                           /* ��� */
        if ( nstrcmp( YoreYakWord, TempIndxm1 ) ) {
            return( TempIndxm1 );                           /* cut before sara O */
        } else {
            return( TempIndx - 2 );                         /* cut before consonant that before Sara O */
        }

    case KorKai:                                            /* ���� */
        if ( nstrcmp( KorKaiWord, TempIndxm1 ) ) {
            return( TempIndxm1 );                           /* cut before sara O */
        } else {
            return( TempIndx - 2 );                         /* cut before consonant that before Sara O */
        }
/*
    default:
        return( TempIndx - 1 );
*/
    }
    return( TempIndx - 1 );
}
