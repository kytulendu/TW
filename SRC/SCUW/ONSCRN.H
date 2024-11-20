#ifndef SCUW_ONSCRN_H_INCLUDED
#define SCUW_ONSCRN_H_INCLUDED

/** Write tab on screen. */
void writetab( void );

/** Center line.
*  \param[in]  yCursorPos       Line cursor position in editing window. */
void centerline( unsigned int p_yCursorPos );

/** Do <CTRL><O> functions.
*  \param[in]  p_key            Keyboard code.
*  \param[in]  p_xCursorPos     Column cursor position in editing window.
*  \param[in]  p_yCursorPos     Line cursor position in editing window. */
void doonscrn( unsigned int p_key, unsigned int p_xCursorPos, unsigned int p_yCursorPos );

/** Move to tab.
*  \param[in]  p_xCursorPos     Column cursor position in editing window.
*  \param[in]  p_yCursorPos     Line cursor position in editing window. */
void movetotab( unsigned int *p_xCursorPos, unsigned int p_yCursorPos );

/** Call doonscrn to do <CTRL><O> Functions.
*  \param[in]  p_xCursorPos     Column cursor position in editing window.
*  \param[in]  p_yCursorPos     Line cursor position in editing window. */
void onscreen( unsigned int p_xCursorPos, unsigned int p_yCursorPos );

#endif /* SCUW_ONSCRN_H_INCLUDED */
