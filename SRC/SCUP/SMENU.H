#ifndef SCUP_SMENU_H_INCLUDED
#define SCUP_SMENU_H_INCLUDED

/** Select menu
*   popup menu for user to select, programmer must save and restore the screen
*
*   - input x, y, number of messege, messege, curmenu
*   - output curmenu
*   - return ESCKEY or RETKEY
*
*   Written: Suttipong Kanakakorn
*   Date: Fri  08-18-1989  09:16:37 */
int smenu( register int p_x, register int p_y, int p_number, char *p_message[], int *p_curmenu );

/**  */
unsigned int find_menu_len( register int p_number, char *p_message[] );

#endif /* SCUP_SMENU_H_INCLUDED */
