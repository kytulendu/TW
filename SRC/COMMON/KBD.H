#ifndef SCUP_KBD_H_INCLUDED
#define SCUP_KBD_H_INCLUDED

/** Wait for keyboard press.
*   \param[in]  p_xcurpos		Vertical position of cursor.
*   \param[in]  p_ycurpos		Horizontal position of cursor.*/
void waitkbd( unsigned int p_xcurpos, unsigned int p_ycurpos );

/** Read keyboard.
*   \return int					*/
int readkbd( void );

#endif /* SCUP_KBD_H_INCLUDED */