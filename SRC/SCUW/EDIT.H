#ifndef SCUW_EDIT_H_INCLUDED
#define SCUW_EDIT_H_INCLUDED

#ifdef WANT_TO_USE_GRAPH
/**  */
void set_graphic_buffer( void );
#endif

/** From attribute given, find string of ASCII control code.
*  \param[in]  p_fontcode		Position to find control code.
*  \param[in]  p_attr			Character attribute. */
void findstrcode( unsigned char *p_fontcode, font_attr p_attr );

/** Find line number from line pointer given from line_node sentinel.
*  \param[in]  p_line			linenode to find line number.
*  \return unsigned int			Line number. */
unsigned int findlineno( struct line_node *p_line );

/** Find line pointer from line number given from line_node sentinel.
*  \param[in]  p_linenum		Line number to get line pointer.
*  \return struct line_node		Line pointer. */
struct line_node *linepointer( unsigned int p_linenum );

/** Display all line in page from linked list. Stop display if keyboard is
*  pressed,then set flag "pagecomplete" to NO,else "pagecomplete" is set to YES. */
void showpage( void );

/** Show all lines in page,ignore pressing keyboard. */
void showpageall( void );

/** Find value of current row from global variable "curpage" and "curline".
*  \return unsigned int			Current row. */
unsigned int findrow( void );

/** Adjust column to right position.
*  \param[in]  p_col			Column to adjust. */
void adjustcol( unsigned int *p_col );

/** Load line from linked list to workline.
*  \param[in]  p_text			Linked list to load to linenode workline. */
void loadtoline( unsigned char *p_text );

/** Store line from workline to linked list.
*  \param[in]  p_line			linenode. */
void storeline( struct line_node *p_line );

/** Display line from workline at row given. Start display from column given.
*  \param[in]  p_col			Column position.
*  \param[in]  p_row			Row position. */
void refreshline( unsigned int p_col, unsigned int p_row );

#endif /* SCUW_EDIT_H_INCLUDED */
