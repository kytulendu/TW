/*
* ============================================================================
* DIR.C
*
* Updated: Suttipong Kanakakorn
*          Sun  08-06-1989  18:24:10
* ============================================================================
*/

#include <stdlib.h>
#include <dir.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>

#include "cwtype.h"
#include "cscrn.h"
#include "cwgrphc.h"
#include "ekbd.h"
#include "kbdcode.h"
#include "sound.h"

#include "dir.h"

#define DIRCOLMAX 5
#define DIRROWMAX 5

struct dirnode {
	char filename[13];
	char attrib;
	struct dirnode *previous;
	struct dirnode *next;
};

static struct dirnode *headdir, *dirpage;

static int dircol;
static int dirrow;

/* private prototype function */
int createdir( char *p_fileMask );
void showfile( int col, int row, char attr );
void showpagedir( void );
void freedir( void );
void dirpgup( void );
void setdirpos( struct dirnode *namewant );
void dirpgdn( void );
void dirup( void );
void dirdown( void );
void dirright( void );
void dirleft( void );

int createdir( char *p_fileMask ) {
	struct dirnode *tempdir;
	struct ffblk ffblock;
	int done, i;
	char *fileName;

	headdir->previous = headdir;
	headdir->next = headdir;
	tempdir = headdir;

	/* Find files. */
	done = findfirst( p_fileMask, &ffblock, FA_NORMAL );

	while ( !done ) {
		tempdir->next = ( struct dirnode * ) malloc( sizeof( struct dirnode ) );
		if ( tempdir->next == NULL ) {
			errorsound( );
			blockmsg( 5 );
			dispstrhgc( "หน่วยความจำไม่พอ ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 8, 5, 2 );
			while ( ebioskey( 0 ) != ESCKEY );
			freedir( );
			return( NO );
		}

		fileName = ffblock.ff_name;

		i = 0;
		while ( *fileName != '\0' ) {
			( tempdir->next )->filename[i] = *( fileName++ );
			i++;
		}
		( tempdir->next )->filename[i] = '\0';

		( tempdir->next )->attrib = ffblock.ff_attrib;

		( tempdir->next )->previous = tempdir;
		tempdir = tempdir->next;
		tempdir->next = headdir;
		headdir->previous = tempdir;

		done = findnext( &ffblock );
	}

	/* Find directory. */
	done = findfirst( "*.*", &ffblock, FA_DIREC );

	while ( !done ) {
		/* Check if the file is directory and not working directory ("."). */
		if ( ( ffblock.ff_attrib == FA_DIREC ) && ( strcmp( ffblock.ff_name, "." ) != 0 ) ) {
			tempdir->next = ( struct dirnode * ) malloc( sizeof( struct dirnode ) );
			if ( tempdir->next == NULL ) {
				errorsound( );
				blockmsg( 5 );
				dispstrhgc( "หน่วยความจำไม่พอ ! กด <ESC> เพื่อทำงานต่อ", ( 14 + center_factor ) + 8, 5, 2 );
				while ( ebioskey( 0 ) != ESCKEY );
				freedir( );
				return( NO );
			}

			fileName = ffblock.ff_name;

			sprintf( ( tempdir->next )->filename, "%s\0", fileName );
			( tempdir->next )->attrib = ffblock.ff_attrib;

			( tempdir->next )->previous = tempdir;
			tempdir = tempdir->next;
			tempdir->next = headdir;
			headdir->previous = tempdir;
		}
		done = findnext( &ffblock );
	}

	return( YES );
}

void showfile( int col, int row, char attr ) {
	struct dirnode *tempdir;
	int count;
	tempdir = dirpage;
	for ( count = ( DIRCOLMAX * row ) + col; ( count != 0 ) && ( tempdir != headdir ); count-- ) {
		tempdir = tempdir->next;
	}
	if ( tempdir != headdir ) {
		if ( tempdir->attrib == FA_DIREC ) {
			dispprintf( col * 13 + 9, row + 9, attr, "\\%s", tempdir->filename );
		} else {
			dispstrhgc( tempdir->filename, col * 13 + 9, row + 9, attr );
		}
	}
}

void showpagedir( void ) {
	int col, row;
	framebox( 4, 8, 4 + 70, 14, 2 );
	for ( row = 0; row != DIRROWMAX; row++ ) {
		for ( col = 0; col != DIRCOLMAX; col++ ) {
			showfile( col, row, 2 );
		}
	}
}

void freedir( void ) {
	struct dirnode *tempdir, *tempdir2;
	tempdir = headdir->next;
	while ( tempdir != headdir ) {
		tempdir2 = tempdir;
		tempdir = tempdir->next;
		free( tempdir2 );
	}
}

void dirpgup( void ) {
	struct dirnode *tempdir;
	int count, countrow;
	tempdir = dirpage;
	for ( countrow = DIRROWMAX; ( countrow != 0 ) && ( tempdir->previous != headdir ); countrow-- ) {
		for ( count = DIRCOLMAX; ( count != 0 ) && ( tempdir->previous != headdir ); count-- ) {
			tempdir = tempdir->previous;
		}
	}
	if ( tempdir->previous != headdir ) {
		dirpage = tempdir;
	} else {
		dirpage = headdir->next;
		dirrow = 0;
	}
	showpagedir( );
}

void setdirpos( struct dirnode *namewant ) {
	int count;
	struct dirnode *tempdir;
	tempdir = dirpage;
	dirrow = 0;
	dircol = 0;
	while ( tempdir != namewant ) {
		for ( count = ( DIRCOLMAX - 1 ); ( count != 0 ) && ( tempdir != namewant ); count-- ) {
			tempdir = tempdir->next;
			dircol++;
		}
		if ( tempdir != namewant ) {
			dirrow++;
			dircol = 0;
			tempdir = tempdir->next;
		}
	}
}

void dirpgdn( void ) {
	struct dirnode *tempdir;
	int count, countrow;
	tempdir = dirpage;
	for ( countrow = DIRROWMAX; ( countrow != 0 ) && ( tempdir->next != headdir ); countrow-- ) {
		for ( count = DIRCOLMAX; ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
			tempdir = tempdir->next;
		}
		if ( tempdir->next != headdir ) {
			dirpage = tempdir;
		}
	}
	for ( count = dircol; ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
		tempdir = tempdir->next;
	}
	showpagedir( );
	setdirpos( tempdir );
}

void dirup( void ) {
	struct dirnode *tempdir;
	int count;
	tempdir = dirpage;
	for ( count = DIRCOLMAX; ( count != 0 ) && ( tempdir->previous != headdir ); count-- ) {
		tempdir = tempdir->previous;
	}
	if ( count == 0 ) {
		dirpage = tempdir;
		showpagedir( );
	}
}

void dirdown( void ) {
	struct dirnode *tempdir, *tempdir2;
	int count;
	tempdir = dirpage;
	for ( count = ( DIRCOLMAX * dirrow ); ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
		tempdir = tempdir->next;
	}
	tempdir2 = dirpage;
	for ( count = ( DIRCOLMAX - 1 ); ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
		tempdir = tempdir->next;
		tempdir2 = tempdir2->next;
	}
	if ( tempdir->next != headdir ) {
		tempdir2 = tempdir2->next;
		if ( dirrow == ( DIRROWMAX - 1 ) ) {
			dirpage = tempdir2;
			showpagedir( );
		}
		for ( count = ( dircol + 1 ); ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
			tempdir = tempdir->next;
		}
		setdirpos( tempdir );
	}
}

void dirright( void ) {
	struct dirnode *tempdir;
	int count;
	tempdir = dirpage;
	for ( count = ( DIRCOLMAX * dirrow ) + dircol; count != 0; count-- ) {
		tempdir = tempdir->next;
	}
	if ( tempdir->next != headdir ) {
		dircol++;
	}
}

void dirleft( void ) {
	struct dirnode *tempdir;
	int count;
	tempdir = dirpage;
	for ( count = ( DIRCOLMAX * dirrow ) + DIRCOLMAX - 1; ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
		tempdir = tempdir->next;
	}
	setdirpos( tempdir );
}

int selectfile( char *p_fileMask ) {
	struct dirnode *tempdir;
	int count, key, i, j;

	if ( createdir( p_fileMask ) == NO ) {
		return( NO );
	}
	if ( headdir->next != headdir ) {
		dirpage = headdir->next;
		dircol = 0;
		dirrow = 0;
		showpagedir( );
		showfile( dircol, dirrow, 0 );
		do {
			key = ebioskey( 0 );
			switch ( key ) {
			case UPKEY:
				showfile( dircol, dirrow, 2 );
				if ( dirrow == 0 ) {
					dirup( );
				} else {
					dirrow--;
				}
				showfile( dircol, dirrow, 0 );
				break;
			case DNKEY:
				showfile( dircol, dirrow, 2 );
				dirdown( );
				showfile( dircol, dirrow, 0 );
				break;
			case RIKEY:
				showfile( dircol, dirrow, 2 );
				if ( dircol == ( DIRCOLMAX - 1 ) ) {
					dircol = 0;
				} else {
					dirright( );
				}
				showfile( dircol, dirrow, 0 );
				break;
			case LEKEY:
				showfile( dircol, dirrow, 2 );
				if ( dircol == 0 ) {
					dirleft( );
				} else {
					dircol--;
				}
				showfile( dircol, dirrow, 0 );
				break;
			case PGUPKEY:
				dirpgup( );
				showfile( dircol, dirrow, 0 );
				break;
			case PGDNKEY:
				dirpgdn( );
				showfile( dircol, dirrow, 0 );
				break;
			case ESCKEY:
				freedir( );
				p_fileMask[0] = '\0';
				return( NO );
			case RETKEY:
				tempdir = dirpage;
				for ( count = ( DIRCOLMAX * dirrow ) + dircol; ( count != 0 ) && ( tempdir->next != headdir ); count-- ) {
					tempdir = tempdir->next;
				}

				if ( tempdir->attrib == FA_DIREC ) {
					if ( chdir( tempdir->filename ) ) {
						/* Can't change directory. */
						chdir( ".." );
						return( NO );
					}

					if ( createdir( p_fileMask ) == NO ) {
						return( NO );
					}

					if ( headdir->next != headdir ) {
						dirpage = headdir->next;
						dircol = 0;
						dirrow = 0;
						showpagedir( );
						showfile( dircol, dirrow, 0 );
					} else {
						p_fileMask[0] = '\0';
						return( NO );
					}
					break;
				} else {
					j = strlen( p_fileMask );
					while ( ( j != 0 ) && ( p_fileMask[j] != '\\' ) && ( p_fileMask[j] != ':' ) ) {
						j--;
					}
					if ( j != 0 ) {
						j++;
					}
					for ( i = 0; i < 13; i++ ) {
						p_fileMask[j++] = tempdir->filename[i];
					}
					freedir( );
					return( YES );
				}
			};
		} while ( 1 );

	} else {
		p_fileMask[0] = '\0';
		return( NO );
	}
}
