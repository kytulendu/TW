#ifndef SCUW_KBD_H_INCLUDED
#define SCUW_KBD_H_INCLUDED

/**  */
void waitkbd( unsigned int x, unsigned int y );

/**  */
int changekey( int key );

/**  */
int readkbd( void );

/** Alt_char_map function
*
*   remap alternate character, return (-1) if fail. */
int alt_char_map( int c );

#endif /* SCUW_KBD_H_INCLUDED */
