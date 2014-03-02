#ifndef GRPHC_H_INCLUDED
#define GRPHC_H_INCLUDED

/* From cwgraphc.c edisp.asm hdisp.asm */
void prchar( unsigned c, unsigned attr, unsigned x, unsigned y );
void prblank( unsigned x, unsigned y );
void setcurpos( unsigned x, unsigned y, int thaimode );
void plot( unsigned x, unsigned y );
void setgraph( void );
void settext( void );
char stdtoku( char c );
char kutostd( char c );
int  thaikey( unsigned c );
int  asm_keypressed( void );
void savepic( void );
void retpic( void );
void clsall( void );
void clsgraph( unsigned x1, unsigned y1, unsigned x2, unsigned y2 );
void clrline( unsigned x1, unsigned y1, unsigned x2 );
void prakeaw( void );
int whatlevel( char c );
void rdchardot( unsigned int x, unsigned int y );
void wrchardot( unsigned int x, unsigned int y );

#endif /* GRPHC_H_INCLUDED */
