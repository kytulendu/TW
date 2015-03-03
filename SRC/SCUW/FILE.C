/*
* ============================================================================
* FILE.C
*
* add function file_exist by Suttipong Kanakakorn
*  Thu  08-03-1989  00:16:25
* use framebox instead of dispstrhgc
*  Sat  08-05-1989  02:59:38
* ============================================================================
*/

#include <stdlib.h>
#include <io.h>
#include <dos.h>

#include "..\common\cwtype.h"
#include "..\common\cwgrphc.h"
#include "..\common\cscrn.h"
#include "..\common\ekbd.h"
#include "..\common\sound.h"

#include "var.h"
#include "block.h"

#include "file.h"

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

int read_file( char *file_name ) {
	struct line_node *space;
	space = rdfiletospace( file_name );
	if ( space != NULL ) {
		insertlinklist( space, curline, 0 );
		return( !ERROR );
	} else {
		return( ERROR );
	}
}
