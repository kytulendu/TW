#ifndef SCUW_MOVE_CONST_H_INCLUDED
#define SCUW_MOVE_CONST_H_INCLUDED

/** Go to line specified.
*  \param[in]  p_linetogo		Line to go. */
void goline( unsigned int p_linetogo );

/** Go to column specified, column is origin 0
*  \param[in]  p_coltogo		Column to go.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void gocol( unsigned int p_coltogo, unsigned int *p_xCursorPos );

/** Go to first column of line.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void home( unsigned int *p_xCursorPos );

/** Go to end of line.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void endline( unsigned int *p_xCursorPos );

/** Go to top of file.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void topfile( unsigned int *p_xCursorPos );

/** Go to end of file.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void endfile( unsigned int *p_xCursorPos );

/** Goto previous word.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void backword( unsigned int *p_xCursorPos );

/** Goto next word.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  y_CursorPos		Line cursor position in editing window. */
void nextword( unsigned int *p_xCursorPos, unsigned int p_yCursorPos );

/** Goto page specified. */
void gotopage( void );

/** Goto line specified. */
void gotoline( void );

/** Goto begining of block.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void gobeginblk( unsigned int *p_xCursorPos );

/** Goto end of block.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void goendblk( unsigned int *p_xCursorPos );

/**
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  yCursorPos		Line cursor position in editing window. */
void quick( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

#endif /* SCUW_MOVE_CONST_H_INCLUDED */
