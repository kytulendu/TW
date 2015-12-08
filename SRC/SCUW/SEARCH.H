#ifndef SCUW_SEARCH_H_INCLUDED
#define SCUW_SEARCH_H_INCLUDED

/** Search string
*   require
*   (1)  source    ->  source string for search
*   (2)  option    ->  option that will be
*                     G  ->  global search
*                     U  ->  mix lower & upper
*                     N  ->  no pause
*                     W  ->  full word
*   return 0 if error occur. */
int searchonlyinfo( void );

/** Search and replace string
*   require
*   (1)  source    ->  source string for search
*   (2)  replace   ->  string to replace
*   (3)  option    ->  option that will be
*                     G  ->  global search
*                     U  ->  mix lower & upper
*                     N  ->  no pause
*                     W  ->  full word
*   return 0 if error occur. */
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
unsigned char *searchline( unsigned char *p_textline, unsigned int p_startpos );

/** Display word not found message. */
void wordnotfound( void );

/**  */
int searchfwd( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
void addblank( void );

/**  */
void searching( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
void replaceword( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
int searchreplace( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
void replacing( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

#endif /* SCUW_SEARCH_H_INCLUDED */
