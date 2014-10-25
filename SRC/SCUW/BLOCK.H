#ifndef SCUW_BLOCK_H_INCLUDED
#define SCUW_BLOCK_H_INCLUDED

/** Hide/display block. It cause the visual marking of a block to be alter-
*   nately switched off and on. Block manipulation commands (copy, move,
*   delete, and write to a file) work only when the block is displayed.
*   Block related cursor movements (jump to beginning/end of block) work
*   whether the block is hidden or displayed). */
void toggleblk( void );

/** Mark the beginning of a block. The marker itself is not visible on the
*   screen, and the block only becomes visibly marked when the End block
*   marker is set. */
void markbegin( unsigned int x );

/** Mark the end of a block. The marker itself is not visible on the screen
*   and the block only becomes visibly marked when the Begin block marker
*   is set. */
void markend( unsigned int x );

/** Check block it is marked or not. Return YES if it is marked , else
*   return NO. */
int haveblock( void );

/** Check position of input to see it is in block or not. Return YES if it
*   is in block , else return NO. */
int inblock( unsigned int linenum, unsigned int colnum );

/** Copy linked list from assigned line & column (first & last) to space
*   allocated from MS-DOS. Data structer of space is circular linked list,
*   previous pointer of first line point to last line & next pointer of
*   last line point to first line. Return value is pointer to first line
*   of space. Text is copied only,no graphic image is.
*
*   *fline, *lline;  first line & last line to be copied
*   fcol, lcol; first column in 1'st line & last column in last line, column is origin 0 */
struct line_node *copytospace( struct line_node *fline, struct line_node *lline, unsigned int fcol, unsigned int lcol );

/** Insert source linked list pointed by sourceline,that previous pointer
*   point to last line,to destination linked list pointed by destline and
*   first column (in thai) is destcol.
*
*   unsigned int destcol; thai column */
void insertlinklist( struct line_node *sourceline, struct line_node *destline, unsigned int destcol );

/** Delete part of linked list from struct from assigned parameter.
*
*   void deletelinklist( fline, lline, fcol, lcol )
*   struct line_node *fline, *lline; first line & last line to be deleted
*   unsigned int fcol, lcol;  first column in 1'st line & last column in last line, origin 0 */
void deletelinklist( struct line_node *fline, struct line_node *lline, unsigned int fcol, unsigned int lcol );

/** Insert block at current cursor position. */
void copyblk( unsigned int *x );

/** Delete block at current cursor position. */
void deleteblk( void );

/** Move block to insert to current cursor position. */
void moveblk( unsigned int *x );

/** Read file from disk. Parameter is filename wanted to read. Space is
*   allocated from MS-DOS. Data structer of space is circular linked list,
*   previous pointer of first line point to last line & next pointer of
*   last line point to first line. Return value is pointer to space,
*   if error return NULL. */
struct line_node *rdfiletospace( char *file_name );

/** Find size of space that allocated form MS-DOS. Data structer of space
*   is circular linked list, previous pointer of first line point to last
*   line & next pointer of last line point to first line. Return value is
*   number of line of space. */
unsigned spacesize( struct line_node *space );

/** Read block from file to insert to current cursor position. */
int readblk( unsigned int *x );

/**  */
unsigned long getfilesize( void );

/**  */
unsigned long diskfree( int driveno );

/**  */
int chkspace( char *fname );

/** char file_name[];
*    struct line_node *linebegin, *lineend;
*    unsigned int colbegin, colend; physical column  */
void writeblk( char *file_name, struct line_node *linebegin, unsigned int colbegin, struct line_node *lineend, unsigned int colend );

/**  */
void writeblock( void );

/**  */
void blkcmd( register unsigned int key, unsigned int *x );

/**  */
void blockcommand( unsigned int *x );

#endif /* SCUW_BLOCK_H_INCLUDED */
