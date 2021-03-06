#ifndef SCUW_CW_H_INCLUDED
#define SCUW_CW_H_INCLUDED

/** Set up first set of linked list, it must consist of at least two line
*   below follow.
*   1. sentinel line - Next pointer of sentinel node point to first line
*                      & previous pointer point to last line to form
*                      circular linked list.
*   2. first line    - It's contain no string but it's serious required !. */
void setupnode( void );

/** Destroy node created by setupnode();. */
void destroynode( void );

/** Show splash screen. */
void splashscreen( void );

#endif /* SCUW_CW_H_INCLUDED */
