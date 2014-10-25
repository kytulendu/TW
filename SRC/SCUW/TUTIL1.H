#ifndef SCUW_TUTIL1_H_INCLUDED
#define SCUW_TUTIL1_H_INCLUDED

/** find length of thai string
*   input
*    thaist : thai string
*    return : length of thai string
*    Modify : Suttipong  Kanakakakorn
*
*   Mon  07-31-1989  08:32:36   use only pointer no index. */
unsigned int thaistrlen( register unsigned char *thaist );

/** Find column of string from column given in Thai,ignore level of Thai
*   character & attribute code of font. Column is origin 0. Find current
*   attribute of font of string via *font too. */
unsigned int linearcolumn( char *textstream, unsigned int thaicol, font_attr *font );

#endif /* SCUW_TUTIL1_H_INCLUDED */
