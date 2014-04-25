#ifndef SCUP_SMENU_H_INCLUDED
#define SCUP_SMENU_H_INCLUDED

int smenu( register int x, register int y, int number, char *message[], int *curmenu );
unsigned int find_menu_len( register int number, char *message[] );

#endif /* SCUP_SMENU_H_INCLUDED */
