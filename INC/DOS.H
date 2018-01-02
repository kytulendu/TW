/*  dos.h

Defines structs, unions, macros, and tions for dealing
with MSDOS and the Intel iAPX86 microprocessor family.

Copyright (c) 1987, 1992 by Borland International
All Rights Reserved.
*/

#ifndef far
#define far
#endif

#ifndef __DOS_H
#define __DOS_H

#define FA_NORMAL   0x00        /* Normal file, no attributes */
#define FA_RDONLY   0x01        /* Read only attribute */
#define FA_HIDDEN   0x02        /* Hidden file */
#define FA_SYSTEM   0x04        /* System file */
#define FA_LABEL    0x08        /* Volume label */
#define FA_DIREC    0x10        /* Directory */
#define FA_ARCH     0x20        /* Archive */

/* MSC names for file attributes */

#define _A_NORMAL   0x00        /* Normal file, no attributes */
#define _A_RDONLY   0x01        /* Read only attribute */
#define _A_HIDDEN   0x02        /* Hidden file */
#define _A_SYSTEM   0x04        /* System file */
#define _A_VOLID    0x08        /* Volume label */
#define _A_SUBDIR   0x10        /* Directory */
#define _A_ARCH     0x20        /* Archive */

struct  dfree {
	unsigned df_avail;
	unsigned df_total;
	unsigned df_bsec;
	unsigned df_sclus;
};

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

#ifndef _FFBLK_DEF
#define _FFBLK_DEF
struct  ffblk {
	char        ff_reserved[21];
	char        ff_attrib;
	unsigned    ff_ftime;
	unsigned    ff_fdate;
	long        ff_fsize;
	char        ff_name[13];
};
#endif  /* _FFBLK_DEF */

/* axret values for _hardresume() */

#define _HARDERR_IGNORE 0   /* ignore error */
#define _HARDERR_RETRY  1   /* retry the operation */
#define _HARDERR_ABORT  2   /* abort program */
#define _HARDERR_FAIL   3   /* fail the operation */

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

void getdfree( unsigned char __drive, struct dfree  *__dtable );

void _harderr( void( *__fptr )( ) );
void _hardresume( int __axret );
void _hardretn( int __retn );
void harderr( int( *__handler )( ) );
void hardresume( int __axret );
void hardretn( int __retn );

unsigned char inportb( unsigned __portid );

int  int86( int __intno, union REGS  *__inregs, union REGS  *__outregs );
int  int86x( int __intno, union REGS  *__inregs,  union REGS  *__outregs, struct SREGS  *__segregs );
int  intdos( union REGS  *__inregs, union REGS  *__outregs );
int  intdosx( union REGS  *__inregs, union REGS  *__outregs, struct SREGS  *__segregs );
void intr( int __intno, struct REGPACK  *__preg );

void outportb( unsigned __portid, unsigned char __value_d );

#define MK_FP( seg,ofs )( (void  * )( seg ) +( void  * )( ofs ))
#define FP_SEG( fp )( (unsigned )( void  * )( void * )( fp ))
#define FP_OFF( fp )( (unsigned )( fp ))

void nosound( void );
void sound( unsigned frequency );

#define peek( a,b )( *( (int  far* )MK_FP( (a ),( b )) ))
#define peekb( a,b )( *( (char far* )MK_FP( (a ),( b )) ))
#define poke( a,b,c )( *( (int  far* )MK_FP( (a ),( b )) ) =( int )( c ))
#define pokeb( a,b,c )( *( (char far* )MK_FP( (a ),( b )) ) =( char )( c ))

#endif  /* __DOS_H */
