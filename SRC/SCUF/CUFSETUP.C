/*
* ============================================================================
* CUFSETUP.C
*
* CUFONT setup
*
* By Suttipong Kanakakorn
* Fri  08-25-1989  23:14:04
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <dir.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>

#include "..\common\cwtype.h"

#define DEFINE_VAR 1

#include "..\common\var.h"
#include "var.h"

#undef DEFINE_VAR

#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\grdetect.h"

#include "cufsetup.h"

void set_directory( void );
void usage( void );

void cufsetup( int argc, char *argv[] ) {
	register int i;

	progname = argv[0];

	while ( ( --argc > 0 ) && ( ( i = ( *++argv )[0] ) == '/' || i == '-' ) ) {
		strupr( ++argv[0] );
		while ( i = *( argv[0]++ ) )
			switch ( i ) {
			case 'H':
				scrmode = HERCMONO;
				break;
				/* e alone = ega, em = ega monochrome */
			case 'E':
				scrmode = EGA;
				break;
				/* m alone = mcga */
			case 'M':
				if ( scrmode == EGA ) {
					scrmode = EGAMONO;
				} else {
					scrmode = MCGA;
				}
				break;
			case 'V':
				scrmode = VGA;
				break;
			case 'A':
				scrmode = ATT400;
				break;
			case 'C':
				herc_align = 5;
				break;
			default:
				usage( );
		}
	}

	set_directory( );
	readscrfont( dfont, "NORMAL.FON", cuf_dir );
	harderr( handler );
}

void usage( void ) {
	fputs( "Usage: TWFONT.EXE [option]\n", stderr );
	fputs( "Options:\n", stderr );
	fputs( "\t-h,  /h  Hercules Graphic Card.\n", stderr );
	fputs( "\t-hc, /hc Hercules Graphic Card, 80 column.\n", stderr );
	fputs( "\t-v,  /v  VGA.\n", stderr );
	fputs( "\t-e,  /e  EGA with EGA display.\n", stderr );
	fputs( "\t-em, /em EGA with Monochrome display.\n", stderr );
	fputs( "\t-m,  /m  MCGA.\n", stderr );
	fputs( "\t-a,  /a  AT&T400.\n", stderr );
	exit( EXIT_FAILURE );
}

void set_directory( void ) {
	char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT];

	/* build cuf_dir like this -> c:\edit\cuwriter */
	fnsplit( progname, drive, dir, name, ext );
	sprintf( cuf_dir, "%s%s", drive, dir );
	cuf_dir[strlen( cuf_dir ) - 1] = '\0'; /* clear \ */
}
