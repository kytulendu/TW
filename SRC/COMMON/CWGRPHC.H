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
#else
EXTERN int scrmode = DETECT; /* not initialize (text) mode */
#endif

EXTERN unsigned int graph_seg;
EXTERN unsigned char *screen_buffptr;

/* ===================================================================== */

typedef void( Prchar_func )( unsigned char p_char, unsigned int p_attr, unsigned int x, unsigned int y );
typedef Prchar_func *Prchar_ptr;

EXTERN Prchar_ptr  prchar_ptr;
EXTERN Prchar_func hprchar, eprchar, aprchar;

/* --------------------------------------------------------------------- */

typedef void ( Prblank_func )( unsigned int x, unsigned int y );
typedef Prblank_func *Prblank_ptr;

EXTERN Prblank_func hprblank, eprblank, aprblank;
EXTERN Prblank_ptr  prblank_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Setcurpos_func )( unsigned int x, unsigned int y, int p_thaimode );
typedef Setcurpos_func *Setcurpos_ptr;

EXTERN Setcurpos_func hsetcurpos, esetcurpos, asetcurpos;
EXTERN Setcurpos_ptr  setcurpos_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Plot_func )( unsigned int x, unsigned int y );
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

typedef void ( Clsgraph_func )( unsigned int x1, unsigned int x2,
	unsigned int y1, unsigned int y2 );
typedef Clsgraph_func *Clsgraph_ptr;

EXTERN Clsgraph_func hclsgraph, eclsgraph, aclsgraph;
EXTERN Clsgraph_ptr  clsgraph_ptr;

/* --------------------------------------------------------------------- */

typedef void ( Clrline_func )( unsigned int x1, unsigned int y1, unsigned int x2 );
typedef Clrline_func *Clrline_ptr;

EXTERN Clrline_func hclrline, eclrline, aclrline;
EXTERN Clrline_ptr  clrline_ptr;

/* --------------------------------------------------------------------- */

typedef void ( RWchardot_func )( unsigned int x, unsigned int y );
typedef RWchardot_func *RWchardot_ptr;

EXTERN RWchardot_func hrdchardot, erdchardot, ardchardot,
hwrchardot, ewrchardot, awrchardot;
EXTERN RWchardot_ptr  rdchardot_ptr, wrchardot_ptr;

/* --------------------------------------------------------------------- */

typedef void ( PGwind_func )( unsigned int x1, unsigned int x2,
	unsigned linecount, unsigned bytecount,
	char *buffer );
typedef PGwind_func *PGwind_ptr;

EXTERN PGwind_func hputwind, eputwind, aputwind, hgetwind, egetwind, agetwind;
EXTERN PGwind_ptr  putwind_ptr, getwind_ptr;

/* ===================================================================== */

/***/
void prchar( unsigned char p_char, unsigned int p_attr, unsigned int x, unsigned int y );

/***/
void prblank( unsigned int x, unsigned int y );

/***/
void setcurpos( unsigned int x, unsigned int y, int p_thaimode );

/***/
void plot( unsigned int x, unsigned int y );

/** set graphic mode */
void setgraph( void );

/** set text mode */
void settext( void );

/***/
void savepic( void );

/***/
void retpic( void );

/** clear screen*/
void clsall( void );

/***/
void clsgraph( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2 );

/***/
void clrline( unsigned int x1, unsigned int y1, unsigned int x2 );

/** display Prakeaw ( Chula University logo ) at top-left of screen ( fixed position ) */
void prakeaw( void );

/***/
void rdchardot( unsigned int x, unsigned int y );

/***/
void wrchardot( unsigned int x, unsigned int y );

#endif /* COMMON_CWGRPHC_H_INCLUDED */
