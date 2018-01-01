#ifndef SCUF_FONTMSG_H_INCLUDED
#define SCUF_FONTMSG_H_INCLUDED

void put_box( int x1, int y1, int x2, int y2 );

/** use
*   creat = 1 when want to creat new file that doesn't exist.
*   creat = 0 when want to display a directory to screen when file not exist. */
int fontnamebox( char *pname, int creat );

void error_message( char *prompt );

int immediatebox( int x, int y, char *str, char *ans );

#endif /* SCUF_FONTMSG_H_INCLUDED */
