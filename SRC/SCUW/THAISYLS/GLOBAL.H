#ifndef SCUW_THAISYLS_GLOBAL_H_INCLUDED
#define SCUW_THAISYLS_GLOBAL_H_INCLUDED

/*------------------Global Reference------------------*/

extern unsigned char *( *FuncPtr[] )( char * );
extern unsigned char *ThaiEngCutRtn( char * );
extern unsigned char *Indx, *RightMargin, *EndOfText, *LeftLimit;

short int findchar( unsigned char ch, unsigned char *strbuf );
int nstrcmp( register char *source, register char *destination );

/*---------------------End Global---------------------*/

/*---------------Symbol that used often---------------*/
#ifndef NULL
#define NULL 0
#endif

#ifndef FAIL
#define FAIL 0
#endif

#endif /* SCUW_THAISYLS_GLOBAL_H_INCLUDED */
