#ifndef SCUW_TUTIL1_H_INCLUDED
#define SCUW_TUTIL1_H_INCLUDED

/** Find column of string from column given in Thai, ignore level of Thai
*   character & attribute code of font. Column is origin 0. Find current
*   attribute of font of string via *p_attr too.
*  \param[in]  p_textstream     Pointer to string.
*  \param[in]  p_thaiCol        Column, column is origin 0
*  \param[in]  p_attr           Character attribute.
*  \return size_t                */
size_t linearcolumn( unsigned char *p_textstream, unsigned int p_thaiCol, font_attr *p_attr );

/** Convert Arabic number to Thai number.
*  \param[in]  p_string         Number string to convert. */
void arabictothai( unsigned char *p_string );

#endif /* SCUW_TUTIL1_H_INCLUDED */
