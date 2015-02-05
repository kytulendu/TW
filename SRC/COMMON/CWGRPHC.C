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
*           Add egamono mode
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#include "cwtype.h"
#include "common.h"
#include "grdetect.h"

#define DEFINE_VAR

#include "cwgrphc.h"

void prchar( unsigned char p_char, unsigned int p_attr, unsigned int x, unsigned int y ) {
	( *prchar_ptr )( p_char, p_attr, x, y );
}

void prblank( unsigned int x, unsigned int y ) {
	( *prblank_ptr )( x, y );
}

void setcurpos( unsigned int x, unsigned int y, int p_thaimode ) {
	( *setcurpos_ptr )( x, y, p_thaimode );
}

void plot( unsigned int x, unsigned int y ) {
	( *plot_ptr )( x, y );
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
	if ( ( screen_buffptr = malloc( ( unsigned int ) 32768L ) ) == NULL ) {
		fputs( "Not enough memory\n", stderr );
		exit( 1 );
	}

	if ( scrmode == DETECT ) {
		graph_detecthardware( ( graphics_hardware * ) &scrmode );
	}

#ifdef EDA_VERSION
	if ( scrmode == EGAMONO ) {
		scrmode = HERCMONO;
	}
#endif
	if ( scrmode == CGA ) {
		scrmode = ATT400;
	}

	switch ( scrmode ) {
	case EGA:
	case EGAMONO:
	case EGA64:
	/* MCGA here because current VGA use 640x480 monochrome graphic mode */
	case MCGA:
	case VGA:
		prchar_ptr = eprchar;
		prblank_ptr = eprblank;
		setcurpos_ptr = esetcurpos;
		plot_ptr = eplot;
		setgraph_ptr = esetgraph;
		settext_ptr = esettext;
		savepic_ptr = esavepic;
		retpic_ptr = eretpic;
		clsall_ptr = eclsall;
		clsgraph_ptr = eclsgraph;
		clrline_ptr = eclrline;
		prakeaw_ptr = eprakeaw;
		putwind_ptr = eputwind;
		getwind_ptr = egetwind;
		break;

	case HERCMONO:
		prchar_ptr = hprchar;
		prblank_ptr = hprblank;
		setcurpos_ptr = hsetcurpos;
		plot_ptr = hplot;
		setgraph_ptr = hsetgraph;
		settext_ptr = hsettext;
		savepic_ptr = hsavepic;
		retpic_ptr = hretpic;
		clsall_ptr = hclsall;
		clsgraph_ptr = hclsgraph;
		clrline_ptr = hclrline;
		prakeaw_ptr = hprakeaw;
		putwind_ptr = hputwind;
		getwind_ptr = hgetwind;
		break;

	case ATT400:
		prchar_ptr = aprchar;
		prblank_ptr = aprblank;
		setcurpos_ptr = asetcurpos;
		plot_ptr = aplot;
		setgraph_ptr = asetgraph;
		settext_ptr = asettext;
		savepic_ptr = asavepic;
		retpic_ptr = aretpic;
		clsall_ptr = aclsall;
		clsgraph_ptr = aclsgraph;
		clrline_ptr = aclrline;
		prakeaw_ptr = aprakeaw;
		putwind_ptr = aputwind;
		getwind_ptr = agetwind;
		break;

	default:
		fputs( "This software run on Hercules/EGA/VGA/MCGA/AT&T display card only.", stderr );
		exit( 1 );
	}
	( *setgraph_ptr )( );
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

void clsgraph( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 ) {
	( *clsgraph_ptr )( x1, y1, x2, y2 );
}

void clrline( unsigned int x1, unsigned int y1, unsigned int x2 ) {
	( *clrline_ptr )( x1, y1, x2 );
}

void prakeaw( ) {
	( *prakeaw_ptr )( );
}
