#ifndef SCUW_MOVEMENT_H_INCLUDED
#define SCUW_MOVEMENT_H_INCLUDED

void cursor_up( void );
void cursor_down( unsigned int y );
void cursor_left( unsigned int *x );
void cursor_right( unsigned int *x, unsigned int y );
void page_up( void );
void page_down( void );
void scroll_up( void );
void scroll_down( void );
void top_of_page( void );
void bottom_of_page( void );

#endif /* SCUW_MOVEMENT_H_INCLUDED */
