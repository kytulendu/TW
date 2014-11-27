#ifndef SCUP_ATTR_H_INCLUDED
#define SCUP_ATTR_H_INCLUDED

/* -- print data to buffer and manage all attribute -- */

/** Function     : cp_lqscr_blank
*   Description  : clear buffer
*   Parameters   : buf - font buffer
*   Return value : pointer to the font buffer
*   Remark       : This function used buf as buffer */
FONT *cp_lqscr_blank( FONT *buf );

/** Function     : cp_sub_middle_lower
*   Description  : write subscript character middle and
*                  lower to font character buffer
*   Parameters   : buf    - font buffer
*                  middle - middle subscript buffer
*                  lower  - lower subscript buffer
*   Return value : pointer to the font buffer
*   Remark       : This function used buf as buffer */
FONT *cp_sub_middle_lower( FONT *buf, FONTSCR *middle, FONTSCR *lower );

/** Function     : cp_sub_upper_middle
*   Description  : write subscript character upper and
*                  middle to font character buffer
*   Parameters   : buf    - font buffer
*                  middle - middle subscript buffer
*                  upper  - upper subscript buffer
*   Return value : pointer to the font buffer
*   Remark       : This function used buf as buffer */
FONT *cp_sub_upper_middle( FONT *buf, FONTSCR *upper, FONTSCR *middle );

/** Function     : cp_super_upper_middle
*   Description  : write superscript character upper and
*                  middle to font character buffer
*   Parameters   : buf    - font buffer
*                  middle - middle subscript pointer
*                  upper  - upper subscript pointer
*   Return value : pointer to the font buffer
*   Remark       : This function used buf as buffer */
FONT *cp_super_upper_middle( FONT *buf, FONTSCR *upper, FONTSCR *middle );

/** Function     : cp_super_middle_lower
*   Description  : write superscript character middle and
*                  lower to font character buffer
*   Parameters   : buf   - font buffer
*                  lower - lower superscript pointer
*   Return value : pointer to the font buffer
*   Remark       : This function used buf as buffer */
FONT *cp_super_middle_lower( FONT *buf, FONTSCR *middle, FONTSCR *lower );

/** Function     : cp_underline
*   Description  : underline character in buffer
*   Parameters   : newchar - new character buffer
*                 oldchar - old character pointer
*   Return value : pointer to newchar buffer
*   Remark       : This function used newchar as buffer */
FONT *cp_underline( FONT *newchar, FONT *oldchar );

/** Function     : cp_doubleline
*   Description  : doubleline character in buffer
*   Parameters   : newchar - new character buffer
*                  oldchar - old character pointer
*   Return value : pointer to newchar buffer
*   Remark       : This function used newchar as buffer */
FONT *cp_doubleline( FONT *newchar, FONT *oldchar );

/** Function     : cp_enlarge
*   Description  : enlarge character in graphic buffer
*   Parameters   : buf   - graphic buffer
*                  index - index to text position in graphic buffer
*   Return value : index to next position in graph buffer */
int cp_enlarge( struct cp_grlqbuf buf, int index );

/** Function     : cp_bold
*   Description  : change any character to boldface
*   Parameters   : buf   - graphic buffer
*                  index - index to text position in graphic buffer
*   Return value : NONE */
void cp_bold( struct cp_grlqbuf buf, int index );

#endif /* SCUP_ATTR_H_INCLUDED */
