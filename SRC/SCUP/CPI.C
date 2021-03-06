#include <stdlib.h>
#include <string.h>

#include "cpi.h"

void charwidth( char *p_buffer ) {
    extern int maxdot;                                      /* already defined in prt.c and pmenu.c */
    extern int maxbuffer;                                   /* already defined in pmenu.c */
    extern int cpi;                                         /* already defined in prt.c and pmenu.c */

    char *buffer;
    char cf[21];
    register int i;
    register int j;
    register int k;
    register int m;

    buffer = ( char * ) calloc( maxdot + 100, sizeof( char ) );
    i = 0;
    j = 0;
    switch ( cpi ) {
    case 0:
        break;
    case 1:                                             /* term '10/cpi' generate number */
    case 2:                                         /* of times the same dot appears */
    case 5:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            k = j + 10 / cpi;
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 3:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            k = j + 3;  /* 3 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
            k = j + 3;  /* 3 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
            k = j + 4;  /* 4 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 4:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            k = j + 2;  /* 2 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
            k = j + 3;  /* 3 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 6:
        while ( ( i<maxbuffer ) && ( j<maxdot ) ) {
            k = j + 2;  /* 2 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
            k = j + 2;  /* 2 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
            k = j + 1;  /* 1 times repeat */
            for ( ; j < k; j++ ) { buffer[j] = p_buffer[i]; }
            i++;
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 7:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            for ( m = 0; m<5; m++ ) {
                k = i + 1;  /* 1 times iteration */
                for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
                buffer[j++] = p_buffer[i];
                buffer[j++] = p_buffer[i++]; /* 1 dot repeat */
            }
            buffer[j++] = p_buffer[i++];
            buffer[j++] = p_buffer[i++];
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 8:                                                 /* term '3+4*(cpi-8)' refer to 3,7 accordingly */
    case 9:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            k = i + 3 + 4 * ( cpi - 8 );  /* 3,7 times iteration */
            for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
            buffer[j++] = p_buffer[i];
            buffer[j++] = p_buffer[i++]; /* 1 dot repeat */
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 10:
        break;
    case 11: cf[11] = 12;                                   /* terms (12/-576)(cpi-12)(cpi-13)(...)...(...)... */
    case 12: cf[12] = 6;                                    /* +     ( 6/ 168)(cpi-11)(cpi-13)(...)...(...)... */
    case 13: cf[13] = 4;                                    /* +     ...                                       */
    case 15: cf[15] = 3;                                    /* +     ( 2/1520)(cpi-11)(cpi-12)..(..)..(cpi-19) */
    case 19: cf[19] = 2;                                    /* refer to 12,6,4,3,2,2 accordingly               */
    case 20: cf[20] = 2;
        /*
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            k = i - 1 + cf[cpi];
            for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
            j--;
            buffer[j++] |= p_buffer[i++]; *//* 1 dot deplete */
        /*}
        */
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            k = i - 1 + cf[cpi];
            for ( ; i < k; ) { buffer[j++] |= p_buffer[i++]; }
            j--;
            buffer[j++] |= p_buffer[i];
            buffer[j] |= p_buffer[i++]; /* 1 dot deplete */
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 14:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            for ( m = 0; m<7; m++ ) {
                k = i + 2;
                for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
                i++;  /* ignore 1 dot of 3 */
            }
            k = i + 3;
            for ( ; i<k; ) buffer[j++] = p_buffer[i++];
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 16:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            for ( m = 0; m<7; m++ ) {
                k = i + 2;
                for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
                i++;  /* ignore 1 dot of 3 */
            }
            i++; i++;
            buffer[j++] = p_buffer[i++];
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 17:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            for ( m = 0; m<5; m++ ) {
                k = i + 1;
                for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
                i++;  /* ignore 1 dot of 2 */
            }
            k = i + 2;
            for ( ; i<k; ) buffer[j++] = p_buffer[i++];
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    case 18:
        while ( ( i < maxbuffer ) && ( j < maxdot ) ) {
            for ( m = 0; m < 11; m++ ) {
                k = i + 1;
                for ( ; i < k; ) { buffer[j++] = p_buffer[i++]; }
                i++;  /* ignore 1 dot of 2 */
            }
            k = i + 2;
            for ( ; i < k; ) buffer[j++] = p_buffer[i++];
        }
        memmove( p_buffer, buffer, maxdot );
        break;
    default:
        break;
    }
    free( buffer );
}
