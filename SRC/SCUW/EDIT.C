/*
* ============================================================================
* EDIT.C 15 JAN 89
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\common.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\cscrn.h"
#include "..\common\sound.h"

#include "var.h"

#include "block.h"
#include "scrn.h"
#include "onscrn.h"

#include "edit.h"

#ifdef WANT_TO_USE_GRAPH
void set_graphic_buffer( void ) {
	unsigned int count;
	unsigned int i;
	unsigned int j;
	unsigned int m;
	unsigned int n;
	unsigned int linenum = lineno;
	unsigned int linenum2;
	struct line_node *templine;
	unsigned char *gr;

	templine = curpage;
	while ( templine != curline ) {    /* find lineno of curpage */
		linenum--;
		templine = templine->next;
	}
	j = 0;
	while ( j < wind.width ) {
		if ( graphbuff[j] != NULL ) {
			free( graphbuff[j] );
		}
		graphbuff[j] = NULL;
		j++;
	}

	/*return;*/

	templine = curpage;
	count = 0;
	while ( ( templine->graph == NULL ) &&
		( count != 66 ) && ( templine->previous != sentinel ) ) {
		templine = templine->previous;
		count++;
	}
	if ( templine->graph != NULL ) {
		gr = templine->graph;
		gr += strlen( gr ) + 4;
		while ( ( count != 0 ) && ( *gr != 0x80 ) ) {
			m = 0;
			while ( ( m != 20 ) && ( *gr != 0x80 ) ) {
				gr += strlen( gr ) + 1;
				m++;
			}
			count--;
		}
		linenum2 = linenum;
		i = 0;
		while ( ( *gr != 0x80 ) && ( i < wind.width ) ) {
			m = 0;
			n = 0;
			while ( ( m != 20 ) && ( gr[n] != 0x80 ) ) {
				n += strlen( gr + n ) + 1;
				m++;
			}
			graphbuff[i] = ( unsigned char * ) malloc( n );
			memcpy( graphbuff[i], gr, n );
			gr += n;
			i++;
			linenum2++;
			if ( ( pagebreak == YES ) &&
				( ( ( linenum2 - 1 ) % lineperpage ) == 0 ) ) {
				if ( i != wind.width ) {
					i++;
				}
			}
		}
	}

	templine = curpage;
	i = 0;
	while ( ( i < wind.width ) && ( templine != sentinel ) ) {
		if ( templine->graph != NULL ) {
			j = i;
			linenum2 = linenum;
			gr = templine->graph;
			gr += strlen( templine->graph ) + 4;
			while ( ( *gr != 0x80 ) && ( j < wind.width ) ) {
				m = 0;
				n = 0;
				while ( ( m != 20 ) && ( gr[n] != 0x80 ) ) {
					n += strlen( gr + n ) + 1;
					m++;
				}
				graphbuff[j] = ( unsigned char * ) malloc( n );
				memcpy( graphbuff[j], gr, n );
				gr += n;
				linenum2++;
				j++;
				if ( ( pagebreak == YES ) &&
					( ( ( linenum2 - 1 ) % lineperpage ) == 0 ) ) {
					if ( j != wind.width ) {
						j++;
					}
				}
			}
		}
		templine = templine->next;
		i++;
		linenum++;
		if ( ( pagebreak == YES ) &&
			( ( ( linenum - 1 ) % lineperpage ) == 0 ) ) {
			if ( i != wind.width )
				i++;
		}
	}
}
#endif

void findstrcode( unsigned char *p_fontcode, font_attr p_attr ) {
	int i = 0;

	if ( ( p_attr & ONELINEATTR ) != 0 ) {
		p_fontcode[i] = ONELINECODE;
		i++;
	}
	if ( ( p_attr & SUPERATTR ) != 0 ) {
		p_fontcode[i] = SUPERCODE;
		i++;
	}
	if ( ( p_attr & SUBATTR ) != 0 ) {
		p_fontcode[i] = SUBCODE;
		i++;
	}
	if ( ( p_attr & ITALICATTR ) != 0 ) {
		p_fontcode[i] = ITALICCODE;
		i++;
	}
	if ( ( p_attr & BOLDATTR ) != 0 ) {
		p_fontcode[i] = BOLDCODE;
		i++;
	}
	if ( ( p_attr & TWOLINEATTR ) != 0 ) {
		p_fontcode[i] = TWOLINECODE;
		i++;
	}
	if ( ( p_attr & ENLARGEATTR ) != 0 ) {
		p_fontcode[i] = ENLARGECODE;
		i++;
	}
	p_fontcode[i] = '\0';
}

unsigned int findlineno( struct line_node *p_line ) {
	register unsigned int linenumber = 1;
	struct line_node *templine;

	templine = sentinel->next;
	while ( templine != p_line ) {
		templine = templine->next;
		linenumber++;
	}
	return( linenumber );
}

struct line_node *linepointer( unsigned int p_linenum ) {
	struct line_node *line;

	line = sentinel->next;
	while ( p_linenum-- > 1 ) {
		line = line->next;
	}
	return( line );
}

void displine( struct line_node *p_line, unsigned int p_row, unsigned int p_linenum ) {
	register unsigned int x = 0;
	int count = firstcol;
	font_attr tempfont;
	font_attr curfont = NORMALATTR;
	unsigned char *st;

	st = p_line->text;
	p_row += wind.row;
	while ( ( count > 0 ) && ( *st != '\0' ) ) {
		if ( whatlevel( *st ) == MIDDLE ) {
			if ( *st < 32 ) {
				togglefont( &curfont, *st );
			} else {
				if ( ( curfont & ENLARGEATTR ) == ENLARGEATTR ) {
					count--;
				}
				count--;
			}
		}
		st++;
	}
	if ( ( count < 0 ) && ( ( curfont & ENLARGEATTR ) == ENLARGEATTR ) ) {
		x++;
	}
	while ( ( *st != '\0' ) && ( x < ( wind.length - 2 ) ) ) {
		if ( *st < 32 ) {
			togglefont( &curfont, *st );
		} else {
			tempfont = curfont;
			if ( haveblock( ) && inblock( p_linenum, x + firstcol ) && dispblock ) {
				curfont = curfont | REVERSEATTR;
			}
			if ( whatlevel( *st ) != MIDDLE ) {
				if ( x > 0 ) {
					if ( ( curfont & ENLARGEATTR ) == ENLARGEATTR ) {
						if ( x >= 2 ) {
							prchar( *st, curfont, wind.col + x - 2, p_row );
						}
					} else {
						prchar( *st, curfont, wind.col + x - 1, p_row );
					}
				}
			} else {
				if ( ( *st != ' ' ) || ( curfont != 0 ) ) {
					if ( ( curfont & ENLARGEATTR ) != ENLARGEATTR ) {
						prchar( *st, curfont, wind.col + x, p_row );
						x++;
					} else {
						prchar( *st, curfont, wind.col + x, p_row );
						x += 2;
					}
				} else { /* if it's blank and normal attribute,use prblank to speed up */
					prblank( wind.col + x, p_row );
					x++;
				}
			}
			curfont = tempfont;
		}
		st++;
	}
	clrline( wind.col + x, p_row, wind.col + wind.length - 1 );
	if ( p_line->wrap == NO ) {
		prchar( '<', NORMALATTR, wind.col + wind.length - 1, p_row );
	}
	if ( *st != '\0' ) {
		prchar( '+', NORMALATTR, wind.col + wind.length - 1, p_row );
	}
#ifdef WANT_TO_USE_GRAPH
	p_row -= wind.row;
	if ( graphbuff[p_row] != NULL ) {
		paintlinegraph( graphbuff[p_row], y );
	}
#endif
}

void disppagebreak( unsigned int p_row ) {
	register unsigned int i = 0;
	register unsigned int j;

	p_row += wind.row;
	j = wind.col + wind.length - 1;
	while ( i != j ) {
		prchar( '-', NORMALATTR, wind.col + i, p_row );
		i++;
	}
	prchar( 'P', NORMALATTR, i, p_row );
}

void showpage( void ) {
	register unsigned int y = 0;
	register unsigned int linenum = lineno;
	struct line_node *temppage = curpage;

#ifdef WANT_TO_USE_GRAPH
	set_graphic_buffer();
#endif
	while ( temppage != curline ) {    /* find lineno of curpage */
		linenum--;
		temppage = temppage->next;
	}
	temppage = curpage;
	while ( ( y != wind.width ) && ( temppage != sentinel ) ) {
		if ( keypressed( ) ) {
			pagecomplete = NO;
			return;
		}
		if ( temppage != curline ) {
			displine( temppage, y, linenum );  /* display line from linked list */
		} else {
			refreshline( 0, y );              /* display line from workline */
		}
		temppage = temppage->next;
		linenum++;
		y++;
		if ( ( pagebreak == YES ) &&
			( ( ( linenum - 1 ) % lineperpage ) == 0 ) ) {
			if ( y != wind.width ) {
				disppagebreak( y );
				y++;
			}
		}
	}
	if ( temppage == sentinel ) {
		while ( y != wind.width ) {
			if ( keypressed( ) ) {
				pagecomplete = NO;
				return;
			}
			clrline( wind.col, wind.row + y, wind.col + wind.length - 1 );
			prchar( '.', NORMALATTR, wind.col + wind.length - 1, wind.row + y );
			y++;
		}
	}
	writetab( );
	pagecomplete = YES;
	return;
}

void showpageall( void ) {
	if ( filename[0] != '\0' ) {
		do {
			showpage( );
			if ( !pagecomplete ) {
				ebioskey( 0 );
			}
		} while ( !pagecomplete );
	} else {
		cls( );
	}
}

unsigned int findrow( void ) {
	register unsigned int row = 0;
	register unsigned int linenum = lineno;
	struct line_node *temppage = curpage;

	while ( temppage != curline ) {
		linenum--;
		temppage = temppage->next;
	}
	temppage = curpage;
	while ( temppage != curline ) {
		if ( ( pagebreak == YES ) &&
			( ( ( linenum - 1 ) % lineperpage ) == ( lineperpage - 1 ) ) ) {
			row++;
		}
		temppage = temppage->next;
		linenum++;
		row++;
	}
	return( row );
}

void adjustcol( unsigned int *p_col ) {
	if ( ( *p_col + firstcol ) >= strlen( workline.middle ) ) {
		if ( firstcol > ( strlen( workline.middle ) - 1 ) ) {
			firstcol = strlen( workline.middle ) - 1;
			pagecomplete = NO;
		}
		*p_col = strlen( workline.middle ) - 1 - firstcol;
		if ( *p_col > ( wind.length - 2 ) ) {
			firstcol += *p_col - ( wind.length - 2 );
			pagecomplete = NO;
		}
	}
	if ( *p_col > 0 ) {
		if ( workline.below[*p_col + firstcol + 1] == ENLARGEATTR ) {
			( *p_col )--;
		}
	} else {
		if ( ( workline.below[*p_col + firstcol + 1] == ENLARGEATTR ) &&
			( firstcol != 0 ) ) {
			firstcol--;
			pagecomplete = NO;
		}
	}
}

void loadtoline( unsigned char *p_text ) {
	register unsigned int index = 1;
	font_attr curfont;
	font_attr oldfont;

	workline.middle[0] = ' ';
	while ( index <= ( MAXCOL + 1 ) ) {
		workline.topest[index] = ' ';
		workline.upper[index] = ' ';
		workline.middle[index] = ' ';
		workline.below[index] = ' ';
		workline.attr[index] = 0x00;
		index++;
	}
	index = 0;
	curfont = 0;
	oldfont = 0;
	while ( ( *p_text != '\0' ) && ( index <= MAXCOL ) ) {
		if ( *p_text < 32 ) {
			togglefont( &curfont, *p_text );
		} else {
			switch ( whatlevel( *p_text ) ) {
			case MIDDLE:
				index++;
				if ( ( oldfont & ENLARGEATTR ) == ENLARGEATTR ) {
					workline.attr[index] = oldfont;
					workline.middle[index] = workline.middle[index - 1];
					workline.below[index] = ENLARGEATTR;
					index++;
				}
				workline.middle[index] = ( *p_text );
				workline.attr[index] = curfont;
				break;
			case UPPER:
				workline.upper[index] = ( *p_text );
				break;
			case TOPEST:
				workline.topest[index] = ( *p_text );
				break;
			case BELOW:
				workline.below[index] = ( *p_text );
				break;
			}
			oldfont = curfont;
		}
		p_text++;
	}
	index++;
	if ( ( oldfont & ENLARGEATTR ) == ENLARGEATTR ) {
		workline.attr[index] = oldfont;
		workline.middle[index] = workline.middle[index - 1];
		workline.below[index] = ENLARGEATTR;
		index++;
	}
	workline.middle[index] = '\0';
}

void storeline( struct line_node *p_line ) {
	unsigned int count = 0;
	unsigned int col = 1;
	unsigned char *oneline;
	unsigned char oldfont = 0;
	unsigned char fontcode[9];
	unsigned char *keep_ptr;

	oneline = ( unsigned char * ) malloc( MAXCOL * sizeof( unsigned char ) );
	if ( oneline == NULL ) {
		errorsound( );
		return;								/* Not enough memory */
	}

	while ( ( col <= MAXCOL ) && ( workline.middle[col] != '\0' ) ) {
		if ( workline.attr[col] != oldfont ) {
			if ( oldfont != 0 ) {
				findstrcode( fontcode, oldfont );
				strcpy( &oneline[count], fontcode );
				count += strlen( fontcode );
			}
			findstrcode( fontcode, workline.attr[col] );
			strcpy( &oneline[count], fontcode );
			count += strlen( fontcode );
		}
		oldfont = workline.attr[col];
		oneline[count] = workline.middle[col];
		count++;
		if ( workline.below[col] != ' ' ) {
			oneline[count] = workline.below[col];
			count++;
		}
		if ( workline.upper[col] != ' ' ) {
			oneline[count] = workline.upper[col];
			count++;
		}
		if ( workline.topest[col] != ' ' ) {
			oneline[count] = workline.topest[col];
			count++;
		}
		if ( ( oldfont & ENLARGEATTR ) == ENLARGEATTR ) {
			col++;
		}
		col++;
	}
	if ( oldfont != 0 ) {
		findstrcode( fontcode, oldfont );
		strcpy( &oneline[count], fontcode );
		count += strlen( fontcode );
	}
	oneline[count] = '\0';

	keep_ptr = p_line->text;
	p_line->text = ( unsigned char * ) malloc( count + 1 );
	if ( p_line->text != NULL ) {
		if ( keep_ptr != NULL ) {
			free( keep_ptr );
		}
		strcpy( p_line->text, oneline );
	} else {
		p_line->text = keep_ptr;
		dispstrhgc( "Internal error in storeline", 1, 1, REVERSEATTR );
		getchar( );
	}

	free( oneline );
}

void refreshline( unsigned int p_col, unsigned int p_row ) {
	register size_t i;
	register size_t len;
	unsigned char attr;

	len = wind.length - 2;
	p_row += wind.row;
	if ( p_col == 0 ) {
		if ( workline.below[firstcol + p_col + 1] == ENLARGEATTR ) {
			prchar( ' ', workline.attr[firstcol + p_col + 1], wind.col + p_col, p_row );
			p_col++;
		}
	} else {
		if ( workline.below[firstcol + p_col] != ENLARGEATTR ) {
			p_col--;
		} else {
			if ( p_col >= 2 ) {
				p_col = p_col - 2;
			}
		}
	}
	i = firstcol + p_col + 1;
	while ( ( p_col < len ) && ( workline.middle[i] != '\0' ) ) {
		attr = workline.attr[i];
		if ( haveblock( ) && inblock( lineno, i - 1 ) && dispblock ) {
			attr = attr | REVERSEATTR;
		}
		if ( ( workline.middle[i] != ' ' ) || ( attr != 0 ) ) {
			prchar( workline.middle[i], attr, wind.col + p_col, p_row );
			if ( workline.below[i] != ' ' ) {
				prchar( workline.below[i], attr, wind.col + p_col, p_row );
			}
			if ( workline.upper[i] != ' ' ) {
				prchar( workline.upper[i], attr, wind.col + p_col, p_row );
			}
			if ( workline.topest[i] != ' ' ) {
				prchar( workline.topest[i], attr, wind.col + p_col, p_row );
			}
		} else {
			prblank( wind.col + p_col, p_row );
		}
		if ( ( workline.attr[i] & ENLARGEATTR ) == ENLARGEATTR ) {
			p_col++;
		}
		p_col++;
		i = firstcol + p_col + 1;
	}
	prblank( wind.col + wind.length - 2, p_row );
	if ( workline.middle[i] == '\0' ) {
		for ( ; p_col < len; p_col++ ) {
			prblank( wind.col + p_col, p_row );
		}
		if ( curline->wrap == NO ) {
			prchar( '<', NORMALATTR, wind.col + wind.length - 1, p_row );
		} else {
			prblank( wind.col + wind.length - 1, p_row );
		}
	} else {
		prchar( '+', NORMALATTR, wind.col + wind.length - 1, p_row );
	}
#ifdef WANT_TO_USE_GRAPH
	p_row -= wind.row;
	if ( graphbuff[p_row] != NULL ) {
		paintlinegraph( graphbuff[p_row], p_row );
	}
#endif
}
