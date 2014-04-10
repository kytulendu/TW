#ifndef SCUF_GETCH_H_INCLUDED
#define SCUF_GETCH_H_INCLUDED

int cursorkey( char *key );
int get_pos( unsigned int *x, unsigned int *y, unsigned int block_x, unsigned int block_y, unsigned int width_x, unsigned int width_y );

#endif /* SCUF_GETCH_H_INCLUDED */