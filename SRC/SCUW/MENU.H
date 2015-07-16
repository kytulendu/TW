#ifndef SCUW_MENU_H_INCLUDED
#define SCUW_MENU_H_INCLUDED

/** Select menu.
*   input : number origin 1
*           *curmenu origin 1 */
int selectmenu( unsigned int x, unsigned int y, unsigned int number, unsigned char *message[], unsigned int *curmenu );

/** Write menu-bar. */
void headmenu( unsigned int topmenu, font_attr attr );

/** Find current menu. */
unsigned int findcurmenu( unsigned int lev1, unsigned int lev2, unsigned int lev3, unsigned int lev4 );

/** Find current level. */
void findcurlevel( unsigned int curmenu, unsigned int *lev1, unsigned int *lev2, unsigned int *lev3, unsigned int *lev4 );

/** Select menu from pulled-down menu. Recieve value of curmenu by reference
*   to be displayed on screen. User would select menu so value of curmenu
*   should be changed too. Return RETKEY if user press return,else ESCKEY if
*   escape key is pressed,else COMMAND KEY if command key is pressed. */
unsigned int pulled_down_menu( unsigned int *curmenu, unsigned int *x, unsigned int *y );

#endif /* SCUW_MENU_H_INCLUDED */
