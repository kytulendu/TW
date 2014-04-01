#ifndef COVERT_H_INCLUDED
#define COVERT_H_INCLUDED

int load_font( );
int save_font( );
int save_fed( );
int cleanup_load_routine( );
int load_fed( );
int load_24( );
int con_24_to_fed( char *oldfon, char *newfon );
int save_24( );
int con_fed_to_24( char *buff, char *new );
int save_prn( );
int fed_to_prn_ch( char *buff, char *res );
int conv_fed_to_22x16( char *buff, char *result );
int load_prn( );
int prn_to_fed_ch( char *buff, char *res );
int conv_22x16_to_fed( char *buff, char *result );
int load_scr( );
int save_scr( );
int load_sup_sub( );
int con_sup_to_fed_chr( char *oldch, char *newch );
int con_sup_to_fed( char *oldfon, char *newfon );
int save_sup_sub( );
int con_fed_to_sup_chr( char *oldch, char *newch );
int con_fed_to_sup( char *oldfon, char *newfon );

#endif /* COVERT_H_INCLUDED */
