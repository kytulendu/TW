#ifndef COMMON_FILEUTIL_H_INCLUDED
#define COMMON_FILEUTIL_H_INCLUDED

/**  */
boolean file_exist( char *filename );

/**  */
int havewild( char *filname );

/** read screen font from current dir first, if not found try reading from search_path
*   Tue  08-01-1989  13:52:17 */
void readscrfont( void *font_buffer, char *fontname, char *search_path );

/**  */
search_file_mode find_file( char *filename, char *search_path );

/** Error handler */
int handler( int errval, int ax, int bp, int si );

#endif /* COMMON_FILEUTIL_H_INCLUDED */
