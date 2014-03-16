#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

void findstrcode( char fontcode[], font_attr attr );
unsigned findlineno( struct line_node *line );
struct line_node *linepointer( unsigned int linenum );
void displine( struct line_node *line, unsigned int y, unsigned int linenum );
void disppagebreak( unsigned int y );
void showpage( void );
void showpageall( void );
unsigned findrow( void );
void adjustcol( unsigned int *x );
void loadtoline( char *text );
void storeline( struct line_node *line );
void refreshline( unsigned int x, unsigned int y );

#endif
