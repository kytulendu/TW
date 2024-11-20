#include "tctype.h"
#include "thai.h"

#include "global.h"
#include "routine.h"

unsigned char *RoreReoRtn( register unsigned char *TempIndx ) {
    if ( *( TempIndx - 1 ) != RoreReo ) {
        return( FAIL );
    }
    if ( istrvwl( *( TempIndx - 2 ) ) ) {
        return( TempIndx - 1 );
    }
    return( FAIL );
}
