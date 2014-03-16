#ifndef CWSETUP_H_INCLUDED
#define CWSETUP_H_INCLUDED

void cwsetup( int argc, char *argv[] );
void usage( void );
void set_directory( void );
int  readoption( search_file_mode mode );
void saveoption( search_file_mode mode );
void blankoption( int y );
void dispoption( int i );
void setoption( void );
void initvalue( unsigned int *x, unsigned int *y );
void edit_font( void );
void offbreak( void );

#endif
