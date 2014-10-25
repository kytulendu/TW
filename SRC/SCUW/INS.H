#ifndef SCUW_INS_H_INCLUDED
#define SCUW_INS_H_INCLUDED

/** Insert blank to workline at specified column(origin 1). */
void insertblank( unsigned int j, char code );

/** Insert new line after line specified. */
void insert_line( struct line_node *currentline, struct line_node *newline );

/** Shift right screen by number given. */
void shiftscrn( unsigned int count, unsigned int *x );

/** Sound beeper then display message "line too long" and wait keyboard
*   for ESCAPE key. */
void linetoolong( void );

/** Insert print control character at column given. */
void inscntrl( char cntrl, unsigned int x, unsigned int y );

/** Wait keyboard for insert control character then insert it to workline
*   at current cursor position. */
void printcntrl( unsigned int x, unsigned int y );

/** insert character 'c' at cursor position *x,*y */
int insert_char( unsigned char c, unsigned int *x, unsigned int *y );

/** Overwrite character 'c' at cursor position *x,*y */
int ovrwrite_char( unsigned char c, unsigned int *x, unsigned int *y );

/** Insert return at line & column given, don't update block position. */
void insertreturn( struct line_node *line, unsigned int thaicol );

/** Insert return at current line & column given, also update block position. */
void insert_ret( unsigned int *x );

/** Return cursor to first column of next line of current line. */
void returnkey( unsigned int *x, unsigned int y );

/** Insert return then return cursor. */
void ret_with_ins( unsigned int *x, unsigned int y );

/** Insert macro word at current cursor position. */
void insertmacro( char *macro, unsigned int *x, unsigned int *y );

/**  */
void blankmaro( int y );

/**  */
void dispmacro( int i );

/**  */
void editmacro( void );

#endif /* SCUW_INS_H_INCLUDED */
