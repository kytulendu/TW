/** MACRO for cw.exe only 15 JAN 89
*  Updated: Suttipong Kanakakorn
*           Sun  08-06-1989  10:04:26
*/

#ifndef CW_CONST_H_INCLUDED
#define CW_CONST_H_INCLUDED

#define MAXCOL 266
#define MAXRMAR 256
#define ERROR 1

#define WRAPCODE 0x8d
#define WRAPBLANK 0xa0

#define HUNAKADMITO 0xdb  /* treat as upper level */

#define ISBLANK(X)  ((X)==' ' || (X)==WRAPBLANK)

#endif /* CW_CONST_H_INCLUDED */
