/*
* ============================================================================
* GRPH.C
*
* CU-Writer graphic feature.
* ============================================================================
*/

#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\cwgrphc.h"
#include "..\common\cscrn.h"
#include "..\common\dir.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\sound.h"
#include "..\common\getstr.h"

#include "var.h"

#include "edit.h"

#include "pic.h"

#ifdef WANT_TO_USE_GRAPH
char *readgraph( char *filename ) {
	size_t filelen, namelen;
	int handle;
	char *buffer;
	if ( ( handle = open( filename, O_RDONLY || O_BINARY ) ) == -1 ) {
		return( NULL );
	}
	filelen = ( size_t ) filelength( handle );
	namelen = strlen( filename );
	buffer = ( char * ) malloc( filelen + namelen + 2 );
	strcpy( buffer, filename );
	read( handle, buffer + namelen + 1, filelen );
	close( handle );
	buffer[namelen + filelen] = '\0';
	buffer[namelen + filelen + 1] = 0x80;       /* code of end of graph */
	return( buffer );
}

void paintlinegraph( char *graph, unsigned int y ) {
	unsigned int endy, x;
	char tp;

	x = wind.col * 8;
	y = ( y * 20 ) + 84;
	if ( y >= 344 ) {
		return;
	}
	endy = y + 20;
	if ( endy > 344 ) {
		endy = 344;
	}
	while ( ( y != endy ) && ( *graph != 0x80 ) ) {
		tp = *graph;
		if ( tp == 0 ) {
			graph++;
			y++;
			x = wind.col * 8;
		} else {
			if ( tp < 128 ) {
				/*h_line_g( x, x + tp, y ); */ /* invalid function */
			} else {
				tp -= 128;
			}
			x += tp;
			graph++;
		}
	}
}

void notavailable( void ) {
	savepic( );
	blockmsg( 5 );
	dispstrhgc( "คำสั่งนี้อยู่ระหว่างการพัฒนา ! กดปุ่มใดๆ เพื่อทำงานต่อ", ( 14 + center_factor ) + 4, 5, REVERSEATTR );

	ebioskey( 0 );
	retpic( );
}

void insertgraph( ) {
	int i;
	char graphname[30];

	notavailable( ); /* comment this out */

	storeline( curline );

	blockmsg( 5 );
	dispstrhgc( "ใส่ชื่อแฟ้มรูปภาพที่ต้องการอ่าน :", ( 14 + center_factor ) + 3, 6, REVERSEATTR );

	strcpy( graphname, "*.*" );
	i = getname( graphname,  ( 14 + center_factor ) + 28, 5, 22, REVERSEATTR );
	if ( ( i == YES ) && ( graphname[0] != '\0' ) ) {
		if ( havewild( graphname ) ) {
			selectfile( graphname );
		}
		curline->graph = readgraph( graphname );
	}
	changeflag = YES;
	pagecomplete = NO;
	loadtoline( curline->text );
}

void deletegraph( ) {

	notavailable( );  /* comment this out */

	if ( curline->graph != NULL ) {
		free( curline->graph );
		curline->graph = NULL;
		changeflag = YES;
		pagecomplete = NO;
	} else {
		errorsound( );
	}
}
#endif
