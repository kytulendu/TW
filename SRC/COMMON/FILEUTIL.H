#ifndef COMMON_FILEUTIL_H_INCLUDED
#define COMMON_FILEUTIL_H_INCLUDED

/** Check if given file exist.
*   \param[in]  p_filename		Name of file to check.
*   \return boolean				0 (NO), file not exist.
*								1 (YES), file exist. */
boolean file_exist( char *p_filename );

/** Find file.
*   \param[in]  p_filename		Name of file to search.
*   \param[in]  p_searchpath	Path to search for given file.
*   \return search_file_mode	-1 (NOT_FOUND), File not found.
*								1 (CUR_DIR), Found in current directory.
*								2 (CW_DIR), Found in Thai Write directory. */
search_file_mode find_file( char *p_filename, char *p_searchpath );

/** Check if given file name have wildcard character.
*   \param[in]  p_filename		Name of file to check.
*   \return boolean				0 (NO), not have wildcard.
*								1 (YES), have wildcard. */
boolean havewild( char *p_filename );

/** Read screen font from current dir first, if not found try reading from searchpath
*   Tue  08-01-1989  13:52:17
*   \param[in]  p_fontbuffer	Font buffer array.
*   \param[in]  p_fontname		Font file name to load.
*   \param[in]  p_searchpath	Path to search for given font file. */
void readscrfont( void *p_fontbuffer, char *p_fontname, char *p_searchpath );

/** Error handler */
int handler( int errval, int ax, int bp, int si );

#endif /* COMMON_FILEUTIL_H_INCLUDED */
