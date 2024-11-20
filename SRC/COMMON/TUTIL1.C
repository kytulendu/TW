#include <stdio.h>

#include "cwtype.h"
#include "common.h"
#include "cscrn.h"

#include "tutil1.h"

size_t thaistrlen( register unsigned char *p_thaistring ) {
    register size_t count = 0;
    font_attr curfont = 0;

    while ( *p_thaistring ) {
        if ( whatlevel( *p_thaistring ) == MIDDLE ) {
            if ( *p_thaistring < 32 ) {     /* if is control code */
                togglefont( &curfont, *p_thaistring );
            } else {
                count++;
                if ( ( curfont & ENLARGEATTR ) == ENLARGEATTR ) {
                    count++;
                }
            }
        }
        p_thaistring++;
    }
    return( count );
}
