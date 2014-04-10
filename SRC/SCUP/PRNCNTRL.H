#ifndef SCUP_PRNCNTRL_H_INCLUDED
#define SCUP_PRNCNTRL_H_INCLUDED

void putp( unsigned c );
int PrinterReadstatus( void );
void PrinterInitialize( void );
void PrinterSetFormLenghtInch( register unsigned n );
void PrinterSkipLine( register int n );
void PrinterFormFeed( void );
void PrinterLineFeed( register unsigned n );
void PrinterMasterSelectMode( register unsigned n );
void PrinterSetGraphicMode9pinQuadrupleDensity( register unsigned n );
void PrinterSetGraphicMode24pinTripleDensity( register unsigned n );
void PrinterSet10cpi( void );

#endif /* SCUP_PRNCNTRL_H_INCLUDED */
