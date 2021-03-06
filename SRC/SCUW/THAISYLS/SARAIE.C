#include "tctype.h"
#include "thai.h"

#include "global.h"
#include "routine.h"

/** Programmer   : Subun Yenjaichon
*   Date written : Tuesday, 17 May, 1988 2:53:20 PM
*   Last Updated : Monday, 23 May, 1988
*/

unsigned char *SaraIeRtn( unsigned char *TempIndx ) {
	short i;
	unsigned char *TempIndxm1 = TempIndx - 1;
	unsigned char *TempIndxm2 = TempIndx - 2;
	unsigned char *TempIndxm3 = TempIndx - 3;
	unsigned char *TempIndxm4 = TempIndx - 4;
	unsigned char *TempIndxp1 = TempIndx + 1;
	unsigned char *TempIndxp2 = TempIndx + 2;

	static unsigned char *DoreDekSaraIeEx[] = {
		"��ô�", "��ô�"
	};
	static unsigned char *ToreTaoSaraIeEx[] = {
		"�ѵ�", "�ѵ�", "�ѵ�", "�Ե�", "�ص�", "�ٵ�", "�ҵ�", "�ҵ�", "⪵�"
	};
	static unsigned char *JoreJarnSaraIeEx[] = {
		"�٨�", "�ب�"
	};

	/* start  check SaraA before */
	if ( *TempIndxm3 == SaraA )
		if ( isttnl( *TempIndxp1 ) && TempIndxp2 <= RightMargin ){
			return( TempIndxp2 );							/* cut after speller */
		} else {
			Indx = TempIndxm3;
			return( ( *FuncPtr[*Indx] )( Indx ) );			/* Jmp to SaraARtn */
		} else if ( *TempIndxm2 == SaraA ) {
			if ( isttnl( *TempIndxp1 ) ) {
				return( ( TempIndxp2 <= RightMargin ) ? TempIndxp2 : TempIndxm3 );
			}
			return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm3 );
		}

		/* begin SaraIeRtn with out SaraA before */
		if ( isttnl( *TempIndxp1 ) && TempIndxp2 <= RightMargin ) {
			return( TempIndxp2 );
		}

		if ( findchar( *TempIndxp1, "������������" ) ) {
			return( TempIndx );
		}

		switch ( *TempIndxp1 ) {
		case  KorKai:
			if ( *TempIndxm1 != LoreLing ) {
				return( TempIndx );
			}
			break;
		case KoreKwai:
			if ( !( findchar( *TempIndxm1, "������" ) ) ) {
				return( TempIndx );
			}
			break;
		case JoreJarn:
			if ( !( findchar( *TempIndxm1, "����" ) ) ) {
				return( TempIndx );
			}
			break;
		case SoreSoe:
			if ( *TempIndxm1 != MoreMar ) {
				return( TempIndx );
			}
			break;
		case YoreYing:
			if ( !( findchar( *TempIndxm1, "�����" ) ) ) {
				return( TempIndx );
			}
			break;
		case ThorSantan:
			if ( *TempIndxm1 != OrAng ) {
				return( TempIndx );
			}
			break;
		case NoreNane:
			if ( !( findchar( *TempIndxm1, "���" ) ) ) {
				return( TempIndx );
			}
			break;
		case ToreTaharn:
			if ( !( findchar( *TempIndxm1, "������" ) ) ) {
				return( TempIndx );
			}
			break;
		case ToreTong:
			if ( *TempIndxm1 != PoreParn ) {
				return( TempIndx );
			}
			break;
		case PoreParn:
			if ( !( findchar( *TempIndxm1, "����" ) ) ) {
				return( TempIndx );
			}
			break;
		case ForeFun:
			if ( !( findchar( *TempIndxm1, "��" ) ) ) {
				return( TempIndx );
			}
			break;
		case LoreLing:
			if ( !( findchar( *TempIndxm1, "��������" ) ) ) {
				return( TempIndx );
			}
			break;
		case SoreSala:
			if ( !( findchar( *TempIndxm1, "������" ) ) ) {
				return( TempIndx );
			}
		case SoreRusi:
			if ( !( findchar( *TempIndxm1, "������" ) ) ) {
				return( TempIndx );
			}
			break;
		case SoreSeo:
			if ( !( findchar( *TempIndxm1, "���������" ) ) ) {
				return( TempIndx );
			}
			break;
		}

		/* Front Cut */
		if ( findchar( *TempIndxm1, "�������������" ) || istlcon( *TempIndxm1 ) ) {
			return( TempIndxm2 );							/* cut before consonant */
		}
		switch ( *TempIndxm1 ) {
		case JoreJarn:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( JoreJarnSaraIeEx[i], TempIndxm3 ) ) ) {
					return( TempIndx );
				}
			}
			return( TempIndxm2 );							/* cut before JoreJarn */
		case DoreDek:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( DoreDekSaraIeEx[i], TempIndxm4 ) ) ) {
					return( TempIndx - 5 );
				}
			}
			if ( !( nstrcmp( "���ʴ", ( TempIndx - 5 ) ) ) ) {
				return( TempIndx - 6 );
			}
			return( TempIndxm2 );							/* cut before DoreDeck */
		case ToreTao:
			for ( i = 0; i <= 8; ++i ) {
				if ( !( nstrcmp( ToreTaoSaraIeEx[i], TempIndxm3 ) ) ) {
					return( TempIndx );
				}
			}
			if ( !( findchar( *TempIndxm2, "������" ) ) ) {
				return( TempIndxm2 );						/* cut before ToreTao */
			}
			break;
		case TorePootao:
			break;											/* can't cut before TorePootao */
		case NoreNoo:
			if ( !( findchar( *TempIndxm2, "��������" ) ) ) {
				return( TempIndxm2 );						/* cut before norenoo */
			}
			break;
		case RoreReo:
			if ( !( findchar( *TempIndxm2, "�������������" ) ) ) {
				return( TempIndxm2 );						/* cut before RoreReo */
			}
			break;
		case NgorNgoo:
			if ( *TempIndxm2 != HorHeeb ) {
				return( TempIndxm2 );						/* cut before NgorNgoo */
			} else {
				return( TempIndxm3 );						/* cut before HorHeeb */
			}
		case MoreMar:
			if ( !( nstrcmp( "����", TempIndxm3 ) ) ) {
				return( TempIndx );							/* cut after SaraIe */
			}
			if ( !( findchar( *TempIndxm2, "�����" ) ) ) {
				return( TempIndxm2 );						/* cut before MoreMar */
			}
			break;
		case YoreYak:
			if ( !( findchar( *TempIndxm2, "���" ) ) ) {
				return( TempIndxm2 );						/* cut before YoreYak */
			}
			break;
		case WoreWaan:
			if ( !( findchar( *TempIndxm2, "��������" ) ) ) {
				return( TempIndxm2 );						/* cut before WoreWaan */
			}
			break;
		case LoreLing:
			if ( !( findchar( *TempIndxm2, "������������" ) ) ) {
				return( TempIndxm2 );						/* cut before LoreLing */
			}
			break;
		case HorHeeb:
			if ( *TempIndxm2 != OrAng ) {
				return( TempIndxm2 );						/* cut before HorHeeb */
			}
			break;
		case ShoreChang:
			if ( *TempIndxm2 != WoreWaan && *TempIndxm2 != KoreKwai ) {
				return( TempIndxm2 );						/* cut before ShoreChang */
			}
			break;
		case ThorToong:
			if ( *TempIndxm2 != SoreSeo ) {
				return( TempIndxm2 );						/* cut before ThorToong */
			}
			break;
		case NoreNane:
			break;											/* uncut before norenane */
		case ToreTong:
			if ( !( nstrcmp( "�ط��", TempIndxm4 ) ) ) {
				return( TempIndx );							/* if found cut after saraIe */
			}
			if ( *TempIndxm2 != OrAng ) {
				return( TempIndxm2 );						/* cut before ToreTong */
			}
			break;											/* uncut before ToreTong */
		case PoreSumpao:
			if ( *TempIndxm2 != OrAng ) {
				return( TempIndxm2 );						/* cut before PoreSumpao */
			}
			break;
		case SoreSeo:
			if ( !( nstrcmp( "��ԡ�", TempIndxm2 ) ) ) {
				return( TempIndxm3 );						/* cut before KoreGai */
			} else {
				return( TempIndxm2 );						/* cut before SoreSeo */
			}
		case SoreSala:
			if ( *TempIndxm2 != SoreSala ) {
				return( TempIndxm2 );						/* cut before SoreSala */
			}
			break;
		case PoreParn:
			if ( *TempIndxm2 != BoreBaimai ) {
				return( TempIndxm2 );						/* cut before PoreParn */
			}
			break;
		}

		return( FAIL );
}
