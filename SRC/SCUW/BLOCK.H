#ifndef SCUW_BLOCK_H_INCLUDED
#define SCUW_BLOCK_H_INCLUDED

void toggleblk( void );
void markbegin( unsigned int x );
void markend( unsigned int x );
int haveblock( void );
int inblock( unsigned int linenum, unsigned int colnum );
struct line_node *copytospace( struct line_node *fline, struct line_node *lline, unsigned int fcol, unsigned int lcol );
void insertlinklist( struct line_node *sourceline, struct line_node *destline, unsigned int destcol );
void deletelinklist( struct line_node *fline, struct line_node *lline, unsigned int fcol, unsigned int lcol );
unsigned spacesize( struct line_node *space );
struct line_node *rdfiletospace( char file_name[] );
void copyblk( unsigned int *x );
void deleteblk( void );
void moveblk( unsigned int *x );
int readblk( unsigned int *x );
unsigned long getfilesize( void );
unsigned long diskfree( int driveno );
void writeblk( char file_name[], struct line_node *linebegin, unsigned int colbegin, struct line_node *lineend, unsigned int colend );
void writeblock( void );
void blkcmd( unsigned int key, unsigned int *x );
void blockcommand( unsigned int *x );
int chkspace( char * );

#endif /* SCUW_BLOCK_H_INCLUDED */
