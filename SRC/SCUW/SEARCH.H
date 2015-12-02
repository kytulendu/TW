#ifndef SCUW_SEARCH_H_INCLUDED
#define SCUW_SEARCH_H_INCLUDED

/** Searching string
*   require
*   (1)  source    ->  source string for search
*   (2)  replace   ->  string to replace
*   (3)  option    ->  option that will be
*                     G  ->  global search
*                     U  ->  mix lower & upper
*                     N  ->  no pause
*                     W  ->  full word
*   return 0 if error occur. */
int searchonlyinfo( void );

/**  */
int searchreplaceinfo( void );

/**  */
int optionglobal( void );

/**  */
int optionupper( void );

/**  */
int optionword( void );

/**  */
int optionnoask( void );

/**  */
unsigned char *searchline( unsigned char *textline, unsigned int startpos );

/**  */
void wordnotfound( void );

/**  */
int searchfwd( unsigned int *x, unsigned int *y );

/**  */
void addblank( void );

/**  */
void searching( unsigned int *x, unsigned int *y );

/**  */
void replaceword( unsigned int *x, unsigned int *y );

/**  */
int searchreplace( unsigned int *x, unsigned int *y );

/**  */
void replacing( unsigned int *x, unsigned int *y );

#endif /* SCUW_SEARCH_H_INCLUDED */
