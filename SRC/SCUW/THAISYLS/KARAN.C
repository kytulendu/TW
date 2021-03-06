#include "tctype.h"
#include "thai.h"

#include "global.h"
#include "routine.h"

/** Programmer   : Subun Yenjaichon
*   Written Date : Monday, 16 May, 1988 1:04:44 PM
*   Last Updated : Tuesday, 17 May, 1988 11:15:14 AM
*/

unsigned char *KaranRtn( unsigned char *TempIndx ) {
	short i;
	unsigned char *TempIndxp1 = TempIndx + 1;
	unsigned char *TempIndxm1 = TempIndx - 1;
	unsigned char *TempIndxm3 = TempIndx - 3;
	unsigned char *TempIndxm4 = TempIndx - 4;
	unsigned char *TempIndxm5 = TempIndx - 5;

	/* RoreReo */
	static unsigned char *MoreMarRoreReoTable5[] = {
		"�����", "�����", "�����", "�����"
	};
	static unsigned char *ToreTaoRoreReoTable5[] = {
		"����", "����", "����", "����"
	};
	static unsigned char *DoreDekRoreReoTable5[] = {
		"����", "����", "����", "����", "����", "����"
	};
	static unsigned char *KoreKwaiRoreReoTable5[] = {
		"����", "����", "����"
	};
	static unsigned char *KoreGaiRoreReoTable5[] = {
		"����"
	};
	static unsigned char *LoreLingRoreReoTable5[] = {
		"�����"
	};
	static unsigned char *PorePlaRoreReoTable5[] = {
		"����"
	};
	static unsigned char *JoreJarnRoreReoTable5[] = {
		"����"
	};
	static unsigned char *PoreParnRoreReoTable5[] = {
		"����"
	};
	static unsigned char *ShoreChangRoreReoTable5[] = {
		"����"
	};
	static unsigned char *SoreSeoRoreReoTable5[] = {
		"�����"
	};
	static unsigned char *ToreTaharnRoreReoTable5[] = {
		"����"
	};
	static unsigned char *ToreTaharnRoreReoTable6[] = {
		"�����", "ʵ���", ";���"
	};
	static unsigned char *ToreTaoRoreReoTable6[] = {
		"ʻ���", "ʵ���", ";���"
	};
	static unsigned char *DoreDekRoreReoTable6[] = {
		"����", "�����"
	};
	static unsigned char *KoreKwaiRoreReoTable6[] = {
		"����", "�����"
	};
	static unsigned char *MoreMarRoreReoTable6[] = {
		"�����", "������"
	};
	static unsigned char *NoreNooRoreReoTable6[] = {
		"����", "����"
	};
	static unsigned char *KoreGaiRoreReoTable6[] = {
		"����", "����"
	};
	static unsigned char *ForeFunRoreReoTable6[] = {
		"�����"
	};
	static unsigned char *LoreLingRoreReoTable6[] = {
		"������"
	};
	static unsigned char *MoreMarRoreReoTable7[] = {
		"������", "������"
	};

	/* LoreLing */
	static unsigned char *MoreMarLoreLingTable5[] = {
		"�����", "�����", "�����", "�����"
	};
	static unsigned char *KoreKwaiLoreLingTable5[] = {
		"����", "����", "����", "���"
	};
	static unsigned char *KoreGaiLoreLingTable5[] = {
		"����"
	};
	static unsigned char *ForeFunLoreLingTable5[] = {
		"����", "����"
	};
	static unsigned char *WoreWaanLoreLingTable5[] = {
		"�����"
	};

	if ( istrvwl( *( TempIndx + 2 ) ) ) {
		return( TempIndx );									/* cut after karan */
	}
	switch ( *TempIndxm1 ) {
	case RoreReo:
		switch ( *TempIndxp1 ) {
		case MoreMar:
			/* cut after following-consonant */
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( MoreMarRoreReoTable7[i], ( TempIndx - 5 ) ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : ( TempIndx - 6 ) );
				}
			}
			/* cut after following-consonant  */
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( MoreMarRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			/* cut after following-consonant */
			for ( i = 0; i <= 3; ++i ) {
				if ( !( nstrcmp( MoreMarRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case ToreTao:
			for ( i = 0; i <= 2; ++i ) {
				if ( !( nstrcmp( ToreTaoRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			for ( i = 0; i <= 3; ++i ) {
				if ( !( nstrcmp( ToreTaoRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case DoreDek:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( DoreDekRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			for ( i = 0; i <= 5; ++i ) {
				if ( !( nstrcmp( DoreDekRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case KoreKwai:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( KoreKwaiRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			for ( i = 0; i <= 2; ++i ) {
				if ( !( nstrcmp( KoreKwaiRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case KoreGai:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( KoreGaiRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( KoreGaiRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case ToreTaharn:
			for ( i = 0; i <= 2; ++i ) {
				if ( !( nstrcmp( ToreTaharnRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( ToreTaharnRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case LoreLing:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( LoreLingRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( LoreLingRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case PorePla:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( PorePlaRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case ShoreChang:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( ShoreChangRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case JoreJarn:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( JoreJarnRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case PoreParn:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( PoreParnRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case SoreSeo:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( SoreSeoRoreReoTable5[i], TempIndxm3 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
				}
			}
			break;
		case ForeFun:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( ForeFunRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		case NoreNoo:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( NoreNooRoreReoTable6[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		default:
			return( TempIndx );
		}	/* end switch RoreReo */
	case LoreLing:
		switch ( *TempIndxp1 ) {
		case MoreMar:
			for ( i = 0; i <= 3; ++i ) {
				if ( !( nstrcmp( MoreMarLoreLingTable5[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		case KoreKwai:
			for ( i = 0; i <= 3; ++i ) {
				if ( !( nstrcmp( KoreKwaiLoreLingTable5[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		case KoreGai:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( KoreGaiLoreLingTable5[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		case ForeFun:
			for ( i = 0; i <= 1; ++i ) {
				if ( !( nstrcmp( ForeFunLoreLingTable5[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		case WoreWaan:
			for ( i = 0; i <= 0; ++i ) {
				if ( !( nstrcmp( WoreWaanLoreLingTable5[i], TempIndxm4 ) ) ) {
					return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm5 );
				}
			}
			break;
		default:
			return( TempIndx );
		}	/* end switch LoreLing */

	case SoreSeo:
		if ( !( nstrcmp( "����", TempIndxm3 ) ) || !( nstrcmp( "����", TempIndxm3 ) ) ) {
			/* cut after following-consonant or before SoreSeo or SoreSara */
			return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
		}
		break;

	case WoreWaan:
		if ( !( nstrcmp( "����", TempIndxm3 ) ) ) {
			/* cut after following-consonant or before SaraO */
			return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
		}
		break;

	case HorHeeb:
		if ( !( nstrcmp( "�����", TempIndxm3 ) ) ) {
			/* cut after following-consonant or before SaraO */
			return( ( TempIndxp1 <= RightMargin ) ? TempIndxp1 : TempIndxm4 );
		}
		break;

	default:
		return( TempIndx );	/* cut after karan */
	}
	return( TempIndx );		/* cut after karan */
}
