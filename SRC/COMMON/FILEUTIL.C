/*
* ============================================================================
* FILEUTIL.C
*
* Written: Suttipong Kanakakorn
* Updated: Sun  08-27-1989  22:40:12
* ============================================================================
*/

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

boolean file_exist( char *filename ) {
	int fd;

	if ( ( fd = open( filename, O_RDONLY || O_BINARY ) ) == -1 ) {
		return NO;
	} else {
		close( fd );
		return YES;
	}
}
/*
search_file_mode find_file( char *filename, char *search_path ) {
	struct ffblk ffblk;
	char p[MAXPATH];

	if ( findfirst( filename, &ffblk, 0 ) == 0 ) {
		return CUR_DIR;
	}
	sprintf( p, "%s\\%s", search_path, filename );
	if ( findfirst( p, &ffblk, 0 ) == 0 ) {
		return CW_DIR;
	}
	return NOT_FOUND;
}
*/
int havewild( char *filname ) {
	while ( *filname ) {
		if ( ( *filname == '*' ) || ( *filname == '?' ) ) {
			return( YES );
		}
		filname++;
	}
	return( NO );
}

void readscrfont( void *font_buffer, char *fontname, char *search_path ) {
	register int handle;
	char fn[MAXPATH];

	if ( ( handle = open( fontname, O_RDONLY || O_BINARY ) ) == -1 ) {
		sprintf( fn, "%s\\%s", search_path, fontname );
		handle = open( fn, O_RDONLY || O_BINARY );
	}
	if ( handle != -1 ) {
		read( handle, font_buffer, 20 * 256 );
		close( handle );
	} else {
		fprintf( stderr, "FONT FILE (%s) NOT FOUND !\n", fontname );
		exit( EXIT_FAILURE );
	}
}

int handler( int errval, int ax, int bp, int si ) {
	char *scrn;

	errorsound( );
	if ( ax >= 0 ) {
		scrn = savescrn( 18 - center_factor, 9, 71 - center_factor, 11 );
		blockmsg( 10 );
		dispprintf( 25 - center_factor, 10, 2, "Disk error on drive %c ! กดปุ่มใดๆเพื่อทำงานต่อ", 'A' + ( ax & 0x00FF ) );
		ebioskey( 0 );
		resscrn( scrn, 18 - center_factor, 9, 71 - center_factor, 11 );
	}
	hardretn( -1 );
}
