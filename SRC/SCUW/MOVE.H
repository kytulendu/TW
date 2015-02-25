#ifndef SCUW_MOVE_CONST_H_INCLUDED
#define SCUW_MOVE_CONST_H_INCLUDED

/** Go to line specified. */
void goline( unsigned int linetogo );

/** Go to column specified. (Column origin 0) */
void gocol( unsigned int coltogo, unsigned int *x );

/** Go to first column of line. */
void home( unsigned int *x );

/** Go to end of line. */
void endline( unsigned int *x );

/** Go to top of file. */
void topfile( unsigned int *x );

/** Go to end of file. */
void endfile( unsigned int *x );

/** Goto previous word.  */
void backword( unsigned int *x );

/** Goto next word. */
void nextword( unsigned int *x, unsigned int y );

/** Goto page specified. */
void gotopage( void );

/** Goto line specified. */
void gotoline( void );

/**  */
void gobeginblk( unsigned int *x );

/**  */
void goendblk( unsigned int *x );

/**  */
void quick( unsigned int *x, unsigned int *y );

#endif /* SCUW_MOVE_CONST_H_INCLUDED */
