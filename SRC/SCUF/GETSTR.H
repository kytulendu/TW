#ifndef GETSTR_H_INCLUDED
#define GETSTR_H_INCLUDED

/** get string
*   input
*   textst : string want to get
*   x      : vertical position ( 0 - 89 )
*   y      : horisontal position ( 0 - 16 )
*   maxlen : maximum length of string
*   attr   : attribute of string for displaying
*   mode   : THAIENG, ENGLISH, ENGUPCASE, NUMBER, ONEORTWO */
int getstring( char textst[], unsigned int x, unsigned int y, unsigned int maxlen, char attr, strtype mode );

/**  */
int getname( char textst[], unsigned int x, unsigned int y, unsigned int maxlen, char attr );

#endif /* GETSTR_H_INCLUDED */
