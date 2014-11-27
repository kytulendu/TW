#ifndef SCUP_PREPROC_H_INCLUDED
#define SCUP_PREPROC_H_INCLUDED

/** Function      : cp_init_textbuf
*   Description   : initialize memory for text buffer
*   Parameters    : NONE
*   Return values : NONE
*   Remark        : use GLOBAL variable "cp_buf" */
void cp_init_textbuf( void );

/** Function      : cp_init_grpbuf
*   Description   : initialize memory for text buffer
*   Parameters    : NONE
*   Return values : NONE
*   Remark        : use GLOBAL variable "cp_lqbuf" */
void cp_init_grpbuf( void );

/* ----- NORMAL and ITALIC CODE ----- */

/** Function      : cp_combine_fontlq
*   Description   : Combine upper sara and wannayok
*   Parameters    : combcode - pointer to the result code
*                   sara     - pointer to upper sara
*                   wannayok - pointer to wannayok
*   Return values : NONE */
void cp_combine_fontlq( FONT *combcode, FONT *sara, FONT *wannayok );

/* ----- NORMAL and ITALIC CODE ----- */

/** Function      : cp_create_lqcombine
*   Description   : create combine code printer table for
*                   easily use in print_lq function
*   Parameters    : NONE
*   Return values : pointer to combine code table */
FONT *cp_create_lqcombine( FONT *fntable );

/* --- SUBCRIPT and SUPERSCRIPT --- */

/** Function      : cp_loadfont_lqscr
*   Description   : load subscript and italic subscript font
*   Parameters    : fname  - font filename
*   Return values : fntptr - pointer to font table
*   Remark        : This function allocate the font table */
FONTSCR *cp_loadfont_lqscr( char *fname );

/** Function      : cp_combine_fontlqscr
*   Description   : Combine upper sara and wannayok
*   Parameters    : combcode - pointer to the result code
*                   sara     - pointer to upper sara
*                   wannayok - pointer to wannayok
*   Return values : NONE */
void cp_combine_fontlqscr( FONTSCR *combcode, FONTSCR *sara, FONTSCR *wannayok );

/** Function      : cp_create_lqscrcombine
*   Description   : create combine code printer table for
*                   easily use in print_lq function
*   Parameters    : NONE
*   Return values : pointer to combine code table */
FONTSCR *cp_create_lqscrcombine( FONTSCR *fntable );

#endif /* SCUP_PREPROC_H_INCLUDED */
