/*
* ============================================================================
* Graphics module header file for CW 1.20
*
* Suttipong Kanakakorn
* Date    : Sun  07-30-1989  16:01:13
* ============================================================================
*/

#ifndef COMMON_CWGRPHC_H_INCLUDED
#define COMMON_CWGRPHC_H_INCLUDED

#ifdef  DEFINE_VAR
#define EXTERN
#else
#define EXTERN extern
#endif

/* Just a thing for test compile with Visual Studio :P */
#ifdef _WIN32
#ifndef far
#define far
#endif
#endif

#ifndef DEFINE_VAR
extern int scrmode;				/* Graphic mode. */
extern int shrink_factor;		/* Columns decreased. 90 column : 10, 80 column : 0 ) */
extern int center_factor;		/* Shifting left factor. 90 column : 5, 80 column : 0) */
#else
int scrmode = DETECT;	/* Not initialize (text) mode */
int shrink_factor = 0;	/* Columns decreased. 90 column : 10, 80 column : 0 ) */
int center_factor = 0;	/* Shifting left factor. 90 column : 5, 80 column : 0) */
#endif

EXTERN unsigned char dfont[20 * 256];
EXTERN unsigned char ditalicfont[20 * 256];
EXTERN unsigned char *screen_buffptr;
EXTERN unsigned char far *vram;
EXTERN int original_videomode;

extern int herc_align; /* from COMMON\HERC.ASM */

/* ===================================================================== */

typedef void( Prchar_func )( unsigned char p_char, int p_attr, int p_x, int p_y );
typedef Prchar_func *Prchar_ptr;

EXTERN Prchar_ptr  prchar_ptr;
EXTERN Prchar_func herc_prchar, ega_prchar, att_prchar;

/* --------------------------------------------------------------------- */

typedef void ( Prblank_func )( int p_x, int p_y );
typedef Prblank_func *Prblank_ptr;

EXTERN Prblank_func herc_prblank, ega_blank, att_prblank;
EXTERN Prblank_ptr  prblank_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Setcurpos_func )( int p_x, int p_y, int p_thaimode );
typedef Setcurpos_func *Setcurpos_ptr;

EXTERN Setcurpos_func herc_setcurpos, ega_setcurpos, att_setcurpos;
EXTERN Setcurpos_ptr  setcurpos_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Putpixel_func )( int p_x, int p_y );
typedef Putpixel_func *Putpixel_ptr;

EXTERN Putpixel_func herc_putpixel, ega_putpixel, att_putpixel;
EXTERN Putpixel_ptr putpixel_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Voidvoid_func )( void );
typedef Voidvoid_func *Voidvoid_ptr;

EXTERN Voidvoid_func herc_setgraph, ega_setgraph, att_setgraph,
herc_settext;
EXTERN Voidvoid_func herc_savepic, ega_savepic, att_savepic,
herc_retpic, ega_retpic, att_retpic;
EXTERN Voidvoid_func herc_clsall, ega_clsall, att_clsall,
herc_prakeaw, ega_prakeaw, att_prakeaw;

EXTERN Voidvoid_ptr setgraph_ptr, savepic_ptr, retpic_ptr;
EXTERN Voidvoid_ptr clsall_ptr, prakeaw_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Clsgraph_func )( int p_x1, int p_x2, int p_y1, int p_y2 );
typedef Clsgraph_func *Clsgraph_ptr;

EXTERN Clsgraph_func herc_clsgraph, ega_clsgraph, att_clsgraph;
EXTERN Clsgraph_ptr  clsgraph_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Clrline_func )( int p_x1, int p_y1, int p_x2 );
typedef Clrline_func *Clrline_ptr;

EXTERN Clrline_func herc_clrline, ega_clrline, att_clrline;
EXTERN Clrline_ptr  clrline_ptr;

/* --------------------------------------------------------------------- */

typedef void ( PGwind_func )( int p_x1, int p_x2, int p_linecount, int p_bytecount,
	unsigned char *p_buffer );
typedef PGwind_func *PGwind_ptr;

EXTERN PGwind_func herc_putwind, ega_putwind, att_putwind, herc_getwind, ega_getwind, att_getwind;
EXTERN PGwind_ptr  putwind_ptr, getwind_ptr;

#undef EXTERN /* restore it */

/* ===================================================================== */

/** Put a character with attribute at given position.
*  \param[in]  p_char			Character.
*  \param[in]  p_attr			Attribute.
*                                   bit 0 -> single underline
*                                   bit 1 -> reverse
*                                   bit 2 -> bold
*                                   bit 3 -> superscript
*                                   bit 4 -> subscript
*                                   bit 5 -> italic
*                                   bit 6 -> enlarge
*                                   bit 7 -> double underline
*  \param[in]  p_x				Horizontal position.
*  \param[in]  p_y				Vertical position. */
void prchar( unsigned char p_char, int p_attr, int p_x, int p_y );

/** Put a blank character at given position.
*  \param[in]  p_x				Horizontal position.
*  \param[in]  p_y				Vertical position. */
void prblank( int p_x, int p_y );

/** XOR cursor at specified cursor position.
*  \param[in]  p_x				Horizontal position.
*  \param[in]  p_y				Vertical position.
*  \param[in]  p_thaimode		Thai/English mode. */
void setcurpos( int p_x, int p_y, int p_thaimode );

/** Put a pixel at given position.
*  \param[in]  p_x				Horizontal position.
*  \param[in]  p_y				Vertical position. */
void _putpixel( int p_x, int p_y );

/** Get current video mode through int 10, function 0Fh.
*  \return int					Current video mode. */
int getcurrentmode( void );

/** Set graphic mode. */
void setgraph( void );

/** Set text mode. */
void settext( void );

/** Save picture from screen memory page 1 to page 0. */
void savepic( void );

/** Return picture from screen memory page 0 to page 1. */
void retpic( void );

/** Clear screen memory page 1 to blank. */
void clsall( void );

/** Clear graphic screen for window specified.
*  \param[in]  p_xStart			Vertical position of start point.
*  \param[in]  p_yStart			Horizontal position of start point.
*  \param[in]  p_xEnd			Vertical position of end point.
*  \param[in]  p_yEnd			Horizontal position of end point. */
void clsgraph( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd );

/** Clear line p_y1 from p_x1 to p_x2. */
void clrline( int p_x1, int p_y1, int p_x2 );

/** Display Prakeaw ( Chula University logo ) at top-left of screen. */
void prakeaw( void );

#endif /* COMMON_CWGRPHC_H_INCLUDED */
