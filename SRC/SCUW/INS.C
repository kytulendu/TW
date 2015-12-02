/*
* ============================================================================
* INS.C 15 JAN 89
*
* Update: Suttipong Kanakakorn
*         Sat  08-05-1989  03:59:22
* Update: CUCC
*         - Debug 256 right margin.
* ============================================================================
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "..\common\const.h"
#include "..\common\cwtype.h"
#include "..\common\common.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\kbdcode.h"
#include "..\common\sound.h"
#include "..\common\getstr.h"

#include "var.h"

#include "block.h"
#include "cw.h"
#include "edit.h"
#include "kbd.h"
#include "move.h"
#include "movement.h"
#include "status.h"
#include "tutil2.h"
#include "wrap.h"

#include "ins.h"

void insertblank( unsigned int p_col, unsigned char p_blankchar ) {
	register size_t i;
	i = strlen( workline.middle );
	while ( i >= p_col ) {
		workline.middle[i + 1] = workline.middle[i];  /* shift right */
		workline.upper[i + 1] = workline.upper[i];    /*  by ignore  */
		workline.topest[i + 1] = workline.topest[i];  /*  character  */
		workline.below[i + 1] = workline.below[i];    /*   at last   */
		workline.attr[i + 1] = workline.attr[i];      /*   column    */
		i--;
	}
	workline.middle[p_col] = p_blankchar;  /* put blank */
	workline.upper[p_col] = ' ';           /* put blank */
	workline.topest[p_col] = ' ';          /* put blank */
	workline.below[p_col] = ' ';           /* put blank */
	workline.attr[p_col] = 0;
	if ( haveblock( ) ) {
		if ( lineno == blkbegin.lineno ) {
			if ( ( p_col - 1 ) <= blkbegin.column ) {
				blkbegin.column++;
			}
		}
		if ( lineno == blkend.lineno ) {
			if ( ( p_col - 1 ) < blkend.column ) {
				blkend.column++;
			}
		}
	}
	changeflag = YES;
}

void insert_line( struct line_node *p_curline, struct line_node *p_newline ) {
	p_newline->previous = p_curline;
	p_newline->next = p_curline->next;
	( p_curline->next )->previous = p_newline;
	p_curline->next = p_newline;
}

void shiftscrn( unsigned int p_count, unsigned int *p_x ) {
	storeline( curline );
	while ( ( p_count != 0 ) && ( ( firstcol + wind.length ) <= MAXCOL ) ) {
		firstcol++;
		( *p_x )--;
		p_count--;
	}
	pagecomplete = NO;  /* set flag to refresh screen */
}

void linetoolong( void ) {
	errorsound( );
	blockmsg( 5 );
	dispstrhgc( "บรรทัดยาวเกินไป ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 9, 5, REVERSEATTR );
	while ( ebioskey( 0 ) != ESCKEY );
	pagecomplete = NO;
}

void inscntrl( unsigned char p_ctrlChar, unsigned int p_xCursorPos, unsigned int p_yCursorPos ) {
	register unsigned int i = MAXCOL;
	register unsigned int j = p_xCursorPos + firstcol + 1;
	while ( i >= j ) {
		workline.middle[i + 1] = workline.middle[i];  /* shift right */
		workline.upper[i + 1] = workline.upper[i];    /*  by ignore  */
		workline.topest[i + 1] = workline.topest[i];  /*  character  */
		workline.below[i + 1] = workline.below[i];    /*   at last   */
		workline.attr[i + 1] = workline.attr[i];      /*   column    */
		i--;
	}
	workline.middle[j] = p_ctrlChar;	/* put print control character */
	workline.upper[j] = ' ';			/* put blank */
	workline.topest[j] = ' ';			/* put blank */
	workline.below[j] = ' ';			/* put blank */
	workline.attr[j] = fontused;
	storeline( curline );				/* store workline to linked list then */
	loadtoline( curline->text );		/* load back and redisplay line */
	refreshline( 0, p_yCursorPos );		/* to show new attribute of character */
}

void printcntrl( register unsigned int p_xCursorPos, register unsigned int p_yCursorPos ) {
	register int key;

	dispkey( CNTRL_P );
	waitkbd( 3, 2 );
	key = ebioskey( 0 ) & 0xff;
	prchar( key, NORMALATTR, 3, 2 );
	if ( !isalpha( key ) && !iscntrl( key ) )
		return;
	switch ( key & 0x1f ) {
	case 'w' - 'a' + 1:
		inscntrl( CNTRL_W, p_xCursorPos, p_yCursorPos );
		break;
	case 's' - 'a' + 1:
		inscntrl( CNTRL_S, p_xCursorPos, p_yCursorPos );
		break;
	case 'r' - 'a' + 1:
		inscntrl( CNTRL_R, p_xCursorPos, p_yCursorPos );
		break;
	case 'b' - 'a' + 1:
		inscntrl( CNTRL_B, p_xCursorPos, p_yCursorPos );
		break;
	case 'e' - 'a' + 1:
		inscntrl( CNTRL_E, p_xCursorPos, p_yCursorPos );
		break;
	case 't' - 'a' + 1:
		inscntrl( CNTRL_T, p_xCursorPos, p_yCursorPos );
		break;
	case 'v' - 'a' + 1:
		inscntrl( CNTRL_V, p_xCursorPos, p_yCursorPos );
		break;
	};
}

int insert_char( unsigned char p_char, unsigned int *p_xCursorPos, unsigned int *p_yCursorPos ) {
	register unsigned int i;
	unsigned int j;
	if ( ( *p_xCursorPos + firstcol + 1 ) <= MAXCOL ) {   /* if out of line , not insert */
		if ( wordwrap && ( ( *p_xCursorPos + firstcol + 1 ) >= ( rightmar + 5 ) ) ) {
			if ( relmargin == NO ) {
				autowrap( p_xCursorPos, p_yCursorPos );
			}
		}
		switch ( whatlevel( p_char ) ) {
		case MIDDLE:
			if ( ( *p_xCursorPos + firstcol + 1 ) < leftmar ) {  /* cursor before left margin ? */
				if ( !relmargin ) {    /* release margin ? */
					for ( i = *p_xCursorPos + firstcol + 1; i != leftmar; i++ ) {
						insertblank( 1, WRAPBLANK );
					}
					gocol( leftmar - 1, p_xCursorPos );
					refreshline( 0, *p_yCursorPos );
				}
			}
			i = strlen( workline.middle );
			j = *p_xCursorPos + firstcol + 1;
			while ( i >= j ) {
				workline.middle[i + 1] = workline.middle[i];  /* shift right */
				workline.upper[i + 1] = workline.upper[i];    /*  by ignore  */
				workline.topest[i + 1] = workline.topest[i];  /*  character  */
				workline.below[i + 1] = workline.below[i];    /*   at last   */
				workline.attr[i + 1] = workline.attr[i];      /*   column    */
				i--;
			}
			workline.middle[j] = p_char; /* put character */
			workline.upper[j] = ' ';     /* put blank */
			workline.topest[j] = ' ';    /* put blank */
			workline.below[j] = ' ';     /* put blank */
			workline.attr[j] = fontused;
			if ( haveblock( ) ) {
				if ( lineno == blkbegin.lineno ) {
					if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
						blkbegin.column++;
					}
				}
				if ( lineno == blkend.lineno ) {
					if ( ( *p_xCursorPos + firstcol ) < blkend.column ) {
						blkend.column++;
					}
				}
			}
			if ( ( fontused & ENLARGEATTR ) == ENLARGEATTR ) {
				i = strlen( workline.middle ); /*  if enlarge , insert special column  */
				i++;
				j = *p_xCursorPos + firstcol + 2;
				while ( i >= j ) {
					workline.middle[i + 1] = workline.middle[i];
					workline.upper[i + 1] = workline.upper[i];
					workline.topest[i + 1] = workline.topest[i];
					workline.below[i + 1] = workline.below[i];
					workline.attr[i + 1] = workline.attr[i];
					i--;
				}
				workline.middle[j] = p_char;
				workline.below[j] = ENLARGEATTR;
				workline.attr[j] = fontused;
				if ( haveblock( ) ) {
					if ( lineno == blkbegin.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
							blkbegin.column++;
						}
					}
					if ( lineno == blkend.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) < blkend.column ) {
							blkend.column++;
						}
					}
				}
			}
			break;
		case UPPER:
			i = *p_xCursorPos + firstcol;
			if ( ( workline.middle[i] >= 'ก' ) &&   /* possible character ? */
				( workline.middle[i] <= 'ฮ' ) ) {
				if ( workline.below[i] == ENLARGEATTR ) {
					if ( p_char != HUNAKADMITO ) {
						workline.upper[i - 1] = p_char;
					} else {
						workline.topest[i - 1] = 0xe9;
						workline.upper[i - 1] = 0xd1;
					}
				} else {
					if ( p_char != HUNAKADMITO ) {
						workline.upper[i] = p_char;
					} else {
						workline.topest[i] = 0xe9;
						workline.upper[i] = 0xd1;
					}
				}
			} else {
				errorsound( );
			}
			break;
		case TOPEST:
			i = *p_xCursorPos + firstcol;
			if ( ( workline.middle[i] >= 'ก' ) &&
				( workline.middle[i] <= 'ฮ' ) ) {
				if ( workline.below[i] == ENLARGEATTR ) {
					workline.topest[i - 1] = p_char;
				} else {
					workline.topest[i] = p_char;
				}
			} else {
				errorsound( );
			}
			break;
		case BELOW:
			i = *p_xCursorPos + firstcol;
			if ( ( workline.middle[i] >= 'ก' ) &
				( workline.middle[i] <= 'ฮ' ) ) {
				if ( workline.below[i] == ENLARGEATTR ) {
					workline.below[i - 1] = p_char;
				} else {
					workline.below[i] = p_char;
				}
			} else {
				errorsound( );
			}
			break;
		}
		if ( *p_xCursorPos >= ( wind.length - 2 ) ) {
			if ( whatlevel( p_char ) == MIDDLE ) {
				shiftscrn( 20, p_xCursorPos );
			}
		}
		if ( whatlevel( p_char ) == MIDDLE ) {
			if ( ( fontused & ENLARGEATTR ) == ENLARGEATTR ) {
				( *p_xCursorPos )++;
			}
			( *p_xCursorPos )++;
		}
		changeflag = YES;
		return( YES );
	} else {
		return( NO );
	}
}

int ovrwrite_char( unsigned char p_char, unsigned int *p_xCursorPos, unsigned int *p_yCursorPos ) {
	register unsigned int i;
	unsigned int j;
	if ( ( *p_xCursorPos + firstcol + 1 ) <= MAXCOL ) {   /* no write at last column */
		if ( wordwrap && ( ( *p_xCursorPos + firstcol + 1 ) >= ( rightmar + 5 ) ) ) {
			if ( relmargin == NO ) {
				autowrap( p_xCursorPos, p_yCursorPos );
			}
		}
		switch ( whatlevel( p_char ) ) {
		case MIDDLE:
			if ( ( *p_xCursorPos + firstcol + 1 ) < leftmar ) {  /* cursor before left margin ? */
				if ( !relmargin ) {    /* release margin ? */
					for ( i = *p_xCursorPos + firstcol + 1; i != leftmar; i++ ) {
						insertblank( 1, WRAPBLANK );
					}
					gocol( leftmar - 1, p_xCursorPos );
					refreshline( 0, *p_yCursorPos );
				}
			}
			if ( ( workline.attr[*p_xCursorPos + firstcol + 1] & ENLARGEATTR ) == ENLARGEATTR ) {
				i = *p_xCursorPos + firstcol + 2;
				while ( i < MAXCOL ) {
					workline.middle[i] = workline.middle[i + 1];
					workline.upper[i] = workline.upper[i + 1];
					workline.topest[i] = workline.topest[i + 1];
					workline.below[i] = workline.below[i + 1];
					workline.attr[i] = workline.attr[i + 1];
					i++;
				}
				if ( haveblock( ) ) {
					if ( lineno == blkbegin.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
							blkbegin.column--;
						}
					}
					if ( lineno == blkend.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) < blkend.column ) {
							blkend.column--;
						}
					}
				}
			}
			i = *p_xCursorPos + firstcol + 1;
			if ( workline.middle[i] == '\0' )
				workline.middle[i + 1] = '\0';
			workline.middle[i] = p_char;
			workline.upper[i] = ' ';
			workline.below[i] = ' ';
			workline.topest[i] = ' ';
			workline.attr[i] = fontused;
			if ( ( fontused & ENLARGEATTR ) == ENLARGEATTR ) {
				i = MAXCOL + 5;
				j = *p_xCursorPos + firstcol + 2;
				while ( i >= j ) {
					workline.middle[i + 1] = workline.middle[i];
					workline.upper[i + 1] = workline.upper[i];
					workline.topest[i + 1] = workline.topest[i];
					workline.below[i + 1] = workline.below[i];
					workline.attr[i + 1] = workline.attr[i];
					i--;
				}
				workline.middle[j] = p_char;
				workline.below[j] = ENLARGEATTR;
				workline.attr[j] = fontused;
				if ( haveblock( ) ) {
					if ( lineno == blkbegin.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
							blkbegin.column++;
						}
					}
					if ( lineno == blkend.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) < blkend.column ) {
							blkend.column++;
						}
					}
				}
			}
			break;
		case UPPER:
			i = *p_xCursorPos + firstcol;
			if ( ( workline.middle[i] >= 'ก' ) &&
				( workline.middle[i] <= 'ฮ' ) ) {
				if ( workline.below[i] == ENLARGEATTR ) {
					if ( p_char != HUNAKADMITO ) {
						workline.upper[i - 1] = p_char;
					} else {
						workline.topest[i - 1] = 0xe9;
						workline.upper[i - 1] = 0xd1;
					}
				} else {
					if ( p_char != HUNAKADMITO ) {
						workline.upper[i] = p_char;
					} else {
						workline.topest[i] = 0xe9;
						workline.upper[i] = 0xd1;
					}
				}
			} else {
				errorsound( );
			}
			break;
		case TOPEST:
			i = *p_xCursorPos + firstcol;
			if ( ( workline.middle[i] >= 'ก' ) &&
				( workline.middle[i] <= 'ฮ' ) ) {
				if ( workline.below[i] == ENLARGEATTR ) {
					workline.topest[i - 1] = p_char;
				} else {
					workline.topest[i] = p_char;
				}
			} else {
				errorsound( );
			}
			break;
		case BELOW:
			i = *p_xCursorPos + firstcol;
			if ( ( workline.middle[i] >= 'ก' ) &&
				( workline.middle[i] <= 'ฮ' ) ) {
				if ( workline.below[i] == ENLARGEATTR ) {
					workline.below[i - 1] = p_char;
				} else {
					workline.below[i] = p_char;
				}
			} else {
				errorsound( );
			}
			break;
		}
		if ( *p_xCursorPos >= ( wind.length - 2 ) ) {
			if ( whatlevel( p_char ) == MIDDLE ) {
				shiftscrn( 20, p_xCursorPos );
			}
		}
		if ( whatlevel( p_char ) == MIDDLE ) {
			if ( ( fontused & ENLARGEATTR ) == ENLARGEATTR ) {
				( *p_xCursorPos )++;
			}
			( *p_xCursorPos )++;
		}
		changeflag = YES;
		return( YES );
	} else {
		return( NO );
	}
}

void insertreturn( struct line_node *p_line, unsigned int p_col ) {
	font_attr font = NORMALATTR;
	unsigned char fontcode[9], *text;
	struct line_node *line2;
	register int i;

	i = linearcolumn( p_line->text, p_col, &font );
	findstrcode( fontcode, font );
	line2 = ( struct line_node * ) malloc( sizeof( struct line_node ) );
	line2->wrap = p_line->wrap;
#ifdef WANT_TO_USE_GRAPH
	line2->graph = NULL;
#endif
	line2->text = ( unsigned char * ) malloc( strlen( p_line->text ) + strlen( fontcode ) - i + 1 );
	strcpy( line2->text, fontcode );
	strcpy( ( line2->text ) + strlen( fontcode ), ( p_line->text ) + i );
	text = ( unsigned char * ) malloc( i + strlen( fontcode ) + 1 );
	strncpy( text, p_line->text, i );
	strcpy( text + i, fontcode );
	free( p_line->text );
	p_line->text = text;
	insert_line( p_line, line2 );
}

void insert_ret( unsigned int *p_xCursorPos ) {
	storeline( curline );
	insertreturn( curline, *p_xCursorPos + firstcol );
	curline->wrap = NO;
	if ( haveblock( ) ) {
		if ( lineno <= blkend.lineno ) {
			if ( lineno == blkend.lineno ) {
				if ( ( *p_xCursorPos + firstcol ) < blkend.column ) {
					blkend.lineno++;
					blkend.column = blkend.column - *p_xCursorPos - firstcol;
					if ( lineno == blkbegin.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
							blkbegin.lineno++;
							blkbegin.column = blkbegin.column - *p_xCursorPos - firstcol;
						}
					}
				}
			} else {
				if ( lineno <= blkbegin.lineno ) {
					if ( lineno == blkbegin.lineno ) {
						if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
							blkbegin.lineno++;
							blkbegin.column = blkbegin.column - *p_xCursorPos - firstcol;
						}
					} else {  /* so -> lineno < blkbegin.lineno */
						blkbegin.lineno++;
					}
				}
				blkend.lineno++;
			}
		}
	}
	loadtoline( curline->text );
	pagecomplete = NO;
	changeflag = YES;
}

void returnkey( unsigned int *p_xCursorPos, register unsigned int p_yCursorPos ) {
	if ( firstcol != 0 ) {
		firstcol = 0;
		pagecomplete = NO;
	}
	*p_xCursorPos = 0;
	if ( curline->next != sentinel ) {
		storeline( curline );
		lineno++;
		if ( p_yCursorPos == ( wind.width - 1 ) ) {
			if ( ( pagebreak == YES ) && ( ( ( lineno - 1 ) % lineperpage ) == 0 ) ) {
				curpage = curpage->next;
			}
			curpage = curpage->next;
			curline = curline->next;
			pagecomplete = NO;
		} else {
			if ( ( pagebreak == YES ) && ( p_yCursorPos == ( wind.width - 2 ) ) &&
				( ( ( lineno - 1 ) % lineperpage ) == 0 ) ) {
				curpage = curpage->next;
				pagecomplete = NO;
			}
			curline = curline->next;
		}
		loadtoline( curline->text );
	} else {
		errorsound( );
	}
}

void ret_with_ins( unsigned int *p_xCursorPos, unsigned int p_yCursorPos ) {
	insert_ret( p_xCursorPos );
	returnkey( p_xCursorPos, p_yCursorPos );
}

void insertmacro( unsigned char *p_macro, unsigned int *p_xCursorPos, unsigned int *p_yCursorPos ) {
	int quit = NO;
	while ( ( *p_macro != '\0' ) && ( quit == NO ) ) {
		if ( !insert_char( *p_macro, p_xCursorPos, p_yCursorPos ) ) {
			linetoolong( );
			quit = YES;
		}
		p_macro++;
	}
	refreshline( 0, *p_yCursorPos );
}

void blankmaro( int p_yPos ) {
	dispprintf( 19 + center_factor, p_yPos, REVERSEATTR, " – CTRL-F   =%37s– ", " " );
}

/* Modify by Suttpong Sat  08-05-1989  03:07:24 */
void dispmacro( register int p_macro ) {
	static unsigned char *numstr[] = {
		"1", "2", "3", "4", "5",
		"6", "7", "8", "9", "10"
	};

	blankmaro( 5 + p_macro );
	dispstrhgc( numstr[p_macro], 28 + center_factor, 5 + p_macro, REVERSEATTR );
	dispstrhgc( &macro[p_macro][0], 33 + center_factor, 5 + p_macro, REVERSEATTR );
}

void editmacro( void ) {
	register int i;
	register int c;
	pagecomplete = NO;
	framebox( 19 + center_factor, 4, ( 19 + center_factor ) + 51, 15, REVERSEATTR );
	for ( i = 0; i < 10; i++ ) {
		dispmacro( i );
	}
	dispstrhgc( "กด <ESC> เพื่อเลิกการแก้ไขคำย่อ", ( 19 + center_factor ) + 3, 15, REVERSEATTR );
	i = 0;
	for ( ;; ) {
		c = getstring( &macro[i][0], 33 + center_factor, 5 + i, 35, NORMALATTR, THAIENG );
		switch ( c ) {
		case UPKEY:
			dispmacro( i );
			if ( i == 0 ) {
				i = 9;
			} else {
				i--;
			}
			break;
		case YES:
		case DNKEY:
			dispmacro( i );
			if ( i == 9 ) {
				i = 0;
			} else {
				i++;
			}
			break;
		case ESCKEY:
			writelanguage( );
			return;
		}
	}
}
