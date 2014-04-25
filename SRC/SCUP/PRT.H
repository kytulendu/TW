#ifndef SCUP_PRT_H_INCLUDED
#define SCUP_PRT_H_INCLUDED

void AllocateBuffer9pin( void );
int PrinterLoadFont9pin( void );
int islevel( int *pline );
void PrinterLoadLine( char pline[] );
void PrinterLoadLine9pin( char line[] );

#endif /* SCUP_PRT_H_INCLUDED */
