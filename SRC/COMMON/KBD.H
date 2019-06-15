#ifndef SCUP_KBD_H_INCLUDED
#define SCUP_KBD_H_INCLUDED

/** Wait for keyboard press and display cursor at given position.
*   \param[in]  p_xcurpos		Vertical position of cursor.
*   \param[in]  p_ycurpos		Horizontal position of cursor.*/
void waitkbd( int p_xcurpos, int p_ycurpos );

/** Read keyboard.
*   \return unsigned int		Keyboard code. */
int readkbd( void );

#endif /* SCUP_KBD_H_INCLUDED */
