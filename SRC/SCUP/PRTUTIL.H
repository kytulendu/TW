#ifndef SCUP_PRTUTIL_H_INCLUDED
#define SCUP_PRTUTIL_H_INCLUDED

/**  */
int find_line_space( void );

/**  */
int find_line_perpage( void );

/**  */
int find_max_line_perpage( void );

/**  */
int find_max_userline_perpage( void );

/**  */
void set_all_lineperpage( set_linespace_mode mode );

/** feed n/216 inche or n/180 inch depend on printer, n can be any integer */
void line_feed( unsigned int n );

/** skip n lines */
void skip_line( unsigned int n );

/**  */
char *find_lineperinch( void );

#endif /* SCUP_PRTUTIL_H_INCLUDED */