#ifndef SCUW_MENU_H_INCLUDED
#define SCUW_MENU_H_INCLUDED

char *savescrn( int x1, int y1, int x2, int y2 );
void resscrn( char *scrnindex, int x1, int y1, int x2, int y2 );
int selectmenu( unsigned int x, unsigned int y, unsigned int number, char *message[], unsigned int *curmenu );
void headmenu( unsigned int topmenu, char attr );
unsigned int findcurmenu( unsigned int lev1, unsigned int lev2, unsigned int lev3, unsigned int lev4 );
void findcurlevel( unsigned int curmenu, unsigned int *lev1, unsigned int *lev2, unsigned int *lev3, unsigned int *lev4 );
unsigned int pulled_down_menu( unsigned int *curmenu, unsigned int *x, unsigned int *y );
void print_file( void );
void showerrno( void );

#endif /* SCUW_MENU_H_INCLUDED */
