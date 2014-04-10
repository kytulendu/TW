#ifndef SCUW_DEL_H_INCLUDED
#define SCUW_DEL_H_INCLUDED

void delete_char( unsigned int x );
void deletereturn( struct line_node *line );
void del_return( void );
void backspace( unsigned int *x );
void delete_word( unsigned int x );
void deltoendline( unsigned int x, unsigned int y );
void deleteline( struct line_node *line );
void delete_line( void );

#endif /* SCUW_DEL_H_INCLUDED */
