/*
* ============================================================================
* CWSETUP.C
*
* Written: Suttipong Kanakakorn
* Mon  07-31-1989  20:31:09
* ============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <process.h>
#include <string.h>
#include <conio.h>

#include "..\common\cwtype.h"
#include "..\common\cscrn.h"
#include "..\common\cwgrphc.h"
#include "..\common\cwtype.h"
#include "..\common\ekbd.h"
#include "..\common\fileutil.h"
#include "..\common\grdetect.h"
#include "..\common\kbdcode.h"
#include "..\common\getstr.h"
#include "..\common\tutil1.h"

#include "var.h"

#include "cw.h"
#include "edit.h"
#include "file.h"
#include "menu.h"

#include "cwsetup.h"

static char cup_option[16]; /* assume that only 16 char max for argument */

typedef struct each_option_setup {
    char *option_name;
    unsigned char *label;
    unsigned int *p_option_value;
    unsigned int p_option_default;
    unsigned char maxlen;
    strtype stype;
} each_option_setup;

each_option_setup option_setup[] = {
        { "thaicode", "���� (1.���. 2.�ɵ�)", ( unsigned int * ) &stdcode, YES, 1, ONEORTWO },
        { "pagebreak", "��˹�� (1.�� 2.�����)", ( unsigned int * ) &pagebreak, YES, 1, ONEORTWO },
        { "wordwrap", "�Ѵ���ѵ��ѵ� (1.�Ѵ 2.���Ѵ)", ( unsigned int * ) &wordwrap, YES, 1, ONEORTWO },
        { "createbackup", "���ҧ������ͧ�ء���駷���ա���红����� (1.���ҧ 2.������ҧ)", ( unsigned int * ) &create_bak, YES, 1, ONEORTWO },
        { "song", "���ŧ (1. �� 2. �����) ", ( unsigned int * ) &cu_song, YES, 1, ONEORTWO },
        { "leftmargin", "���˹�ҫ���", &leftmar, 1, 3, NUMBER },
        { "rightmargin", "���˹�Ң�� (����Թ 256)", &rightmar, 65, 3, NUMBER },
        { "lineperpage", "�ӹǹ��÷Ѵ���˹��", &lineperpage, 33, 3, NUMBER },
};

/* number of element of option_setup */
#define NELEM_OPTION ( sizeof( option_setup ) / sizeof( option_setup[0] ) )

void usage( void );
void set_directory( void );
void dispoption( size_t i );
void set_option_to_default( void );
void offbreak( void );

/** Print usage information. */
void usage( void ) {
    fputs( "Usage: TW.EXE [option] [file]\n", stderr );
    fputs( "Options:\n", stderr );
    fputs( "\t-h,  /h  Hercules Graphic Card.\n", stderr );
    fputs( "\t-hc, /hc Hercules Graphic Card, 80 column.\n", stderr );
    fputs( "\t-v,  /v  VGA.\n", stderr );
    fputs( "\t-e,  /e  EGA with EGA display.\n", stderr );
    fputs( "\t-em, /em EGA with Monochrome display.\n", stderr );
    fputs( "\t-m,  /m  MCGA.\n", stderr );
    fputs( "\t-a,  /a  AT&T400.\n", stderr );
    fputs( "\t-n,  /n  No backup file created.\n", stderr );
    fputs( "\t-w,  /w  No word wrap.\n", stderr );
    fputs( "\t-p,  /p  No page break.\n", stderr );
    fputs( "\t-s,  /s  No splash screen song.\n", stderr );
    exit( EXIT_FAILURE );
}

void inittabvalue( void ) {
    register size_t i;

    for ( i = 0; i < MAXCOL; ++i ) {
        tab[i] = NO;
    }
    for ( i = 5; i < ( rightmar - 6 ); i += 5 ) {
        tab[i] = YES;
    }
}

void cwsetup( int argc, char *argv[] ) {
    unsigned int dummy;
    register int i;

    progname = argv[0];

    while ( ( --argc > 0 ) && ( ( i = ( *++argv )[0] ) == '/' || i == '-' ) ) {
        strcat( cup_option, argv[0] );
        strcat( cup_option, " " );
        strupr( ++argv[0] );
        while ( i = *argv[0]++ ) {
            switch ( i ) {
            case 'H':
                scrmode = HERCMONO;
                break;
            case 'E':       /* e alone = EGA, em = EGA Monochrome */
                scrmode = EGA;
                break;
            case 'M':       /* m alone = MCGA */
                if ( scrmode == EGA ) {
                    scrmode = EGAMONO;
                } else {
                    scrmode = MCGA;
                }
                break;
            case 'V':
                scrmode = VGA;
                break;
            case 'A':
                scrmode = ATT400;
                break;
            case 'C':       /* /HC for Hercules, 80 column. */
                herc_align = 5;
                break;
            case 'N':
                create_bak = NO;
                break;
            case 'W':
                wordwrap = NO;
                break;
            case 'P':
                pagebreak = NO;
                break;
            case 'S':
                cu_song = NO;
                break;
            default:
                usage( );
            }
        }
    }
    if ( cup_option[0] == '\0' ) {
        strcpy( cup_option, "/" );
    }

    if ( argc >= 1 ) {
        placekey( ' ' );
        if ( file_exist( argv[0] ) ||
            strchr( argv[0], '*' ) ||
            strchr( argv[0], '?' ) ) {
            placekey( DNKEY );
        }
        placekey( RETKEY );
        while ( i = *argv[0]++ ) {
            placekey( i );
        }
        placekey( RETKEY );
    }

    set_directory( );
    if ( readoption( AUTO_FIND ) == 0 ) {
        set_option_to_default( );
    }

    readscrfont( dfont, "NORMAL.FON", cw_dir );
    readscrfont( ditalicfont, "ITALIC.FON", cw_dir );

    harderr( handler );
    initvalue( &dummy, &dummy );
    inittabvalue( );
    for ( i = 0; i < 10; i++ ) {
        macro[i][0] = '\0';
    }
    filename[0] = '\0';

    initscrn( );

    /** Set window of edit area by video mode
    *   CGA                  78 column, 5 line.
    *   VGA, MCGA            78 column, 19 line.
    *   EGA, EGA64, EGAMONO  78 column, 13 line.
    *   HERCMONO             88 column, 13 line.
    *   ATT400               78 column, 15 line. */
    wind.row = 4;
    wind.col = 1;
    wind.length = ( ( scrmode == HERCMONO ) && ( herc_align == 0 ) ) ? 88 : 78;

    switch ( scrmode ) {
    case VGA:
    case MCGA:
        wind.width = 19;
        break;
    case ATT400:
        wind.width = 15;
        break;
    case CGA:
        wind.width = 5;
        break;
    default:            /* HERCMONO, EGA, EGA64, EGAMONO */
        wind.width = 13;
    }

    offbreak( );        /* Turn off Ctrl-C checking */
}

/** Set CW directory. */
void set_directory( void ) {
    char drive[MAXDRIVE];
    char dir[MAXDIR];
    char name[MAXFILE];
    char ext[MAXEXT];

    /* build cw_dir like this -> c:\edit\cuwriter */
    fnsplit( progname, drive, dir, name, ext );
    sprintf( cw_dir, "%s%s", drive, dir );
    cw_dir[strlen( cw_dir ) - 1] = '\0'; /* clear \ */
}

int readoption( search_file_mode p_mode ) {
    FILE *fp;
    char fname[MAXPATH];
    int field;
    unsigned int temp;
    char opname[15];
    each_option_setup *op;


    sprintf( fname, "%s\\TW.CFG", cw_dir );
    if ( p_mode == CUR_DIR || p_mode == AUTO_FIND ) {
        fp = fopen( "TW.CFG", "rt" );
    } else {
        fp = fopen( fname, "rt" );
    }

    if ( fp == NULL && p_mode == AUTO_FIND ) {
        /* fopen file not success */
        /* continue searching in cw_dir */
        if ( ( fp = fopen( fname, "rt" ) ) == NULL ) {
            return 0; /* if not found in both dir return 0 for autofind */
        }
    }
    if ( fp == NULL ) {
        showerrno( );
        return -1; /* if search in CUR_DIR or CW_DIR and not found return -1 */
    }
    /* If we reach here we successfully open cfg file */
    for ( op = option_setup; op < option_setup + NELEM_OPTION; op++ ) {
        field = fscanf( fp, "%s %u", opname, &temp );
        if ( field == 2 ) { /* succesfully scan */
            if ( *op->p_option_value == -1 ) { /* not set from command line */
                *op->p_option_value = temp; /* so set it */
            }
        } else { /* error */
            break;
        }
    }
    fclose( fp );

    return 1;
}

void saveoption( search_file_mode p_mode ) {
    FILE *fp;
    char config_file[MAXPATH];
    each_option_setup *op;

    if ( p_mode == CUR_DIR || p_mode == AUTO_FIND ) {
        fp = fopen( "TW.CFG", "wt" );
    } else {
        sprintf( config_file, "%s\\TW.CFG", cw_dir );
        fp = fopen( config_file, "wt" );
    }
    if ( fp == NULL ) {
        return;
    }
    for ( op = option_setup; op < option_setup + NELEM_OPTION; op++ ) {
        fprintf( fp, "%s %u\n", op->option_name, *op->p_option_value );
    }
    fprintf( fp, "\n" );
    fclose( fp );
}

/** Display options on screen. */
void dispoption( size_t i ) {
    dispstrhgc( option_setup[i].label,
        65 - thaistrlen( option_setup[i].label ), i + 6, NORMALATTR );
    dispprintf( 65, i + 6, NORMALATTR, " :%d", *option_setup[i].p_option_value );
}

void setoption( void ) {
    size_t i;
    int c;
    char st[5];

    pagecomplete = NO;
    if ( stdcode == 0 ) { stdcode = 2; }
    if ( pagebreak == 0 ) { pagebreak = 2; }
    if ( wordwrap == 0 ) { wordwrap = 2; }
    if ( create_bak == 0 ) { create_bak = 2; }
    if ( cu_song == 0 ) { cu_song = 2; }
    framebox( 14, 5, 14 + 60, 5 + 1 + NELEM_OPTION, NORMALATTR );
    for ( i = 0; i < NELEM_OPTION; i++ ) {
        dispoption( i );
    }
    i = 0;
    for ( ;; ) {
        sprintf( st, "%d", *option_setup[i].p_option_value );
        c = getstring( st, 65 + 2, 6 + i, option_setup[i].maxlen,
            NORMALATTR, option_setup[i].stype );
        *option_setup[i].p_option_value = atoi( st );

        switch ( c ) {
        case UPKEY:
            dispoption( i );
            if ( i == 0 ) {
                i = NELEM_OPTION - 1;
            } else {
                i--;
            }
            break;
        case DNKEY:
            dispoption( i );
            if ( i == NELEM_OPTION - 1 ) {
                i = 0;
            } else {
                i++;
            }
            break;
        case YES:
            dispoption( i );
            if ( i < NELEM_OPTION - 1 ) {
                i++;
                break;
            }
        case ESCKEY:
            if ( stdcode == 2 ) { stdcode = 0; }
            if ( pagebreak == 2 ) { pagebreak = 0; }
            if ( wordwrap == 2 ) { wordwrap = 0; }
            if ( create_bak == 2 ) { create_bak = 0; }
            if ( cu_song == 2 ) { cu_song = 0; }
            return;
        }
    }
}

/** Set options to default setting. */
void set_option_to_default( void ) {
    each_option_setup *op;

    for ( op = option_setup; op < option_setup + NELEM_OPTION; op++ ) {
        /* not set from command line, or from config file */
        if ( *op->p_option_value == -1 ) {
            /* so set it */
            *op->p_option_value = op->p_option_default;
        }
    }
}

void initvalue( unsigned int *xCursorPos, unsigned int *yCursorPos ) {
    lineno = 1;
    *xCursorPos = 0;
    *yCursorPos = 0;
    firstcol = 0;
    blkbegin.lineno = 1;
    blkend.lineno = 1;
    blkbegin.column = 0;
    blkend.column = 0;
    dispblock = YES;
}

void initscrn( void ) {
    unsigned int countcol;

    setgraph( );              /* set to graphic mode */
    clsall( );

    _rectangle( 0, 0,
        ( ( scrmode == HERCMONO ) && ( herc_align == 0 ) ) ? 719 : 639,
        ( ( scrmode == VGA ) || ( scrmode == MCGA ) ) ? 479 :
        ( scrmode == ATT400 ) ? 399 :
        ( scrmode == CGA ) ? 199 :
        347 );

    prakeaw( );
    dispstrhgc( "����ŧ�ó�����Է�����", 6, 0, BOLDATTR );
    dispstrhgc( "� ESC<->MENU", ( ( scrmode == HERCMONO ) && ( herc_align == 0 ) ) ? 76 : 66, 1, BOLDATTR );

    for ( countcol = 1; countcol <= 10; countcol++ ) {
        headmenu( countcol, NORMALATTR );
    }
}

void print_file( void ) {
    static char cup[] = "TWPRINT.EXE";
    char ncup[40];

    savepic( );
    if ( changeflag ) {
        framebox( 4, 3, 4 + 2 + 37 + thaistrlen( filename ) + 2, 10, NORMALATTR );
        dispprintf( 4 + ( 2 + 37 + thaistrlen( filename ) + 2 - 13 ) / 2, 4, BOLDATTR,
            "**�ô�ѧࡵ�**" );
        dispprintf( 4 + 2, 5, NORMALATTR,
            "TWPRINT �о��������Ũҡ��� 㹴�ʡ���ҹ��" );
        dispprintf( 4 + 2, 6, NORMALATTR,
            "�����  %.30s  㹴�ʡ����ç�Ѻ�������˹��¤�����", filename );
        dispprintf( 4 + 2, 7, NORMALATTR,
            "�ѧ��鹼š�þ��������ç�Ѻ�������˹��¤�����" );
        dispprintf( 4 + ( 2 + 37 + thaistrlen( filename ) + 2 - 17 ) / 2, 9, NORMALATTR,
            "������� � ���ͷӧҹ���" );
        ebioskey( 0 );
    }
    settext( );
    /* Find CUPRINT by PATH */
    if ( spawnlp( P_WAIT, cup, cup, cup_option, filename, NULL ) == -1 ) {
        strcpy( ncup, cw_dir );                         /* Not found */
        strcat( ncup, "\\" );                           /* Search at CW dir */
        strcat( ncup, cup );
        if ( spawnl( P_WAIT, ncup, ncup, cup_option, filename, NULL ) == -1 ) {
            printf( "\n\nCannot find file : TWPRINT.EXE\nPress any key\n\007" );
            ebioskey( 0 );
        }
    }
    initscrn( );
    retpic( );
    showpageall( );
}

void edit_font( void ) {
    static char cuf[] = "TWFONT.EXE";

    if ( spawnlp( P_WAIT, cuf, cuf, cup_option, NULL ) == -1 ) {
        showerrno( );
    }
    initscrn( );
    showpageall( );
}

/** Turn off Ctrl-C checking */
void offbreak( ) {
    union REGS inreg, outreg;

    inreg.x.ax = 0x3301;
    inreg.h.dl = 0;
    intdos( &inreg, &outreg );
}
