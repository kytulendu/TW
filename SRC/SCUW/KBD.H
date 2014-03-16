#ifndef KBD_H_INCLUDED
#define KBD_H_INCLUDED

void waitkbd( unsigned int x, unsigned int y );
int changekey( int key );
int readkbd( void );
int alt_char_map( int c );

#endif
