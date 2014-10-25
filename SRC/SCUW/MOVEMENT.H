#ifndef SCUW_MOVEMENT_H_INCLUDED
#define SCUW_MOVEMENT_H_INCLUDED

/** Up line one line. */
void cursor_up( void );

/** Down line one line. */
void cursor_down( unsigned int y );

/** Left cursor. */
void cursor_left( unsigned int *x );

/** Right cursor. */
void cursor_right( unsigned int *x, unsigned int y );

/** Page up. */
void page_up( void );

/** Page down. */
void page_down( void );

/** Scroll page up.
*  WARNING : Curline is not updated in this routine,it must be updated
*            by calling function (main) after call if current cursor
*            position is at bottom of screen. */
void scroll_up( void );

/** Scroll page down. */
void scroll_down( void );

/** Goto top of page. (CTRL-QE in wordstar) */
void top_of_page( void );

/** Goto bottom of page. (CTRL-QX in wordstar) */
void bottom_of_page( void );

#endif /* SCUW_MOVEMENT_H_INCLUDED */
