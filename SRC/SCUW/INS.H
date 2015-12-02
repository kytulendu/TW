#ifndef SCUW_INS_H_INCLUDED
#define SCUW_INS_H_INCLUDED

/** Insert blank to workline at specified column (origin 1).
*  \param[in]  p_col			Column position (physical).
*  \param[in]  p_blankchar		Blank character to insert. */
void insertblank( unsigned int p_col, unsigned char p_blankchar );

/** Insert new line after line specified.
*  \param[in]  p_curline		Pointer to current line.
*  \param[in]  p_newline		Pointer to new line. */
void insert_line( struct line_node *p_curline, struct line_node *p_newline );

/** Shift right screen by number given. */
void shiftscrn( unsigned int p_count, unsigned int *p_x );

/** Sound beeper then display message "line too long" and wait keyboard
*   for ESCAPE key. */
void linetoolong( void );

/** Insert print control character at column given.
*  \param[in]  p_ctrlChar		Control character to insert.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
void inscntrl( unsigned char p_ctrlChar, unsigned int p_xCursorPos, unsigned int p_yCursorPos );

/** Wait keyboard for insert control character then insert it to workline
*   at current cursor position.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
void printcntrl( unsigned int p_xCursorPos, unsigned int p_yCursorPos );

/** Insert a character at cursor position.
*  \param[in]  p_char			Control character to insert.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
int insert_char( unsigned char p_char, unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

/** Overwrite a character at cursor position.
*  \param[in]  p_char			Control character to insert.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
int ovrwrite_char( unsigned char p_char, unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

/** Insert return at line & column given, don't update block position.
*  \param[in]  p_line			line to insert.
*  \param[in]  p_col			Column position (physical). */
void insertreturn( struct line_node *p_line, unsigned int p_col );

/** Insert return at current line & column given, also update block position.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void insert_ret( unsigned int *p_xCursorPos );

/** Return cursor to first column of next line of current line.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
void returnkey( unsigned int *p_xCursorPos, unsigned int p_yCursorPos );

/** Insert return then return cursor.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
void ret_with_ins( unsigned int *p_xCursorPos, unsigned int p_yCursorPos );

/** Insert macro word at current cursor position.
*  \param[in]  p_macro			Pointer to macro to insert.
*  \param[in]  p_xCursorPos		Column cursor position in editing window.
*  \param[in]  p_yCursorPos		Line cursor position in editing window. */
void insertmacro( unsigned char *p_macro, unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

/** Display blank macro dialog at given line.
*  \param[in]  p_yPos			Line to display the dialog. */
void blankmaro( int p_yPos );

/** Display given macro number.
*  \param[in]  p_macro			Macro no. to display. */
void dispmacro( int p_macro );

/** Display dialog to edit macro word. */
void editmacro( void );

#endif /* SCUW_INS_H_INCLUDED */
