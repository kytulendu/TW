#ifndef SCUP_CUPSETUP_H_INCLUDED
#define SCUP_CUPSETUP_H_INCLUDED

void cupsetup( int argc, char *argv[] );
void usage( void );
void set_directory( void );
void readoption( search_file_mode mode );
void saveoption( search_file_mode mode );
int handler( int errval, int ax, int bp, int si );
void *cp_loadfont( char *fname, unsigned font_size );

#endif /* SCUP_CUPSETUP_H_INCLUDED */
