#ifndef SCUW_WRAP_H_INCLUDED
#define SCUW_WRAP_H_INCLUDED

/** Insert blank code (bit 8 = 1) to justify text to right margin. Text
*   must be in workline,not linked list. */
void justify_right( void );

/** Reform paragraph from line specified to end of paragraph. */
void reform( void );

/** Manualy wrap lines.
*  \param[in]  p_xCursorPos     Column cursor position in editing window.
*  \param[in]  y_CursorPos      Line cursor position in editing window. */
void manualwrap( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

/** Automatically wrap lines.
*  \param[in]  p_xCursorPos     Column cursor position in editing window.
*  \param[in]  y_CursorPos      Line cursor position in editing window. */
void autowrap( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

/** leave the leading blank alone, just compress the rest
*   and trim the trailing blank.
*  \param[in]  p_string         Pointer to string. */
void compress_blank( unsigned char *p_string );

#endif /* SCUW_WRAP_H_INCLUDED */
