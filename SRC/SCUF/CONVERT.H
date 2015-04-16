#ifndef SCUF_COVERT_H_INCLUDED
#define SCUF_COVERT_H_INCLUDED

/** Load font. */
int load_font( );

/** Save font. */
int save_font( );

/** malloc all_font
*   load font into all_font
*   set X, Y
*   set pos_x,pos_y to zero
*   draw grid
*   malloc matrix_image
*   set BYTE = sizeof X in bytes
*/
int load_fed( );

/** save font from all_font */
int save_fed( );

/**  */
int load_24( );

/**  */
void con_24_to_fed( char *oldfon, char *newfon );

/**  */
int save_24( );

/**  */
void con_fed_to_24( char *buff, char *new );

/**  */
int save_prn( );

/**  */
void fed_to_prn_ch( char *buff, char *res );

/**  */
void conv_fed_to_22x16( char *buff, char *result );

/**  */
int load_prn( );

/**  */
void prn_to_fed_ch( char *buff, char *res );

/**  */
void conv_22x16_to_fed( char *buff, char *result );

/**  */
int load_scr( );

/**  */
int save_scr( );

/**  */
int load_sup_sub( );

/**  */
void con_sup_to_fed_chr( char *oldch, char *newch );

/**  */
void con_sup_to_fed( char *oldfon, char *newfon );

/**  */
int save_sup_sub( );

/**  */
void con_fed_to_sup_chr( char *oldch, char *newch );

/**  */
void con_fed_to_sup( char *oldfon, char *newfon );

#endif /* SCUF_COVERT_H_INCLUDED */
