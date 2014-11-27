#ifndef SCUP_PRNCNTRL_H_INCLUDED
#define SCUP_PRNCNTRL_H_INCLUDED

/**  */
void putp( unsigned int c );

/**  */
int PrinterReadstatus( void );

/**  */
void PrinterInitialize( void );

/**  */
void PrinterSetFormLenghtInch( register unsigned int n );

/**  */
void PrinterSkipLine( register int n );

/**  */
void PrinterFormFeed( void );

/** Will feed n/180 inches on 24 pins printer and
*   n/216 inches on 9 pins printer
*
*   modify by Suttipong Kanakakorn Tue  08-29-1989  12:56:39 */
void PrinterLineFeed( register unsigned int n );

/**  */
void PrinterMasterSelectMode( register unsigned int n );

/**  */
void PrinterSetGraphicMode9pinQuadrupleDensity( register unsigned int n );

/**  */
void PrinterSetGraphicMode24pinTripleDensity( register unsigned int n );

/**  */
void PrinterSet10cpi( void );

#endif /* SCUP_PRNCNTRL_H_INCLUDED */
