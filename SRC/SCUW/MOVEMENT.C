/*
* ============================================================================
* MOVEMENT.C
*
* Update: Suttipong Kanakakorn
*         Fri  08-04-1989  20:13:52
*         - Add top_of_page() and bottom_of_page()
* Update: CUCC
*         - Debug 255 Right Margin to work correctly
* ============================================================================
*/

#include <string.h>

#include "const.h"
#include "var.h"

#include "edit.h"
#include "ins.h"
#include "move.h"

#include "movement.h"

void cursor_up( void ) {
	if ( curline->previous != sentinel ) {  /* top of file ? */
		storeline( curline );
		lineno--;
		if ( curpage == curline ) {  /* Is top of page ? */
			curpage = curpage->previous;  /* scroll page up */
			curline = curline->previous;  /* up one line    */
			pagecomplete = NO;            /* refresh screen */
		} else {
			curline = curline->previous;  /* up one line    */
		}
		loadtoline( curline->text );
	}
}

void cursor_down( unsigned int p_yCursorPos ) {
	if ( curline->next != sentinel ) {  /* end of file ? */
		storeline( curline );
		lineno++;                       /* increment lineno */
		curline = curline->next;        /* down one line    */
		if ( p_yCursorPos == ( wind.width - 1 ) ) {    /* bottom of screen ? */
			if ( pagebreak && ( ( ( lineno - 1 ) % lineperpage ) == 0 ) ) {
				curpage = curpage->next;    /* skip over page break */
			}
			curpage = curpage->next;      /* scroll page down */
			pagecomplete = NO;            /* refresh screen   */
		} else {
			if ( pagebreak &&  /* page break is displayed at bottom of screen ? */
				( ( ( ( lineno - 1 ) % lineperpage ) == 0 ) &&
				( p_yCursorPos == ( wind.width - 2 ) ) ) ) {
				curpage = curpage->next;     /* skip over page break */
				pagecomplete = NO;           /* refresh screen       */
			}
		}
		loadtoline( curline->text );
	}
}

void cursor_left( unsigned int *p_xCursorPos ) {
	unsigned int i = *p_xCursorPos + firstcol;

	if ( i != 0 ) {    /* Home of line ? */
		gocol( i - 1, p_xCursorPos );
	} else {
		if ( curline->previous != sentinel ) {
			cursor_up( );   /* go to end of  */
			endline( p_xCursorPos );    /* previous line */
		}
	}
}

void cursor_right( unsigned int *p_xCursorPos, unsigned int p_yCursorPos ) {
	if ( ( *p_xCursorPos + firstcol + 1 ) == strlen( workline.middle ) ) {
		if ( curline->next != sentinel ) {
			cursor_down( p_yCursorPos );
			home( p_xCursorPos );
		}
	} else {
		if ( ( *p_xCursorPos + firstcol + 1 ) < MAXCOL ) {    /* 5 to TUDCUM in 255 RMAR */
			if ( *p_xCursorPos >= ( wind.length - 2 ) ) {
				shiftscrn( 20, p_xCursorPos );
			}
			if ( ( workline.attr[*p_xCursorPos + firstcol + 1] & ENLARGEATTR ) == ENLARGEATTR ) {
				( *p_xCursorPos )++;
			}
			( *p_xCursorPos )++;
		} else {
			linetoolong( );
		}
	}
}

void page_up( void ) {
	int count;

	storeline( curline );

	if ( curpage->previous != sentinel ) {  /* top of file ? */
		count = wind.width - 1;
		while ( ( count > 0 ) && ( curpage->previous != sentinel ) ) {
			curpage = curpage->previous;
			curline = curline->previous;
			lineno--;
			count--;
		}
		pagecomplete = NO;
	} else {
		curline = curpage;
		lineno = 1;
	}
	loadtoline( curline->text );
}

void page_down( void ) {
	int count;

	if ( curpage->next != sentinel ) { /* bottom of file ? */
		storeline( curline );
		count = wind.width - 1;
		while ( ( count != 0 ) && ( curline->next != sentinel ) ) {
			curline = curline->next;
			curpage = curpage->next;
			count--;
			lineno++;
		}
		if ( count != 0 ) {     /* end of file ? */
			curpage = curline;
		}
		pagecomplete = NO;
		loadtoline( curline->text );
	}
}

void scroll_up( void ) {
	if ( curpage->previous != sentinel ) {   /* top of file ? */
		storeline( curline );
		curpage = curpage->previous;
		pagecomplete = NO;
		loadtoline( curline->text );
	}
}

void scroll_down( void ) {
	if ( curpage->next != sentinel ) {  /* end of file ? */
		storeline( curline );
		if ( curpage != curline ) {
			curpage = curpage->next;
		} else {
			curpage = curpage->next;
			curline = curpage;
			lineno++;
		}
		pagecomplete = NO;
		loadtoline( curline->text );
	}
}

void top_of_page( void ) {
	storeline( curline );
	while ( curline != curpage ) {
		curline = curline->previous;
		lineno--;
	}
	loadtoline( curline->text );
}

void bottom_of_page( void ) {
	int count;

	top_of_page( );
	count = wind.width - 1;
	storeline( curline );
	while ( ( curline != sentinel ) && count-- ) {
		curline = curline->next;
		lineno++;
	}
	if ( curline == sentinel ) {
		curline = sentinel->previous;
		lineno--;
	}
	loadtoline( curline->text );
}
