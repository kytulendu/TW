#ifndef SCUP_DOT_H_INCLUDED
#define SCUP_DOT_H_INCLUDED

/** Mailmerge Function. [ f(stringin,stringout) ]
*   To merge mail string (stringin)
*   when mailmerge field ( &XXXX& ) exist
*   output to stringout. */
void mailmerge( char *stringin, char *stringout );

/** Dotcommand Function. [ f(string) ]
*   To process dotcommand when the input
*   string appears as char '.' preceding. */
void dotcommand( char *string );

/** Blankskip Routine.
*   Skip to non-blank char of string s[].
*   Return number of blanks found.
*   Updated: Suttipong Kanakakorn Mon  08-07-1989  03:06:47 */
int blankskip( char *s );

#endif /* SCUP_DOT_H_INCLUDED */
