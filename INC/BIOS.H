/*  bios.h

Access to bios services.

Copyright (c) 1987, 1992 by Borland International
All Rights Reserved.
*/

#ifndef far
#define far
#endif

#if !defined(__BIOS_H)
#define __BIOS_H

/* cmd values for _bios_keybrd() */

#define _KEYBRD_READ            0       /* read key */
#define _NKEYBRD_READ           0x10    /* read key - enhanced */
#define _KEYBRD_READY           1       /* check key ready */
#define _NKEYBRD_READY          0x11    /* check key ready - enhanced */
#define _KEYBRD_SHIFTSTATUS     2       /* get shift status */
#define _NKEYBRD_SHIFTSTATUS    0x12    /* get shift status - enhanced */

/* cmd values for _bios_printer() */

#define _PRINTER_WRITE  0       /* send a byte to printer */
#define _PRINTER_INIT   1       /* initialize printer */
#define _PRINTER_STATUS 2       /* read printer status */

/* register structure definitions for int86(), int86x() */

#ifndef _REG_DEFS
#define _REG_DEFS

struct WORDREGS {
	unsigned int    ax, bx, cx, dx, si, di, cflag, flags;
};

struct BYTEREGS {
	unsigned char   al, ah, bl, bh, cl, ch, dl, dh;
};

union   REGS {
	struct  WORDREGS x;
	struct  BYTEREGS h;
};

struct  SREGS {
	unsigned int    es;
	unsigned int    cs;
	unsigned int    ss;
	unsigned int    ds;
};

struct  REGPACK {
	unsigned    r_ax, r_bx, r_cx, r_dx;
	unsigned    r_bp, r_si, r_di, r_ds, r_es, r_flags;
};

#endif  /* _REG_DEFS */

/* Old-style BIOS functions.
*/
int      bioskey( int __cmd );
int      biosprint( int __cmd, int __abyte, int __port );
long     biostime( int __cmd, long __newtime );

/* Miscellaneous prototypes for MSC compatibility
*/
int          int86( int __intno,
union REGS  *__inregs,
union REGS  *__outregs );

#endif  /* __BIOS_H */
