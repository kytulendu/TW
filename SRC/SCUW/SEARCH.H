#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

int searchonlyinfo( void );
int searchreplaceinfo( void );
int optionglobal( void );
int optionupper( void );
int optionword( void );
int optionnoask( void );
char *searchline( char *textline, int startpos );
void wordnotfound( void );
int searchfwd( unsigned int *x, unsigned int *y );
void addblank( void );
void searching( unsigned int *x, unsigned int *y );
void replaceword( unsigned int *x, unsigned int *y );
int searchreplace( unsigned int *x, unsigned int *y );
void replacing( unsigned int *x, unsigned int *y );

#endif
