#ifndef POPUP_H_INCLUDED
#define POPUP_H_INCLUDED

#define CENTER 1

#define OLD    1
#define DIRECT 2
#define HIGH_LIGHT 3

int popup_message( char *item[] );
int popup_menu( char *item[], char**buff );
int remove_menu( char **p );

#endif /* POPUP_H_INCLUDED */
