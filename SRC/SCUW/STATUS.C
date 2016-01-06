/*
* ============================================================================
* STATUS.C
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <dir.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\var.h"

#include "var.h"

void relmarstatus( void ) {
	if ( relmargin == YES ) {
		dispstrhgc( "ปล่อยขอบ", 65 - 3, 2, BOLDATTR );
	} else {
		dispstrhgc( "       ", 65 - 3, 2, NORMALATTR );
	}
}

void arabictothai( char *p_string ) {
	while ( *p_string != '\0' ) {
		if ( ( *p_string >= '0' ) && ( *p_string <= '9' ) ) {
			*p_string = *p_string | 0xf0;
		}
		p_string++;
	}
}

void writepage( void ) {
	char page[4];
	dispstrhgc( "หน้า    ", 4, 2, NORMALATTR );
	sprintf( page, "%d", ( ( lineno - 1 ) / lineperpage ) + 1 );
	arabictothai( page );
	dispstrhgc( page, 8, 2, NORMALATTR );
}

void writeline( void ) {
	char line[5];
	dispstrhgc( "บรรทัด    ", 11, 2, NORMALATTR );
	sprintf( line, "%d", ( ( lineno - 1 ) % lineperpage ) + 1 );
	arabictothai( line );
	dispstrhgc( line, 17, 2, NORMALATTR );
}

void writelineno( void ) {
	char st2[6];
	dispstrhgc( "     บรรทัด       ", 4, 2, NORMALATTR );
	sprintf( st2, "%u", lineno );
	arabictothai( st2 );
	dispstrhgc( st2, 15, 2, NORMALATTR );
}

void writepageline( void ) {
	if ( pagebreak ) {
		writepage( );
		writeline( );
	} else {
		writelineno( );
	}
}

void writecolno( unsigned int p_xCursorPos ) {
	char st2[5];
	dispstrhgc( "คอลัมน์", 21, 2, NORMALATTR );
	sprintf( st2, "%u", p_xCursorPos + 1 );
	dispstrhgc( "    ", 27, 2, NORMALATTR );
	arabictothai( st2 );
	dispstrhgc( st2, 27, 2, NORMALATTR );
}

void writeinsmode( void ) {
	if ( insertmode ) {
		dispstrhgc( "พิมพ์แทรก", 33, 2, NORMALATTR );
	} else {
		dispstrhgc( " พิมพ์ทับ ", 33, 2, NORMALATTR );
	}
}

void writelanguage( void ) {
	if ( thaimode ) {
		dispstrhgc( "  ไทย  ", 42 - 1, 2, BOLDATTR );
	} else {
		dispstrhgc( "English", 42 - 1, 2, BOLDATTR );
	}
}

void writeattr( void ) {
	dispstrhgc( "            ", 50 - 1, 2, NORMALATTR );
	if ( fontused == 0 ) {
		dispstrhgc( " ตัวอักษรปกติ", 50 - 1, 2, fontused );
	} else if ( ( fontused & 0x08 ) == 0x08 ) {
		dispstrhgc( "ตัวยกขึ้น", 50 - 1, 2, fontused & 0xf7 );
	} else if ( ( fontused & 0x10 ) == 0x10 ) {
		dispstrhgc( "ตัวห้อย", 50 - 1, 2, fontused & 0xef );
	} else {
		dispstrhgc( "ตัวอักษร", 50 - 1, 2, fontused );
	}
}

void writefilename( void ) {
	dispstrhgc( "แฟ้มข้อมูล :                     ", 48, 0, NORMALATTR );
	if ( filename[0] != '\0' ) {
		dispstrhgc( filename, 58, 0, BOLDATTR );
	}
}

void writedriveno( void ) {
	dispstrhgc( "ไดรฟ์  :", 40, 0, NORMALATTR );
	prchar( 'A' + getdisk( ), BOLDATTR, 45, NORMALATTR );
}

void writestatus( unsigned int p_xCursorPos ) {
	writepageline( );
	writecolno( p_xCursorPos );
	writeinsmode( );
	writelanguage( );
	writedriveno( );
	writefilename( );
	writeattr( );
	relmarstatus( );
}
