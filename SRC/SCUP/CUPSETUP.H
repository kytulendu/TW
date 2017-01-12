#ifndef SCUP_CUPSETUP_H_INCLUDED
#define SCUP_CUPSETUP_H_INCLUDED

/**  */
void cupsetup( int argc, char *argv[] );

/** Print program usuage. */
void usage( void );

/** Set cup_dir to current directory. */
void set_directory( void );

/** Read option from file TWPRINT.CFG.
*   Tue  08-01-1989  12:10:39
*  \param[in]  p_mode		mode to read the config file. ( AUTO, CUR_DIR, CW_DIR )
*   AUTO_FIND               try reading from current directory first,
*                           then cw_dir if not found use the default value.
*   CUR_DIR                 read from current dir if not found display error.
*   CW_DIR                  read from TW.EXE directory if not found display error. */
void readoption( search_file_mode p_mode );

/** Save option to file TWPRINT.CFG in either current directory or cw_dir.
*  \param[in]  p_mode		mode to save the config file. ( AUTO, CUR_DIR, CW_DIR )
*   AUTO_FIND               try saving to current directory first,
*                           then cw_dir if can't use the default value.
*   CUR_DIR                 save to current dir if not found display error.
*   CW_DIR                  save to TW.EXE directory if not found display error. */
void saveoption( search_file_mode p_mode );

/** Load printer font.
*   This function allocate the font table.
*   Written : Suttipong Kanakakorn
*             Tue  08-15-1989  00:23:58
*   \param[in]  p_filename	font filename.
*   \param[in]  p_fontsize  font size in byte.
*   \return void			pointer to font table. */
void *cp_loadfont( char *p_filename, size_t p_fontsize );

#endif /* SCUP_CUPSETUP_H_INCLUDED */
