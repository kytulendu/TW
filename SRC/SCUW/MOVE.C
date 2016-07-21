/*
* ============================================================================
* MOVE.C
*
* Updated: Suttipong Kanakakorn
*          Fri  08-04-1989  20:53:38
* ============================================================================
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\kbdcode.h"
#include "..\common\getstr.h"

#include "var.h"

#include "block.h"
#include "cw.h"
#include "del.h"
#include "edit.h"
#include "kbd.h"
#include "movement.h"
#include "search.h"

#include "move.h"

void goline( unsigned int p_linetogo ) {
	storeline( curline );
	curline = sentinel->next;
	lineno = 1;
	while ( ( lineno != p_linetogo ) && ( curline->next != sentinel ) ) {
		curline = curline->next;
		lineno++;
	}
	loadtoline( curline->text );
	curpage = curline;
	pagecomplete = NO;
}

void gocol( unsigned int p_coltogo, unsigned int *p_xCursorPos ) {
	if ( p_coltogo > MAXCOL ) {
		workline.middle[MAXCOL + 1] = '\0';
		p_coltogo = MAXCOL;
	}
	if ( p_coltogo > ( strlen( workline.middle ) - 1 ) ) {
		p_coltogo = strlen( workline.middle );
	}
	if ( p_coltogo < firstcol ) {
		firstcol = p_coltogo;
		pagecomplete = NO;
	}
	*p_xCursorPos = p_coltogo - firstcol;
	if ( *p_xCursorPos > ( wind.length - 2 ) ) {
		firstcol = firstcol + *p_xCursorPos - ( wind.length - 2 );
		*p_xCursorPos = p_coltogo - firstcol;
		pagecomplete = NO;
	}
	adjustcol( p_xCursorPos ); /* adjust if cursor is positioned to end of enlarge char */
}

void home( unsigned int *p_xCursorPos ) {
	*p_xCursorPos = 0;
	if ( firstcol != 0 ) {
		firstcol = 0;
		pagecomplete = NO;
	}
}

void endline( unsigned int *p_xCursorPos ) {
	gocol( strlen( workline.middle ) - 1, p_xCursorPos );
}

void topfile( unsigned int *p_xCursorPos ) {
	storeline( curline );
	if ( curpage != sentinel->next ) {
		curpage = sentinel->next;
		pagecomplete = NO;
	}
	curline = curpage;
	*p_xCursorPos = 0;
	firstcol = 0;
	lineno = 1;
	loadtoline( curline->text );
}

void endfile( unsigned int *p_xCursorPos ) {
	int count;
	int linenum;

	storeline( curline );
	curline = sentinel->previous;
	curpage = curline;
	lineno = findlineno( curline );
	if ( pagebreak ) {
		linenum = findlineno( curpage );
	}
	count = wind.width - 1;
	while ( ( count != 0 ) && ( curpage->previous != sentinel ) ) {
		if ( pagebreak ) {
			if ( ( linenum % lineperpage ) != 0 ) {
				curpage = curpage->previous;
				linenum--;
			}
		} else {
			curpage = curpage->previous;
		}
		count--;
	}
	loadtoline( curline->text );
	endline( p_xCursorPos );
	pagecomplete = NO;
}

void backword( unsigned int *p_xCursorPos ) {
	int i;

	i = *p_xCursorPos + firstcol + 1;
	if ( i != 1 ) {   /* first column ? */
		if ( ( !ISBLANK( workline.middle[i] ) ) && ( !ISBLANK( workline.middle[i - 1] ) ) ) {
			while ( ( !ISBLANK( workline.middle[i] ) ) && ( i > 0 ) ) {
				i--;
			}
		} else {
			if ( ISBLANK( workline.middle[i - 1] ) ) {
				i--;
			}
			while ( ISBLANK( workline.middle[i] ) && ( i > 0 ) ) {
				i--;
			}
			while ( !ISBLANK( workline.middle[i] ) && ( i > 0 ) ) {
				i--;
			}
		}
		gocol( i, p_xCursorPos );
		if ( ( i == 0 ) && ( ISBLANK( workline.middle[1] ) ) ) {
			backword( p_xCursorPos );
		}
	} else {
		if ( curline->previous != sentinel ) {
			cursor_up( );
			endline( p_xCursorPos );
		}
	}
}

void nextword( unsigned int *p_xCursorPos, unsigned int p_yCursorPos ) {
	int i;
	unsigned int j;

	i = *p_xCursorPos + firstcol + 1;
	j = i;
	while ( !ISBLANK( workline.middle[i] ) && ( i != MAXCOL ) ) {
		i++;
	}
	while ( ISBLANK( workline.middle[i] ) && ( i != MAXCOL ) ) {
		i++;
	}
	if ( i != MAXCOL ) {
		i--;
		gocol( i, p_xCursorPos );
	} else {
		endline( p_xCursorPos );
		if ( ( *p_xCursorPos + firstcol + 1 ) <= j ) {
			cursor_down( p_yCursorPos );
			home( p_xCursorPos );
			if ( ISBLANK( workline.middle[1] ) ) {
				nextword( p_xCursorPos, p_yCursorPos );
			}
		}
	}
}

void gotopage( void ) {
	char st[4];
	int linetogo;

	st[0] = '\0';

	blockmsg( 5 );
	dispstrhgc( "ต้องการไปที่หน้าที่เท่าไร ?", ( 14 + center_factor ) + 17, 5, REVERSEATTR );

	if ( getstring( st, ( 16 + center_factor ) + 37, 5, 3, REVERSEATTR, NUMBER ) ) {
		linetogo = ( atoi( st ) * lineperpage ) - lineperpage + 1;
		if ( linetogo >= 1 ) {
			goline( linetogo );
		}
	}
	pagecomplete = NO;
}

void gotoline( void ) {
	char st[5];
	register int linetogo;
	st[0] = '\0';

	blockmsg( 5 );
	dispstrhgc( "ต้องการไปที่บรรทัดที่เท่าไร ? (นับจากต้นแฟ้มข้อมูล)", ( 14 + center_factor ) + 2, 5, REVERSEATTR );

	if ( getstring( st, ( 14 + center_factor ) + 42, 5, 5, REVERSEATTR, NUMBER ) ) {
		linetogo = atoi( st );
		if ( linetogo >= 1 ) {
			goline( linetogo );
		}
	}
	pagecomplete = NO;
}

void gobeginblk( unsigned int *p_xCursorPos ) {
	if ( haveblock( ) ) {
		goline( blkbegin.lineno );
		gocol( blkbegin.column, p_xCursorPos );
	}
}

void goendblk( unsigned int *p_xCursorPos ) {
	if ( haveblock( ) ) {
		goline( blkend.lineno );
		gocol( blkend.column, p_xCursorPos );
	}
}

void quick( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos ) {
	register int key;

	dispkey( CNTRL_Q );
	waitkbd( 3, 2 );
	key = ebioskey( 0 ) & 0xff;
	prchar( key, NORMALATTR, 3, 2 );
	if ( !isalpha( key ) && !iscntrl( key ) ) {
		return;
	}
	switch ( key & 0x1f ) {
	case 'r' - 'a' + 1:
		topfile( p_xCursorPos );
		break;
	case 'c' - 'a' + 1:
		endfile( p_xCursorPos );
		break;
	case 'f' - 'a' + 1:
		searching( p_xCursorPos, p_yCursorPos );
		break;
	case 'a' - 'a' + 1:
		replacing( p_xCursorPos, p_yCursorPos );
		break;
	case 'y' - 'a' + 1:
		deltoendline( *p_xCursorPos, *p_yCursorPos );
		break;
	case 'l' - 'a' + 1:
		loadtoline( curline->text );
		refreshline( 0, *p_yCursorPos );
		break;
	case 'b' - 'a' + 1:
		gobeginblk( p_xCursorPos );
		break;
	case 'k' - 'a' + 1:
		goendblk( p_xCursorPos );
		break;
	case 'd' - 'a' + 1:
		endline( p_xCursorPos );
		break;
	case 's' - 'a' + 1:
		home( p_xCursorPos );
		break;
	case 'x' - 'a' + 1:
		bottom_of_page( );
		break;
	case 'e' - 'a' + 1:
		top_of_page( );
		break;
	}
}
