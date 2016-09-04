/*
* ============================================================================
* ERROR.C
* ============================================================================
*/

#include <stdlib.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\ekbd.h"

#include "printing.h"

#include "error.h"

void disperror( char *p_string ) {
	clear_message( );                                       /* from printing.obj */
	dispstrhgc( p_string, 40 - ( strlen( p_string ) / 2 ), 13, REVERSEATTR );
	/* errorsound( ); */
	while ( !keypressed( ) );
	clear_message( );                                       /* from printing.obj */
}

void execerror( char *p_err, char *p_exterr ) {
	char se[80];
	strcpy( se, p_err );
	strcat( se, p_exterr );
	disperror( se );
	/* settext();              *//* Change to text mode */
	/*
	fprintf( stderr, "%s", p_err );
	if ( p_exterr ) {
		fprintf( stderr, "%s", p_exterr );
	}*/
	settext( );
	exit( EXIT_FAILURE );
}
