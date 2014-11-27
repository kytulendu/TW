#ifndef SCUP_CUPSETUP_H_INCLUDED
#define SCUP_CUPSETUP_H_INCLUDED

/**  */
void cupsetup( int argc, char *argv[] );

/**  */
void usage( void );

/**  */
void set_directory( void );

/** read option from file cuprint.cfg
*   mode == AUTO try reading from current directoy first, then cw_dir
*    if not found use the default value
*   mode == CUR_DIR read from current dir
*    if not found display error
*   mode == CW_DIR  read from cw.exe directory
*    if not found display error
*   Tue  08-01-1989  12:10:39
*/
void readoption( search_file_mode mode );

/** save option to file cw.cfg in either current directory or cw_dir. */
void saveoption( search_file_mode mode );

/**  */
int handler( int errval, int ax, int bp, int si );

/** Function     : cp_loadfont
*   Description  : load printer font
*   Parameters   : fname - font filename
*   Return value :       - pointer to font table
*   Remark       : This function allocate the font table
*   Written      : Suttipong Kanakakorn
*                  Tue  08-15-1989  00:23:58 */
void *cp_loadfont( char *fname, unsigned int font_size );

#endif /* SCUP_CUPSETUP_H_INCLUDED */
