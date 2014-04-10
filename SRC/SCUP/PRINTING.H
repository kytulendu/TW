#ifndef SCUP_PRINTING_H_INCLUDED
#define SCUP_PRINTING_H_INCLUDED

void initializebufferandfont( void );
void printing( void );
void marginset( char t[] );
void contostd( char *t );
void strfilter( char *s, char cutout );
void seekbeginline( void );
void printtitle( char str[], int loc );
char *setpageformat( char form[], int max );
char *adjust( char c[], int k );
void pagewait( register int i );
void linewait( int *printquit );
void preprinterloadline( char s[] );
void clear_message( void );

#endif /* SCUP_PRINTING_H_INCLUDED */