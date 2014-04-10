#ifndef SCUP_PRTUTIL_H_INCLUDED
#define SCUP_PRTUTIL_H_INCLUDED

int find_line_space( void );
int find_line_perpage( void );
int find_max_line_perpage( void );
int find_max_userline_perpage( void );
void set_all_lineperpage( set_linespace_mode mode );
void line_feed( unsigned n );
void skip_line( unsigned n );
char *find_lineperinch( void );

#endif /* SCUP_PRTUTIL_H_INCLUDED */