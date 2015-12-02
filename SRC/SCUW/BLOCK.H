#ifndef SCUW_BLOCK_H_INCLUDED
#define SCUW_BLOCK_H_INCLUDED

/** Hide/display block. It cause the visual marking of a block to be
*   alternately switched off and on. Block manipulation commands (copy, move,
*   delete, and write to a file) work only when the block is displayed.
*   Block related cursor movements (jump to beginning/end of block) work
*   whether the block is hidden or displayed). */
void toggleblk( void );

/** Mark the beginning of a block. The marker itself is not visible on the
*   screen, and the block only becomes visibly marked when the End block
*   marker is set.
*  \param[in]  p_xCursorPos		Column cursor position in editing window to mark. */
void markbegin( unsigned int p_xCursorPos );

/** Mark the end of a block. The marker itself is not visible on the screen
*   and the block only becomes visibly marked when the Begin block marker
*   is set.
*  \param[in]  p_xCursorPos		Column cursor position in editing window to mark. */
void markend( unsigned int p_xCursorPos );

/** Check block it is marked or not.
*  \return int					YES if it is marked, else NO. */
int haveblock( void );

/** Check position of input to see it is in block or not, column is origin 0
*  \param[in]  p_line			Line number.
*  \param[in]  p_col			Column position (physical).
*  \return int					Return YES if it is in block, else return NO. */
int inblock( unsigned int p_line, unsigned int p_col );

/** Copy linked list from assigned line & column (first & last) to space
*   allocated from MS-DOS. Data structure of space is circular linked list,
*   previous pointer of first line point to last line & next pointer of
*   last line point to first line. Return value is pointer to first line
*   of space. Text is copied only, no graphic image is.
*  \param[in]  p_firstLine		First line to be copied.
*  \param[in]  p_lastLine		Last line to be copied.
*  \param[in]  p_firstCol		First column (physical) in 1'st line, column is origin 0.
*  \param[in]  p_lastCol		Last column (physical) in last line, column is origin 0.
*  \return struct line_node		Pointer to line copied. */
struct line_node *copytospace( struct line_node *p_firstLine, struct line_node *p_lastLine, unsigned int p_firstCol, unsigned int p_lastCol );

/** Insert source linked list pointed by sourceline, that previous pointer
*   point to last line, to destination linked list pointed by p_destLine and
*   first column (in Thai) is p_destCol.
*  \param[in]  p_sourceLine		Source linked list.
*  \param[in]  p_destLine		Destination linked list.
*  \param[in]  p_destCol		Destination column (physical). */
void insertlinklist( struct line_node *p_sourceLine, struct line_node *p_destLine, unsigned int p_destCol );

/** Delete part of linked list from structure from assigned parameter.
*  \param[in]  p_firstLine		First line to be deleted.
*  \param[in]  p_lastLine		Last line to be deleted.
*  \param[in]  p_firstCol		First column (physical) in 1'st line, column is origin 0.
*  \param[in]  p_lastCol		Last column (physical) in last line, column is origin 0. */
void deletelinklist( struct line_node *p_firstLine, struct line_node *p_lastLine, unsigned int p_firstCol, unsigned int p_lastCol );

/** Insert block at current cursor position.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void copyblk( unsigned int *p_xCursorPos );

/** Delete selected block. */
void deleteblk( void );

/** Move block to insert to current cursor position.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void moveblk( unsigned int *p_xCursorPos );

/** Read file from disk. Parameter is file name wanted to read. Space is
*   allocated from MS-DOS. Data structure of space is circular linked list,
*   previous pointer of first line point to last line & next pointer of
*   last line point to first line.
*  \param[in]  p_filename		File name want to read.
*  \return int					Return pointer to space, if error return NULL. */
struct line_node *rdfiletospace( char *p_filename );

/** Find size of space that allocated form MS-DOS. Data structure of space
*   is circular linked list, previous pointer of first line point to last
*   line & next pointer of last line point to first line.
*  \param[in]  p_space			linenode to find it's size.
*  \return unsigned int			Number of line of p_space. */
unsigned int spacesize( struct line_node *p_space );

/** Read block from file to insert to current cursor position.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void readblk( unsigned int *p_xCursorPos );

/** Get file size. */
unsigned long getfilesize( void );

/** Get disk free space of given drive.
*  \param[in]  p_driveno		Drive to get free space.
*  \return unsigned long		Free space. */
unsigned long diskfree( char p_driveno );

/** Check for size of given file and free disk space.
*  \param[in]  p_filename		File name want to check it's size.
*  \return int					0 if no error, 1 if not enough space. */
int chkspace( char *p_filename );

/** */
void writeblk( char *p_filename, struct line_node *p_firstLine, unsigned int p_firstCol, struct line_node *p_lastLine, unsigned int p_lastCol );

/** Write block to file. */
void writeblock( void );

/**  */
void blkcmd( register unsigned int p_key, unsigned int *p_xCursorPos );

/**  */
void blockcommand( unsigned int *p_xCursorPos );

#endif /* SCUW_BLOCK_H_INCLUDED */
