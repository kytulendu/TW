/*------------------Global Reference------------------*/

extern unsigned char *( *FuncPtr[] )( char * );
extern unsigned char *ThaiEngCutRtn( char * );
extern unsigned char *Indx, *RightMargin, *EndOfText, *LeftLimit;

short int findchar( unsigned char ch, unsigned char *strbuf );
int nstrcmp( register char *source, register char *destination );

/*---------------------End Global---------------------*/

/*---------------Symbol that used often---------------*/
#define NULL 0
#define FAIL 0
