#ifndef SCUW_CWSETUP_H_INCLUDED
#define SCUW_CWSETUP_H_INCLUDED

/** Initialize tab value from right margin. */
void inittabvalue( void );

/**  */
void cwsetup( int argc, char *argv[] );

/** Read option from file TW.CFG
*  \param[in]  p_mode		mode to read the config file. ( AUTO, CUR_DIR, CW_DIR )
*   AUTO_FIND               try reading from current directory first,
*                           then cw_dir if not found use the default value.
*   CUR_DIR                 read from current dir if not found display error.
*   CW_DIR                  read from TW.EXE directory if not found display error.
*  \return int				Return 1 if found and read successful.
*                           Return 0 if not found in CUR_DIR and CW_DIR, then do autofind.
*                           Return -1 if search in CUR_DIR or CW_DIR and not found. */
int readoption( search_file_mode p_mode );

/** Save option to file TW.CFG in either current directory or cw_dir
*  \param[in]  p_mode		mode to save the config file. ( AUTO, CUR_DIR, CW_DIR )
*   AUTO_FIND               try saving to current directory first,
*                           then cw_dir if can't use the default value.
*   CUR_DIR                 save to current dir if not found display error.
*   CW_DIR                  save to TW.EXE directory if not found display error. */
void saveoption( search_file_mode p_mode );

/** Set options. */
void setoption( void );

/** Initialize starting value.
*  \param[in]  xCursorPos	Column cursor position in editing window.
*  \param[in]  yCursorPos	Line cursor position in editing window. */
void initvalue( unsigned int *xCursorPos, unsigned int *yCursorPos );

/** Initialize screen.*/
void initscrn( void );

/** Run printer. */
void print_file( void );

/** Run font editor. */
void edit_font( void );

#endif /* SCUW_CWSETUP_H_INCLUDED */
