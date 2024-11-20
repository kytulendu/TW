/*
* ============================================================================
* ATTR.C
*
* Print data to buffer and manage all attribute.
* ============================================================================
*/

#include <string.h>

#include "24pins.h"

#include "attr.h"

FONT *cp_lqscr_blank( FONT *p_buffer ) {
    memset( p_buffer, 0, CP_LQ_FONTSIZE );
    return ( p_buffer );
}

FONT *cp_sub_middle_lower( FONT *p_buffer, FONTSCR *p_middle, FONTSCR *p_lower ) {
    int i;

    memset( p_buffer, 0, CP_LQ_FONTSIZE );
    for ( i = 0; i < CP_LQCOL; i++ ) {
        p_buffer->font[i][0] = p_middle->font[i][1];
        p_buffer->font[i][1] = ( ( p_lower->font[i][0] ) << 4 ) | ( ( p_lower->font[i][1] ) >> 4 );
        p_buffer->font[i][2] = ( ( p_lower->font[i][1] ) << 4 );
    }
    return ( p_buffer );
}

FONT *cp_sub_upper_middle( FONT *p_buffer, FONTSCR *p_upper, FONTSCR *p_middle ) {
    int i;

    memset( p_buffer, 0, CP_LQ_FONTSIZE );
    for ( i = 0; i < CP_LQCOL; i++ ) {
        p_buffer->font[i][1] = ( ( p_upper->font[i][0] ) << 4 ) | ( ( p_upper->font[i][1] ) >> 4 );
        p_buffer->font[i][2] = ( ( p_upper->font[i][1] ) << 4 ) | p_middle->font[i][0];
    }
    return ( p_buffer );
}

FONT *cp_super_upper_middle( FONT *p_buffer, FONTSCR *p_upper, FONTSCR *p_middle ) {
    int i;

    memset( p_buffer, 0, CP_LQ_FONTSIZE );
    for ( i = 0; i < CP_LQCOL; i++ ) {
        p_buffer->font[i][0] = ( ( p_upper->font[i][0] ) << 4 ) | ( ( p_upper->font[i][1] ) >> 4 );
        p_buffer->font[i][1] = ( ( p_upper->font[i][1] ) << 4 );
        p_buffer->font[i][2] = ( ( p_middle->font[i][0] ) << 4 ) | ( ( p_middle->font[i][1] ) >> 4 );
    }
    return ( p_buffer );
}

FONT *cp_super_middle_lower( FONT *p_buffer, FONTSCR *p_middle, FONTSCR *p_lower ) {
    int i;

    memset( p_buffer, 0, CP_LQ_FONTSIZE );
    for ( i = 0; i < CP_LQCOL; i++ ) {
        p_buffer->font[i][0] = ( ( p_middle->font[i][1] ) << 4 );
        p_buffer->font[i][1] = ( ( p_lower->font[i][0] ) << 4 ) | ( ( p_lower->font[i][1] ) >> 4 );
        p_buffer->font[i][2] = ( ( p_lower->font[i][1] ) << 4 );
    }
    return ( p_buffer );
}

FONT *cp_underline( FONT *p_newchar, FONT *p_oldchar ) {
    int i;

    memcpy( p_newchar, p_oldchar, CP_LQ_FONTSIZE );
    for ( i = 0; i < CP_LQCOL; i++ ) {
        p_newchar->font[i][0] |= CP_UNDERLINE_MSK;
    }
    return ( p_newchar );
}

FONT *cp_doubleline( FONT *p_newchar, FONT *p_oldchar ) {
    int i;

    memcpy( p_newchar, p_oldchar, CP_LQ_FONTSIZE );
    for ( i = 0; i < CP_LQCOL; i++ ) {
        p_newchar->font[i][0] |= CP_DOUBLELINE_MSK;
    }
    return ( p_newchar );
}

int cp_enlarge( struct cp_grlqbuf p_buffer, int p_index ) {
    int i, j;
    FONT upper[2], middle[2], lower[2];

    p_index--;                                                /* Pointer to that character */
    for ( i = 0; i < 17; i++ ) {
        for ( j = 0; j < CP_LQROW; j++ ) {
            upper[0].font[2 * i][j] = upper[0].font[2 * i + 1][j]
                = ( p_buffer.upper + p_index )->font[i][j];
            middle[0].font[2 * i][j] = middle[0].font[2 * i + 1][j]
                = ( p_buffer.middle + p_index )->font[i][j];
            lower[0].font[2 * i][j] = lower[0].font[2 * i + 1][j]
                = ( p_buffer.lower + p_index )->font[i][j];
        }
    }

    for ( j = 0; j < CP_LQROW; j++ ) {
        upper[0].font[2 * i][j] = upper[0].font[2 * i + 1][j]
            = ( p_buffer.upper + p_index )->font[i][j];
        middle[0].font[2 * i][j] = middle[0].font[2 * i + 1][j]
            = ( p_buffer.middle + p_index )->font[i][j];
        lower[0].font[2 * i][j] = lower[0].font[2 * i + 1][j]
            = ( p_buffer.lower + p_index )->font[i][j];
    }

    memcpy( p_buffer.upper + p_index, upper, 2 * CP_LQ_FONTSIZE );
    memcpy( p_buffer.middle + p_index, middle, 2 * CP_LQ_FONTSIZE );
    memcpy( p_buffer.lower + p_index, lower, 2 * CP_LQ_FONTSIZE );
    return ( p_index + 2 );
}

void cp_bold( struct cp_grlqbuf p_buffer, int p_index ) {
    int i, j;
    FONT upper, middle, lower;

    p_index--;                                              /* Pointer to that character */
    for ( i = 0; i < 17; i++ ) {
        for ( j = 0; j < CP_LQROW; j++ ) {
            upper.font[i][j] = ( p_buffer.upper + p_index )->font[i][j];
            upper.font[i][j] |= ( p_buffer.upper + p_index )->font[i + 1][j];

            middle.font[i][j] = ( p_buffer.middle + p_index )->font[i][j];
            middle.font[i][j] |= ( p_buffer.middle + p_index )->font[i + 1][j];

            lower.font[i][j] = ( p_buffer.lower + p_index )->font[i][j];
            lower.font[i][j] |= ( p_buffer.lower + p_index )->font[i + 1][j];
        }
    }

    for ( j = 0; j < CP_LQROW; j++ ) {
        upper.font[i][j] = ( p_buffer.upper + p_index )->font[i][j];
        middle.font[i][j] = ( p_buffer.middle + p_index )->font[i][j];
        lower.font[i][j] = ( p_buffer.lower + p_index )->font[i][j];
    }

    memcpy( p_buffer.upper + p_index, &upper, CP_LQ_FONTSIZE );
    memcpy( p_buffer.middle + p_index, &middle, CP_LQ_FONTSIZE );
    memcpy( p_buffer.lower + p_index, &lower, CP_LQ_FONTSIZE );
}
