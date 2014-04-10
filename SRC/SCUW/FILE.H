#ifndef SCUW_FILE_H_INCLUDED
#define SCUW_FILE_H_INCLUDED

int handler( int errval, int ax, int bp, int si );
int havewild( char filname[] );
int read_file( char *file_name );
void abandonfile( void );
boolean file_exist( char *filename );

#endif /* SCUW_FILE_H_INCLUDED */
