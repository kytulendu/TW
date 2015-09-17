/*
* ============================================================================
* Graphics module for CW 1.20
*
* Kraisorn Liansee
* Date    : 04/21/89
* Updated : 04/21/89
*
* Suttipong Kanakakorn
* Updated : Sun  07-30-1989  17:46:05
*         : Tue  08-15-1989  02:09:46
*           Use macro instead of function call
*         : Tue  08-22-1989  02:01:28
*           Add EGAMONO mode
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#include "cwtype.h"
#include "common.h"
#include "grdetect.h"

#define DEFINE_VAR 1

#include "cwgrphc.h"

#undef DEFINE_VAR

void prchar( unsigned char p_char, int p_attr, int p_x, int p_y ) {
	( *prchar_ptr )( p_char, p_attr, p_x, p_y );
}

void prblank( int p_x, int p_y ) {
	( *prblank_ptr )( p_x, p_y );
}

void setcurpos( int p_x, int p_y, int p_thaimode ) {
	( *setcurpos_ptr )( p_x, p_y, p_thaimode );
}

void _putpixel( int p_x, int p_y ) {
	( *putpixel_ptr )( p_x, p_y );
}

void settext( ) {
	( *settext_ptr )( );
}

void savepic( ) {
	( *savepic_ptr )( );
}

void retpic( ) {
	( *retpic_ptr )( );
}

void clsall( ) {
	( *clsall_ptr )( );
}

void clsgraph( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd ) {
	( *clsgraph_ptr )( p_xStart, p_yStart, p_xEnd, p_yEnd );
}

void clrline( int x1, int y1, int x2 ) {
	( *clrline_ptr )( x1, y1, x2 );
}

void prakeaw( ) {
	( *prakeaw_ptr )( );
}

void setgraph( ) {
	static int first = 1;

	if ( !first ) {
		( *setgraph_ptr )( );
		return;
	}

	first = 0;
#ifdef EDA_VERSION
	scrmode = DETECT;
#endif
	if ( ( screen_buffptr = malloc( ( size_t ) 38400L ) ) == NULL ) {
		fputs( "Not enough memory\n", stderr );
		exit( EXIT_FAILURE );
	}

	if ( scrmode == DETECT ) {
		graph_detecthardware( ( graphics_hardware * ) &scrmode );
	}

#ifdef EDA_VERSION
	if ( scrmode == EGAMONO ) {
		scrmode = HERCMONO;
	}
#endif

	switch ( scrmode ) {
	case EGA:
	case EGAMONO:
	case EGA64:
	/* MCGA here because current VGA use 640x480 monochrome graphic mode */
	case MCGA:
	case VGA:
		prchar_ptr = ega_prchar;
		prblank_ptr = ega_blank;
		setcurpos_ptr = ega_setcurpos;
		putpixel_ptr = ega_putpixel;
		setgraph_ptr = ega_setgraph;
		settext_ptr = ega_settext;
		savepic_ptr = ega_savepic;
		retpic_ptr = ega_retpic;
		clsall_ptr = ega_clsall;
		clsgraph_ptr = ega_clsgraph;
		clrline_ptr = ega_clrline;
		prakeaw_ptr = ega_prakeaw;
		putwind_ptr = ega_putwind;
		getwind_ptr = ega_getwind;
		break;

	case HERCMONO:
		shrink_factor = 10;
		center_factor = 5;

		prchar_ptr = herc_prchar;
		prblank_ptr = herc_prblank;
		setcurpos_ptr = herc_setcurpos;
		putpixel_ptr = herc_putpixel;
		setgraph_ptr = herc_setgraph;
		settext_ptr = herc_settext;
		savepic_ptr = herc_savepic;
		retpic_ptr = herc_retpic;
		clsall_ptr = herc_clsall;
		clsgraph_ptr = herc_clsgraph;
		clrline_ptr = herc_clrline;
		prakeaw_ptr = herc_prakeaw;
		putwind_ptr = herc_putwind;
		getwind_ptr = herc_getwind;
		break;

	case ATT400:
		prchar_ptr = att_prchar;
		prblank_ptr = att_prblank;
		setcurpos_ptr = att_setcurpos;
		putpixel_ptr = att_putpixel;
		setgraph_ptr = att_setgraph;
		settext_ptr = att_settext;
		savepic_ptr = att_savepic;
		retpic_ptr = att_retpic;
		clsall_ptr = att_clsall;
		clsgraph_ptr = att_clsgraph;
		clrline_ptr = att_clrline;
		prakeaw_ptr = att_prakeaw;
		putwind_ptr = att_putwind;
		getwind_ptr = att_getwind;
		break;

	default:
		fputs( "This software run on Hercules/EGA/VGA/MCGA/AT&T display card only.", stderr );
		exit( EXIT_FAILURE );
	}
	( *setgraph_ptr )( );
}
