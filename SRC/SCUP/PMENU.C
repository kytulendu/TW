/*
* ============================================================================
* PMENU.C
*
* Function : user menu interactions
*
* Written Oct-87
* Update  10-6-88
* Update  24-9-88
* Update  25-12-88
* Update  09-04-89
* Update  27-04-89
*  - Add print configuration feature.
*
* Update Suttipong Kanakakorn
* Mon  08-07-1989 00:00:55
*  - break the program smaller and add function prototype,
*    clear all warning message
* Fri  08-11-1989  02:25:09
*  - call cwsetup.c
* Sun  09-03-1989  01:29:31
*  - call line per page routine
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <dir.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\dir.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\grdetect.h"
#include "..\common\kbdcode.h"
#include "..\common\getstr.h"
#include "..\common\kbd.h"

#include "const.h"
#include "cuptype.h"
#include "global.h"

#include "cupsetup.h"
#include "printing.h"
#include "prncntrl.h"
#include "prtutil.h"
#include "smenu.h"

#include "pmenu.h"

#define DIRCOLMAX 5
#define DIRROWMAX 5
#define MAXNUM 20

void writefilename( void );

/**  */
void writeallmenu( void );

/**  */
void menuselect( void );

/**  */
void prtwriteallmenu( void );

/**  */
void prtwritemenu( int p_row, font_attr p_attr );

/**  */
void prtmenuselect( void );

/**  */
void setprinter( int p_smallpaper, int p_printer24pin );

/**  */
void prtdocommand( int p_row );

/**  */
void modewriteallmenu( void );

/**  */
void modewritemenu( int p_row, font_attr p_attr );

/**  */
void modemenuselect( void );

/**  */
void modedocommand( int p_row );

/**  */
void titlewriteallmenu( void );

/**  */
void titlewritemenu( int p_row, font_attr p_attr );

/**  */
void titlemenuselect( void );

/**  */
void titledocommand( int p_row );

int main( int argc, char *argv[] ) {
	cupsetup( argc, argv );
	setgraph( );
	writeallmenu( );
	menuselect( );
	settext( );

	return 0;
}

void writefilename( void ) {
	dispstrhgc( "��������� : ", 44, 0, NORMALATTR );
	dispstrhgc( "                         ", 54, 0, NORMALATTR );
	dispstrhgc( filename, 54, 0, NORMALATTR );
}

void writemenu( int p_row, int p_col, font_attr p_attr ) {
	char st[5];
	switch ( p_col ) {
	case 0:
		switch ( p_row ) {
		case 0:
			dispstrhgc( " ��������������ŷ���ͧ��þ����  ", mcol[p_col], 3, p_attr );
			writefilename( );
			break;
		case 1:
			dispstrhgc( " �������������������          ", mcol[p_col], 4, p_attr );
			break;
		case 2:
			dispstrhgc( " ��ͧ��(Disk Drive)     ", mcol[p_col], 5, p_attr );
			prchar( 'A' + getdisk( ), p_attr, smcol[0] - 1, 5 );
			break;
		case 3:
			dispstrhgc( " ����¹�ҡ(Directory)    ", mcol[p_col], 6, p_attr );
			break;
		case 4:
			dispstrhgc( " ��к���Ժѵԡ�ê��Ǥ���    ", mcol[p_col], 7, p_attr );
			break;
		case 5:
			dispstrhgc( " ����ͧ�����               ", mcol[p_col], 8, p_attr );
			break;
		case 6:
			if ( stdcode == YES ) {
				dispstrhgc( " ���ʢ�����������    ���. ", mcol[p_col], 9, p_attr );
			} else {
				dispstrhgc( " ���ʢ�����������   �ɵ� ", mcol[p_col], 9, p_attr );
			}
			break;
		case 7:
			dispstrhgc( " ��ԡ��÷ӧҹ      ALT-X ", mcol[p_col], 10, p_attr );
			break;
		}
		break;
	case 1:
		switch ( p_row ) {
		case 0:
			dispstrhgc( " �ӹǹ��÷Ѵ���˹��        ", mcol[p_col], 3, p_attr );
			itoa( userlineperpage, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 3, p_attr );
			break;
		case 1:
			dispstrhgc( " ��Ҵ����ѡ�� (��ǵ�͹���)    ", mcol[p_col], 4, p_attr );
			itoa( cpi, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 4, p_attr );
			break;
		case 2:
			dispstrhgc( " �ͺ����                 ", mcol[p_col], 5, p_attr );
			itoa( leftmargin, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 5, p_attr );
			break;
		case 3:
			dispstrhgc( " �ͺ���                 ", mcol[p_col], 6, p_attr );
			/* rightmargin = ( ( rightmargin > leftmargin ) && ( rightmargin < maxcol ) ) ? rightmargin : maxcol; */
			itoa( rightmargin, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 6, p_attr );
			break;
		case 4:
			dispstrhgc( " ������������˹��             ", mcol[p_col], 7, p_attr );
			itoa( pagebegin, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 7, p_attr );
			break;
		case 5:
			dispstrhgc( " ��ش�������˹��             ", mcol[p_col], 8, p_attr );
			itoa( pageend, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 8, p_attr );
			break;
		case 6:
			dispstrhgc( " �����Ţ˹���������        ", mcol[p_col], 9, p_attr );
			itoa( pagenumberoffset, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 9, p_attr );
			break;
		case 7:
			dispstrhgc( " �ӹǹ�ش������� (COPY)     ", mcol[p_col], 10, p_attr );
			itoa( copytoprint, st, 10 );
			dispstrhgc( st, smcol[p_col] - strlen( st ), 10, p_attr );
			break;
		}
		break;
	case 2:
		switch ( p_row ) {
		case 0:
			dispstrhgc( " ��ǡ�д�� (Header)      ", mcol[p_col], 3, p_attr );
			break;
		case 1:
			dispstrhgc( " ���¡�д�� (Footer)     ", mcol[p_col], 4, p_attr );
			break;
		case 2:
			dispstrhgc( " ˹�ҡ�д�� (PageTitle)  ", mcol[p_col], 5, p_attr );
			break;
		case 3:
			dispstrhgc( " ���˹���Ǣ������ͧ (Title) ", mcol[p_col], 6, p_attr );
			break;
		case 4:
			dispstrhgc( " �纤�ҵ���� (Parameters)", mcol[p_col], 7, p_attr );
			break;
		case 5:
			dispstrhgc( " ��ҹ��ҵ���� (Parameters)", mcol[p_col], 8, p_attr );
			break;
		case 6:
			dispstrhgc( " ���������                ", mcol[p_col], 9, p_attr );
			break;
		case 7:
			if ( pagebreak == YES ) {
				dispstrhgc( " ��ش����¹��д��    ��ش  ", mcol[p_col], 10, p_attr );
			} else {
				dispstrhgc( " ��ش����¹��д��   �����ش ", mcol[p_col], 10, p_attr );
			}
			break;
		}
		break;
	}
}

void docommand( int p_row, int p_col ) {
	char *setpageformat( );
	int key;
	char *fileptr;
	char st[5];
	char cwd[38];

	key = 0;
	fileptr = filename;
	switch ( p_col ) {
	case 0:
		switch ( p_row ) {
		case 0:
			savepic( );
			dispstrhgc( "��������������ŷ���ͧ��þ���� : ", 25, 12, NORMALATTR );
			fileptr = ( filename[0] == '\0' ) ? "*.*" : filename;
			strcpy( filename, fileptr );
			if ( ( getname( filename, 49, 12, 25, REVERSEATTR ) == YES ) && ( filename[0] != '\0' ) ) {
				if ( havewild( filename ) ) {
					selectfile( filename );
					retpic( );
				}
			}
			if ( ( fileready == YES ) && ( filename == oldfilename ) );
			else {
				fclose( fp );     /* close old file */
				if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
					fileready = NO;
					filename[0] = '\0';  /* clear filename */
					strcpy( oldfilename, filename );
					writefilename( );
					blockmsg( 13 );
					dispstrhgc( "*** ��辺��������� *** ������� � ...", 24, 13, REVERSEATTR );
					ebioskey( 0 );  /* clear KBD buffer */
				} else {
					strcpy( oldfilename, filename );
					fileready = YES;
				}
			}
			retpic( );
			writefilename( );
			break;
		case 1:
			if ( fileready == YES ) {
				savepic( );
				/* Suttipong Kanakakorn Fri  10-27-1989  19:09:59 */
				/* check every error of printer before print */
				if ( PrinterReadstatus( ) & 0x80 && ( PrinterReadstatus( ) & 0x29 ) == 0 ) {
					printing( );
				} else {
					blockmsg( 13 );
					dispstrhgc( "*** ����ͧ������������ ***  ������� � ...", 26, 13, REVERSEATTR );
					ebioskey( 0 );  /* clear KBD buffer */
				}
				retpic( );
			} else {
				savepic( );
				blockmsg( 13 );
				dispstrhgc( "*** ��س��Դ��������š�͹ ***  ������� � ...", 18, 13, REVERSEATTR );
				ebioskey( 0 );  /* clear KBD buffer */
				retpic( );
			}
			break;
		case 2:
			savepic( );
			dispstrhgc( " ����¹��ͧ�� (Logged Drive) ��   ", 28, 12, NORMALATTR );
			waitkbd( 60, 12 );
			key = ebioskey( 0 ) & 0xff;
			if ( ( key >= 'a' ) || ( key <= 'p' ) ) {
				setdisk( key - 'a' );
			} else {
				if ( ( key >= 'A' ) || ( key <= 'P' ) ) {
					setdisk( key - 'A' );
				}
			}
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 3:
			savepic( );
			dispstrhgc( "����¹�ҡ (Directory) �� :", 10, 12, NORMALATTR );
			getstring( getcwd( cwd, 37 ), 37, 12, 37, REVERSEATTR, ENGUPCASE );
			chdir( cwd );
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 4:
			settext( );
			puts( "Type EXIT to return to CUPRINT" );
			system( "" );
			setgraph( );
			writeallmenu( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 5:
			savepic( );
			prtwriteallmenu( );
			prtmenuselect( );
			retpic( );
			/* add by Suttipong Kanakakorn Sun  09-03-1989  01:29:17 */
			set_all_lineperpage( INTERACTIVE ); /* set (user)lineperpage */
			writemenu( p_row, p_col, REVERSEATTR );
			writemenu( 3, 1, NORMALATTR );   /* show new right margin */
			break;
		case 6:
			if ( stdcode == YES ) {
				stdcode = NO;
			} else {
				stdcode = YES;
			}
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 7:
			quitprog = YES;
			break;
		}
		break;
	case 1:
		switch ( p_row ) {
		case 0:
			savepic( );
			dispstrhgc( "��ͧ��èӹǹ��÷Ѵ���˹������� : ", 30, 12, NORMALATTR );
			if ( getstring( itoa( userlineperpage, st, 10 ), 59, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				if ( atoi( st ) > 0 ) {
					userlineperpage = atoi( st );
				}
			}
			dispstrhgc( "     ������ǡ�д������� (����) : ", 30, 12, NORMALATTR );
			if ( getstring( itoa( pagelength, st, 10 ), 59, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				if ( atoi( st ) > 0 ) {
					pagelength = atoi( st );
				}
			}
			retpic( );
			/* add by Suttipong Kanakakorn Sun  09-03-1989  01:29:17 */
			set_all_lineperpage( INTERACTIVE ); /* set (user)lineperpage */
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 1:
			savepic( );
			dispstrhgc( "��ͧ��� �ӹǹ����ѡ�õ�͹��� �����     : ", 28, 12, NORMALATTR );
			if ( getstring( itoa( cpi, st, 10 ), 62, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				cpi = atoi( st );
				cpi = ( cpi < 20 ) ? cpi : 20;
				cpi = ( cpi > 0 ) ? cpi : 1;
				if ( ( printer == LQ ) || ( printer == N7 ) || ( printer == N5 ) ) {
					maxcol = 136 * cpi / 10;
					maxdot = 3264;
					maxbuffer = ( cpi<10 ) ? 3264 : 3264 * ( long ) ( cpi ) / 10 + 50;
					/* Strange to Suttipong Kanakakorn */
				} else {
					maxcol = 80 * cpi / 10;
					maxdot = 1920;
					maxbuffer = ( cpi<10 ) ? 1920 : 192 * cpi;
				}
			}
			retpic( );
			writemenu( 3, 1, NORMALATTR );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 2:
			savepic( );
			dispstrhgc( "��ͧ��õ�駢ͺ����(Left Margin)����� : ", 27, 12, NORMALATTR );
			if ( getstring( itoa( leftmargin, st, 10 ), 62, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				leftmargin = ( atoi( st ) > 0 ) ? atoi( st ) : 1;
				leftmargin = ( leftmargin < rightmargin ) ? leftmargin : 1;
			}
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 3:
			savepic( );
			dispstrhgc( "��ͧ��õ�駢ͺ���(Right Margin)�����: ", 27, 12, NORMALATTR );
			if ( getstring( itoa( rightmargin, st, 10 ), 62, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				rightmargin = atoi( st );
			}
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 4:
			savepic( );
			dispstrhgc( "��ͧ���������������˹������� : ", 33, 12, NORMALATTR );
			if ( getstring( itoa( pagebegin, st, 10 ), 57, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				pagebegin = ( atoi( st )>0 ) ? atoi( st ) : 1;
				pagebegin = ( pageend<pagebegin ) ? pageend : pagebegin;
			}
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 5:
			savepic( );
			dispstrhgc( "��ͧ�����ش�������˹�� (PageEnd) �����  :   ", 26, 12, NORMALATTR );
			if ( getstring( itoa( pageend, st, 10 ), 64, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				pageend = atoi( st );
				pageend = ( pageend<pagebegin ) ? pagebegin : pageend;
			}
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 6:
			savepic( );
			dispstrhgc( "��ͧ���������������Ţ˹��������� ����� ?  : ", 26, 12, NORMALATTR );
			if ( getstring( itoa( pagenumberoffset, st, 10 ), 64, 12, 3, REVERSEATTR, NUMBER ) == YES )
				pagenumberoffset = atoi( st );
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 7:
			savepic( );
			dispstrhgc( "��ͧ��þ������ش : ", 37, 12, NORMALATTR );
			if ( getstring( itoa( copytoprint, st, 10 ), 52, 12, 3, REVERSEATTR, NUMBER ) == YES ) {
				copytoprint = ( atoi( st )>0 ) ? atoi( st ) : 1;
			}
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		}
		break;
	case 2:
		switch ( p_row ) {
		case 0:
			savepic( );
			dispstrhgc( "����ͤ�����ǡ�д�� (Heading) ����ͧ��� : ", 1, 12, NORMALATTR );
			getstring( heading, 38, 12, 40, REVERSEATTR, THAIENG );
			retpic( );
			break;
		case 1:
			savepic( );
			dispstrhgc( "����ͤ������¡�д�� (Footing) ����ͧ��� : ", 1, 12, NORMALATTR );
			getstring( footing, 39, 12, 39, REVERSEATTR, THAIENG );
			retpic( );
			break;
		case 2:
			savepic( );
			dispstrhgc( "����ͤ���˹�ҡ�д��(PageTitle)����ͧ��� : ", 1, 12, NORMALATTR );
			getstring( pagetitle, 39, 12, 39, REVERSEATTR, THAIENG );
			strcpy( pageformat, setpageformat( pagetitle, maxcol ) );
			dispstrhgc( pageformat, 2, 13, NORMALATTR );
			retpic( );
			break;
		case 3:
			savepic( );
			titlewriteallmenu( );
			titlemenuselect( );
			retpic( );
			writemenu( p_row, p_col, REVERSEATTR );
			/* add by Suttipong Kanakakorn Sun  09-03-1989  01:29:17 */
			set_all_lineperpage( INTERACTIVE ); /* set (user)lineperpage */
			/* writemenu( 0, 1, 0 ); */  /* show new lines per page */
			break;
		case 4:
		case 5:
		{
			char *option_menu[2];
			char *scrndx2;
			char cur_dir[MAXDRIVE + MAXDIR], buf0[65], buf1[65];
			int i, me = 1;
			search_file_mode smode;

			getcwd( cur_dir, sizeof( cur_dir ) );
			sprintf( buf0, " ��� Current  directory (%.30s) ", cur_dir );
			sprintf( buf1, " ��� Cuwriter directory (%.30s) ", cup_dir );
			option_menu[0] = buf0; option_menu[1] = buf1;
			scrndx2 = savescrn( 20, 8, 20 + 1 + find_menu_len( 2, option_menu ), 8 + 2 + 1 );
			i = smenu( 20 + 1, 8 + 1, 2, option_menu, &me );
			if ( i == RETKEY ) {
				smode = ( me == 1 ) ? CUR_DIR : CW_DIR;
				savepic( );
				framebox( 30, 11, 50, 13, REVERSEATTR );
				dispstrhgc( "��س����ѡ����.....", 33, 12, REVERSEATTR );
				( p_row == 4 ) ? saveoption( smode ) : readoption( smode );
				retpic( );
			}
			resscrn( scrndx2, 20, 8, 20 + 1 + find_menu_len( 2, option_menu ), 8 + 2 + 1 );
			break;
		}
		case 6:
			savepic( );
			modewriteallmenu( );
			modemenuselect( );
			retpic( );
			/* add by Suttipong Kanakakorn Sun  09-03-1989  01:29:17 */
			set_all_lineperpage( INTERACTIVE ); /* set (user)lineperpage */
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		case 7:
			if ( pagebreak == YES ) {
				pagebreak = NO;
			} else {
				pagebreak = YES;
			}
			writemenu( p_row, p_col, REVERSEATTR );
			break;
		}
		break;
	}
}

void writeallmenu( void ) {
	int i;

	clsall( );

	_rectangle( 0, 0,
		( ( scrmode == HERCMONO ) && ( herc_align == 0 ) ) ? 719 : 639,
		( ( scrmode == VGA ) || ( scrmode == MCGA ) ) ? 479 :
			( scrmode == ATT400 ) ? 399 :
			( scrmode == CGA ) ? 199 :
			347 );
	prakeaw( );
	dispstrhgc( "����ŧ�ó�����Է�����", 6, 0, BOLDATTR );
	dispstrhgc( "TW-PRINT", 31, 1, ENLARGEATTR | BOLDATTR | ONELINEATTR );
	dispprintf( 22, 2, NORMALATTR, "Version 1.0.0  %s %s", prog_date, prog_time );
	_line( 0, 24, ( ( scrmode == HERCMONO ) && ( herc_align == 0 ) ) ? 719 : 639, 24 );

	dispstrhgc( "������Ѵ������͡���������/�ѧ���", 25, 15, ONELINEATTR | BOLDATTR );
	mcol[0] = 3;
	mcol[1] = mcol[0] + mlenght + 1;
	mcol[2] = mcol[1] + mlenght + 1;
	smcol[0] = mcol[0] + mlenght - 1;
	smcol[1] = mcol[1] + mlenght - 1;
	smcol[2] = mcol[2] + mlenght - 1;
	_rectangle( mcol[0] * 8 - 2, 62, ( mcol[0] + mlenght ) * 8 + 2, 225 );
	i = 0;
	while ( i <= rowmax[0] ) {
		writemenu( i++, 0, NORMALATTR );
	}
	_rectangle( mcol[1] * 8 - 2, 62, ( mcol[1] + mlenght ) * 8 + 2, 225 );
	i = 0;
	while ( i <= rowmax[1] ) {
		writemenu( i++, 1, NORMALATTR );
	}
	_rectangle( mcol[2] * 8 - 2, 62, ( mcol[2] + mlenght ) * 8 + 2, 225 );
	i = 0;
	while ( i <= rowmax[2] ) {
		writemenu( i++, 2, NORMALATTR );
	}
}

void menuselect( void ) {
	int c;
	int row = 0;
	int col = 0;
	writemenu( row, col, REVERSEATTR );
	do {
		c = ebioskey( 0 );
		switch ( c ) {
		case UPKEY:
			writemenu( row, col, NORMALATTR );
			if ( row == 0 ) {
				row = rowmax[col];
			} else {
				row--;
			}
			writemenu( row, col, REVERSEATTR );
			break;
		case DNKEY:
			writemenu( row, col, NORMALATTR );
			if ( row == rowmax[col] ) {
				row = 0;
			} else {
				row++;
			}
			writemenu( row, col, REVERSEATTR );
			break;
		case RIKEY:
			writemenu( row, col, NORMALATTR );
			if ( col == 2 ) {
				col = 0;
			} else {
				col++;
			}
			if ( row > rowmax[col] ) {
				row = rowmax[col];
			}
			writemenu( row, col, REVERSEATTR );
			break;
		case LEKEY:
			writemenu( row, col, NORMALATTR );
			if ( col == 0 ) {
				col = 2;
			} else {
				col--;
			}
			if ( row > rowmax[col] ) {
				row = rowmax[col];
			}
			writemenu( row, col, REVERSEATTR );
			break;
		case RETKEY:
			docommand( row, col );
			break;
		case ALTX:
			quitprog = YES;
			break;
		}
	} while ( quitprog == NO );
}

void prtwriteallmenu( void ) {
	int i;
	framebox( 3, 9, 36, 13, NORMALATTR );
	i = 0;
	while ( i <= prtrowmax ) {
		prtwritemenu( i++, NORMALATTR );
	}
}

void prtwritemenu( int p_row, font_attr p_attr ) {
	switch ( p_row ) {
	case 0:
		switch ( printer ) {
		case EPSON9PIN80COLTYPE1:
			dispstrhgc( " ����ͧ�����  FX 80,800 : EX800  ", 5, 10, p_attr );
			break;
		case EPSON9PIN136COLTYPE1:
			dispstrhgc( " ����ͧ�����  FX 100,850,1050    ", 5, 10, p_attr );
			break;
		case EPSON9PIN80COLTYPE2:
			dispstrhgc( " ����ͧ�����  LX 80,800          ", 5, 10, p_attr );
			break;
		case EPSON24PIN80COL:
			dispstrhgc( " ����ͧ�����  LQ 500,800         ", 5, 10, p_attr );
			break;
		case EPSON24PIN136COL:
			dispstrhgc( " ����ͧ�����  LQ 1050,1500,2500  ", 5, 10, p_attr );
			break;
		case NEC24PIN80COL:
			dispstrhgc( " ����ͧ�����  NEC P2200          ", 5, 10, p_attr );
			break;
		case NEC24PIN136COL:
			dispstrhgc( " ����ͧ�����  NEC P5,P7,P9 XL    ", 5, 10, p_attr );
			break;
		}
		break;
	case 1:
		if ( smallpaper == NO ) {
			dispstrhgc( " ��Ҵ˹�ҡ�д��      136 ������� ", 5, 11, p_attr );
		} else {
			dispstrhgc( " ��Ҵ˹�ҡ�д��       80 ������� ", 5, 11, p_attr );
		}
		break;
	case 2:
		if ( prtcodestd == YES ) {
			dispstrhgc( " ��������ͧ�����             ���. ", 5, 12, p_attr );
		} else {
			dispstrhgc( " ��������ͧ�����            �ɵ� ", 5, 12, p_attr );
		}
		break;
	}
}

void prtmenuselect( void ) {
	int quitprt = NO;
	int c;
	int row = 0;
	prtwritemenu( row, REVERSEATTR );
	do {
		c = ebioskey( 0 );
		switch ( c ) {
		case UPKEY:
			prtwritemenu( row, NORMALATTR );
			if ( row == 0 ) {
				row = prtrowmax;
			} else {
				row--;
			}
			prtwritemenu( row, REVERSEATTR );
			break;
		case DNKEY:
			prtwritemenu( row, NORMALATTR );
			if ( row == prtrowmax ) {
				row = 0;
			} else {
				row++;
			}
			prtwritemenu( row, REVERSEATTR );
			break;
		case RETKEY:
			prtdocommand( row );
			break;
		case ESCKEY:
			quitprt = YES;
			break;
		}
	} while ( quitprt == NO );
}

void setprinter( int p_smallpaper, int p_printer24pin ) {
	int col;
	if ( p_smallpaper == YES ) {
		col = 80;
	} else {
		col = 136;
	}
	if ( p_printer24pin == YES ) {
		maxcol = col*cpi / 10;
		maxdot = col * 18;
		maxbuffer = col * 18 * 2;
	} else {
		maxcol = col*cpi / 10;
		maxdot = col * 24;
		maxbuffer = col * 24 * 2;
	}
}

void prtdocommand( int p_row ) {
	switch ( p_row ) {
	case 0:
		switch ( printer ) {
		case EPSON9PIN80COLTYPE1:
			printer = EPSON9PIN136COLTYPE1;
			linespace = 15;
			smallpaper = NO;
			printer24pin = NO;
			break;
		case EPSON9PIN136COLTYPE1:
			printer = EPSON9PIN80COLTYPE2;
			linespace = 4;
			smallpaper = YES;
			printer24pin = NO;
			break;
		case EPSON9PIN80COLTYPE2:
			printer = EPSON24PIN80COL;
			linespace = 4;
			smallpaper = YES;
			printer24pin = YES;
			break;
		case EPSON24PIN80COL:
			printer = EPSON24PIN136COL;
			linespace = 4;
			smallpaper = NO;
			printer24pin = YES;
			break;
		case EPSON24PIN136COL:
			printer = NEC24PIN80COL;
			linespace = 4;
			smallpaper = YES;
			printer24pin = YES;
			break;
		case NEC24PIN80COL:
			printer = NEC24PIN136COL;
			linespace = 4;
			smallpaper = NO;
			printer24pin = YES;
			break;
		case NEC24PIN136COL:
			printer = EPSON9PIN80COLTYPE1;
			linespace = 15;
			smallpaper = YES;
			printer24pin = NO;
			break;
		}
		prtwritemenu( p_row, REVERSEATTR );
		prtwritemenu( 1, NORMALATTR );  /* show new paper width */
		break;
	case 1:
		if ( smallpaper == NO ) {
			smallpaper = YES;
		} else {
			if ( ( printer == FX ) || ( printer == LX ) );/*no chg*/
			else { smallpaper = NO; }
		}
		prtwritemenu( p_row, REVERSEATTR );
		break;
	case 2:
		if ( prtcodestd == NO ) {
			prtcodestd = YES;
		} else {
			prtcodestd = NO;
		}
		prtwritemenu( p_row, REVERSEATTR );
		break;
	}
	setprinter( smallpaper, printer24pin );
}

void modewriteallmenu( void ) {
	int i;
	framebox( 48, 10, 79, 13, NORMALATTR );
	i = 0;
	while ( i <= moderowmax ) {
		modewritemenu( i++, NORMALATTR );
	}
}

void modewritemenu( int p_row, font_attr p_attr ) {
	char smcol;
	smcol = mcol[2] - 3;
	switch ( p_row ) {
	case 0:
		if ( graphicprint == YES ) {
			dispstrhgc( " Print Mode         GRAPHIC ", smcol, 11, p_attr );
		} else {
			dispstrhgc( " Print Mode           TEXT  ", smcol, 11, p_attr );
		}
		break;
	case 1:
		if ( nlqmode == YES ) {
			dispstrhgc( " Precision             NLQ  ", smcol, 12, p_attr );
		} else {
			dispstrhgc( " Precision            Draft ", smcol, 12, p_attr );
		}
		break;
	}
}

void modemenuselect( void ) {
	int quit = NO;
	int c;
	int row = 0;
	modewritemenu( row, REVERSEATTR );
	do {
		c = ebioskey( 0 );
		switch ( c ) {
		case UPKEY:
			modewritemenu( row, NORMALATTR );
			if ( row == 0 ) {
				row = moderowmax;
			} else {
				row--;
			}
			modewritemenu( row, REVERSEATTR );
			break;
		case DNKEY:
			modewritemenu( row, NORMALATTR );
			if ( row == moderowmax ) {
				row = 0;
			} else {
				row++;
			}
			modewritemenu( row, REVERSEATTR );
			break;
		case RETKEY:
			modedocommand( row );
			break;
		case ESCKEY:
			quit = YES;
			break;
		}
	} while ( quit == NO );
}

void modedocommand( int p_row ) {
	switch ( p_row ) {
	case 0:
		if ( graphicprint == YES ) {
			graphicprint = NO;
		} else {
			graphicprint = YES;
		}
		modewritemenu( p_row, REVERSEATTR );
		break;
	case 1:
		if ( nlqmode == YES ) {
			nlqmode = NO;
		} else {
			nlqmode = YES;
		}
		modewritemenu( p_row, REVERSEATTR );
		break;
	}
}

void titlewriteallmenu( void ) {
	int i;
	framebox( 48, 7, 79, 11, NORMALATTR );
	i = 0;
	while ( i <= titlerowmax ) {
		titlewritemenu( i++, NORMALATTR );
	}
}

void titlewritemenu( int p_row, font_attr p_attr ) {
	char smcol;
	smcol = mcol[2] - 3;
	switch ( p_row ) {
	case 0:
		switch ( locheading ) {
		case 0:
			dispstrhgc( " ���˹���ǡ�д��       ������� ", smcol, 8, p_attr );
			break;
		case 1:
			dispstrhgc( " ���˹���ǡ�д��        ����  ", smcol, 8, p_attr );
			break;
		case 2:
			dispstrhgc( " ���˹���ǡ�д��        ��ҧ ", smcol, 8, p_attr );
			break;
		case 3:
			dispstrhgc( " ���˹���ǡ�д��        ���  ", smcol, 8, p_attr );
			break;
		case 4:
			dispstrhgc( " ���˹���ǡ�д��      ���,����", smcol, 8, p_attr );
			break;
		case 5:
			dispstrhgc( " ���˹���ǡ�д��      ����,���", smcol, 8, p_attr );
			break;
		}
		break;
	case 1:
		switch ( locfooting ) {
		case 0:
			dispstrhgc( " ���˹觷��¡�д��      ������� ", smcol, 9, p_attr );
			break;
		case 1:
			dispstrhgc( " ���˹觷��¡�д��       ����  ", smcol, 9, p_attr );
			break;
		case 2:
			dispstrhgc( " ���˹觷��¡�д��       ��ҧ ", smcol, 9, p_attr );
			break;
		case 3:
			dispstrhgc( " ���˹觷��¡�д��       ���  ", smcol, 9, p_attr );
			break;
		case 4:
			dispstrhgc( " ���˹觷��¡�д��     ���,����", smcol, 9, p_attr );
			break;
		case 5:
			dispstrhgc( " ���˹觷��¡�д��     ����,���", smcol, 9, p_attr );
			break;
		}
		break;
	case 2:
		switch ( locpagetitle ) {
		case 0:
			dispstrhgc( " ���˹�˹�ҡ�д��      ������� ", smcol, 10, p_attr );
			break;
		case 1:
			dispstrhgc( " ���˹�˹�ҡ�д��       ����  ", smcol, 10, p_attr );
			break;
		case 2:
			dispstrhgc( " ���˹�˹�ҡ�д��       ��ҧ ", smcol, 10, p_attr );
			break;
		case 3:
			dispstrhgc( " ���˹�˹�ҡ�д��       ���  ", smcol, 10, p_attr );
			break;
		case 4:
			dispstrhgc( " ���˹�˹�ҡ�д��     ���,����", smcol, 10, p_attr );
			break;
		case 5:
			dispstrhgc( " ���˹�˹�ҡ�д��     ����,���", smcol, 10, p_attr );
			break;
		}
		break;
	}
}

void titlemenuselect( void ) {
	int quit = NO;
	int c;
	int row = 0;
	titlewritemenu( row, REVERSEATTR );
	do {
		c = ebioskey( 0 );
		switch ( c ) {
		case UPKEY:
			titlewritemenu( row, NORMALATTR );
			if ( row == 0 ) {
				row = titlerowmax;
			} else {
				row--;
			}
			titlewritemenu( row, REVERSEATTR );
			break;
		case DNKEY:
			titlewritemenu( row, NORMALATTR );
			if ( row == titlerowmax ) {
				row = 0;
			} else {
				row++;
			}
			titlewritemenu( row, REVERSEATTR );
			break;
		case RETKEY:
			titledocommand( row );
			break;
		case ESCKEY:
			quit = YES;
			break;
		}
	} while ( quit == NO );
}

void titledocommand( int p_row ) {
	switch ( p_row ) {
	case 0:
		if ( locheading != 5 ) {
			locheading++;
		} else {
			locheading = 0;
		}
		break;
	case 1:
		if ( locfooting != 5 ) {
			locfooting++;
		} else {
			locfooting = 0;
		}
		break;
	case 2:
		if ( locpagetitle != 5 ) {
			locpagetitle++;
		} else {
			locpagetitle = 0;
		}
		break;
	}
	/*writemenu( 0, 1, 0 );*/
	titlewritemenu( p_row, REVERSEATTR );
}
