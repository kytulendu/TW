#ifndef SCUW_FILE_H_INCLUDED
#define SCUW_FILE_H_INCLUDED

/**  */
int handler( int errval, int ax, int bp, int si );

/**  */
int read_file( char *file_name );

/**  */
void destroynode( void );

#endif /* SCUW_FILE_H_INCLUDED */
