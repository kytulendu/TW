#ifndef STATUS_H_INCLUDED
#define STATUS_H_INCLUDED

void relmarstatus( void );
void arabictothai( char *st );
void writepage( void );
void writeline( void );
void writelineno( void );
void writepageline( void );
void writecolno( unsigned int x );
void writeinsmode( void );
void writelanguage( void );
void writeattr( void );
void writefilename( void );
void writedriveno( void );
void writestatus( unsigned int x );

#endif
