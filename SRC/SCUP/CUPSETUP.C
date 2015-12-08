/*
* ============================================================================
* CUPSETU.C
*
* Written: Suttipong Kanakakorn
* Fri  08-11-1989  01:56:46
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <dir.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\grdetect.h"
#include "..\common\kbdcode.h"

#include "global.h"

#include "24pins.h"
#include "cuptype.h"
#include "error.h"
#include "prtutil.h"

#include "cupsetup.h"

void cupsetup( int argc, char *argv[] ) {
	register int i;

	progname = argv[0];

	while ( ( --argc > 0 ) && ( ( i = ( *++argv )[0] ) == '/' || i == '-' ) ) {
		strupr( ++argv[0] );
		while ( i = *( argv[0]++ ) ) {
			switch ( i ) {
			case 'H':
				scrmode = HERCMONO;
				break;

			case 'E':/* e alone = ega, em = ega monochrome */
				scrmode = EGA;
				break;

			case 'M':/* m alone = mcga */
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
			case 'C':/* /HC for Hercules, 80 column */
				herc_align = 5;
				break;
			case 'N':
			case 'W':
			case 'P':
				break;
			default:  usage( );
			}
		}
	}

	if ( argc >= 1 && ( file_exist( argv[0] ) ||
		strchr( argv[0], '*' ) || strchr( argv[0], '?' ) ) ) {
		placekey( RETKEY );
		while ( i = *argv[0]++ ) {
			placekey( i );
		}
		placekey( RETKEY );
	}

	set_directory( );
	readoption( AUTO_FIND );
	readscrfont( dfont, "NORMAL.FON", cup_dir );
	readscrfont( ditalicfont, "ITALIC.FON", cup_dir );

	harderr( handler );
	filename[0] = '\0';
}

void usage( void ) {
	fputs( "Usage: TWPRINT [option] [file]\n", stderr );
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

	/* build cup_dir like this -> c:\edit\cuwriter */
	fnsplit( progname, drive, dir, name, ext );
	sprintf( cup_dir, "%s%s", drive, dir );
	cup_dir[strlen( cup_dir ) - 1] = '\0'; /* clear \ */
}

typedef struct each_option_setup {
	char *option_name;
	void *p_option_value;
} each_option_setup;

each_option_setup option_setup[] = {
	{ "graphicprint", &graphicprint },
	{ "prtcodestd", &prtcodestd },
	{ "character/inch", &cpi },
	{ "userlineperpage", &userlineperpage },
	{ "pagelength", &pagelength },
	{ "leftmargin", &leftmargin },
	{ "rightmargin", &rightmargin },
	{ "locpagetitle", &locpagetitle },
	{ "locheading", &locheading },
	{ "locfooting", &locfooting },
	{ "printer", &printer },
	{ "printer24pin", &printer24pin },
	{ "maxcol", &maxcol },
	{ "maxdot", &maxdot },
	{ "maxbuffer", &maxbuffer },
	{ "nlqmode", &nlqmode },
	{ "pagebreak", &pagebreak },
	{ "pagebegin", &pagebegin },
	{ "pageend", &pageend },
	{ "pagenumberoffset", &pagenumberoffset },
	{ "copytoprint", &copytoprint },
	{ "stdcode", &stdcode },
	{ "smallpaper", &smallpaper },
	{ NULL, NULL },
	{ "pagetitle", pagetitle },
	{ "pageformat", pageformat },
	{ "heading", heading },
	{ "footing", footing },
	{ NULL, NULL }
};

/* number of element of option_setup */
#define NELEM_OPTION (sizeof(option_setup)/sizeof(option_setup[0]))

void readoption( search_file_mode mode ) {
	FILE *fp;
	char fname[MAXPATH];
	int  field, temp;
	char opname[25];
	char tstr[60];
	each_option_setup *op;

	set_all_lineperpage( BATCH );

	sprintf( fname, "%s\\TWPRINT.CFG", cup_dir );
	if ( mode == CUR_DIR || mode == AUTO_FIND ) {
		fp = fopen( "TWPRINT.CFG", "rt" );
	} else {
		fp = fopen( fname, "rt" );
	}
	if ( fp == NULL && mode == AUTO_FIND ) {
		/* fopen file not success */
		/* continue searching in cup_dir */
		if ( ( fp = fopen( fname, "rt" ) ) == NULL ) {
			return; /* if not found in both dir use default value */
		}
	}
	if ( fp == NULL ) {
		showerrno( );
		return;
	}
	/* If we reach here we succesfully open cw.cfg file */
	for ( op = option_setup; op->option_name != NULL; op++ ) {
		field = fscanf( fp, "%s %d", opname, &temp );
		if ( field == 2 ) { /* succesfully scan */
			*( int * ) op->p_option_value = temp;
		} else {
			break;
		}
	}
	for ( op++; op->option_name != NULL; op++ ) {
		fscanf( fp, "%s", opname ); /* get option name */
		fgets( tstr, 60, fp );      /* get the rest */
		if ( tstr[0] ) {
			tstr[strlen( tstr ) - 1] = '\0'; /* delete \n */
			strcpy( op->p_option_value, tstr + 1 ); /* skip first blank */
		}
	}
	fclose( fp );

	set_all_lineperpage( BATCH );
}

void saveoption( search_file_mode mode ) {
	FILE *fp;
	char config_file[MAXPATH];
	each_option_setup *op;

	if ( mode == CUR_DIR || mode == AUTO_FIND ) {
		fp = fopen( "TWPRINT.CFG", "wt" );
	} else {
		sprintf( config_file, "%s\\TWPRINT.CFG", cup_dir );
		fp = fopen( config_file, "wt" );
	}
	if ( fp == NULL ) {
		return;
	}
	for ( op = option_setup; op->option_name != NULL; op++ ) {
		fprintf( fp, "%s %d\n", op->option_name, *( int * ) op->p_option_value );
	}
	for ( op++; op->option_name != NULL; op++ ) {
		fprintf( fp, "%s %s\n", op->option_name, ( char * ) op->p_option_value );
	}
	fprintf( fp, "\n" );
	fclose( fp );
}

void *cp_loadfont( char *fname, unsigned font_size ) {
	void *p;
	int handle;
	char fn[80];

	p = ( void * ) malloc( font_size );
	if ( p == NULL ) {
		execerror( "Insufficient memory\n", "" );
	}
	if ( ( handle = open( fname, O_RDONLY | O_BINARY ) ) == -1 ) {
		sprintf( fn, "%s\\%s", cup_dir, fname );
		handle = open( fn, O_RDONLY | O_BINARY );
	}
	if ( handle != -1 ) {
		read( handle, p, font_size );
		close( handle );
	} else {
		execerror( "Printer font file not found : ", fname );
	}
	return ( p );
}
