/*
* ============================================================================
* Module        : 24PINS.H
* Description   : define characteristic used in 24pins.C
* Written by    : Mr. Thotsapol Aphikulvanich ID.2818966
* Date written  : 23 April 1989
* Last modified : 3  June  1989
* Modified By   : CUCC
* Last modified : 22 June 1990
*                 - Extend Bar Table.
* ============================================================================
*/

#ifndef SCUP_24PINS_H_INCLUDED
#define SCUP_24PINS_H_INCLUDED

/* ----- define error and success value ------- */
#define CP_ERROR    -1
#define CP_SUCCESS  0
#define CP_WRAPCODE 0xA0
#define CP_BLANK    0x20
#define CP_ENGLISH  0x80

/* ----- define sara and wannayok ---------- */
#define CP_SARAAR   0xD2
#define CP_SARAUM   0xD3
#define CP_HUNARKAD 0xD1
#define CP_SARAI    0xD4
#define CP_SARAE    0xD5
#define CP_SARAUD   0xD6
#define CP_SARAEE   0xD7

#define CP_MIAKE    0xE8
#define CP_MITO     0xE9
#define CP_MITEE    0xEA
#define CP_MIJUDTAWA    0xEB
#define CP_KARUN    0xEC

/* ---- define printing mode of output ------- */
#define CP_TEXT     0
#define CP_DOWNLOAD 1
#define CP_GRAPHICS 2

/* ---- define quality of output printing ---- */
#define CP_DRAFT    0
#define CP_LQ       1

/* ---- define print size ----- */
#define CP_10CPI    0
#define CP_12CPI    1
#define CP_15CPI    3

/* ---- define head type ------ */
#define CP_24PINS   0
#define CP_9PINS    1
#define CP_HPLASER  2
#define CP_OLYMPIA  3

/* ---- define size of 24 pins printer font ---- */
#define CP_LQ_FONTSIZE      54
#define CP_LQSCR_FONTSIZE   36
#define CP_LQ_TABSIZE       12096       /* SPACE -> 0xFF */
#define CP_LQSCR_TABSIZE    8064        /* SPACE -> 0xFF */
#define CP_LQCOMB_TABSIZE   1620        /* Combine code table */
#define CP_LQSCRCOMB_TABSIZE    1080

/* ---- define printing buffer size ----------- */
#define CP_MAX_TEXTBUF      272
#define CP_LQ_MAXPRBUF      272 * CP_LQ_FONTSIZE

/* ---- define printing control code ---------- */
#define CP_NORMALATTR       0x00
#define CP_ITALICATTR       0x01
#define CP_SUBATTR          0x02
#define CP_SUPERATTR        0x04

#define CP_UNDERLINEATTR    0x08
#define CP_DOUBLELINEATTR   0x10

#define CP_ENLARGEATTR      0x20
#define CP_BOLDATTR         0x40

#define CP_ITALIC           23  /* ^W */
#define CP_SUBSCRIPT        22  /* ^V */
#define CP_SUPERSCRIPT      20  /* ^T */
#define CP_ENLARGE          05  /* ^E */
#define CP_BOLD             02  /* ^B */
#define CP_UNDERLINE        19  /* ^S */
#define CP_DOUBLELINE       18  /* ^R */

#define CP_UNDERLINE_MSK    0x18
#define CP_DOUBLELINE_MSK   0x33

#define MSK_CHARTYPE(ch)    ( ch & 0x07 )
#define MSK_LINE(ch)        ( ch & 0x18 )
#define MSK_CHARATTR(ch)    ( ch & 0xE0 )

/* ---- used as buffer before printing to print buffer ---- */
struct cp_textbuf {
	unsigned char *uppest;  /* buffer for wannayok    */
	unsigned char *upper;   /* buffer for upper line  */
	unsigned char *middle;  /* buffer for middle line */
	unsigned char *lower;   /* buffer for lower line  */
};

/* ---- graphics printing buffer ------ */
#define CP_LQCOL    18
#define CP_LQROW    3
#define CP_LQSCRROW 2

typedef struct FONT {
	unsigned char font[CP_LQCOL][CP_LQROW];
} FONT;

typedef struct FONTSCR {
	unsigned char font[CP_LQCOL][CP_LQSCRROW];
} FONTSCR;

struct cp_grlqbuf {
	FONT *upper;
	FONT *middle;
	FONT *lower;
	FONT *extbar;
};

/* ---- define buffer used in 24pins.c module ----- */
extern struct cp_textbuf cp_buf;
extern struct cp_grlqbuf cp_lqbuf;

/* ----- define character font table  -------- */
extern FONT *cp_lqnorm;
extern FONT *cp_lqitalic;
extern FONT *cp_lqnorm_comb;
extern FONT *cp_lqitalic_comb;
extern FONTSCR *cp_lqscr;
extern FONTSCR *cp_lqscr_italic;
extern FONTSCR *cp_lqscr_comb;
extern FONTSCR *cp_lqscr_italic_comb;

/* ------ define control byte for character attribute ----- */
extern unsigned char cp_control;

/* ----- define prototype of function in 24pins.c module ----- */

/** Function      : execerror
*   Description   : report error and terminate program
*   Parameters    : s - general error
*                   t - extended error
*   Return values : NONE
*   Remark        : This function causes the program to stop */
void execerror( char *s, char *t );

/** Function      : cp_clearbuf
*   Description   : clear 4 lines buffer
*   Parameters    : NONE
*   Return values : NONE
*   Remark        : used global variable cp_buf */
void cp_clearbuf( void );

/** Function      : cp_split4level
*   Description   : split thai message into 4 levels
*   Parameters    : linemsg - message to be printed
*   Return values : NONE
*   Remark        : global variable "cp_buf" is result */
void cp_split4level( unsigned char *linemsg );

/* ----- NORMAL and ITALIC CODE ----- */

/** Function      : cp_lq_font
*   Description   : search character in font table
*   Parameters    : fntable - pointer to the font table
*                 : ch      - character to be search
*   Return values : pointer to searching font */
FONT *cp_lq_font( FONT *fntable, unsigned char ch );

/** Function      : cp_lq_combinecode
*   Description   : searching combine sara and wannayok
*   Parameters    : fntable   - pointer to font table
*                   combtable - pointer to combine table
*                   sara      - sara ASCII code
*                   wannayok  - wannayok ASCII code
*   Return values : pointer to new combine character */
FONT *cp_lq_combinecode( FONT *fntable, FONT *combtable, unsigned char sara, unsigned char wannayok );

/* --- SUBCRIPT and SUPERSCRIPT --- */

/**  */
FONTSCR *cp_create_lqscrcombine( FONTSCR *fntable );

/** Function      : cp_lqscr_font
*   Description   : search character in font table
*   Parameters    : fntable - pointer to the font table
*                 : ch      - character to be search
*   Return values : pointer to searching font */
FONTSCR *cp_lqscr_font( FONTSCR *fntable, unsigned char ch );

/** Function      : cp_lqscr_combinecode
*   Description   : searching combine sara and wannayok
*   Parameters    : fntable   - pointer to font table
*                   combtable - pointer to combine table
*                   sara      - sara ASCII code
*                   wannayok  - wannayok ASCII code
*   Return values : pointer to new combine character */
FONTSCR *cp_lqscr_combinecode( FONTSCR *fntable, FONTSCR *combtable, unsigned char sara, unsigned char wannayok );

/* -- print data to buffer and manage all attribute -- */

/** Function      : cp_pr_lqbuf
*   Description   : printing data to buffer
*   Parameters    : buffer - pointer to printing buffer
*                   data   - data to printing
*                   index  - index of last printing position
*   Return values : CP_ERROR - when error occurs
*                   gindex   - last to printing position */
int cp_pr_lqbuf( struct cp_grlqbuf lqbuf, struct cp_grlqbuf grpchar, int gindex );

/** Function      : cp_printlq(void)
*   Description   : printing 4 level data to printing buffer
*   Parameters    : NONE
*   Return values : CP_ERROR - when error occurs or buffer full
*                   gindex   - number of printing character
*   Remark        : use GLOBAL variable "cp_lqbuf" */
int cp_printlq( void );

/* --- set control flag --- */

/** Function      : cp_set_reset
*   Description   : set or reset mask bits of attrib control
*   Parameters    : ch     - input character
*                   cntptr - pointer to control
*   Return values : NONE */
int cp_set_reset( unsigned char ch, unsigned char *cntptr );

#endif /* SCUP_24PINS_H_INCLUDED */
