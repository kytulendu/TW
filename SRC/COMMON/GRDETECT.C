/*
* ============================================================================
* Graphics hardware detector module for TURBO C 2.0
*
* Kraisorn Liansee
* Date    : 4/27/89
* Updated : 4/27/89
* Updated : Suttipong Kanakakorn Sun  08-20-1989  11:28:45
* ============================================================================
*/

#include <dos.h>

#include "grdetect.h"

void graph_detecthardware( graphics_hardware *mode_ptr ) {
	union REGS reg_pack;
	unsigned char far *mem_ptr;
	unsigned char byte_keep;

	*mode_ptr = UNKNOWN_HW;

	reg_pack.h.ah = 0x0F;						/* read current video state */
	int86( 0x10, &reg_pack, &reg_pack );

	if ( reg_pack.h.al == 0x07 ) {				/* Monochrome mode */
		/* May be CGA/EGA/VGA/MDA/Hercules */
		if ( is_egavga( ) ) {
			/* EGA/VGA test */
			egavga_class( mode_ptr );			/* Classify EGA/VGA */
			return;
		}
		/* CGA/MDA/Hercules test */
		if ( check_vretrace( ) == 0 ) {			/* No Vertical retrace change*/
			mem_ptr = ( unsigned char far * ) 0xB8000L;	/* point to screen */
			byte_keep = *mem_ptr;
			( *mem_ptr ) ^= 0xFF;
			byte_keep ^= 0xFF;
			if ( byte_keep != ( *mem_ptr ) ) {	/* No memory in this area */
				*mode_ptr = MDA;				/* IBM Monochrome monitor */
			} else {
				*mode_ptr = CGA;
			}
			return;								/* CGA adapter */
		} else {
			*mode_ptr = HERCMONO;
			return;
		}
	} else {									/* Assuming ALL except Mono */
		if ( is_egavga( ) ) {
			/* EGA/VGA test */
			egavga_class( mode_ptr );			/* Classify EGA/VGA */
			return;
		}
		if ( is_mcga( ) ) {
			*mode_ptr = MCGA;
			return;
		}

		/* CGA or ATT400 */
		if ( is_att400( ) ) {					/* CGA 400 line test */
			*mode_ptr = ATT400;
		} else {
			*mode_ptr = CGA;
		}
		return;
	}
}

int is_egavga( void ) {
	union REGS reg_pack;

	reg_pack.x.ax = 0x1200;				/* Read EGA/VGA configuration */
	reg_pack.h.bl = 0x10;
	reg_pack.h.bh = 0xFF;				/* video controller mode */
	reg_pack.h.cl = 0x0F;				/* video config mode */
	int86( 0x10, &reg_pack, &reg_pack );

	if ( ( reg_pack.h.cl > 0x0C ) ||	/* invalid configuration */
		( reg_pack.h.bh > 0x01 ) ||		/* invalid controller mode */
		( reg_pack.h.bl > 0x03 ) ) {	/* invalid memory size */
		return ( 0 );
	} else {
		return ( 1 );
	}
}

void egavga_class( graphics_hardware *mode_ptr ) {
	union REGS reg_pack;
	unsigned char far *mem_ptr;

	reg_pack.x.ax = 0x1200;				/* Read EGA/VGA configuration */
	reg_pack.h.bl = 0x10;
	reg_pack.h.bh = 0xFF;				/* video controller mode */
	reg_pack.h.cl = 0x0F;				/* video config mode */
	int86( 0x10, &reg_pack, &reg_pack );

	*mode_ptr = EGA64;					/* Assumes EGA with 64K first */
	if ( reg_pack.h.bh == 1 ) {			/* Config in Monochrome mode */
		*mode_ptr = EGAMONO;
		return;
	}
	if ( ( reg_pack.h.bl == 0 ) || ( reg_pack.h.cl == 0 ) || ( reg_pack.h.cl == 1 )
		|| ( reg_pack.h.cl == 6 ) || ( reg_pack.h.cl == 7 ) ) {
		return;							/* EGA 64K */
	}
	*mode_ptr = EGA;
	mem_ptr = ( unsigned char far * ) 0xC0039L;	/* Checking ROM */
	if ( is_mcga( ) ) {
		*mode_ptr = VGA;
	} else {
		if ( ( *mem_ptr == 0x5A ) && ( *( mem_ptr + 1 ) == 0x34 ) && ( *( mem_ptr + 2 ) == 0x34 )
			&& ( *( mem_ptr + 3 ) == 0x39 ) ) {
			*mode_ptr = VGA;
		}
	}
	return;
}

int is_mcga( void ) {
	union REGS reg_pack;

	reg_pack.x.ax = 0x1A00;				/* Read video information */
	int86( 0x10, &reg_pack, &reg_pack );

	if ( reg_pack.h.al != 0x1A ) {		/* Not MCGA or VGA */
		return ( 0 );
	}
	if ( ( reg_pack.h.bl == 7 ) || ( reg_pack.h.bl == 8 ) ||
		( reg_pack.h.bl == 0x0B ) || ( reg_pack.h.bl == 0x0C ) ) {
		return ( 1 );
	} else {
		return ( 0 );
	}
}

int is_att400( void ) {
	union REGS reg_pack;
    struct SREGS sreg_pack;

    unsigned char ret;
    unsigned int far *idWord;
    unsigned char far *idByte;

    /* Ideas are from https://github.com/MobyGamer/TOPBENCH */

    /* AT&T 6300 have no int15 support in BIOS. */
    reg_pack.h.ah = 0xC0;
    int86x( 0x15, &reg_pack, &reg_pack, &sreg_pack );

    /* AT&T 6300 found! */
    if ( reg_pack.x.cflag ) {
        /* Use AT&T 6300 specific BIOS int */
        /** Int 1A/AH=FEh
        *		AT&T 6300 - READ TIME AND DATE
        *		AH = FEh
        *	Return:
        *		BX = day count (0 = Jan 1, 1984)
        *		CH = hour
        *		CL = minute
        *		DH = second
        *		DL = hundredths */
        reg_pack.x.ax = 0xFE00;
        int86( 0x1a, &reg_pack, &reg_pack );
        if ( reg_pack.x.cx != 0 ) {			/* if any bits are set, we have AT&T 6300 */
            return ( 1 );
        }
    } else if ( ( ( reg_pack.x.flags && reg_pack.x.cflag ) == 0 ) && ( reg_pack.h.ah == 0 ) ) {
        /* Check for Compaq */
        /* Since I don't have this computer and there are no emulator as the date of writing
        *  This code is untested! */
        idWord = ( unsigned int far * ) MK_FP( sreg_pack.es, ( reg_pack.x.bx + 2 ) );
        idByte = ( unsigned char far * ) MK_FP( sreg_pack.es, ( reg_pack.x.bx + 4 ) );

        if ( *idWord == 0x01FC ) {
            if ( *idByte == 0 ) {
                /* Detect Compaq Portable III internal plasma flat panel monitor */
                ret = inportb( 0x1BC6 );
                if ( ( ret >> 4 ) == 4 ) {  /* 4 if have internal plasma monitor */
                    return ( 1 );
                }
            }
        }
    }

    return ( 0 );
}

int check_vretrace( void ) {
	register unsigned int change;
	register unsigned int old_value;
	unsigned int count;

	old_value = inportb( 0x3BA ) & 0x80;
	change = 0;
	for ( count = 0; count <= 0x7FFF; count++ ) {
		if ( ( inportb( 0x3BA ) & 0x80 ) != old_value ) {
			if ( ++change > 10 ) {		/* Vertical Retrace changes */
				break;
			}
		}
	}
	if ( change <= 10 ) {				/* Not hercules */
		return ( 0 );
	}

	for ( count = 0; count <= 0x7FFF; count++ ) {
		if ( ( inportb( 0x3BA ) & 0x30 ) != 0x10 ) {
			return ( 1 );
		}
	}

	return ( 2 );
}
