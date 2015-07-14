/*
* ============================================================================
* Common screen utility
* ============================================================================
*/

#ifndef COMMON_CSCRN_H_INCLUDED
#define COMMON_CSCRN_H_INCLUDED

/** Draw line using Bresenham's line algorithm.
*  author Zingl Alois
*  code from http://members.chello.at/~easyfilter/bresenham.html
*  more info http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*  \param[in]  p_xStart			Vertical position of start point.
*  \param[in]  p_yStart			Horizontal position of start point.
*  \param[in]  p_xEnd			Vertical position of end point.
*  \param[in]  p_yEnd			Horizontal position of end point.
*  \param[in]  p_color			Color of line. */
void _line( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd/*, int p_color*/ );

/** Draw rectangle.
*  \param[in]  p_xStart			Vertical position of start point.
*  \param[in]  p_yStart			Horizontal position of start point.
*  \param[in]  p_xEnd			Vertical position of end point.
*  \param[in]  p_yEnd			Horizontal position of end point.
*  \param[in]  p_color			Color of line. */
void _rectangle( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd/*, p_color*/ );

/** Display string on hercules graphic card.
*  \param[in]  p_string			String to be displayed.
*  \param[in]  p_xPos			Vertical position ( 0 - 89 ).
*  \param[in]  p_yPos			Horizontal position ( 0 - 16 ).
*  \param[in]  p_attr			Attribute of string. */
void dispstrhgc( char *p_string, int p_xPos, int p_yPos, font_attr p_attr );

/** Display string with printf capability.
*   Written: Suttipong Kanakakorn
*            Wed  08-02-1989  00:33:25
*  \param[in]  p_xPos			Vertical position ( 0 - 89 ).
*  \param[in]  p_yPos			Horizontal position ( 0 - 16 ).
*  \param[in]  p_attr			Attribute of string.
*  \param[in]  p_string			String to be displayed.
*  \param[in]  p_format			Format of string. */
void dispprintf( int p_xPos, int p_yPos, font_attr p_attr, char *p_format, ... );

/** Display string on hercules graphic card.
*  \param[in]  p_xPos			Vertical position ( 0 - 89 ).
*  \param[in]  p_yPos			Horizontal position ( 0 - 16 ).
*  \param[in]  p_count			Number of blank to be displayed.
*  \param[in]  p_attr			Attribute of blank. */
void dispblank( int p_xPos, int p_yPos, size_t p_count, font_attr p_attr );

/** Set bit in attribute byte on/off from ascii control code given.
*  \param[in]  p_curfont		Current font.
*  \param[in]  p_code			Control code. */
void togglefont( font_attr *p_curfont, font_code p_code );

/** Draw frame box on screen
*   Written: Suttipong Kanakakorn
*            Fri  08-04-1989  23:39:16
*  \param[in]  p_xStart			Vertical position of start point.
*  \param[in]  p_yStart			Horizontal position of start point.
*  \param[in]  p_xEnd			Vertical position of end point.
*  \param[in]  p_yEnd			Horizontal position of end point.
*  \param[in]  p_attr			Attribute of blank. */
void framebox( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd, int p_attr );

/** Draw message box on screen at given line position, Max 55 characters.
*  \param[in]  p_linePos		Line position to display. */
void blockmsg( int p_linePos );

/** Show Error. */
void showerrno( void );

/** Save content of screen. Return pointer to content of screen.
*  \param[in]  p_xStart			Vertical position of start point.
*  \param[in]  p_yStart			Horizontal position of start point.
*  \param[in]  p_xEnd			Vertical position of end point.
*  \param[in]  p_yEnd			Horizontal position of end point.
*  \return char					Pointer to content of screen. */
char *savescrn( int p_xStart, int p_yStart, int p_xEnd, int  p_yEnd );

/** Restore content of screen..
*  \param[in]  p_scrnindex		Pointer to saved screen.
*  \param[in]  p_xStart			Vertical position of start point.
*  \param[in]  p_yStart			Horizontal position of start point.
*  \param[in]  p_xEnd			Vertical position of end point.
*  \param[in]  p_yEnd			Horizontal position of end point. */
void resscrn( char *p_scrnindex, int p_xStart, int p_yStart, int p_xEnd, int p_yEnd );

#endif /* COMMON_CSCRN_H_INCLUDED */
