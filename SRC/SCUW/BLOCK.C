/*
* ============================================================================
* BLOCK.C 15 JAN 89
*
* Updated: Suttipong Kanakakorn
*          Thu  08-03-1989  10:47:20
*           - Create .bak,
*           - use dispprintf instead of dispstr for compress program size
*          Fri  08-04-1989  22:10:45
*           - reduce case in function blkcmd to reduce size of program
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <dir.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>

#include "..\common\cwtype.h"
#include "..\common\common.h"
#include "..\common\cwgrphc.h"
#include "..\common\const.h"
#include "..\common\cscrn.h"
#include "..\common\dir.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\kbdcode.h"
#include "..\common\sound.h"
#include "..\common\getstr.h"
#include "..\common\tutil1.h"

#include "const.h"
#include "var.h"

#include "cw.h"
#include "del.h"
#include "edit.h"
#include "ins.h"
#include "kbd.h"
#include "menu.h"
#include "cwsetup.h"
#include "tutil2.h"

#include "block.h"

void freeblk( FILE *p_file, struct line_node *p_space, struct line_node *p_currentline, struct line_node *p_freeline, unsigned char *p_textstr );

void toggleblk( void ) {
	dispblock = !dispblock;
	pagecomplete = NO;
}

void markbegin( unsigned int p_xCursorPos ) {
	blkbegin.lineno = lineno;
	blkbegin.column = firstcol + p_xCursorPos;
	if ( blkbegin.lineno > blkend.lineno ) {
		blkend.lineno = blkbegin.lineno;
		blkend.column = blkbegin.column;
	} else {
		if ( blkbegin.lineno == blkend.lineno ) {
			if ( blkbegin.column > blkend.column ) {
				blkend.column = blkbegin.column;
			}
		}
	}
	dispblock = YES;
	pagecomplete = NO;
}

void markend( unsigned int p_xCursorPos ) {
	blkend.lineno = lineno;
	blkend.column = firstcol + p_xCursorPos;
	if ( blkbegin.lineno > blkend.lineno ) {
		blkbegin.lineno = blkend.lineno;
		blkbegin.column = blkend.column;
	} else {
		if ( blkbegin.lineno == blkend.lineno ) {
			if ( blkbegin.column > blkend.column ) {
				blkbegin.column = blkend.column;
			}
		}
	}
	dispblock = YES;
	pagecomplete = NO;
}

int haveblock( void ) {
	if ( ( blkbegin.lineno == blkend.lineno ) &&
		( blkbegin.column == blkend.column ) ) {
		return( NO );
	} else {
		return( YES );
	}
}

int inblock( unsigned int p_line, unsigned int p_col ) {
	if ( ( p_line >= blkbegin.lineno ) &&
		( p_line <= blkend.lineno ) ) {
		if ( p_line == blkbegin.lineno ) {
			if ( p_col < blkbegin.column ) {
				return( NO );
			}
		}
		if ( p_line == blkend.lineno ) {
			if ( p_col >= blkend.column ) {
				return( NO );
			}
		}
		return( YES );
	} else {
		return( NO );
	}
}

struct line_node *copytospace( struct line_node *p_firstLine, struct line_node *p_lastLine,
	unsigned int p_firstCol, unsigned int p_lastCol ) {

	struct line_node *firstline;
	struct line_node *templine;
	struct line_node *newline;
	unsigned int i;
	unsigned int j;
	font_attr font;
	unsigned char fontcode[9];
	unsigned char *temp;

	firstline = ( struct line_node * ) malloc( sizeof( struct line_node ) );
	firstline->next = firstline;		/* set up     */
	firstline->previous = firstline;	/* first node */
	firstline->wrap = p_firstLine->wrap;
#ifdef WANT_TO_USE_GRAPH
	firstline->graph = NULL;			/* graphic image is not copied */
#endif
	i = linearcolumn( p_firstLine->text, p_firstCol, &font );
	findstrcode( fontcode, font );		/* find string of control code */
	firstline->text = ( unsigned char * ) malloc( strlen( fontcode ) + strlen( p_firstLine->text ) - i + 1 );
	strcpy( firstline->text, fontcode );
	strcat( firstline->text, ( p_firstLine->text ) + i );
	if ( p_firstLine == p_lastLine ) {
		j = linearcolumn( p_lastLine->text, p_lastCol, &font );
		temp = firstline->text;
		*( temp + strlen( fontcode ) + ( j - i ) ) = '\0';
		findstrcode( fontcode, font );
		firstline->text = ( unsigned char * ) malloc( strlen( temp ) + strlen( fontcode ) + 1 );
		strcpy( firstline->text, temp );
		strcat( firstline->text, fontcode );
		free( temp );
	}
	templine = firstline;
	while ( p_firstLine != p_lastLine ) {
		p_firstLine = p_firstLine->next;
		newline = ( struct line_node * ) malloc( sizeof( struct line_node ) );
		newline->wrap = p_firstLine->wrap;
#ifdef WANT_TO_USE_GRAPH
		newline->graph = NULL;
#endif
		if ( p_firstLine != p_lastLine ) {
			newline->text = ( unsigned char * ) malloc( strlen( p_firstLine->text ) + 1 );
			strcpy( newline->text, p_firstLine->text );
			insert_line( templine, newline );
			templine = templine->next;
		} else {
			i = linearcolumn( p_lastLine->text, p_lastCol, &font );
			findstrcode( fontcode, font );
			newline->text = ( unsigned char * ) malloc( i + strlen( fontcode ) + 1 );
			strncpy( newline->text, p_lastLine->text, i );
			strcpy( newline->text + i, fontcode );
			insert_line( templine, newline );
		}
	}
	return( firstline );
}

void insertlinklist( struct line_node *p_sourceLine, struct line_node *p_destLine,
	unsigned int p_destCol ) {

	unsigned int i;
	struct line_node *lastline;
	font_attr font;
	unsigned char fontcode[9];
	unsigned char *temp;

	lastline = p_sourceLine->previous;
	if ( p_sourceLine->next != p_sourceLine ) {		/* > 1 line ? */
		insertreturn( p_destLine, p_destCol );
		( p_destLine->next )->previous = lastline;	/* link all before */
		lastline->next = p_destLine->next;			/* delete first &  */
		p_destLine->next = p_sourceLine;			/* last line of    */
		p_sourceLine->previous = p_destLine;		/* source after    */
		p_destLine->wrap = p_sourceLine->wrap;
		temp = ( unsigned char * ) malloc( strlen( p_destLine->text ) + strlen( p_sourceLine->text ) + 1 );
		strcpy( temp, p_destLine->text );
		strcat( temp, p_sourceLine->text );
		free( p_destLine->text );
		p_destLine->text = temp;
		temp = ( unsigned char * ) malloc( strlen( lastline->text ) + strlen( ( lastline->next )->text ) + 1 );
		strcpy( temp, lastline->text );
		strcat( temp, ( lastline->next )->text );
		free( ( lastline->next )->text );
		( lastline->next )->text = temp;
		deleteline( p_sourceLine );
		deleteline( lastline );
	} else {	/* only one line */
		i = linearcolumn( p_destLine->text, p_destCol, &font );
		findstrcode( fontcode, font );
		temp = ( unsigned char * ) malloc( strlen( p_sourceLine->text ) + strlen( p_destLine->text ) + ( 2 * strlen( fontcode ) ) + 1 );
		strncpy( temp, p_destLine->text, i );
		temp[i] = '\0';
		strcat( temp, fontcode );
		strcat( temp, p_sourceLine->text );
		strcat( temp, fontcode );
		strcat( temp, ( p_destLine->text ) + i );
		free( p_destLine->text );
		p_destLine->text = temp;
	}
}

void deletelinklist( struct line_node *p_firstLine, struct line_node *p_lastLine,
	unsigned int p_firstCol, unsigned int p_lastCol ) {

	struct line_node *templine;
	struct line_node *freeline;

	insertreturn( p_lastLine, p_lastCol );
	p_lastLine = p_lastLine->next;
	insertreturn( p_firstLine, p_firstCol );
	templine = p_firstLine->next;
	p_firstLine->next = p_lastLine;
	p_lastLine->previous = p_firstLine;
	while ( templine != p_lastLine ) {
		if ( templine == curline ) {
			curline = p_firstLine;
		}
		if ( templine == curpage ) {
			curpage = p_firstLine;
		}
		freeline = templine;
		templine = templine->next;
		if ( freeline->text != NULL ) {
			free( freeline->text );
		}
#ifdef WANT_TO_USE_GRAPH
		if ( freeline->graph != NULL ) {
			free( freeline->graph );
		}
#endif
		free( freeline );
	}
	deletereturn( p_firstLine );
}

void copyblk( unsigned int *p_xCursorPos ) {
	struct line_node *fline;
	struct line_node *lline;
	struct line_node *space;

	if ( haveblock( ) && dispblock ) {
		storeline( curline );
		fline = linepointer( blkbegin.lineno );
		lline = linepointer( blkend.lineno );
		space = copytospace( fline, lline, blkbegin.column, blkend.column );
		insertlinklist( space, curline, *p_xCursorPos + firstcol );
		blkend.lineno = lineno + blkend.lineno - blkbegin.lineno;
		blkbegin.lineno = lineno;
		if ( blkbegin.lineno == blkend.lineno ) {
			blkend.column = blkend.column - blkbegin.column + *p_xCursorPos + firstcol;
		}
		blkbegin.column = *p_xCursorPos + firstcol;
		pagecomplete = NO;
		changeflag = YES;
		dispblock = YES;
		loadtoline( curline->text );
	}
}

void deleteblk( void ) {
	struct line_node *firstline;
	struct line_node *lastline;

	if ( haveblock( ) && dispblock ) {
		storeline( curline );
		firstline = linepointer( blkbegin.lineno );
		lastline = linepointer( blkend.lineno );
		deletelinklist( firstline, lastline, blkbegin.column, blkend.column );
		lineno = findlineno( curline );
		loadtoline( curline->text );
		blkbegin.lineno = 1;
		blkbegin.column = 0;
		blkend.lineno = 1;
		blkend.column = 0;
		changeflag = YES;
		pagecomplete = NO;
	}
}

void moveblk( unsigned int *p_xCursorPos ) {
	struct line_node *space;
	struct line_node *fline;
	struct line_node *lline;

	if ( haveblock( ) && dispblock ) {
		storeline( curline );
		fline = linepointer( blkbegin.lineno );
		lline = linepointer( blkend.lineno );
		space = copytospace( fline, lline, blkbegin.column, blkend.column );
		deletelinklist( fline, lline, blkbegin.column, blkend.column );
		if ( lineno == blkend.lineno ) {
			if ( blkend.column > blkbegin.column ) {
				if ( *p_xCursorPos > blkend.column ) {
					*p_xCursorPos = *p_xCursorPos - ( blkend.column - blkbegin.column );
				} else {
					if ( *p_xCursorPos > blkbegin.column ) {
						*p_xCursorPos = blkbegin.column;
					}
				}
			}
			if ( blkbegin.column > blkend.column ) {
				*p_xCursorPos = *p_xCursorPos + blkbegin.column - blkend.column;
			}
		}
		lineno = findlineno( curline );
		blkbegin.lineno = lineno;
		blkbegin.column = *p_xCursorPos + firstcol;
		blkend.lineno = lineno + spacesize( space );
		if ( space->next != space ) {
			blkend.column = thaistrlen( ( space->previous )->text );
		} else {
			blkend.column = blkbegin.column + thaistrlen( space->text );
		}
		insertlinklist( space, curline, *p_xCursorPos + firstcol );
		loadtoline( curline->text );
		changeflag = YES;
		pagecomplete = NO;
		dispblock = YES;
	}
}

struct line_node *rdfiletospace( char *p_filename ) {
	FILE *fip;
	register int i;
	struct line_node *space;
	struct line_node *newline;
	struct line_node *currentline;
	struct line_node *freeline;
	unsigned char *text_str;

	fip = fopen( p_filename, "rt" );
	if ( fip ) {
		blockmsg( 5 );
		dispstrhgc( "กำลังอ่านข้อมูลจากแผ่นจานแม่เหล็กอยู่ กรุณารอสักครู่...", ( 14 + center_factor ) + 6, 5, REVERSEATTR );

		text_str = ( unsigned char * ) malloc( MAXCOL * sizeof( unsigned char ) );
		if ( text_str == NULL ) {
			freeblk( fip, space, currentline, freeline, text_str );
			return( NULL );
		}

		space = ( struct line_node * ) malloc( sizeof( struct line_node ) );
		if ( space == NULL ) {
			freeblk( fip, space, currentline, freeline, text_str );
			return( NULL );
		}

		space->next = space;
		space->previous = space;
		space->wrap = NO;
#ifdef WANT_TO_USE_GRAPH
		space->graph = NULL;
#endif
		space->text = ( unsigned char * ) malloc( 1 );

		if ( space->text == NULL ) {
			freeblk( fip, space, currentline, freeline, text_str );
			return( NULL );
		}

		*( space->text ) = '\0';
		if ( fgets( text_str, MAXCOL, fip ) != NULL ) {
			i = strlen( text_str );
			if ( ( i > 0 ) && ( text_str[i - 1] == '\n' ) ) {
				text_str[i - 1] = '\0';
				i--;
			}
#ifdef WANT_TO_USE_GRAPH
			if ( ( text_str[0] == '.' ) &&
				( text_str[1] == 'G' ) &&
				( text_str[2] == 'R' ) ) {
				space->graph = NULL;
				space->graph = readgraph( text_str + 4 );
				free( space->text );
				space->text = NULL;
			} else {
#endif
				if ( ( i > 0 ) && ( text_str[i - 1] == WRAPCODE ) ) {
					text_str[i - 1] = '\0';
					space->wrap = YES;
				}
				free( space->text );
				space->text = ( unsigned char * ) malloc( strlen( text_str ) + 1 );

				if ( space->text == NULL ) {
					freeblk( fip, space, currentline, freeline, text_str );
					return( NULL );
				}

				if ( !stdcode ) {
					for ( i = 0; text_str[i] != '\0'; i++ ) {
						text_str[i] = kutostd( text_str[i] );
					}
				}
				strcpy( space->text, text_str );
#ifdef WANT_TO_USE_GRAPH
			}
#endif
			currentline = space;
			while ( fgets( text_str, MAXCOL, fip ) != NULL ) {
				if ( currentline->text == NULL ) {
					newline = currentline;
				} else {
					newline = ( struct line_node * ) malloc( sizeof( struct line_node ) );

					if ( newline == NULL ) {
						freeblk( fip, space, currentline, freeline, text_str );
						return( NULL );
					}

					newline->text = NULL;
#ifdef WANT_TO_USE_GRAPH
					newline->graph = NULL;
#endif
					newline->wrap = NO;
					insert_line( currentline, newline );
				}
				i = strlen( text_str );
				if ( ( i > 0 ) && ( text_str[i - 1] == '\n' ) ) {
					text_str[i - 1] = '\0';
					i--;
				}

#ifdef WANT_TO_USE_GRAPH
				if ( ( text_str[0] == '.' ) &&
					( text_str[1] == 'G' ) &&
					( text_str[2] == 'R' ) ) {
					newline->graph = readgraph( text_str + 4 );
				} else {
#endif
					if ( ( i > 0 ) && ( text_str[i - 1] == WRAPCODE ) ) {
						text_str[i - 1] = '\0';
						newline->wrap = YES;
					}
					newline->text = ( unsigned char * ) malloc( strlen( text_str ) + 1 );

					if ( newline->text == NULL ) {
						freeblk( fip, space, currentline, freeline, text_str );
						return( NULL );
					}

					if ( !stdcode ) {
						for ( i = 0; text_str[i] != '\0'; i++ ) {
							text_str[i] = kutostd( text_str[i] );
						}
					}
					strcpy( newline->text, text_str );
#ifdef WANT_TO_USE_GRAPH
				}
#endif
				currentline = newline;
			}
		}
		fclose( fip );
		free( text_str );
		return( space );
	} else {
		errorsound( );

		blockmsg( 5 );
		dispstrhgc( "ไม่พบแฟ้มข้อมูลนี้ ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 10, 5, REVERSEATTR );

		while ( ebioskey( 0 ) != ESCKEY );
		return( NULL );
	}
}

/* Free memory for rdfiletospace() if no memory available. */
void freeblk( FILE *p_file, struct line_node *p_space, struct line_node *p_currentline, struct line_node *p_freeline, unsigned char *p_textstr ) {
	fclose( p_file );

	errorsound( );

	blockmsg( 5 );
	dispstrhgc( "หน่วยความจำไม่พอ ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 8, 5, REVERSEATTR );

	while ( ebioskey( 0 ) != ESCKEY );
	dispstrhgc( "กำลังคืนหน่วยความจำให้ระบบ กรุณารอสักครู่ ...", ( 14 + center_factor ) + 8, 6, REVERSEATTR );
	if ( p_space != NULL ) {
		p_currentline = p_space->next;
		while ( p_currentline != p_space ) {
			p_freeline = p_currentline;
			p_currentline = p_currentline->next;
			if ( p_freeline->text != NULL ) {
				free( p_freeline->text );
			}
#ifdef WANT_TO_USE_GRAPH
			if ( p_freeline->graph != NULL ) {
				free( p_freeline->graph );
			}
#endif
			free( p_freeline );
		}
		if ( p_space->text != NULL ) {
			free( p_space->text );
		}
#ifdef WANT_TO_USE_GRAPH
		if ( p_space->graph != NULL ) {
			free( p_space->graph );
		}
#endif
		free( p_space );
	}

	if ( p_textstr != NULL ) {
		free( p_textstr );
	}
}

unsigned int spacesize( struct line_node *p_space ) {
	struct line_node *temp;
	unsigned int size = 0;

	temp = p_space;
	while ( temp->next != p_space ) {
		temp = temp->next;
		size++;
	}
	return( size );
}

void readblk( unsigned int *p_xCursorPos ) {
	char file_name[MAXPATH];
	struct line_node *space;
	int i;

	storeline( curline );
	pagecomplete = NO;
	blockmsg( 5 );
	dispstrhgc( "ใส่ชื่อแฟ้มข้อมูลที่ต้องการอ่าน :", ( 14 + center_factor ) + 3, 5, REVERSEATTR );
	strcpy( file_name, "*.*" );
	i = getname( file_name, ( 14 + center_factor ) + 27, 5, 22, REVERSEATTR );
	if ( ( i == YES ) && ( file_name[0] != '\0' ) ) {
		if ( havewild( file_name ) ) {
			selectfile( file_name );
		}
		space = rdfiletospace( file_name );
		if ( space != NULL ) {
			blkbegin.lineno = lineno;
			blkbegin.column = *p_xCursorPos + firstcol;
			blkend.lineno = lineno + spacesize( space );
			if ( space->next != space ) {
				blkend.column = thaistrlen( ( space->previous )->text );
			} else {
				blkend.column = blkbegin.column + thaistrlen( space->text );
			}
			insertlinklist( space, curline, *p_xCursorPos + firstcol );
			changeflag = YES;
			dispblock = YES;
			loadtoline( curline->text );
		}
	}
}

unsigned long getfilesize( void ) {
	struct line_node *keepline;
	struct line_node *templine = sentinel->next;

	unsigned long fsize = 0;
	unsigned int line = 0;

	keepline = templine;
	if ( templine == NULL ) {
		blockmsg( 5 );
		dispstrhgc( "getfilesize() error", 1, 1, REVERSEATTR );
		ebioskey( 0 );
	}
	++line;
	while ( templine->next != sentinel ) {
		fsize = fsize + strlen( templine->text ) + 2;
		if ( templine->wrap == YES ) {
			fsize++;
		}
		templine = templine->next;
		++line;

		if ( templine == NULL ) {
			dispstrhgc( "getfilesize() error", 1, 1, REVERSEATTR );
			dispstrhgc( keepline->text, 1, 2, REVERSEATTR );
			dispprintf( 1, 3, REVERSEATTR, "Line no = %u", line );
			ebioskey( 0 );
			settext( );
			exit( EXIT_FAILURE );
		}
		keepline = templine;
	}
	fsize += strlen( templine->text );
	return( fsize );
}

struct dfree *dfreep;

unsigned long diskfree( char p_driveno ) {
	unsigned long avail;
	unsigned long bsec;
	unsigned long sclus;

	getdfree( p_driveno, dfreep );

	avail = dfreep->df_avail;
	bsec = dfreep->df_bsec;
	sclus = dfreep->df_sclus;

	return( avail * bsec * sclus );
}

int chkspace( char *p_filename ) {
	unsigned long diskspace;
	unsigned long filesize;
	int flag;
	char i;
	struct ffblk fdat;
	char drv[MAXDRIVE];
	char dir[MAXDIR];
	char name[MAXFILE];
	char ext[MAXEXT];

	flag = fnsplit( p_filename, drv, dir, name, ext );	/* Analyse Fname */
	filesize = getfilesize( );

	framebox( 14 + center_factor, 4, ( 14 + center_factor ) + 52, 8, REVERSEATTR );
	dispstrhgc( "ขนาดแฟ้มข้อมูล =                   ไบต์", ( 14 + center_factor ) + 13, 5, REVERSEATTR );
	dispstrhgc( "เนื้อที่ว่างบนแผ่นจานแม่เหล็ก =                   ไบต์", ( 14 + center_factor ) + 3, 6, REVERSEATTR );
	dispprintf( ( 14 + center_factor ) + 29, 5, REVERSEATTR, "%#10lu", filesize );
	if ( flag & DRIVE ) {	/* Has it Drive */
		i = drv[0] - 'A' + 1;
	} else {
		i = 0;
	}
	diskspace = diskfree( i );

	if ( !create_bak && file_exist( p_filename ) ) {	/* If .BAK is not necessary */
		findfirst( p_filename, &fdat, 0 );				/* DiskSpace can be increased */
		diskspace += ( unsigned long ) fdat.ff_fsize;	/* By old file size */
	}

	dispprintf( ( 14 + center_factor ) + 29, 6, REVERSEATTR, "%10lu", diskspace );
	if ( diskspace < filesize ) {
		dispstrhgc( "เนื้อที่บนแผ่นจานแม่เหล็กไม่พอ ! กดปุ่ม ESC เพื่อทำงานต่อ...", ( 14 + center_factor ) + 3, 7, REVERSEATTR );
		errorsound( );
		while ( ebioskey( 0 ) != ESCKEY );
		return( 0 );
	} else {
		return( 1 );
	}
}

void writeblk( char *p_filename, struct line_node *p_firstLine, unsigned int p_firstCol,
	struct line_node *p_lastLine, unsigned int p_lastCol ) {

	FILE *fip;
	struct line_node *currentline;
	int key;
	int i;
	int j;
	int firstround;
	int count;
	unsigned char *templine;
	unsigned char fontcode[9];
	font_attr font;
	char drv[MAXDRIVE];
	char dir[MAXDIR];
	char name[MAXFILE];
	char ext[MAXEXT];
	char name_bak[MAXPATH];

	static char bakext[] = ".BAK";
	unsigned char *text_str;

	text_str = ( unsigned char * ) malloc( MAXCOL * sizeof( unsigned char ) );
	if ( text_str == NULL ) {
		errorsound( );
		return;									/* Not enough memory */
	}

	pagecomplete = NO;
	storeline( curline );

	blockmsg( 5 );
	dispstrhgc( "ใส่ชื่อแฟ้มข้อมูลที่ต้องการจัดเก็บ :", ( 14 + center_factor ) + 3, 5, REVERSEATTR );
	i = getname( p_filename, ( 14 + center_factor ) + 29, 5, 22, REVERSEATTR );
	if ( ( i != YES ) || ( p_filename[0] == '\0' ) ) {
		free( text_str );
		return;
	}

	blockmsg( 5 );
	fnsplit( p_filename, drv, dir, name, ext );

	if ( file_exist( p_filename ) ) {
		dispstrhgc( "แฟ้มข้อมูลเดิมมีอยู่แล้ว ต้องการเขียนทับหรือไม่ ? (Y/N)", ( 14 + center_factor ) + 5, 5, REVERSEATTR );
		do {
			key = toupper( ebioskey( 0 ) & 0xff );
		} while ( ( key != 'N' ) && ( key != 'Y' ) );

		if ( key == 'Y' ) {						/* Save edited file */
			if ( create_bak ) {					/* Create .BAK */
				fnmerge( name_bak, drv, dir, name, bakext );
				remove( name_bak );				/* Delete Old .BAK */
				if ( chkspace( p_filename ) ) {	/* Enough Space ? */
					rename( p_filename, name_bak );
				} else {
					free( text_str );
					return;						/* File too large */
				}
			} else {							/* Ignore .BAK */
				if ( chkspace( p_filename ) ) {	/* Enough Space ? */
					remove( p_filename );
				} else {
					free( text_str );
					return;
				}
			}
		} else {								/* Don't save edited file */
			free( text_str );
			return;
		}
	} else {									/* Save new File */
		if ( !chkspace( p_filename ) ) {			/* Not enough space */
			free( text_str );
			return;
		}
	}

	if ( ( fip = fopen( p_filename, "wt" ) ) != NULL ) {
		dispstrhgc( "กำลังจัดเก็บแฟ้มข้อมูลอยู่ กรุณารอสักครู่...", ( 14 + center_factor ) + 12, 7, REVERSEATTR );
		currentline = p_firstLine;
#ifdef WANT_TO_USE_GRAPH
		if ( currentline->graph != NULL ) {
			fprintf( fip, ".GR %s\n", currentline->graph );
		}
#endif
		firstround = linearcolumn( currentline->text, p_firstCol, &font );
		findstrcode( fontcode, font );
		fputs( fontcode, fip );
		while ( currentline != p_lastLine ) {
			if ( !stdcode ) {
				templine = currentline->text;
				i = 0;
				while ( *( templine + firstround + i ) != '\0' ) {
					text_str[i] = *( templine + firstround + i );
					i++;
				}
				text_str[i] = '\0';
				i = 0;
				while ( text_str[i] != '\0' ) {
					text_str[i] = stdtoku( text_str[i] );
					i++;
				}
				fputs( text_str, fip );
			} else {
				templine = currentline->text;
				fputs( templine + firstround, fip );
			}
			if ( currentline->wrap ) {
				putc( WRAPCODE, fip );
			}
			putc( '\n', fip );
			firstround = 0;
			currentline = currentline->next;
#ifdef WANT_TO_USE_GRAPH
			if ( currentline->graph != NULL ) {
				fprintf( fip, ".GR %s\n", currentline->graph );
			}
#endif
		}
		templine = currentline->text;
		count = linearcolumn( templine, p_lastCol, &font );
		i = firstround;
		j = 0;
		while ( ( i != count ) &&
			( *( templine + i ) != '\0' ) ) {
			text_str[j++] = *( templine + i );
			i++;
		}
		text_str[j] = '\0';
		if ( !stdcode ) {
			i = 0;
			while ( text_str[i] != '\0' ) {
				text_str[i] = stdtoku( text_str[i] );
				i++;
			}
		}
		fputs( text_str, fip );
		if ( currentline->wrap ) {
			putc( WRAPCODE, fip );
		}
		putc( 0x1a, fip );
		free( text_str );
		fclose( fip );
	} else {
		errorsound( );
		blockmsg( 5 );
		dispstrhgc( "จัดเก็บแฟ้มข้อมูลผิดพลาด ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 6, 7, REVERSEATTR );
		while ( ebioskey( 0 ) != ESCKEY );
		free( text_str );
	}
}

void writeblock( void ) {
	int linenum;
	char file_name[22];
	struct line_node *firstline;
	struct line_node *lastline;

	if ( haveblock( ) ) {
		file_name[0] = '\0';
		linenum = blkbegin.lineno;			/* get displacement */
		firstline = sentinel->next;			/* then set pointer */
		while ( linenum-- > 1 ) {			/* to first line of */
			firstline = firstline->next;	/* block position   */
		}
		linenum = blkend.lineno;			/* get displacement */
		lastline = sentinel->next;			/* of end block to  */
		while ( linenum-- > 1 ) {			/* set pointer to   */
			lastline = lastline->next;		/* last line of block */
		}
		writeblk( file_name, firstline, blkbegin.column, lastline, blkend.column );
	}
}

void blkcmd( register unsigned int p_key, unsigned int *p_xCursorPos ) {
	p_key &= 0xff;
	if ( !isalpha( p_key ) && !iscntrl( p_key ) ) {
		return;
	}
	switch ( p_key & 0x1f ) {
	case 'b' - 'a' + 1:
		markbegin( *p_xCursorPos );
		break;
	case 'k' - 'a' + 1:
		markend( *p_xCursorPos );
		break;
	case 'c' - 'a' + 1:
		copyblk( p_xCursorPos );
		break;
	case 'y' - 'a' + 1:
		deleteblk( );
		break;
	case 'v' - 'a' + 1:
		moveblk( p_xCursorPos );
		break;
	case 'h' - 'a' + 1:
		toggleblk( );
		break;
	case 'p' - 'a' + 1:
		print_file( );
		break;
	case 'r' - 'a' + 1:
		readblk( p_xCursorPos );
		break;
	case 'w' - 'a' + 1:
		writeblock( );
		break;
	case 's' - 'a' + 1:
		writeblk( filename, sentinel->next, 0, sentinel->previous, MAXCOL );
		changeflag = NO;
		break;
	}
}

void blockcommand( unsigned int *p_xCursorPos ) {
	unsigned int key;

	dispkey( CNTRL_K );
	waitkbd( 3, 2 );
	key = ebioskey( 0 );
	blkcmd( key, p_xCursorPos );
}
