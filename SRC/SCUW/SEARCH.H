#ifndef SCUW_SEARCH_H_INCLUDED
#define SCUW_SEARCH_H_INCLUDED

/** Display word not found message. */
void wordnotfound( void );

/**  */
int searchfwd( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
void searching( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
int searchreplace( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

/**  */
void replacing( unsigned int *p_xCursorPos, unsigned int *y_CursorPos );

#endif /* SCUW_SEARCH_H_INCLUDED */
