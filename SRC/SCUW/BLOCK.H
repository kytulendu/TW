#ifndef SCUW_BLOCK_H_INCLUDED
#define SCUW_BLOCK_H_INCLUDED

/** Check block it is marked or not.
*  \return int                  YES if it is marked, else NO. */
int haveblock( void );

/** Check position of input to see it is in block or not, column is origin 0
*  \param[in]  p_line           Line number.
*  \param[in]  p_col            Column position (physical).
*  \return int                  Return YES if it is in block, else return NO. */
int inblock( unsigned int p_line, unsigned int p_col );

/** Insert source linked list pointed by sourceline, that previous pointer
*   point to last line, to destination linked list pointed by p_destLine and
*   first column (in Thai) is p_destCol.
*  \param[in]  p_sourceLine     Source linked list.
*  \param[in]  p_destLine       Destination linked list.
*  \param[in]  p_destCol        Destination column (physical). */
void insertlinklist( struct line_node *p_sourceLine, struct line_node *p_destLine, unsigned int p_destCol );

/** Read file from disk. Parameter is file name wanted to read. Space is
*   allocated from MS-DOS. Data structure of space is circular linked list,
*   previous pointer of first line point to last line & next pointer of
*   last line point to first line.
*  \param[in]  p_filename       File name want to read.
*  \return int                  Return pointer to space, if error return NULL. */
struct line_node *rdfiletospace( char *p_filename );

/** Write line node to file.
*  \param[in]  p_filename       File name want to write.
*  \param[in]  p_firstLine      First line node.
*  \param[in]  p_firstCol       First column (physical).
*  \param[in]  p_lastLine       Last line node.
*  \param[in]  p_lastCol        Last column (physical). */
void writeblk( char *p_filename, struct line_node *p_firstLine, unsigned int p_firstCol, struct line_node *p_lastLine, unsigned int p_lastCol );

/**  */
void blkcmd( register int p_key, unsigned int *p_xCursorPos );

/**  */
void blockcommand( unsigned int *p_xCursorPos );

#endif /* SCUW_BLOCK_H_INCLUDED */
