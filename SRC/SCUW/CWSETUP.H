#ifndef SCUW_CWSETUP_H_INCLUDED
#define SCUW_CWSETUP_H_INCLUDED

/** Print usage information. */
void usage( void );

/**  */
void cwsetup( int argc, char *argv[] );

/**  */
void set_directory( void );

/** Read option from file cw.cfg
*  \param[in]  p_mode		mode to read the config file. ( AUTO, CUR_DIR, CW_DIR )
*   AUTO_FIND               try reading from current directoy first,
*                           then cw_dir if not found use the default value.
*   CUR_DIR                 read from current dir if not found display error.
*   CW_DIR                  read from cw.exe directory if not found display error. */
int  readoption( search_file_mode p_mode );

/** Save option to file cw.cfg in either current directory or cw_dir
*  \param[in]  p_mode		mode to save the config file. ( AUTO, CUR_DIR, CW_DIR )
*   AUTO_FIND               try saving to current directoy first,
*                           then cw_dir if can't use the default value.
*   CUR_DIR                 save to current dir if if not found display error.
*   CW_DIR                  save to cw.exe directory if not found display error. */
void saveoption( search_file_mode p_mode );

/** Display options on screen. */
void dispoption( int i );

/** Set options. */
void setoption( void );

/** Set options to default setting. */
void set_option_to_default( void );

/**  */
void initvalue( unsigned int *x, unsigned int *y );

/** Run printer. */
void print_file( void );

/** Run font editor. */
void edit_font( void );

/** Turn off Ctrl-C checking */
void offbreak( void );

#endif /* SCUW_CWSETUP_H_INCLUDED */
