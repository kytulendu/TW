/*
* ============================================================================
* WRAP.C
*
* Updated: Suttipong Kanakakorn
*          Thu  08-03-1989  01:05:26
* ============================================================================
*/

#include <stdlib.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\common.h"
#include "..\common\cscrn.h"
#include "..\common\tutil1.h"

#include "var.h"

#include "edit.h"
#include "ins.h"
#include "move.h"
#include "movement.h"

#include "thaisyls\mainsyls.h"

#include "wrap.h"

void justify_right( void ) {
	register size_t count;
	register size_t i;
	register size_t j;
	register size_t k;
	boolean already = NO;
	for ( i = strlen( workline.middle ) - 1;
		( ( workline.middle[i] == ' ' ) || ( workline.middle[i] == WRAPBLANK ) ) &&
		( i > 0 );
		i-- );
	if ( ( i < rightmar ) && ( i > 0 ) ) {
		for ( j = 1;
			( workline.middle[j] == ' ' ) || ( workline.middle[j] == WRAPBLANK );
			j++ );
		k = j;
		count = rightmar - i;
		while ( count > 0 ) {
			while ( ( k < i ) && ( workline.middle[k] != ' ' ) &&
				( workline.middle[k] != WRAPBLANK ) ) {
				k++;
			}
			if ( k < i ) {
				insertblank( k, WRAPBLANK );
				count--;
				i++;
				already = YES;
			}
			while ( ( ( workline.middle[k] == ' ' ) || ( workline.middle[k] == WRAPBLANK ) )
				&& ( k < i ) ) {
				k++;
			}
			if ( k >= i ) {
				if ( already == NO ) {
					return;
				}
				k = j;
			}
		}
	}
}

void reform( void ) {
	struct line_node *templine;
	struct line_node *firstline;
	struct line_node *freeline;
	unsigned char *temp1;
	unsigned char *temp2;
	unsigned char *temp3;
	unsigned char *cuthere;
	unsigned int i;
	unsigned int j;
	font_attr font = NORMALATTR;
	unsigned char fontcode[9];

	storeline( curline );
	firstline = curline;
	templine = firstline;	/* start to concatenate all lines to one line only */
	temp1 = ( unsigned char * ) malloc( 1 );
	*temp1 = '\0';
	for ( ;; ) {
		temp2 = ( unsigned char * ) malloc( strlen( templine->text ) + 1 );
		i = 0;
		j = 0;
		while ( templine->text[i] != '\0' ) {
			if ( templine->text[i] != WRAPBLANK ) {
				temp2[j] = templine->text[i];
				j++;
			}
			i++;
		}
		temp2[j] = '\0';
		temp3 = ( unsigned char * ) malloc( strlen( temp1 ) + strlen( temp2 ) + 1 );
		strcpy( temp3, temp1 );
		strcat( temp3, temp2 );
		free( temp1 );
		free( temp2 );
		if ( templine->wrap == NO ) {
			break;
		}
		temp1 = temp3;
		templine = templine->next;
	}
	/* now paragraph is in the one line only pointed by temp3 */
	/* so we will compress two or more blanks to one blank only */
	compress_blank( temp3 );

	templine->previous = firstline->previous;
	( templine->previous )->next = templine;
	free( templine->text );
	templine->text = temp3;
	if ( curline == curpage ) {
		curpage = templine;
	}
	curline = templine;
	while ( firstline != templine ) {
		freeline = firstline;
		firstline = firstline->next;
		free( freeline->text );
#ifdef WANT_TO_USE_GRAPH
		if ( freeline->graph != NULL ) {
			free( freeline->graph );
		}
#endif
		free( freeline );
	}
	while ( thaistrlen( curline->text ) > ( rightmar - leftmar + 1 ) ) {
		i = rightmar - leftmar;   /*   + 1;   */
		temp1 = curline->text;
		while ( ( i != 0 ) && ( *temp1 != '\0' ) ) {
			for ( temp1++; whatlevel( *temp1 ) != MIDDLE; temp1++ );
			i--;
		}
		temp3 = temp1;
		for ( i = 10; ( i != 0 ) && ( *temp3 != '\0' ); i-- ) {
			temp3++;
		}
		cuthere = FINDCUT( curline->text, temp3, temp1 );
		cuthere++;
		font = 0;
		for ( temp1 = curline->text; temp1 != cuthere; temp1++ ) {
			if ( *temp1 < 32 ) {
				togglefont( &font, *temp1 );
			}
		}
		findstrcode( fontcode, font );
		templine = ( struct line_node * ) malloc( sizeof( struct line_node ) );
		templine->text = ( unsigned char * ) malloc( strlen( fontcode ) + strlen( cuthere ) + 1 );
		templine->wrap = NO;
#ifdef WANT_TO_USE_GRAPH
		templine->graph = NULL;
#endif
		strcpy( templine->text, fontcode );
		strcat( templine->text, cuthere );
		*cuthere = '\0';
		temp3 = ( unsigned char * ) malloc( leftmar + strlen( curline->text ) + strlen( fontcode ) );
		i = 0;
		while ( i != ( leftmar - 1 ) ) {
			temp3[i] = WRAPBLANK;
			i++;
		}
		temp3[i] = '\0';
		strcat( temp3, curline->text );
		strcat( temp3, fontcode );
		free( curline->text );
		curline->text = temp3;
		templine->next = curline->next;
		( curline->next )->previous = templine;
		templine->previous = curline;
		curline->next = templine;
		curline->wrap = YES;
		loadtoline( curline->text );
		justify_right( );
		storeline( curline );
		curline = curline->next;
	}
	temp3 = ( unsigned char * ) malloc( strlen( curline->text ) + leftmar );
	i = 0;
	while ( i != ( leftmar - 1 ) ) {
		temp3[i] = WRAPBLANK;
		i++;
	}
	temp3[i] = '\0';
	strcat( temp3, curline->text );
	free( curline->text );
	curline->text = temp3;
	if ( curline->next != sentinel ) {
		curline = curline->next;
	}
	lineno = findlineno( curline );
	loadtoline( curline->text );
	while ( findrow( ) > ( wind.width - 1 ) ) {
		curpage = curpage->next;
	}
	changeflag = YES;
	pagecomplete = NO;
	blkbegin.lineno = 1;
	blkend.lineno = 1;
	blkbegin.column = 0;
	blkend.column = 0;
}

void manualwrap( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos ) {
	size_t i;
	insert_ret( p_xCursorPos );
	curline->wrap = YES;
	*p_xCursorPos = ( leftmar - 1 ) + ( *p_xCursorPos - thaistrlen( curline->text ) );
	justify_right( );
	*p_yCursorPos = findrow( );
	cursor_down( *p_yCursorPos );
	for ( i = 1; i != leftmar; i++ ) {
		workline.middle[i] = WRAPBLANK;
	}
}

void autowrap( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos ) {
	unsigned int i, j, already = NO, diff;
	unsigned char *temp1, *temp3, *cuthere, fontcode[9];
	font_attr font = NORMALATTR;
	struct line_node *templine;

	storeline( curline );
	diff = strlen( workline.middle ) - ( *p_xCursorPos + firstcol + 1 );
	i = 0;
	j = 0;
	while ( curline->text[i] != '\0' ) {
		if ( curline->text[i] != WRAPBLANK ) {
			curline->text[j] = curline->text[i];
			j++;
			already = YES;
		} else {
			if ( already == NO ) {
				curline->text[j] = curline->text[i];
				j++;
			}
		}
		i++;
	}
	curline->text[j] = '\0';
	temp1 = curline->text;
	for ( i = rightmar - 2; ( i > 0 ) && ( *temp1 != '\0' ); i-- ) {
		temp1++;
		while ( whatlevel( *temp1 ) != MIDDLE ) {
			temp1++;
		}
	}
	temp3 = temp1;
	for ( i = 10; ( i != 0 ) && ( *temp3 != '\0' ); i-- ) {
		temp3++;
	}
	cuthere = FINDCUT( curline->text, temp3, temp1 );
	cuthere++;
	for ( temp1 = curline->text; temp1 != cuthere; temp1++ ) {
		if ( *temp1 < 32 ) {
			togglefont( &font, *temp1 );
		}
	}
	findstrcode( fontcode, font );
	templine = ( struct line_node * ) malloc( sizeof( struct line_node ) );
	templine->text = ( unsigned char * ) malloc( leftmar + strlen( fontcode ) + strlen( cuthere ) );
	for ( i = 0; i != ( leftmar - 1 ); i++ ) {
		templine->text[i] = WRAPBLANK;
	}
	templine->text[i] = '\0';
	strcat( templine->text, fontcode );
	strcat( templine->text, cuthere );
#ifdef WANT_TO_USE_GRAPH
	templine->graph = NULL;
#endif
	templine->wrap = ( curline->next )->wrap;
	*cuthere = '\0';
	temp3 = ( unsigned char * ) malloc( strlen( curline->text ) + strlen( fontcode ) + 1 );
	strcpy( temp3, curline->text );
	strcat( temp3, fontcode );
	free( curline->text );
	curline->text = temp3;
	templine->next = curline->next;
	( curline->next )->previous = templine;
	templine->previous = curline;
	curline->next = templine;
	curline->wrap = YES;
	loadtoline( curline->text );
	justify_right( );
	*p_yCursorPos = findrow( );
	cursor_down( *p_yCursorPos );
	firstcol = 0;
	gocol( strlen( workline.middle ) - 1 - diff, p_xCursorPos );
	pagecomplete = NO;
}

void compress_blank( register unsigned char *p_string ) {
	register unsigned char *r;

	for ( ; *p_string == ' '; p_string++ );
	r = p_string;
	while ( *p_string++ = *r ) {
		if ( *r == ' ' ) {
			for ( ; *r == ' '; r++ );
		} else {
			r++;
		}
	}
	p_string -= 2;
	if ( *p_string == ' ' ) {
		*p_string = '\0';
	}
}
