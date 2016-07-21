/*
* ============================================================================
* SEARCH.C
* ============================================================================
*/

#include <stdlib.h>
#include <string.h>

#include "..\common\cwtype.h"
#include "..\common\common.h"
#include "..\common\var.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\ekbd.h"
#include "..\common\kbdcode.h"
#include "..\common\sound.h"
#include "..\common\getstr.h"

#include "var.h"

#include "del.h"
#include "edit.h"
#include "ins.h"
#include "move.h"
#include "tutil2.h"

#include "search.h"

int searchonlyinfo( void ) {
	int i;

	framebox( 4 + center_factor, 4, ( 7 + center_factor ) + 69, 10, REVERSEATTR );
	dispstrhgc( "ใส่คำที่ต้องการค้นหา :", ( 7 + center_factor ), 5, REVERSEATTR );
	dispstrhgc( "ค้นหาแบบไหน (ใส่ตัวอักษรของตัวเลือกที่ต้องการ) :", ( 7 + center_factor ), 6, REVERSEATTR );
	dispstrhgc( "ตัวเลือก : G = เริ่มค้นหาตั้งแต่ต้นแฟ้มข้อมูล", ( 7 + center_factor ), 7, REVERSEATTR );
	dispstrhgc( "U = ไม่สนใจตัวเล็กหรือตัวใหญ่ (เช่น a กับ A)", ( 7 + center_factor ), 8, REVERSEATTR );
	dispstrhgc( "W = ค้นหาเป็นคำ (หรือเป็นประโยคในภาษาไทย)", ( 7 + center_factor ), 9, REVERSEATTR );
	dispstrhgc( "<ESC> ยกเลิก", ( 7 + center_factor ), 10, 2 );
	dispstrhgc( source, ( 7 + center_factor ), 5, REVERSEATTR );
	dispstrhgc( option, ( 7 + center_factor ), 6, REVERSEATTR );

	pagecomplete = NO;

	for ( ;; ) {
		i = getstring( source, ( 7 + center_factor ) + 18, 5, 49, REVERSEATTR, THAIENG );

		switch ( i ) {
		case ESCKEY:
			return( ESCKEY );
		case DNKEY:
		case YES:
			do {
				i = getstring( option, ( 7 + center_factor ) + 40, 6, 3, REVERSEATTR, ENGLISH );

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
}

int searchreplaceinfo( void ) {
	int i;
	int j;

	framebox( 4 + center_factor, 4, ( 7 + center_factor ) + 69, 12, REVERSEATTR );
	dispstrhgc( "ใส่คำที่ต้องการค้นหา :", ( 7 + center_factor ), 5, REVERSEATTR );
	dispstrhgc( "ใส่คำที่ต้องการแทนที่ :", ( 7 + center_factor ), 6, REVERSEATTR );
	dispstrhgc( "ค้นหาแบบไหน (ใส่ตัวอักษรของตัวเลือกที่ต้องการ) :", ( 7 + center_factor ), 7, REVERSEATTR );
	dispstrhgc( "ตัวเลือก : G = เริ่มค้นหาตั้งแต่ต้นแฟ้มข้อมูล", ( 7 + center_factor ), 8, REVERSEATTR );
	dispstrhgc( "U = ไม่สนใจตัวเล็กหรือตัวใหญ่ (เช่น a กับ A)", ( 7 + center_factor ), 9, REVERSEATTR );
	dispstrhgc( "W = ค้นหาเป็นคำ (หรือเป็นประโยคในภาษาไทย)", ( 7 + center_factor ), 10, REVERSEATTR );
	dispstrhgc( "N = ไม่ต้องหยุดถามว่าจะแทนที่หรือไม่", ( 7 + center_factor ), 11, REVERSEATTR );
	dispstrhgc( "<ESC> ยกเลิก", ( 7 + center_factor ), 12, REVERSEATTR );
	dispstrhgc( source, ( 7 + center_factor ), 5, REVERSEATTR );
	dispstrhgc( replace, ( 7 + center_factor ), 6, REVERSEATTR );
	dispstrhgc( option, ( 7 + center_factor ), 7, REVERSEATTR );

	pagecomplete = NO;

	for ( ;; ) {
		i = getstring( source, ( 7 + center_factor ) + 18, 5, 49, REVERSEATTR, THAIENG );

		switch ( i ) {
		case ESCKEY:
			return( ESCKEY );
		case DNKEY:
		case YES:
			do {
				i = getstring( replace, ( 7 + center_factor ) + 18, 6, 49, REVERSEATTR, THAIENG );

				switch ( i ) {
				case ESCKEY:
					return( ESCKEY );
				case DNKEY:
				case YES:
					do {
						j = getstring( option, ( 7 + center_factor ) + 40, 7, 3, REVERSEATTR, ENGLISH );

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

unsigned char *searchline( unsigned char *p_textline, unsigned int p_startpos ) { /* startpos origin 0 */
	size_t i;
	unsigned char *buffer;
	unsigned char *buffaddr;
	unsigned char *textaddr;
	char *point;

	buffer = ( unsigned char * ) malloc( MAXCOL * sizeof( unsigned char ) );
	if ( buffer == NULL ) {
		errorsound( );
		return( NULL );							/* Not enough memory */
	}

	while ( ( p_startpos > 0 ) && ( *p_textline != '\0' ) ) {
		if ( ( *p_textline < 32 ) && ( *p_textline != '\0' ) ) {
			p_textline++;
		}
		p_textline++;
		p_startpos--;
	}

	textaddr = p_textline;
	i = 0;

	while ( *p_textline != '\0' ) {
		buffer[i++] = *( p_textline++ );
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
		free( buffer );
		return( textaddr );
	} else {
		free( buffer );
		return( NULL );
	}
}

void wordnotfound( void ) {
	errorsound( );
	blockmsg( 5 );
	dispstrhgc( "หาคำไม่พบ ! กด ESC เพื่อทำงานต่อ", ( 14 + center_factor ) + 13, 5, REVERSEATTR );
	while ( ebioskey( 0 ) != ESCKEY );
	pagecomplete = NO;
}

int searchfwd( unsigned int *p_xCursorPos, unsigned int *y_CursorPos ) {
	struct line_node *savepage, *templine;
	boolean enlargeflag;
	unsigned int linecount;
	unsigned int savecol;
	unsigned int startpos;
	size_t i;
	font_attr font = NORMALATTR;
	char *foundpoint;
	char *addr;

	savecol = firstcol;
	savepage = curpage;
	storeline( curline );
	templine = curpage;
	linecount = wind.width - 1;

	while ( templine != curline ) {
		linecount--;
		templine = templine->next;
	}

	startpos = linearcolumn( curline->text, *p_xCursorPos + firstcol, &font );
	foundpoint = NULL;

	while ( ( foundpoint == NULL ) && ( curline != sentinel ) ) {
		foundpoint = searchline( curline->text, startpos );

		if ( foundpoint != NULL ) {		/* found */

			while ( ( *y_CursorPos = findrow( ) ) >= wind.width ) {
				curpage = curpage->next;
			}

			*p_xCursorPos = 0;
			firstcol = 0;
			addr = curline->text;
			enlargeflag = NO;

			while ( addr != foundpoint ) {
				if ( ( whatlevel( *addr ) == MIDDLE ) && ( *addr >= 32 ) ) {
					if ( enlargeflag ) {
						( *p_xCursorPos )++;
					}
					( *p_xCursorPos )++;
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
						( *p_xCursorPos )++;
					}
					( *p_xCursorPos )++;
				}
			}

			while ( *p_xCursorPos >= wind.length ) {
				firstcol = firstcol + wind.length;
				*p_xCursorPos = *p_xCursorPos - wind.length;
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
		endline( p_xCursorPos );
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

void searching( unsigned int *p_xCursorPos, unsigned int *y_CursorPos ) {
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
			topfile( p_xCursorPos );
			showpageall( );
		}
		if ( !searchfwd( p_xCursorPos, y_CursorPos ) ) {
			wordnotfound( );
		}
	}
}

void replaceword( unsigned int *p_xCursorPos, unsigned int *y_CursorPos ) {
	int i;

	for ( i = strlen( source ); i != 0; i-- ) {
		backspace( p_xCursorPos );
	}

	while ( replace[i] != '\0' ) {
		insert_char( replace[i], p_xCursorPos, y_CursorPos );
		i++;
	}

	refreshline( 0, *y_CursorPos );
}

int searchreplace( unsigned int *p_xCursorPos, unsigned int *y_CursorPos ) {
	int ok = 0;
	int i;
	int ask = YES;
	int global = NO;
	int found = NO;

	if ( optionnoask( ) ) {
		ok = 'y';
		ask = NO;
	}
	if ( optionglobal( ) ) {
		topfile( p_xCursorPos );
		showpageall( );
		global = YES;
	}

	do {
		if ( searchfwd( p_xCursorPos, y_CursorPos ) ) {
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
						setcurpos( wind.col + *p_xCursorPos, wind.row + *y_CursorPos, thaimode );
						for ( i = 0; i < 15000; i++ );
						setcurpos( wind.col + *p_xCursorPos, wind.row + *y_CursorPos, thaimode );
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
				replaceword( p_xCursorPos, y_CursorPos );
			}

			ok = 0;

		} else {
			global = NO;
		}

	} while ( global );

	return( found );
}

void replacing( unsigned int *p_xCursorPos, unsigned int *y_CursorPos ) {
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
		if ( !searchreplace( p_xCursorPos, y_CursorPos ) ) {
			wordnotfound( );
		}
	}
}
