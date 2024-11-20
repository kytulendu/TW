#ifndef SCUP_ATTR_H_INCLUDED
#define SCUP_ATTR_H_INCLUDED

/* -- print data to buffer and manage all attribute -- */

/** Clear buffer.
*  \param[in]  p_buffer         font buffer.
*  \return FONT                 pointer to the font buffer. */
FONT *cp_lqscr_blank( FONT *p_buffer );

/** Write subscript character middle and lower to font character buffer.
*  \param[in]  p_buffer         font buffer.
*  \param[in]  p_middle         middle subscript buffer.
*  \param[in]  p_lower          lower subscript buffer.
*  \return FONT                 pointer to the font buffer. */
FONT *cp_sub_middle_lower( FONT *p_buffer, FONTSCR *p_middle, FONTSCR *p_lower );

/** Write subscript character upper and middle to font character buffer.
*  \param[in]  p_buffer         font buffer.
*  \param[in]  p_upper          upper subscript buffer.
*  \param[in]  p_middle         middle subscript buffer.
*  \return FONT                 pointer to the font buffer. */
FONT *cp_sub_upper_middle( FONT *p_buffer, FONTSCR *p_upper, FONTSCR *p_middle );

/** Write superscript character upper and middle to font character buffer.
*  \param[in]  p_buffer         font buffer.
*  \param[in]  p_upper          upper subscript buffer.
*  \param[in]  p_middle         middle subscript buffer.
*  \return FONT                 pointer to the font buffer. */
FONT *cp_super_upper_middle( FONT *p_buffer, FONTSCR *p_upper, FONTSCR *p_middle );

/** Write superscript character middle and lower to font character buffer.
*  \param[in]  p_buffer         font buffer.
*  \param[in]  p_middle         middle subscript buffer.
*  \param[in]  p_lower          lower subscript buffer.
*  \return FONT                 pointer to the font buffer. */
FONT *cp_super_middle_lower( FONT *p_buffer, FONTSCR *p_middle, FONTSCR *p_lower );

/** Underline character in buffer.
*  \param[in]  p_newchar        new character buffer.
*  \param[in]  p_oldchar        old character pointer.
*  \return FONT                 pointer to newchar buffer. */
FONT *cp_underline( FONT *p_newchar, FONT *p_oldchar );

/** Doubleline character in buffer.
*  \param[in]  p_newchar        new character buffer.
*  \param[in]  p_oldchar        old character pointer.
*  \return FONT                 pointer to newchar buffer. */
FONT *cp_doubleline( FONT *p_newchar, FONT *p_oldchar );

/** Enlarge character in graphic buffer.
*  \param[in]  p_buffer         graphic buffer.
*  \param[in]  p_index          index to text position in graphic buffer.
*  \return int                  index to next position in graph buffer. */
int cp_enlarge( struct cp_grlqbuf p_buffer, int p_index );

/** Change any character to boldface.
*  \param[in]  p_buffer         graphic buffer.
*  \param[in]  p_index          index to text position in graphic buffer. */
void cp_bold( struct cp_grlqbuf p_buffer, int p_index );

#endif /* SCUP_ATTR_H_INCLUDED */
