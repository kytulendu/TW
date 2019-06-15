/*
* ============================================================================
* DEL.C 15 JAN 89
* ============================================================================
*/

#include <stdlib.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\tutil1.h"

#include "var.h"

#include "block.h"
#include "edit.h"
#include "move.h"
#include "movement.h"

#include "del.h"

/** Delete a return. */
void del_return( void );

void delete_char( unsigned int p_xCursorPos ) {
	register size_t i = p_xCursorPos + firstcol + 1;
	size_t j = strlen( workline.middle );

	if ( i != j ) {
		if ( ( workline.attr[i] & ENLARGEATTR ) == ENLARGEATTR ) {
			for ( ; i < j; i++ ) {
				workline.middle[i] = workline.middle[i + 1];
				workline.upper[i] = workline.upper[i + 1];
				workline.topest[i] = workline.topest[i + 1];
				workline.below[i] = workline.below[i + 1];
				workline.attr[i] = workline.attr[i + 1];
			}
			if ( haveblock( ) ) {
				if ( lineno == blkbegin.lineno ) {
					if ( ( p_xCursorPos + firstcol ) < blkbegin.column ) {
						blkbegin.column--;
					}
				}
				if ( lineno == blkend.lineno ) {
					if ( ( p_xCursorPos + firstcol ) < blkend.column ) {
						blkend.column--;
					}
				}
			}
			i = p_xCursorPos + firstcol + 1;
		}
		for ( ; i < j; i++ ) {
			workline.middle[i] = workline.middle[i + 1];
			workline.upper[i] = workline.upper[i + 1];
			workline.topest[i] = workline.topest[i + 1];
			workline.below[i] = workline.below[i + 1];
			workline.attr[i] = workline.attr[i + 1];
		}
		if ( haveblock( ) ) {
			if ( lineno == blkbegin.lineno ) {
				if ( ( p_xCursorPos + firstcol ) < blkbegin.column ) {
					blkbegin.column--;
				}
			}
			if ( lineno == blkend.lineno ) {
				if ( ( p_xCursorPos + firstcol ) < blkend.column ) {
					blkend.column--;
				}
			}
		}
	} else {
		del_return( );
	}
	changeflag = YES;
}

void deletereturn( struct line_node *p_line ) {
	unsigned char *temp;
	struct line_node *linedeleted;

	if ( p_line->next != sentinel ) {
		linedeleted = p_line->next;
		temp = ( unsigned char * ) malloc( strlen( p_line->text ) + strlen( linedeleted->text ) + 1 );
		strcpy( temp, p_line->text );
		strcat( temp, linedeleted->text );
		free( p_line->text );
		p_line->text = temp;
		p_line->next = linedeleted->next;
		( linedeleted->next )->previous = p_line;
		p_line->wrap = linedeleted->wrap;
#ifdef WANT_TO_USE_GRAPH
		if ( ( linedeleted->graph != NULL ) && ( p_line->graph == NULL ) ) {
			p_line->graph = linedeleted->graph;
			linedeleted->graph = NULL;
		}
#endif
		if ( linedeleted == curline ) {
			curline = p_line;
		}
		if ( linedeleted == curpage ) {
			curpage = p_line;
		}
		free( linedeleted->text );
#ifdef WANT_TO_USE_GRAPH
		if ( linedeleted->graph != NULL ) {
			free( linedeleted->graph );
		}
#endif
		free( linedeleted );
	}
}

void del_return( void ) {
	if ( haveblock( ) ) {
		if ( lineno < blkend.lineno ) {
			if ( ( lineno + 1 ) == blkend.lineno ) {
				blkend.column = blkend.column + thaistrlen( curline->text );
			}
			blkend.lineno--;
			if ( lineno < blkbegin.lineno ) {
				if ( ( lineno + 1 ) == blkbegin.lineno ) {
					blkbegin.column = blkbegin.column + thaistrlen( curline->text );
				}
				blkbegin.lineno--;
			}
		}
	}
	storeline( curline );
	deletereturn( curline );
	loadtoline( curline->text );
	pagecomplete = NO;
	changeflag = YES;
}

void backspace( unsigned int *p_xCursorPos ) {
	register size_t i;
	boolean enlargeflag = NO;

	i = *p_xCursorPos + firstcol;
	if ( i > 0 ) {	/* begin of line ? */
		if ( workline.below[i] == ENLARGEATTR ) {
			enlargeflag = YES;
			if ( ( workline.topest[i - 1] == ' ' ) &&
				( workline.upper[i - 1] == ' ' ) &&
				( workline.below[i - 1] == ' ' ) ) {
				while ( i < MAXCOL ) {
					workline.middle[i] = workline.middle[i + 1];
					workline.upper[i] = workline.upper[i + 1];
					workline.topest[i] = workline.topest[i + 1];
					workline.below[i] = workline.below[i + 1];
					workline.attr[i] = workline.attr[i + 1];
					i++;
				}
			}
			if ( haveblock( ) ) {
				if ( lineno == blkbegin.lineno ) {
					if ( ( *p_xCursorPos + firstcol ) <= blkbegin.column ) {
						blkbegin.column--;
					}
				}
				if ( lineno == blkend.lineno ) {
					if ( ( *p_xCursorPos + firstcol ) <= blkend.column ) {
						blkend.column--;
					}
				}
			}
			i = *p_xCursorPos + firstcol - 1;
		}
		if ( workline.topest[i] != ' ' ) {
			workline.topest[i] = ' ';
		} else if ( workline.upper[i] != ' ' ) {
			workline.upper[i] = ' ';
		} else if ( workline.below[i] != ' ' ) {
			workline.below[i] = ' ';
		} else {
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
					if ( ( *p_xCursorPos + firstcol ) <= blkend.column ) {
						blkend.column--;
					}
				}
			}
			if ( enlargeflag != YES ) {
				if ( *p_xCursorPos > 0 ) {
					( *p_xCursorPos )--;
				} else {
					firstcol--;
					storeline( curline );
					pagecomplete = NO;
				}
			} else {
				if ( *p_xCursorPos >= 2 ) {
					*p_xCursorPos = *p_xCursorPos - 2;
				} else {
					firstcol = firstcol - 2;
					storeline( curline );
					pagecomplete = NO;
				}
			}
		}
	} else {
		if ( lineno != 1 ) {
			cursor_up( );
			endline( p_xCursorPos );
			del_return( );
		}
	}
	changeflag = YES;
}

void delete_word( unsigned int p_xCursorPos ) {
	size_t i;

	i = p_xCursorPos + firstcol + 1;
	if ( workline.middle[i] != '\0' ) {
		if ( ( workline.middle[i] != ' ' ) && ( workline.middle[i] != WRAPBLANK ) ) {
			while ( ( workline.middle[i] != ' ' ) && ( workline.middle[i] != WRAPBLANK ) && ( workline.middle[i] != '\0' ) ) {
				delete_char( p_xCursorPos );
			}
		} else {
			while ( ( workline.middle[i] == ' ' ) || ( workline.middle[i] == WRAPBLANK ) ) {
				delete_char( p_xCursorPos );
			}
		}
	} else {
		del_return( );
	}
}

void deltoendline( unsigned int p_xCursorPos, unsigned int p_yCursorPos ) {
	register size_t i = MAXCOL + 1;
	size_t j = p_xCursorPos + firstcol + 1;

	while ( i <= j ) {
		workline.topest[i] = ' ';
		workline.upper[i] = ' ';
		workline.middle[i] = ' ';
		workline.below[i] = ' ';
		workline.attr[i] = 0x00;
		i--;
	}
	workline.middle[j] = '\0';
	refreshline( p_xCursorPos, p_yCursorPos );
	changeflag = YES;
}

void deleteline( struct line_node *p_line ) {
	if ( p_line->next != sentinel ) {
		if ( curline == p_line ) {
			curline = curline->next;
			loadtoline( curline->text );
		}
		if ( curpage == p_line ) {
			curpage = curpage->next;
		}
		( p_line->previous )->next = p_line->next;
		( p_line->next )->previous = p_line->previous;
		free( p_line->text );
#ifdef WANT_TO_USE_GRAPH
		if ( p_line->graph != NULL ) {
			free( p_line->graph );
		}
#endif
		free( p_line );
	} else {
		free( p_line->text );
#ifdef WANT_TO_USE_GRAPH
		if ( p_line->graph != NULL ) {
			free( p_line->graph );
		}
#endif
		p_line->text = ( unsigned char * ) malloc( 1 );
		*( p_line->text ) = '\0';
		if ( curline == p_line ) {
			loadtoline( curline->text );
		}
	}
}

void delete_line( void ) {
	if ( haveblock( ) ) {
		if ( lineno < blkend.lineno ) {
			if ( lineno < blkbegin.lineno ) {
				blkbegin.lineno--;
			} else {
				if ( lineno == blkbegin.lineno ) {
					blkbegin.column = 0;
				}
			}
			blkend.lineno--;
		} else {
			if ( lineno == blkend.lineno ) {
				blkend.column = 0;
			}
		}
	}
	deleteline( curline );
	pagecomplete = NO;
	changeflag = YES;
}
