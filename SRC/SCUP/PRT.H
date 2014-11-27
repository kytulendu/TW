#ifndef SCUP_PRT_H_INCLUDED
#define SCUP_PRT_H_INCLUDED

/**  */
void AllocateBuffer9pin( void );

/** Load 3 of 9 pin printer font */
int PrinterLoadFont9pin( void );

/** Print string 'line' to printer
*   this module is called from external routine. */
void PrinterLoadLine9pin( char *line );

/** check character level,
*   upper  level then return 1
*   middle level  "     "    2
*   below  level  "     "    3 */
int islevel( int *pline );

#endif /* SCUP_PRT_H_INCLUDED */
