/*
* ============================================================================
* FILEUTIL.C
*
* Written: Suttipong Kanakakorn
* Updated: Sun  08-27-1989  22:40:12
* ============================================================================
*/

#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <dir.h>
#include <stdio.h>
#include <stdlib.h>

#include "cwtype.h"
#include "cwgrphc.h"

#include "cscrn.h"
#include "ekbd.h"
#include "sound.h"

boolean file_exist( char *p_filename ) {
	FILE* fd = fopen( p_filename, "rb" );
	if ( !fd ) {
		return NO;
	} else {
		fclose( fd );
		return YES;
	}
}

search_file_mode find_file( char *p_filename, char *search_path ) {
	struct ffblk ffblk;
	char p[MAXPATH];

	if ( findfirst( p_filename, &ffblk, 0 ) == 0 ) {
		return CUR_DIR;
	}
	sprintf( p, "%s\\%s", search_path, p_filename );
	if ( findfirst( p, &ffblk, 0 ) == 0 ) {
		return CW_DIR;
	}
	return NOT_FOUND;
}

boolean havewild( char *p_filename ) {
	while ( *p_filename ) {
		if ( ( *p_filename == '*' ) || ( *p_filename == '?' ) ) {
			return( YES );
		}
		p_filename++;
	}
	return( NO );
}

void readscrfont( void *p_fontbuffer, char *p_fontname, char *p_searchpath ) {
	FILE* fp = fopen( p_fontname, "rb" );
	char fn[MAXPATH];

	if ( !fp ) {
		sprintf( fn, "%s\\%s", p_searchpath, p_fontname );
		fp = fopen( fn, "rb" );
	}
	if ( fp ) {
		fread( p_fontbuffer, sizeof( p_fontbuffer ), 20 * 256, fp );
		fclose( fp );
	} else {
		fprintf( stderr, "FONT FILE (%s) NOT FOUND !\n", p_fontname );
		exit( EXIT_FAILURE );
	}
}

int handler( int errval, int ax, int bp, int si ) {
	unsigned char *scrn;

	errorsound( );
	if ( ax >= 0 ) {
		scrn = savescrn( 18 + center_factor, 9, 71 + center_factor, 11 );
		blockmsg( 10 );
		dispprintf( 25 + center_factor, 10, 2, "Disk error on drive %c ! กดปุ่มใดๆเพื่อทำงานต่อ", 'A' + ( ax & 0x00FF ) );
		ebioskey( 0 );
		resscrn( scrn, 18 + center_factor, 9, 71 + center_factor, 11 );
	}
	hardretn( -1 );
}
