#ifndef SCUW_THAISYLS_GLOBAL_H_INCLUDED
#define SCUW_THAISYLS_GLOBAL_H_INCLUDED

/*------------------Global Reference------------------*/

extern unsigned char *( *FuncPtr[] )( unsigned char * );
extern unsigned char *ThaiEngCutRtn( unsigned char * );
extern unsigned char *Indx, *RightMargin, *EndOfText, *LeftLimit;

short int findchar( unsigned char ch, unsigned char *strbuf );
int nstrcmp( register unsigned char *source, register unsigned char *destination );

/*---------------------End Global---------------------*/

/*---------------Symbol that used often---------------*/

#ifndef FAIL
#define FAIL 0
#endif

#endif /* SCUW_THAISYLS_GLOBAL_H_INCLUDED */
