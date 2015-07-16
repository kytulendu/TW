#ifndef SCUW_EDIT_H_INCLUDED
#define SCUW_EDIT_H_INCLUDED

/** From attribute given,find string of ascii control code. */
void findstrcode( unsigned char *fontcode, font_attr attr );

/** Find line number from line pointer given. */
unsigned int findlineno( struct line_node *line );

/** Find line pointer from line number given. */
struct line_node *linepointer( unsigned int linenum );

/** Display line from link list at row given. First column to be displayed
*   is in global variable "firstcol". */
void displine( struct line_node *line, unsigned int y, unsigned int linenum );

/** Display page break line at row given. */
void disppagebreak( unsigned int y );

#ifdef WANT_TO_USE_GRAPH
void set_graphic_buffer( );
#endif

/** Display all line in page from linked list. Stop display if keyboard is
*  pressed,then set flag "pagecomplete" to NO,else "pagecomplete" is set to YES. */
void showpage( void );

/** Show all lines in page,ignore pressing keyboard. */
void showpageall( void );

/** Find value of current row from global variable "curpage" and "curline". */
unsigned int findrow( void );

/** Adjust column to right position. */
void adjustcol( unsigned int *x );

/** Load line from linked list to workline. */
void loadtoline( unsigned char *text );

/** Store line from workline to linked list. */
void storeline( struct line_node *line );

/** Display line from workline at row given.Start display from column given. */
void refreshline( unsigned int x, unsigned int y );

#endif /* SCUW_EDIT_H_INCLUDED */
