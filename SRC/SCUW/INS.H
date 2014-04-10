#ifndef SCUW_INS_H_INCLUDED
#define SCUW_INS_H_INCLUDED

void insertblank( unsigned int j, char code );
void insert_line( struct line_node *currentline, struct line_node *newline );
void shiftscrn( unsigned int count, unsigned int *x );
void linetoolong( void );
void inscntrl( char cntrl, unsigned int x, unsigned int y );
void printcntrl( unsigned int x, unsigned int y );
int insert_char( char c, unsigned int *x, unsigned int *y );
int ovrwrite_char( char c, unsigned int *x, unsigned int *y );
void insertreturn( struct line_node *line, unsigned int thaicol );
void insert_ret( unsigned int *x );
void returnkey( unsigned int *x, unsigned int y );
void ret_with_ins( unsigned int *x, unsigned int y );
void insertmacro( char *macro, unsigned int *x, unsigned int *y );
void blankmaro( int y );
void dispmacro( int i );
void editmacro( void );

#endif /* SCUW_INS_H_INCLUDED */
