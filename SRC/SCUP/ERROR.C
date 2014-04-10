#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\ekbd.h"

#include "printing.h"

#include "error.h"

void disperror( char *s ) {
    clear_message( );                                       /* from printing.obj */
    dispstrhgc( s, 40 - strlen( s ) / 2, 13, 2 );
    /* errorsound(); */
    while ( !keypressed( ) );
    clear_message( );                                       /* from printing.obj */
}
