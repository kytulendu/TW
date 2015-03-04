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

#include "var.h"
#include "block.h"

#include "file.h"

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
