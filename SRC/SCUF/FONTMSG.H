#ifndef SCUF_FONTMSG_H_INCLUDED
#define SCUF_FONTMSG_H_INCLUDED

int fontnamebox( char*pname, int creat );
int error_message( char *prompt );
int immediatebox( int x, int y, char *str, char*ans );
int put_box( int x1, int y1, int x2, int y2 );

#endif /* SCUF_FONTMSG_H_INCLUDED */
