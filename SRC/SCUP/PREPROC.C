/*
* ============================================================================
* PREPROC.C
*
* Modified: Suttipong Kanakakorn
* Tue  08-15-1989  00:10:21
*  - Search for printer font easier
* ============================================================================
*/

#include <alloc.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "..\common\cwtype.h"

#include "24pins.h"
#include "error.h"
#include "global.h"

#include "preproc.h"

void cp_init_textbuf( ) {
	cp_buf.uppest = ( unsigned char * ) malloc( CP_MAX_TEXTBUF );
	if ( cp_buf.uppest == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	cp_buf.upper = ( unsigned char * ) malloc( CP_MAX_TEXTBUF );
	if ( cp_buf.upper == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	cp_buf.middle = ( unsigned char * ) malloc( CP_MAX_TEXTBUF );
	if ( cp_buf.middle == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	cp_buf.lower = ( unsigned char * ) malloc( CP_MAX_TEXTBUF );
	if ( cp_buf.lower == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	/* clear attribute of text character */
	cp_control = 0;
}

void cp_init_grpbuf( ) {
	cp_lqbuf.upper = ( FONT * ) malloc( CP_LQ_MAXPRBUF );
	if ( cp_lqbuf.upper == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	cp_lqbuf.middle = ( FONT * ) malloc( CP_LQ_MAXPRBUF );
	if ( cp_lqbuf.middle == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	cp_lqbuf.lower = ( FONT * ) malloc( CP_LQ_MAXPRBUF );
	if ( cp_lqbuf.lower == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}

	cp_lqbuf.extbar = ( FONT * ) malloc( CP_LQ_MAXPRBUF );
	if ( cp_lqbuf.extbar == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}
}

void cp_combine_fontlq( FONT *p_combcode, FONT *p_sara, FONT *p_wannayok ) {
	int index;

	/* copy wannayok to combcode */
	memcpy( p_combcode, ( ( char * ) p_wannayok ) + 1, CP_LQ_FONTSIZE );

	/* clear byte #2 in every column */
	for ( index = 0; index < CP_LQCOL; index++ ) {
		p_combcode->font[index][2] = 0;
	}
	/* COMBINE SARA AND COMBCODE */
	for ( index = 0; index < CP_LQ_FONTSIZE; index++ ) {
		p_combcode->font[0][index] |= p_sara->font[0][index];
	}
}

FONT *cp_create_lqcombine( FONT *p_fntable ) {
	int x, y;												/* index to lq combine code table */
	int index;												/* index to address in lq combine */
	static unsigned char *sara = "—”‘’÷◊";					/* sara set */
	static unsigned char *wannayok = "ËÈÍÎÏ";				/* wannayok */
	FONT *fontptr;											/* font pointer */

	fontptr = ( FONT * ) malloc( CP_LQCOMB_TABSIZE );
	for ( x = 0; x < 6; x++ ) {
		for ( y = 0; y < 5; y++ ) {
			index = 5 * x + y;
			cp_combine_fontlq( fontptr + index,
				cp_lq_font( p_fntable, sara[x] ),
				cp_lq_font( p_fntable, wannayok[y] ) );
		};
	};
	return ( fontptr );
}

FONTSCR *cp_loadfont_lqscr( char *p_filename ) {
	FONTSCR *p;
	int  fd;

	p = ( FONTSCR * ) malloc( CP_LQSCR_TABSIZE );
	if ( p == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}
	fd = open( p_filename, O_RDONLY | O_BINARY );
	if ( fd < 0 ) {
		execerror( "Printer font file not found : ", p_filename );
	}
	read( fd, p, CP_LQSCR_TABSIZE );
	close( fd );
	return ( p );
}

void cp_combine_fontlqscr( FONTSCR *p_combcode, FONTSCR *p_sara, FONTSCR *p_wannayok ) {
	int index;

	/* clear combcode */
	memset( p_combcode, 0, CP_LQSCR_FONTSIZE );

	/* combine sara and wannayok with shifting up wannayok 6 bits
	and or with sara */
	for ( index = 0; index < CP_LQCOL; index++ ) {
		p_combcode->font[index][0] = 0x0F & ( ( p_wannayok->font[index][1] >> 3 ) | ( p_sara->font[index][0] ) );
		p_combcode->font[index][1] = ( ( p_wannayok->font[index][1] << 5 ) | ( p_sara->font[index][1] ) );
	};
}

FONTSCR *cp_create_lqscrcombine( FONTSCR *p_fntable ) {
	int x;
	int y;												/* index to lq combine code table */
	static unsigned char *sara = "—”‘’÷◊";					/* sara set */
	static unsigned char *wannayok = "ËÈÍÎÏ";				/* wannayok */
	int index;												/* index to address in lq combine */
	FONTSCR *fontptr;										/* font pointer */

	fontptr = ( FONTSCR * ) malloc( CP_LQSCRCOMB_TABSIZE );
	for ( x = 0; x < 6; x++ ) {
		for ( y = 0; y < 5; y++ ) {
			index = 5 * x + y;
			cp_combine_fontlqscr( fontptr + index,
				cp_lqscr_font( p_fntable, sara[x] ),
				cp_lqscr_font( p_fntable, wannayok[y] ) );
		};
	};
	return ( fontptr );
}
