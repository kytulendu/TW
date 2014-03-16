#ifndef MOVE_CONST_H_INCLUDED
#define MOVE_CONST_H_INCLUDED

void goline( unsigned int linetogo );
void gocol( unsigned int coltogo, unsigned int *x );
void home( unsigned int *x );
void endline( unsigned int *x );
void topfile( unsigned int *x );
void endfile( unsigned int *x );
void backword( unsigned int *x );
void nextword( unsigned int *x, unsigned int y );
void gotopage( void );
void gotoline( void );
void gobeginblk( unsigned int *x );
void goendblk( unsigned int *x );
void quick( unsigned int *x, unsigned int *y );

#endif
