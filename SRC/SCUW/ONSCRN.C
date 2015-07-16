/*
* ============================================================================
* ONSCRN.C
*
* Update : Suttipong Kanakakorn
*          Tue  08-01-1989  13:57:19
* Update : CUCC
*          - Garbage Collection
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h" 
#include "..\common\kbdcode.h"
#include "..\common\sound.h"
#include "..\common\getstr.h"

#include "var.h"

#include "cw.h"
#include "del.h"
#include "edit.h"
#include "ins.h"
#include "kbd.h"
#include "move.h"
#include "status.h"

#include "onscrn.h"

void writetab( void ) {
	unsigned int i = 0;
	prblank( wind.col, 3 );

	while ( ( ( i + firstcol + 1 ) < leftmar ) && ( i < wind.length ) ) {
		prblank( wind.col + i, 3 );
		i++;
	}
	if ( ( i < wind.length ) && ( ( i + firstcol + 1 ) == leftmar ) ) {
		prchar( 'L', 0, wind.col + i, 3 );
		i++;
	}

	while ( ( ( i + firstcol + 1 ) < rightmar ) && ( i < wind.length ) ) {
		if ( tab[i + firstcol] == NO ) {
			prchar( '-', 0, wind.col + i, 3 );
		} else {
			prchar( '|', 0, wind.col + i, 3 );
		}
		i++;
	}
	if ( ( rightmar - 1 - firstcol ) < wind.length ) {
		prchar( 'R', 0, wind.col + rightmar - 1 - firstcol, 3 );
	}

	i++;
	while ( i < wind.length ) {
		prblank( wind.col + i, 3 );
		i++;
	}
}

void centerline( unsigned int y ) {
	int i, j, k, count;
	for ( i = 1; ( workline.middle[i] == ' ' ) || ( workline.middle[i] == WRAPBLANK ); i++ );
	for ( j = strlen( workline.middle ) - 1; ( workline.middle[j] == ' ' )
		|| ( workline.middle[j] == WRAPBLANK ); j-- );
	if ( ( rightmar - leftmar ) > ( j - i ) ) {
		k = leftmar + ( ( rightmar - leftmar ) - ( j - i ) ) / 2;
		if ( k < i ) {
			for ( count = i - k; count > 0; count-- ) {
				delete_char( 0 );
			}
		} else {
			for ( count = k - i; count > 0; count-- ) {
				insertblank( 1, ' ' );
			}
		}
		refreshline( 0, y );
	}
}

void doonscrn( register unsigned key, unsigned int x, unsigned int y ) {
	register unsigned int j;
	char st[4], invmsg[60];

	key &= 0xff;
	if ( !isalpha( key ) && !iscntrl( key ) ) {
		return;
	}
	key &= 0x1f;
	switch ( key ) {
	case 'l' - 'a' + 1:
		sprintf( st, "%d", leftmar );
		blockmsg( 5 );
		dispstrhgc( "ต้องการตั้งกั้นซ้ายที่คอลัมน์ที่เท่าไหร่ ?", ( 14 + center_factor ) + 12, 5, REVERSEATTR );
		if ( getstring( st, ( 14 + center_factor ) + 41, 5, 3, REVERSEATTR, NUMBER ) ) {
			j = atoi( st );
			if ( ( j < rightmar ) && ( j > 0 ) ) {
				leftmar = j;
			} else {                                   /* Invalid Left Margin */
				if ( j < 1 ) {
					strcpy( invmsg, "กั้นซ้ายน้อยกว่า 1 !   " );
				} else {
					strcpy( invmsg, "กั้นซ้ายมากกว่ากั้นขวา !" );
				}
				strcat( invmsg, " กดปุ่มใดๆ เพื่อทำงานต่อ ..." );
				blockmsg( 5 );
				dispstrhgc( invmsg, ( 14 + center_factor ) + 6, 5, REVERSEATTR );
				errorsound( );
				ebioskey( 0 );
			}
		}
		break;
	case 'r' - 'a' + 1:
		sprintf( st, "%d", rightmar );
		blockmsg( 5 );
		dispstrhgc( "ต้องการตั้งกั้นขวาที่คอลัมน์ที่เท่าไหร่ ?", ( 14 + center_factor ) + 12, 5, REVERSEATTR );
		if ( getstring( st, ( 14 + center_factor ) + 41, 5, 3, REVERSEATTR, NUMBER ) ) {
			j = atoi( st );
			if ( ( j > leftmar ) && ( j <= MAXRMAR ) ) {
				rightmar = j;
			} else {            			 /* Invalid Right Margin */
				if ( j <= leftmar ) {
					strcpy( invmsg, "กั้นขวาน้อยกว่ากั้นซ้าย !  " );
				} else {
					sprintf( invmsg, "กั้นขวาสูงสุดไม่เกิน %d !", MAXRMAR );
				}
				strcat( invmsg, " กดปุ่มใดๆ เพื่อทำงานต่อ ..." );
				blockmsg( 5 );
				dispstrhgc( invmsg, ( 14 + center_factor ) + 5, 5, REVERSEATTR );
				errorsound( );
				ebioskey( 0 );
			}
		}
		break;
	case 'i' - 'a' + 1:
		sprintf( st, "%d", x + 1 );
		blockmsg( 5 );
		dispstrhgc( "ต้องการตั้ง TAB ที่คอลัมน์ที่เท่าไหร่ ?", ( 14 + center_factor ) + 12, 5, REVERSEATTR );
		if ( getstring( st, ( 16 + center_factor ) + 41, 5, 3, REVERSEATTR, NUMBER ) ) {
			j = atoi( st );
			if ( ( j <= MAXCOL ) && ( j > 0 ) ) {
				tab[j - 1] = YES;
			}
		}
		break;
	case 'n' - 'a' + 1:
		strcpy( st, "ALL" );
		blockmsg( 5 );
		dispstrhgc( "ต้องการลบ TAB ที่คอลัมน์ที่เท่าไหร่ ?", ( 14 + center_factor ) + 12, 5, REVERSEATTR );
		if ( getstring( st, ( 16 + center_factor ) + 41, 5, 3, REVERSEATTR, NUMBER ) ) {
			if ( strcmp( st, "ALL" ) == 0 ) {
				for ( j = 0; j < MAXCOL; ++j ) {
					tab[j] = NO;
				}
			} else {
				j = atoi( st );
				if ( ( j <= MAXCOL ) && ( j > 0 ) ) {
					tab[j - 1] = NO;
				}
			}
		}
		break;
	case 'p' - 'a' + 1:
		sprintf( st, "%d", lineperpage );
		blockmsg( 5 );
		dispstrhgc( "ต้องการตั้งจำนวนบรรทัดต่อหน้าเท่าไหร่ ?", ( 14 + center_factor ) + 11, 5, REVERSEATTR );
		if ( getstring( st, ( 16 + center_factor ) + 43, 5, 3, REVERSEATTR, NUMBER ) ) {
			if ( atoi( st ) > 0 ) {
				lineperpage = atoi( st );
				writepageline( );
			}
		}
		break;
	case 'c' - 'a' + 1:
		centerline( y );
		break;
	case 'x' - 'a' + 1:
		relmargin = !relmargin;
		relmarstatus( );
		break;
	}
	pagecomplete = NO;
	writestatus( x );
}

void movetotab( unsigned int *x, unsigned int y ) {
	size_t i, count;
	if ( ( *x + firstcol ) >= ( leftmar - 1 ) ) {
		i = *x + firstcol + 1;
	} else {
		i = leftmar - 1;
	}
	for ( ; ( i < ( rightmar - 1 ) && ( tab[i] != YES ) ); i++ );
	if ( i < ( rightmar - 1 ) ) {
		count = i - ( *x + firstcol );
		while ( count-- != 0 ) {
			if ( insertmode ) {
				insertblank( *x + firstcol + 1, ' ' );
			}
		}
		gocol( i, x );
		refreshline( 0, y );
	}
}

void onscreen( unsigned int x, unsigned int y ) {
	int key;
	dispkey( CNTRL_O );
	waitkbd( 3, 2 );
	key = ebioskey( 0 );
	prchar( key, 0, 3, 2 );
	doonscrn( key, x, y );
}
