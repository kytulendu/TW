#ifndef SCUW_DEL_H_INCLUDED
#define SCUW_DEL_H_INCLUDED

/** Delete character of current line at column given.
*  \param[in]  p_xCursorPos		Column cursor position in editing window to mark. */
void delete_char( unsigned int p_xCursorPos );

/** Concatenate line given with next line or delete return of line given.
*  \param[in]  p_line			line_node to delete, usually is pointer to current line. */
void deletereturn( struct line_node *p_line );

/** Backspace. delete a character at the left of cursor, include any attribute, return, etc.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void backspace( unsigned int *p_xCursorPos );

/** Delete a word at the right of cursor.
*   (It will not delete entire word if cursor in middle of word.)
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void delete_word( unsigned int p_xCursorPos );

/** Delete the all character in given line.
*  \param[in]  xCursorPos	Column cursor position in editing window.
*  \param[in]  yCursorPos	Line cursor position in editing window. */
void deltoendline( unsigned int p_xCursorPos, unsigned int p_yCursorPos );

/** Delete line_node given.
*  \param[in]  p_line			line_node to delete, usually is pointer to current line. */
void deleteline( struct line_node *p_line );

/** Delete current line at cursor position. */
void delete_line( void );

#endif /* SCUW_DEL_H_INCLUDED */
