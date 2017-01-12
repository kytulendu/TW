#ifndef SCUP_DOT_H_INCLUDED
#define SCUP_DOT_H_INCLUDED

/** Merge mail string (p_stringin) when mailmerge field ( &XXXX& ) exist.
*  \param[in]  p_stringin		Input string.
*  \param[in]  p_stringout		Output string. */
void mailmerge( char *p_stringin, char *p_stringout );

/** Process dotcommand when the input string appears as char '.' preceding.
*  \param[in]  p_string			Input string. */
void dotcommand( char *p_string );

/** Skip to non-blank char of string.
*   Updated: Suttipong Kanakakorn Mon  08-07-1989  03:06:47
*  \param[in]  p_string			Input string.
*  \return int					Number of blanks found. */
int blankskip( char *p_string );

#endif /* SCUP_DOT_H_INCLUDED */
