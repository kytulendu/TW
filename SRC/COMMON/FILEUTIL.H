#ifndef COMMON_FILEUTIL_H_INCLUDED
#define COMMON_FILEUTIL_H_INCLUDED

boolean file_exist( char *filename );
int havewild( char *filname );

/* read screen font */
void readscrfont( void *font_buffer, char *fontname, char *search_path );
/*
search_file_mode find_file( char *filename, char *search_path );
*/
#endif /* COMMON_FILEUTIL_H_INCLUDED */
