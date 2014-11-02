/*
* ===============================================================================
* CUFSETUP.C
*
* CUFONT setup
*
* By Suttipong Kanakakorn
* Fri  08-25-1989  23:14:04
* ===============================================================================
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

#include "var.h"

#undef DEFINE_VAR

#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\grdetect.h"
#include "..\common\grphc.h"

#include "cufsetup.h"

void set_directory( void );
void usage( void );
int handler( int errval, int ax, int bp, int si );

void cufsetup( int argc, char *argv[] ) {
	register int i;
	extern int herc_align;
	extern align;

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
				/* /HL for Hercules, left-justified  */
			case 'L':
				herc_align = 0;
				align = 0;
				break;
			case 'N':
			case 'W':
			case 'P':
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
	fputs( "\t-h,  /h  Hercules graphic adapter\n", stderr );
	fputs( "\t-hl, /hl Hercules graphic adapter, left justify\n", stderr );
	fputs( "\t-v,  /v  vga\n", stderr );
	fputs( "\t-e,  /e  ega with ega display\n", stderr );
	fputs( "\t-m,  /m  ega with monochrome display\n", stderr );
	exit( 1 );
}

void set_directory( void ) {
	char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT];

	/* build cuf_dir like this -> c:\edit\cuwriter */
	fnsplit( progname, drive, dir, name, ext );
	sprintf( cuf_dir, "%s%s", drive, dir );
	cuf_dir[strlen( cuf_dir ) - 1] = '\0'; /* clear \ */
}

int handler( int errval, int ax, int bp, int si ) {
	/* char drive; */

	/* errorsound( ); */
	if ( ax >= 0 ) {
		/* drive = 'A' + ( ax & 0x00FF ); */
		savepic( );
		blockmsg( 10 );
		dispprintf( 20, 10, 2,
			"Disk error on drive %c ! กดปุ่มใดๆเพื่อทำงานต่อ",
			'A' + ( ax & 0x00FF ) );
		/* prchar( drive, REVERSEATTR, 45 - CENTER_FACTOR, 10 ); */
		ebioskey( 0 );
		retpic( );
	}
	hardretn( -1 );
}
