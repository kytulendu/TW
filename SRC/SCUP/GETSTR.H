#ifndef SCUP_GETSTR_H_INCLUDED
#define SCUP_GETSTR_H_INCLUDED

/** get string
*   input
*       textst : string want to get
*       x      : vertical position ( 0 - 89 )
*       y      : horisontal position ( 0 - 16 )
*       maxlen : maximum length of string
*       attr   : attribute of string for displaying */
int getstring( char *textst, int x, int y, int maxlen, font_attr attr );

/**  */
int getname( char *textst, int x, int y, int maxlen, font_attr attr );

/**  */
int getnumber( char *textst, int x, int y, int maxlen, font_attr attr );

#endif /* SCUP_GETSTR_H_INCLUDED */