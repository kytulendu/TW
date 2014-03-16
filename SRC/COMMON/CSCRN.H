#include "cwtype.h"

#ifndef CSCRN_H_INCLUDED
#define CSCRN_H_INCLUDED

/** Draw line using Bresenham's line algorithm.
*  code from http://members.chello.at/~easyfilter/bresenham.html
*  more info http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*  \param[in]  p_xStart		vertical position of start point.
*  \param[in]  p_yStart		horizontal position of start point.
*  \param[in]  p_xEnd		vertical position of end point.
*  \param[in]  p_yEnd		horizontal position of end point.
*  \param[in]  p_color		color of line. */
void _line( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd/*, int p_color*/ );

/** Draw rectangle.
*  \param[in]  p_xStart		vertical position of start point.
*  \param[in]  p_yStart		horizontal position of start point.
*  \param[in]  p_xEnd		vertical position of end point.
*  \param[in]  p_yEnd		horizontal position of end point.
*  \param[in]  p_color		color of line. */
void _rectangle( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd/*, p_color*/ );

/** display string on hercules graphic card.
*  \param[in]  p_string		string to be displayed.
*  \param[in]  p_x			vertical position ( 0 - 89 ).
*  \param[in]  p_y			horizontal position ( 0 - 16 ).
*  \param[in]  p_attr		attribute of string. */
void dispstrhgc( char *p_string, unsigned int p_x, unsigned int p_y, font_attr p_attr );

/** display string with printf capability.
*  \param[in]  p_x			vertical position ( 0 - 89 ).
*  \param[in]  p_y			horizontal position ( 0 - 16 ).
*  \param[in]  p_attr		attribute of string.
*  \param[in]  p_string		string to be displayed.
*  \param[in]  p_format		format of string. */
void dispprintf( unsigned int p_x, unsigned int p_y, font_attr p_attr, char *p_format, ... );

/** display string on hercules graphic card.
*  \param[in]  p_x			vertical position ( 0 - 89 ).
*  \param[in]  p_y			horizontal position ( 0 - 16 ).
*  \param[in]  p_count		number of blank to be displayed.
*  \param[in]  p_attr		attribute of blank. */
void dispblank( unsigned int p_x, unsigned int p_y, unsigned int p_count, font_attr p_attr );

/** Set bit in attribute byte on/off from ascii control code given.
*  \param[in]  p_curfont		current font.
*  \param[in]  p_code			control code. */
void togglefont( font_attr *p_curfont, font_code p_code );

/** Draw frame box on screen
*  \param[in]  p_xStart		vertical position of start point.
*  \param[in]  p_yStart		horizontal position of start point.
*  \param[in]  p_xEnd		vertical position of end point.
*  \param[in]  p_yEnd		horizontal position of end point.
*  \param[in]  p_attr		attribute of blank. */
void framebox( unsigned int p_xStart, unsigned int p_yStart, unsigned int p_xEnd, unsigned int p_yEnd, unsigned int p_attr );

/** Draw message box on screen.
*  \param[in]  p_y		vertical position. */
void blockmsg( int p_y );

/** Show Error. */
void showerrno( void );

/** Save content of screen. Return pointer to content of screen.
*  \param[in]  p_xStart		vertical position of start point.
*  \param[in]  p_yStart		horizontal position of start point.
*  \param[in]  p_xEnd		vertical position of end point.
*  \param[in]  p_yEnd		horizontal position of end point.
*  \return char				pointer to content of screen. */
char *savescrn( int p_xStart, int p_yStart, int p_xEnd, int  p_yEnd );

/** Restore content of screen..
*  \param[in]  p_scrnindex	pointer to saved screen.
*  \param[in]  p_xStart		vertical position of start point.
*  \param[in]  p_yStart		horizontal position of start point.
*  \param[in]  p_xEnd		vertical position of end point.
*  \param[in]  p_yEnd		horizontal position of end point. */
void resscrn( char *p_scrnindex, int p_xStart, int p_yStart, int p_xEnd, int p_yEnd );

#endif /* CSCRN_H_INCLUDED */
