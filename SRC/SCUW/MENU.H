#ifndef SCUW_MENU_H_INCLUDED
#define SCUW_MENU_H_INCLUDED

/** Write menu-bar. */
void headmenu( unsigned int topmenu, font_attr attr );

/** Select menu from pulled-down menu. Receive value of curmenu by reference
*   to be displayed on screen. User would select menu so value of curmenu
*   should be changed too. Return RETKEY if user press return,else ESCKEY if
*   escape key is pressed,else COMMAND KEY if command key is pressed. */
unsigned int pulled_down_menu( unsigned int *curmenu, unsigned int *x, unsigned int *y );

#endif /* SCUW_MENU_H_INCLUDED */
