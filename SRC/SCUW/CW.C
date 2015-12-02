/*
* ============================================================================
* CU-Writer main program.
*
* update : Suttipong Kanakakorn
*          Sun  07-30-1989  20:11:04
*          Thu  08-03-1989  10:13:44
* update : CUCC
*          - Add more comments.
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <dir.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cusong.h"
#include "..\common\ekbd.h"
#include "..\common\grdetect.h"
#include "..\common\kbdcode.h"
#include "..\common\sound.h"

#define DEFINE_VAR 1

#include "..\common\var.h"
#include "var.h"

#undef DEFINE_VAR

#include "..\common\cwgrphc.h"

#include "block.h"
#include "cwsetup.h"
#include "del.h"
#include "edit.h"
#include "ins.h"
#include "kbd.h"
#include "menu.h"
#include "move.h"
#include "movement.h"
#include "onscrn.h"
#include "scrn.h"
#include "search.h"
#include "status.h"
#include "wrap.h"

#include "cw.h"

void setupnode( void ) {
	sentinel = ( struct line_node * ) malloc( sizeof( struct line_node ) );
	sentinel->next = sentinel;
	sentinel->previous = sentinel;
	sentinel->text = NULL;
#ifdef WANT_TO_USE_GRAPH
	sentinel->graph = NULL;
#endif
	sentinel->wrap = NO;
	curline = ( struct line_node * ) malloc( sizeof( struct line_node ) );
	curline->wrap = NO;
	curline->text = ( char * ) malloc( 1 );
	*( curline->text ) = '\0';
#ifdef WANT_TO_USE_GRAPH
	curline->graph = NULL;
#endif
	insert_line( sentinel, curline );
	curpage = curline;
	loadtoline( curline->text );
}

void destroynode( void ) {
	struct line_node *currentline;
	struct line_node *templine;

	blockmsg( 5 );
	dispstrhgc( "กำลังทำการยกเลิกแฟ้มข้อมูลเดิมอยู่ กรุณารอสักครู่...", 26 + center_factor, 5, REVERSEATTR );
	currentline = sentinel->next;
	while ( currentline != sentinel ) {
		templine = currentline;
		currentline = currentline->next;
		free( templine->text );
#ifdef WANT_TO_USE_GRAPH
		if ( templine->graph != NULL ) {
			free( templine->graph );
		}
#endif
		free( templine );
	}
	free( sentinel );
}

unsigned menu_to_key( register unsigned int p_curmenu ) {
	register int i;

	for ( i = 0; ( command_tab[i] != p_curmenu ) && ( command_tab[i] != 0 ); i += 2 );
	return( command_tab[i + 1] );
}

void splashscreen( void ) {
	extern char prog_date[];
	extern char prog_time[];

#ifdef EDA_VERSION

	framebox( 17 + center_factor, 5, ( 17 + center_factor ) + 46, 11, REVERSEATTR );
	dispstrhgc( "CU  WRITER", ( 21 + center_factor ) + 10, 6, REVERSEATTR );
	dispstrhgc( "Version 1.2", ( 21 + center_factor ) + 13, 7, REVERSEATTR );
	dispstrhgc( "EDA version", ( 21 + center_factor ) + 12, 8, REVERSEATTR );
	dispstrhgc( "อภินันทนาการจาก จุฬาลงกรณ์มหาวิทยาลัย", ( 21 + center_factor ) + 4, 9, REVERSEATTR );
	dispstrhgc( "มอบแด่ กระทรวงต่างประเทศ", ( 21 + center_factor ) + 8, 10, REVERSEATTR );

#else
#ifdef CW_VERSION

	framebox( 17 + center_factor, 5, ( 17 + center_factor ) + 46, 13, REVERSEATTR );
	/*
	framebox( 17 + center_factor, 5, ( 17 + center_factor ) + 46, 14, REVERSEATTR );
	*/
	dispstrhgc( "CU  WRITER", ( 21 + center_factor ) + 10, 6, REVERSEATTR );
	dispstrhgc( "Version 1.41", ( 21 + center_factor ) + 13, 7, REVERSEATTR );
	dispprintf( ( 21 + center_factor ) + 8, 8, REVERSEATTR, "%11s   %8s", prog_date, prog_time );
	dispstrhgc( "Hercules/EGA/VGA/MCGA/AT&T", ( 21 + center_factor ) + 6, 9, REVERSEATTR );
	dispstrhgc( "พัฒนาโดย สถาบันบริการคอมพิวเตอร์ ร่วมกับ", ( 21 + center_factor ) + 3, 10, REVERSEATTR );
	dispstrhgc( "ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์", ( 21 + center_factor ), 11, REVERSEATTR );
	/*
	dispstrhgc( "และ ชมรมคอมพิวเตอร์ อบจ.", ( 21 + center_factor ) + 8, 12, REVERSEATTR );
	dispstrhgc("จุฬาลงกรณ์มหาวิทยาลัย", ( 21 + center_factor ) + 10, 13, REVERSEATTR );
	*/
	dispstrhgc( "จุฬาลงกรณ์มหาวิทยาลัย", ( 21 + center_factor ) + 10, 12, REVERSEATTR );

#else

	framebox( 17 + center_factor, 5, ( 17 + center_factor ) + 46, 14, REVERSEATTR );
	dispstrhgc( "THAI  WRITE", ( 21 + center_factor ) + 9, 6, REVERSEATTR );
	dispstrhgc( "Version 1.0.0", ( 21 + center_factor ) + 13, 7, REVERSEATTR );
	dispprintf( ( 21 + center_factor ) + 8, 8, REVERSEATTR, "%11s   %8s", prog_date, prog_time );
	dispstrhgc( "Hercules/EGA/VGA/MCGA/AT&T", ( 21 + center_factor ) + 6, 9, REVERSEATTR );
	dispstrhgc( "Khral Steelforge", ( 21 + center_factor ) + 11, 10, REVERSEATTR );
	dispstrhgc( "The Forge Warband,  Iron Legion", ( 21 + center_factor ) + 4, 11, REVERSEATTR );
	dispstrhgc( "พัฒนาจาก เวิร์ดจุฬา โดย มหาวิทยาลัยจุฬาลงกรณ์", ( 21 + center_factor ) + 1, 13, REVERSEATTR );

#endif
#endif

	if ( cu_song ) {
		cusong( );
	}

	ebioskey( 0 );
	cls( );
}

int main( int argc, char *argv[] ) {
	/* (x,y) position of edit window. x column, y line -> (0,0) at upper left on screen */
	unsigned int xCursorPos = 0;
	unsigned int yCursorPos = 0;

	unsigned int curmenu = 0x1100;
	int i;

	cwsetup( argc, argv );

	writestatus( 0 );
	writetab( );

	splashscreen( );

	/* Main program loop */
	do {
		dispstrhgc( "   ", wind.col, 2, NORMALATTR );
		i = pulled_down_menu( &curmenu, &xCursorPos, &yCursorPos );
		if ( filename[0] != '\0' ) {
			switch ( i ) {
			case RETKEY:
				keymain = menu_to_key( curmenu );
				break;

			case ESCKEY:
				waitkbd( wind.col + xCursorPos, wind.row + yCursorPos );		/* Show blinking cursor */
				keymain = readkbd( );		/* If keypressed Get it */
				break;

			default:
				keymain = i;
				break;
			}

			while ( keymain != ESCKEY ) {
				if ( ( keymain & 0xff ) >= 32 ) {
					keymain = changekey( keymain );
					if ( insertmode ) {
						if ( !insert_char( keymain, &xCursorPos, &yCursorPos ) ) {
							linetoolong( );
						}
					} else {
						if ( !ovrwrite_char( keymain, &xCursorPos, &yCursorPos ) ) {
							linetoolong( );
						}
					}
					refreshline( xCursorPos, yCursorPos );
				} else {	/*  Function Key  */
					switch ( keymain ) {
					case PGUPKEY:
					case CNTRL_R:
						page_up( );
						break;

					case PGDNKEY:
					case CNTRL_C:
						page_down( );
						break;

					case UPKEY:
					case CNTRL_E:
						cursor_up( );
						break;

					case DNKEY:
					case CNTRL_X:
						cursor_down( yCursorPos );
						break;

					case LEKEY:
					case CNTRL_S:
						cursor_left( &xCursorPos );
						break;

					case 0x2301:
						gobeginblk( &xCursorPos );
						break;

					case 0x2401:
						goendblk( &xCursorPos );
						break;

					case RIKEY:
					case CNTRL_D:
						cursor_right( &xCursorPos, yCursorPos );
						break;

					case CNTRL_W:
						scroll_up( );
						break;

					case CNTRL_Z:
						scroll_down( );
						break;

					case CHOMEKEY:
						top_of_page( );
						break;

					case CPGUPKEY:
						topfile( &xCursorPos );
						break;

					case CENDKEY:
						bottom_of_page( );
						break;

					case CPGDNKEY:
						endfile( &xCursorPos );
						break;

					case DELKEY:
					case CNTRL_G:
						delete_char( xCursorPos );
						refreshline( xCursorPos, yCursorPos );
						changeflag = YES;
						break;

					case CNTRL_T:
						delete_word( xCursorPos );
						refreshline( xCursorPos, yCursorPos );
						changeflag = YES;
						break;

					case CNTRL_Y:
						delete_line( );
						changeflag = YES;
						break;

					case CNTRL_M:
					case RETKEY:
						if ( insertmode == NO ) {
							returnkey( &xCursorPos, yCursorPos );
						} else {
							ret_with_ins( &xCursorPos, yCursorPos );
							changeflag = YES;
						}
						break;

					case BSKEY:
					case CNTRL_H:
						backspace( &xCursorPos );
						yCursorPos = findrow( );
						refreshline( 0, yCursorPos );
						changeflag = YES;
						break;

					case INSKEY:
					case CNTRL_V:
						insertmode = !insertmode;
						writeinsmode( );
						break;

					case CNTRL_N:
						insert_ret( &xCursorPos );
						break;

					case F10KEY:
						thaimode = !thaimode;
						writelanguage( );
						break;

					case F1KEY:
						fontused = 0x00;
						writeattr( );
						break;

					case F2KEY:
						fontused = fontused | ITALICATTR;
						writeattr( );
						break;

					case F3KEY:
						fontused = fontused | ONELINEATTR;
						fontused = fontused & 0x7f;
						writeattr( );
						break;

					case F4KEY:
						fontused = fontused | TWOLINEATTR;
						fontused = fontused & 0xfe;
						writeattr( );
						break;

					case F5KEY:
						fontused = fontused | BOLDATTR;
						writeattr( );
						break;

					case F6KEY:
						fontused = fontused | ENLARGEATTR;
						writeattr( );
						break;

					case F7KEY:
						fontused = fontused | SUPERATTR;
						if ( ( fontused & SUBATTR ) == SUBATTR ) {
							fontused = fontused ^ SUBATTR;
						}
						writeattr( );
						break;

					case F8KEY:
						fontused = fontused | SUBATTR;
						if ( ( fontused & SUPERATTR ) == SUPERATTR ) {
							fontused = fontused ^ SUPERATTR;
						}
						writeattr( );
						break;

					case F9KEY:
						manualwrap( &xCursorPos, &yCursorPos );
						break;

					case ALTM:
						editmacro( );
						break;

					case TABKEY:
					case CNTRL_I:
						movetotab( &xCursorPos, yCursorPos );
						break;

					case CNTRL_K:
						blockcommand( &xCursorPos );
						break;

					case 0x1401:
						blkcmd( 'p', &xCursorPos );
						break;
					case 0x6101:
						blkcmd( 'b', &xCursorPos );
						break;
					case 0x6201:
						blkcmd( 'k', &xCursorPos );
						break;
					case 0x6301:
						blkcmd( 'c', &xCursorPos );
						break;
					case 0x6401:
						blkcmd( 'y', &xCursorPos );
						break;
					case 0x6501:
						blkcmd( 'v', &xCursorPos );
						break;
					case 0x6601:
						blkcmd( 'r', &xCursorPos );
						break;
					case 0x6701:
						blkcmd( 'w', &xCursorPos );
						break;
					case 0x6801:
						blkcmd( 'h', &xCursorPos );
						break;

					case CNTRL_O:
						onscreen( xCursorPos, yCursorPos );
						break;

					case 0x7101:
						doonscrn( 'l', xCursorPos, yCursorPos );
						break;
					case 0x7201:
						doonscrn( 'r', xCursorPos, yCursorPos );
						break;
					case 0x7301:
						doonscrn( 'i', xCursorPos, yCursorPos );
						break;
					case 0x7401:
						doonscrn( 'n', xCursorPos, yCursorPos );
						break;
					case 0x7501:
						doonscrn( 'c', xCursorPos, yCursorPos );
						break;
					case 0x7601:
						doonscrn( 'p', xCursorPos, yCursorPos );
						break;
					case 0x7701:
						doonscrn( 'x', xCursorPos, yCursorPos );
						break;

					case CNTRL_Q:
						quick( &xCursorPos, &yCursorPos );
						break;

					case 0x3501:
						deltoendline( xCursorPos, yCursorPos );
						break;

					case 0x8111:
						inscntrl( CNTRL_W, xCursorPos, yCursorPos );
						break;
					case 0x8211:
						inscntrl( CNTRL_S, xCursorPos, yCursorPos );
						break;
					case 0x8311:
						inscntrl( CNTRL_R, xCursorPos, yCursorPos );
						break;
					case 0x8411:
						inscntrl( CNTRL_B, xCursorPos, yCursorPos );
						break;
					case 0x8511:
						inscntrl( CNTRL_E, xCursorPos, yCursorPos );
						break;
					case 0x8611:
						inscntrl( CNTRL_T, xCursorPos, yCursorPos );
						break;
					case 0x8711:
						inscntrl( CNTRL_V, xCursorPos, yCursorPos );
						break;

					case CNTRL_P:
						printcntrl( xCursorPos, yCursorPos );
						break;

					case HOMEKEY:
						home( &xCursorPos );
						break;

					case ENDKEY:
						endline( &xCursorPos );
						break;

					case CLEKEY:
					case CNTRL_A:
						backword( &xCursorPos );
						break;

					case CRIKEY:
					case CNTRL_F:
						nextword( &xCursorPos, yCursorPos );
						break;

					case CNTRL_L:
						if ( source[0] != '\0' ) {
							if ( replaceflag == NO ) {
								if ( searchfwd( &xCursorPos, &yCursorPos ) == NO ) {
									wordnotfound( );
								}
							} else {
								if ( searchreplace( &xCursorPos, &yCursorPos ) == NO ) {
									wordnotfound( );
								}
							}
						}
						break;

					case CNTRL_B:
						reform( );
						break;

					case ALTP:
						gotopage( );
						break;

					case CNTRL_J:
					case ALTL:
						gotoline( );
						break;

					case 0x5101:
						searching( &xCursorPos, &yCursorPos );
						break;

					case 0x5201:
						replacing( &xCursorPos, &yCursorPos );
						break;

					case 0x8501:
						loadtoline( curline->text );
						refreshline( 0, yCursorPos );
						break;

					case CF1KEY:
						insertmacro( &macro[0][0], &xCursorPos, &yCursorPos );
						break;
					case CF2KEY:
						insertmacro( &macro[1][0], &xCursorPos, &yCursorPos );
						break;
					case CF3KEY:
						insertmacro( &macro[2][0], &xCursorPos, &yCursorPos );
						break;
					case CF4KEY:
						insertmacro( &macro[3][0], &xCursorPos, &yCursorPos );
						break;
					case CF5KEY:
						insertmacro( &macro[4][0], &xCursorPos, &yCursorPos );
						break;
					case CF6KEY:
						insertmacro( &macro[5][0], &xCursorPos, &yCursorPos );
						break;
					case CF7KEY:
						insertmacro( &macro[6][0], &xCursorPos, &yCursorPos );
						break;
					case CF8KEY:
						insertmacro( &macro[7][0], &xCursorPos, &yCursorPos );
						break;
					case CF9KEY:
						insertmacro( &macro[8][0], &xCursorPos, &yCursorPos );
						break;
					case CF10KEY:
						insertmacro( &macro[9][0], &xCursorPos, &yCursorPos );
						break;

					case AF2KEY:
						inscntrl( ITALICCODE, xCursorPos, yCursorPos );
						break;
					case AF3KEY:
						inscntrl( ONELINECODE, xCursorPos, yCursorPos );
						break;
					case AF4KEY:
						inscntrl( TWOLINECODE, xCursorPos, yCursorPos );
						break;
					case AF5KEY:
						inscntrl( BOLDCODE, xCursorPos, yCursorPos );
						break;
					case AF6KEY:
						inscntrl( ENLARGECODE, xCursorPos, yCursorPos );
						break;
					case AF7KEY:
						inscntrl( SUPERCODE, xCursorPos, yCursorPos );
						break;
					case AF8KEY:
						inscntrl( SUBCODE, xCursorPos, yCursorPos );
						break;

#ifdef WANT_TO_USE_GRAPH
					case ALTG:
						insertgraph( );
						break;
					case ALTD:
						deletegraph( );
						break;
#endif

					case ALTX:
						quitprog = YES;
						keymain = ESCKEY;
						break;

					default:
						if ( ( alt_char_map( keymain ) ) != -1 ) {
							keymain = alt_char_map( keymain );
							if ( insertmode ) {
								if ( !insert_char( keymain, &xCursorPos, &yCursorPos ) ) {
									linetoolong( );
								}
							} else {
								if ( !ovrwrite_char( keymain, &xCursorPos, &yCursorPos ) ) {
									linetoolong( );
								}
							}
							refreshline( xCursorPos, yCursorPos );
						}
						break;
					} /* switch ( keymain ) */
				}
				adjustcol( &xCursorPos );
				while ( ( yCursorPos = findrow( ) ) > ( wind.width - 1 ) ) {
					storeline( curline );
					curline = curline->previous;
					loadtoline( curline->text );
					lineno--;
				}
				if ( !keypressed( ) ) {
					if ( !pagecomplete ) {
						showpage( );
					}
					if ( !keypressed( ) ) {
						writecolno( firstcol + xCursorPos );
						dispstrhgc( "   ", wind.col, 2, NORMALATTR );
						if ( !keypressed( ) ) {
							writepageline( );
						}
					}
				}
				if ( quitprog != YES ) {
					waitkbd( wind.col + xCursorPos, wind.row + yCursorPos );
					keymain = readkbd( );
					dispkey( keymain );
				}
			}	/* while */
		} else {	/* if filename[0] != '\0' */
			errorsound( );
		}
	} while ( !quitprog );

	if ( changeflag ) {
		blockmsg( 5 );
		dispstrhgc( "ยังไม่ได้จัดเก็บแฟ้มข้อมูล ต้องการจัดเก็บหรือไม่ (Y/N)?", ( 16 + center_factor ) + 7, 5, REVERSEATTR );
		keymain = 0;
		while ( ( keymain != 'n' ) && ( keymain != 'N' )
			&& ( keymain != 'y' ) && ( keymain != 'Y' ) ) {
			keymain = ebioskey( 0 ) & 0xff;
			if ( ( keymain == 'y' ) || ( keymain == 'Y' ) ) {
				writeblk( filename, sentinel->next, 0, sentinel->previous, MAXCOL );
			}
		}
	}
	settext( );

	return 0;
}
