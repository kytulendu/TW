#ifndef SCUW_TUTIL1_H_INCLUDED
#define SCUW_TUTIL1_H_INCLUDED

/** Find column of string from column given in Thai, ignore level of Thai
*   character & attribute code of font. Column is origin 0. Find current
*   attribute of font of string via *font too. */
unsigned int linearcolumn( char *textstream, unsigned int thaicol, font_attr *font );

#endif /* SCUW_TUTIL1_H_INCLUDED */
