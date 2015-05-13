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

#ifndef DEFINE_VAR
EXTERN int scrmode;
EXTERN int shrink_factor;		/* Columns decreased. ( 90 column : 10, 80 column : 0 ) */
EXTERN int center_factor;		/* Shifting left factor. ( 90 column : 5, 80 column : 0) */
#else
EXTERN int scrmode = DETECT;	/* not initialize (text) mode */
EXTERN int shrink_factor = 0;	/* Columns decreased. ( 90 column : 10, 80 column : 0 ) */
EXTERN int center_factor = 0;	/* Shifting left factor. ( 90 column : 5, 80 column : 0) */
#endif

EXTERN unsigned char *screen_buffptr;

/* ===================================================================== */

typedef void( Prchar_func )( char p_char, int p_attr, int x, int y );
typedef Prchar_func *Prchar_ptr;

EXTERN Prchar_ptr  prchar_ptr;
EXTERN Prchar_func hprchar, eprchar, aprchar;

/* --------------------------------------------------------------------- */

typedef void ( Prblank_func )( int x, int y );
typedef Prblank_func *Prblank_ptr;

EXTERN Prblank_func hprblank, eprblank, aprblank;
EXTERN Prblank_ptr  prblank_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Setcurpos_func )( int x, int y, int p_thaimode );
typedef Setcurpos_func *Setcurpos_ptr;

EXTERN Setcurpos_func hsetcurpos, esetcurpos, asetcurpos;
EXTERN Setcurpos_ptr  setcurpos_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Plot_func )( int x, int y );
typedef Plot_func *Plot_ptr;

EXTERN Plot_func hplot, eplot, aplot;
EXTERN Plot_ptr  plot_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Voidvoid_func )( void );
typedef Voidvoid_func *Voidvoid_ptr;

EXTERN Voidvoid_func hsetgraph, esetgraph, asetgraph,
hsettext, esettext, asettext;
EXTERN Voidvoid_func hsavepic, esavepic, asavepic,
hretpic, eretpic, aretpic;
EXTERN Voidvoid_func hclsall, eclsall, aclsall,
hprakeaw, eprakeaw, aprakeaw;

EXTERN Voidvoid_ptr  setgraph_ptr, settext_ptr, savepic_ptr, retpic_ptr;
EXTERN Voidvoid_ptr  clsall_ptr, prakeaw_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Clsgraph_func )( int x1, int x2,
	int y1, int y2 );
typedef Clsgraph_func *Clsgraph_ptr;

EXTERN Clsgraph_func hclsgraph, eclsgraph, aclsgraph;
EXTERN Clsgraph_ptr  clsgraph_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Clrline_func )( int x1, int y1, int x2 );
typedef Clrline_func *Clrline_ptr;

EXTERN Clrline_func hclrline, eclrline, aclrline;
EXTERN Clrline_ptr  clrline_ptr;

/* --------------------------------------------------------------------- */

typedef void ( PGwind_func )( int x1, int x2,
	int linecount, int bytecount,
	char *buffer );
typedef PGwind_func *PGwind_ptr;

EXTERN PGwind_func hputwind, eputwind, aputwind, hgetwind, egetwind, agetwind;
EXTERN PGwind_ptr  putwind_ptr, getwind_ptr;

#undef EXTERN /* restore it */

/* ===================================================================== */

/** put a character with attribute in to x,y position */
void prchar( char p_char, int p_attr, int x, int y );

/** put a blank character in to x,y position */
void prblank( int x, int y );

/** set cursor position */
void setcurpos( int x, int y, int p_thaimode );

/** put a pixel in to x,y position */
void plot( int x, int y );

/** set graphic mode */
void setgraph( void );

/** set text mode */
void settext( void );

/** save screen */
void savepic( void );

/** restore saved screen */
void retpic( void );

/** clear screen */
void clsall( void );

/** clear screen in window */
void clsgraph( int x1, int y1, int x2, int y2 );

/** clear line */
void clrline( int x1, int y1, int x2 );

/** display Prakeaw ( Chula University logo ) at top-left of screen ( fixed position ) */
void prakeaw( void );

#endif /* COMMON_CWGRPHC_H_INCLUDED */
