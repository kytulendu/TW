#ifndef GRPHC_H_INCLUDED
#define GRPHC_H_INCLUDED

/* From cwgraphc.c edisp.asm hdisp.asm */
void prchar( unsigned int c, unsigned int attr, unsigned int x, unsigned int y );
void prblank( unsigned int x, unsigned int y );
void setcurpos( unsigned int x, unsigned int y, int thaimode );
void plot( unsigned int x, unsigned int y );
void setgraph( void );
void settext( void );
char stdtoku( char c );
char kutostd( char c );
int  thaikey( unsigned int c );
int  asm_keypressed( void );
void savepic( void );
void retpic( void );
void clsall( void );
void clsgraph( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 );
void clrline( unsigned int x1, unsigned int y1, unsigned int x2 );
void prakeaw( void );
int whatlevel( char c );
void rdchardot( unsigned int x, unsigned int y );
void wrchardot( unsigned int x, unsigned int y );

#endif /* GRPHC_H_INCLUDED */
