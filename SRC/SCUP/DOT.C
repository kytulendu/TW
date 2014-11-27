/*
* ============================================================================
* DOT.C
* Subroutine Dotcommand & Mailmerge.
*
* Written   date 09-18-88.
* Update    date 09-22-88.
* Update    date 04-08-89.
* Updated : by Suttipong Kanakakorn Wed  08-09-1989  00:10:44
*           - add function prototype , clear all warning
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <ctype.h>

#include "..\common\cwtype.h"

#include "cuptype.h"
#include "global.h"
#include "printing.h"
#include "prncntrl.h"
#include "prtutil.h"

#include "dot.h"

void getfieldname( char *rvstring );
void getfieldcontent( char *string );
int getfield( char *s1, char *s2, int pin );
void lookup( char *field, char *content );

#define MAXNUM        20									/* number of mergefields */
#define MAXLENGTH     80									/* maxlength of each field content */
#define MAXNAMELENGTH 20									/* maxlength of each field name */

/** Global area already defined in pmenu.c */
extern FILE *mfp, *fopen( );
extern char *fieldname[MAXNUM];								/* define array of fieldnames */
extern char *fieldcontent[MAXNUM];							/* define array of strings */
extern int fieldcount;										/* define number of fields */
extern int stdcode;											/* define data file code used */

/** Global area already defined in printvar.h */

/** Routine to identify fieldnames  and
*   allocate corresponding field content
*   after get .RV command and it's parms. */
/* Suttipong Kanakakorn Tue  11-07-1989  01:13:34
someone forget to freemem I just avoid alloc it again only */
void getfieldname( char *rvstring ) {
	char s[MAXNAMELENGTH];									/* field name tempolary area */
	int pin = 0;											/* point through strings */
	int n = 0;												/* number of fields */
	int i = 0;
	while ( rvstring[i] != 0 ) { i++; }
	while ( rvstring[i] <= ' ' ) { i--; }
	rvstring[++i] = '\0';
	do {
		pin = getfield( s, rvstring, pin );
		if ( fieldname[n] == NULL ) {						/* avoid alloc again */
			fieldname[n] = ( char * ) calloc( MAXNAMELENGTH, sizeof( char ) );
			fieldcontent[n] = ( char * ) calloc( MAXLENGTH, sizeof( char ) );
		}
		strcpy( fieldname[n], s );							/* store in global area */
		n++;
	} while ( pin != NULL );
	fieldcount = n;
}

/** Routine to collect fieldcontents
*   after read merge file. */
void getfieldcontent( char *string ) {
	char s[MAXLENGTH];										/* field name tempolary area */
	int pin = 0;											/* point through strings */
	int n = 0;												/* number of fields */
	do {
		pin = getfield( s, string, pin );
		strcpy( fieldcontent[n], s );						/* store in array */
		n++;
	} while ( pin != NULL && n < fieldcount );
}

int getfield( char *s1, char *s2, int pin ) {
	int i = 0;
	while ( s2[pin] == ',' ) { pin++; }						/* skip comma */
	while ( ( s2[pin] != ',' ) && ( s2[pin] != '\0' ) ) {
		if ( s2[pin] >= ' ' ) {
			s1[i] = s2[pin];
			pin++; i++;
		} else {
			pin++;
		}
	}
	s1[i] = '\0';											/* terminate */
	if ( s2[pin] == ',' ) {
		return( ++pin );									/* skip comma and return */
	} else {
		return( 0 );										/* last field reached */
	}
}

void mailmerge( char *stringin, char *stringout ) {
	int i, j, k, m, n;
	char field[20];
	char content[40];
	i = m = 0;
	while ( stringin[i] != '\0' ) {
		if ( stringin[i] == '&' ) {
			j = ++i;										/* testing string initial */
			k = 0;											/* start merge field */
			while ( stringin[j] != '\0' && stringin[j] != '&' ) {
				if ( stringin[j] >= ' ' ) {
					field[k++] = stringin[j++];
				} else {
					j++;
				}
			}
			if ( stringin[j] == '&' ) {						/* case of merge field ( &field& ) */
				i = ++j;									/* mailmerge success the field comsumed */
				field[k] = '\0';							/* terminate string */
				lookup( field, content );					/* get field content */
				n = 0;
				while ( content[n] != '\0' ) {
					stringout[m++] = content[n++];			/* store content */
				}
			} else {
				stringout[m++] = '&';						/* just normal alphasan character */
				i++;										/* consume one character ('&'). */
			}
		} else {
			stringout[m++] = stringin[i++];					/* normal character */
		}
	}
	stringout[m] = '\0';
}

void lookup( char field[], char content[] ) {
	int i = 0;
	int j = 0;
	int k = 0;
	while ( ( strcmp( field, fieldname[i] ) != 0 ) && ( i < fieldcount ) ) {
		i++;
	}
	if ( i != fieldcount ) {								/* found */
		while ( ( content[j++] = fieldcontent[i][k++] ) != '\0' );
	} else {
		content[0] = '\0';									/* not found return null string */
	}
}

void dotcommand( char *string ) {
	/* ----- changeable global area ----- */
	extern char *setpageformat( );
	extern int mailmergeflag;
	extern int mergefileexist;
	extern int fieldnameexist;
	extern int cpi;
	extern int lineperpage;
	extern int userlineperpage;
	extern int leftmargin;
	extern int rightmargin;
	extern char heading[];
	extern char footing[];
	extern char pagetitle[];
	extern char pageformat[];
	extern int newpage;
	extern int curpage;
#ifdef WANT_TO_USE_GRAPH
	extern int pic_print;
	extern int pic_offset;
#endif

	/* ------ nonchange global area ------ */
	extern int locpagetitle;
	extern int locheading;
	extern int locfooting;
	extern int printer;
	extern int maxcol;
	extern int maxdot;
	extern int maxbuffer;
	extern int curline;

	int command;
#ifdef WANT_TO_USE_GRAPH
	int no_arg;
	int handle;
#endif
	int cdtpgbrk;											/* condition page break */
	char content[300];
	char temp[300];
#ifdef WANT_TO_USE_GRAPH
	char arg[10][40];
#endif

	strcpy( temp, &string[3] );								/* text begin at 4th */
	strcpy( temp, &temp[blankskip( temp )] );				/* parse to nonblank */
	temp[strlen( temp ) - 1] = '\0';
	command = ( tolower( string[1] ) << 8 ) + tolower( string[2] ); /* store 2 chars in one integer */
	switch ( command ) {
#ifdef CUSTOM_FONT
	case ( 'l' << 8 ) + 'f':
		get_argument( arg, string, &no_arg );			/* get_argument() in PIC.C */
		if ( no_arg == 2 ) {
			if ( ( handle = open( &arg[1][0], O_RDONLY ) ) >= 0 ) {
				_read( handle, font[0], 11264 );
				close( handle );
			} else {
				disperror( " หาแฟ้มตัวอักษรไม่พบ กดปุ่มใดๆเพื่อทำงานต่อ " );
			}
		} else {
			disperror( " dot command ไม่ถูกต้อง กดปุ่มใดๆเพื่อทำงานต่อ " );
		}
		break;
#endif
#ifdef WANT_TO_USE_GRAPH
	case ( 'g' << 8 ) + 'p':
	case ( 'g' << 8 ) + 'r':							/* graphic print */
		get_argument( arg, string, &no_arg );			/* get print parameter */
		if ( no_arg == 3 ) {
			if ( ( handle = open( &arg[1][0], O_RDONLY ) ) >= 0 ) {
				close( handle );
				analyze_picture_file( &arg[1][0] );
				initialize_read( &arg[1][0] );
				pic_print = YES;
				pic_offset = atoi( &arg[2][0] );
			} else {
				disperror( " หาแฟ้มรูปภาพไม่พบ กดปุ่มใดๆเพื่อทำงานต่อ " );
			}
		} else {
			disperror( " dot command ไม่ถูกต้อง กดปุ่มใดๆเพื่อทำงานต่อ " );
		}
		break;
#endif
	case ( 'p' << 8 ) + 'a':								/* newpage or eject. */
		newpage = YES;
		break;
	case ( 'c' << 8 ) + 'p':								/* condition page brk. */
		cdtpgbrk = ( atoi( temp )>userlineperpage ) ? userlineperpage : atoi( temp );
		if ( curline - 1 + cdtpgbrk > userlineperpage ) {
			newpage = YES;									/* not enough line to print block */
		}
		break;
	case ( 'p' << 8 ) + 'n':								/* change currrent page no. */
		curpage = atoi( temp );
		break;
	case ( 'd' << 8 ) + 'f':								/* open merge file */
		if ( mergefileexist == NO ) {
			if ( ( mfp = fopen( temp, "r" ) ) != NULL ) {
				mergefileexist = YES;
			}
		}
		break;
	case ( 'r' << 8 ) + 'v':								/* read mergefield list */
		if ( fieldnameexist == NO ) {						/* first visit */
			getfieldname( temp );							/* read field name of merge record */
			fieldnameexist = YES;
			if ( ( mergefileexist == YES ) && ( fgets( content, 200, mfp ) != NULL ) ) {
				getfieldcontent( content );
				mailmergeflag = YES;
			}
		}
		break;
	case ( 's' << 8 ) + 'k':								/* skip mailmerge record */
		if ( ( fgets( content, 200, mfp ) != NULL ) ) {
			getfieldcontent( content );
		}
		break;
	case ( 'c' << 8 ) + 'w':								/* set character width */
		cpi = atoi( temp );
		switch ( maxdot ) {
		case 1920:
			maxbuffer = ( cpi<10 ) ? 1920 : 192 * cpi;
			break;
		case 3264:
			maxbuffer = ( cpi<10 ) ? 3264 : 3264 * ( long ) ( cpi ) / 10 + 50;
			break;
		case 1440:
			maxbuffer = ( cpi<10 ) ? 1440 : 144 * cpi;
			break;
		case 2448:
			maxbuffer = ( cpi<10 ) ? 2440 : 245 * cpi;
			break;
		}
		break;
		/* modify by Suttipong Kanakakorn Tue  08-29-1989  13:19:53 */
	case ( 'p' << 8 ) + 'l':								/* set user line per page */
	case ( 'p' << 8 ) + 'i':								/* set page length in inches */
		if ( command == ( ( 'p' << 8 ) + 'l' ) ) {
			userlineperpage = atoi( temp );
		} else {
			pagelength = atoi( temp );
			PrinterSetFormLenghtInch( pagelength );
		}
		set_all_lineperpage( BATCH );
		linespace = find_line_space( );
		break;
	case ( 'h' << 8 ) + 'e':								/* set heading text */
		strcpy( heading, temp );
		if ( stdcode == NO ) {
			contostd( heading );							/* converse from ku to so-mo-or */
		}
		break;
	case ( 'f' << 8 ) + 'o':								/* set footing text */
		strcpy( footing, temp );
		if ( stdcode == NO ) {
			contostd( footing );							/* converse from ku to so-mo-or */
		}
		break;
	case ( 'p' << 8 ) + 't':								/* set pagetitle and pageformat */
		strcpy( pagetitle, temp );
		strcpy( pageformat, setpageformat( pagetitle, maxcol ) );
		if ( stdcode == NO ) {
			contostd( pageformat );							/* converse from ku to so-mo-or */
		}
		break;
	case ( 'p' << 8 ) + 'o':								/* set leftmargin */
		leftmargin = atoi( temp );
		leftmargin = ( leftmargin<rightmargin ) ? leftmargin : 1;
		break;
	case ( 'p' << 8 ) + 'r':								/* set rightmargin */
		rightmargin = atoi( temp );
		rightmargin = ( ( rightmargin>leftmargin ) && ( rightmargin<maxcol ) ) ? rightmargin : maxcol;
		break;

	}
}

int blankskip( char *s ) {
	register int i = 0;
	while ( *s++ == ' ' ) {
		i++;
	}
	return( i );
}
