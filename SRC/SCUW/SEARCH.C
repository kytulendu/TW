/*
* ===============================================================================
* STATUS.C
* ===============================================================================
*/

#include <stdlib.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\ccommon.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\grphc.h"
#include "..\common\kbdcode.h"
#include "..\common\sound.h"

#include "convert.h"
#include "var.h"

#include "del.h"
#include "edit.h"
#include "getstr.h"
#include "ins.h"
#include "move.h"
#include "tutil1.h"

#include "search.h"

int searchonlyinfo( void ) {
	int i;
	framebox( 8 - CENTER_FACTOR, 4, ( 21 - CENTER_FACTOR ) + 60, 10, REVERSEATTR );
	dispstrhgc( "ใส่คำที่ต้องการค้นหา :", 11 - CENTER_FACTOR, 5, REVERSEATTR );
	dispstrhgc( "ค้นหาแบบไหน (ใส่ตัวอักษรของตัวเลือกที่ต้องการ) :", 11 - CENTER_FACTOR, 6, REVERSEATTR );
	dispstrhgc( "ตัวเลือก : G = เริ่มค้นหาตั้งแต่ต้นแฟ้มข้อมูล", 11 - CENTER_FACTOR, 7, REVERSEATTR );
	dispstrhgc( "U = ไม่สนใจตัวเล็กหรือตัวใหญ่ (เช่น a กับ A)", 20 - CENTER_FACTOR, 8, REVERSEATTR );
	dispstrhgc( "W = ค้นหาเป็นคำ (หรือเป็นประโยคในภาษาไทย)", 20 - CENTER_FACTOR, 9, REVERSEATTR );
	dispstrhgc( "<ESC> ยกเลิก", 11 - CENTER_FACTOR, 10, 2 );
	dispstrhgc( source, 29 - CENTER_FACTOR, 5, REVERSEATTR );
	dispstrhgc( option, 51 - CENTER_FACTOR, 6, REVERSEATTR );
	pagecomplete = NO;
	while ( 1 ) {
		i = getstring( source, 29 - CENTER_FACTOR, 5, 50, REVERSEATTR, THAIENG );
		switch ( i ) {
		case ESCKEY:
			return( ESCKEY );
		case DNKEY:
		case YES:
			do {
				i = getstring( option, 51 - CENTER_FACTOR, 6, 3, REVERSEATTR, ENGLISH );
				switch ( i ) {
				case ESCKEY:
					return( ESCKEY );
				case YES:
					strupr( option );    /* to upper case   */
					return( YES );
				}
			} while ( i != UPKEY );
			break;
		}
	}
	return 0;
}

int searchreplaceinfo( void ) {
	int i, j;
	framebox( 8 - CENTER_FACTOR, 4, ( 21 - CENTER_FACTOR ) + 60, 12, REVERSEATTR );
	dispstrhgc( "ใส่คำที่ต้องการค้นหา :", 11 - CENTER_FACTOR, 5, REVERSEATTR );
	dispstrhgc( "ใส่คำที่ต้องการแทนที่ :", 11 - CENTER_FACTOR, 6, REVERSEATTR );
	dispstrhgc( "ค้นหาแบบไหน (ใส่ตัวอักษรของตัวเลือกที่ต้องการ) :", 11 - CENTER_FACTOR, 7, REVERSEATTR );
	dispstrhgc( "ตัวเลือก : G = ค้นหา/แทนที่ทั้งหมดตั้งแต่ต้นจนจบ", 11 - CENTER_FACTOR, 8, REVERSEATTR );
	dispstrhgc( "U = ไม่สนใจตัวเล็กหรือตัวใหญ่ (เช่น a กับ A)", 20 - CENTER_FACTOR, 9, REVERSEATTR );
	dispstrhgc( "W = ค้นหาเป็นคำ (หรือเป็นประโยคในภาษาไทย)", 20 - CENTER_FACTOR, 10, REVERSEATTR );
	dispstrhgc( "N = ไม่ต้องหยุดถามว่าจะแทนที่หรือไม่", 20 - CENTER_FACTOR, 11, REVERSEATTR );
	dispstrhgc( "<ESC> ยกเลิก", 11 - CENTER_FACTOR, 12, REVERSEATTR );
	dispstrhgc( source, 29 - CENTER_FACTOR, 5, REVERSEATTR );
	dispstrhgc( replace, 29 - CENTER_FACTOR, 6, REVERSEATTR );
	dispstrhgc( option, 51 - CENTER_FACTOR, 7, REVERSEATTR );
	pagecomplete = NO;
	while ( 1 ) {
		i = getstring( source, 29 - CENTER_FACTOR, 5, 50, REVERSEATTR, THAIENG );
		switch ( i ) {
		case ESCKEY:
			return( ESCKEY );
		case DNKEY:
		case YES:
			do {
				i = getstring( replace, 29 - CENTER_FACTOR, 6, 50, REVERSEATTR, THAIENG );
				switch ( i ) {
				case ESCKEY:
					return( ESCKEY );
				case DNKEY:
				case YES:
					do {
						j = getstring( option, 51 - CENTER_FACTOR, 7, 3, REVERSEATTR, ENGLISH );
						switch ( j ) {
						case ESCKEY:
							return( ESCKEY );
						case YES:
							strupr( option );
							return( YES );
						}
					} while ( j != UPKEY );
					break;
				}
			} while ( i != UPKEY );
			break;
		}
	}
	return 0;
}

int optionglobal( void ) {
	int i = 0;
	while ( option[i] != '\0' ) {
		if ( option[i] == 'G' ) {
			return( YES );
		}
		i++;
	}
	return( NO );
}

int optionupper( void ) {
	int i = 0;
	while ( option[i] != '\0' ) {
		if ( option[i] == 'U' ) {
			return( YES );
		}
		i++;
	}
	return( NO );
}

int optionword( void ) {
	int i = 0;
	while ( option[i] != '\0' ) {
		if ( option[i] == 'W' ) {
			return( YES );
		}
		i++;
	}
	return( NO );
}

int optionnoask( void ) {
	int i = 0;
	while ( option[i] != '\0' ) {
		if ( option[i] == 'N' ) {
			return( YES );
		}
		i++;
	}
	return( NO );
}

char *searchline( char *textline, int startpos ) { /* startpos origin 0 */
	int i;
	static char buffer[MAXCOL * 5];
	char *point, *buffaddr, *textaddr;
	while ( ( startpos > 0 ) && ( *textline != '\0' ) ) {
		if ( ( *textline < 32 ) && ( *textline != '\0' ) ) {
			textline++;
		}
		textline++;
		startpos--;
	}
	textaddr = textline;
	i = 0;
	while ( *textline != '\0' ) {
		buffer[i++] = *( textline++ );
	}
	buffer[i] = ' ';
	buffer[i + 1] = '\0';
	if ( optionupper( ) ) {
		strupr( buffer );
	}
	if ( ( point = strstr( buffer, source ) ) != NULL ) {
		buffaddr = buffer;
		while ( buffaddr++ != point ) {
			textaddr++;
		}
		return( textaddr );
	} else {
		return( NULL );
	}
}

void wordnotfound( void ) {
	errorsound( );
	framebox( 27 - CENTER_FACTOR, 5, ( 27 - CENTER_FACTOR ) + 33, 7, REVERSEATTR );
	dispstrhgc( "หาคำไม่พบ ! กด ESC เพื่อทำงานต่อ", 30 - CENTER_FACTOR, 6, REVERSEATTR );
	while ( ebioskey( 0 ) != ESCKEY );
	pagecomplete = NO;
}
int searchfwd( unsigned int *x, unsigned int *y ) {
	struct line_node *savepage, *templine;
	int linecount, savecol, i, enlargeflag, startpos;
	font_attr font = 0;
	char *foundpoint, *addr;
	savecol = firstcol;
	savepage = curpage;
	storeline( curline );
	templine = curpage;
	linecount = wind.width - 1;
	while ( templine != curline ) {
		linecount--;
		templine = templine->next;
	}
	startpos = linearcolumn( curline->text, *x + firstcol, &font );
	foundpoint = NULL;
	while ( ( foundpoint == NULL ) && ( curline != sentinel ) ) {
		foundpoint = searchline( curline->text, startpos );
		if ( foundpoint != NULL ) {		/* found */
			while ( ( *y = findrow( ) ) >= wind.width ) {
				curpage = curpage->next;
			}
			*x = 0;
			firstcol = 0;
			addr = curline->text;
			enlargeflag = NO;
			while ( addr != foundpoint ) {
				if ( ( whatlevel( *addr ) == MIDDLE ) && ( *addr >= 32 ) ) {
					if ( enlargeflag ) {
						( *x )++;
					}
					( *x )++;
				} else {
					if ( *addr == ENLARGECODE ) {
						enlargeflag = enlargeflag ^ 1;
					}
				}
				addr++;
			}
			for ( i = 0; source[i] != '\0'; i++ ) {
				if ( whatlevel( source[i] ) == MIDDLE ) {
					if ( enlargeflag ) {
						( *x )++;
					}
					( *x )++;
				}
			}
			while ( *x >= wind.length ) {
				firstcol = firstcol + wind.length;
				*x = *x - wind.length;
			}
		} else {
			if ( linecount > 0 ) {
				linecount--;
				curline = curline->next;
				lineno++;
			} else {
				curline = curline->next;
				lineno++;
				curpage = curline;
				linecount = wind.width - 1;
			}
			startpos = 0;
		}
	}
	if ( foundpoint == NULL ) {
		curline = sentinel->previous;
		curpage = curline;
		loadtoline( curline->text );
		endline( x );
	}
	loadtoline( curline->text );
	if ( savepage != curpage ) {
		showpageall( );
	} else {
		if ( firstcol != savecol ) {
			showpageall( );
		}
	}
	if ( foundpoint != NULL ) {
		return( YES );
	} else {
		return( NO );
	}
}

void addblank( void ) {
	int i = 79;
	while ( i != 0 ) {
		source[i] = source[i - 1];
		i--;
	}
	source[0] = ' ';
	i = strlen( source );
	source[i] = ' ';
	source[i + 1] = '\0';
}

void searching( unsigned int *x, unsigned int *y ) {
	storeline( curline );
	if ( searchonlyinfo( ) == YES ) {
		showpageall( );
		replaceflag = NO;
		if ( optionword( ) ) {
			addblank( );
		}
		if ( optionupper( ) ) {
			strupr( source );
		}
		if ( optionglobal( ) ) {
			topfile( x );
			showpageall( );
		}
		if ( !searchfwd( x, y ) ) {
			wordnotfound( );
		}
	}
}

void replaceword( unsigned int *x, unsigned int *y ) {
	int i;
	for ( i = strlen( source ); i != 0; i-- ) {
		backspace( x );
	}
	while ( replace[i] != '\0' ) {
		insert_char( replace[i], x, y );
		i++;
	}
	refreshline( 0, *y );
}

int searchreplace( unsigned int *x, unsigned int *y ) {
	int ok = 0, i, ask = YES, global = NO, found = NO;
	if ( optionnoask( ) ) {
		ok = 'y';
		ask = NO;
	}
	if ( optionglobal( ) ) {
		topfile( x );
		showpageall( );
		global = YES;
	}
	do {
		if ( searchfwd( x, y ) ) {
			found = YES;
			if ( ask ) {
				dispstrhgc( "แทนที่หรือไม่ ? (Y/N) ", 1, 2, BOLDATTR );
				while ( ( ok != 'y' ) && ( ok != 'n' ) &&
					( ok != 'Y' ) && ( ok != 'N' ) ) {
					while ( !keypressed( ) ) {
						setcurpos( 19, 2, thaimode );
						for ( i = 0; i < 15000; i++ );
						setcurpos( 19, 2, thaimode );
						for ( i = 0; i < 15000; i++ );
						setcurpos( wind.col + *x, wind.row + *y, thaimode );
						for ( i = 0; i < 15000; i++ );
						setcurpos( wind.col + *x, wind.row + *y, thaimode );
						for ( i = 0; i < 15000; i++ );
					} /* while !keypressed */
					ok = ebioskey( 0 );
					if ( ( ok != CNTRL_U ) && ( ok != ESCKEY ) ) {
						ok = ok & 0xff;
					} else {
						return( CNTRL_U );
					}
				} /* while ok */
			} else {
				if ( keypressed( ) ) {
					ok = ebioskey( 0 );
					if ( ( ok == CNTRL_U ) || ( ok == ESCKEY ) ) {
						return( CNTRL_U );
					}
				}
				ok = 'y';
			}
			if ( ( ok == 'y' ) || ( ok == 'Y' ) ) {
				replaceword( x, y );
			}
			ok = 0;
		} else {
			global = NO;
		}
	} while ( global );
	return( found );
}

void replacing( unsigned int *x, unsigned int *y ) {
	storeline( curline );
	if ( searchreplaceinfo( ) == YES ) {
		showpageall( );
		replaceflag = YES;
		if ( optionword( ) ) {
			addblank( );
		}
		if ( optionupper( ) ) {
			strupr( source );
		}
		if ( !searchreplace( x, y ) ) {
			wordnotfound( );
		}
	}
}
