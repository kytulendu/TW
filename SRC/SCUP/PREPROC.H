#ifndef SCUP_PREPROC_H_INCLUDED
#define SCUP_PREPROC_H_INCLUDED

/** Initialize memory for text buffer.
*   use GLOBAL variable "cp_buf". */
void cp_init_textbuf( void );

/** Initialize memory for text buffer.
*   use GLOBAL variable "cp_lqbuf". */
void cp_init_grpbuf( void );

/* ----- NORMAL and ITALIC CODE ----- */

/** Combine upper sara and wannayok.
*  \param[in]  p_combcode       pointer to the result code.
*  \param[in]  p_sara           pointer to upper sara.
*  \param[in]  p_wannayok       pointer to wannayok. */
void cp_combine_fontlq( FONT *p_combcode, FONT *p_sara, FONT *p_wannayok );

/* ----- NORMAL and ITALIC CODE ----- */

/** Create combine code printer table for easily use in print_lq function.
*  \param[in]  p_fntable        pointer to font table.
*  \return FONT                 pointer to combine code table. */
FONT *cp_create_lqcombine( FONT *p_fntable );

/* --- SUBCRIPT and SUPERSCRIPT --- */

/** Load subscript and italic subscript font.
*  \param[in]  p_filename       font filename.
*  \return FONTSCR              pointer to font table. */
FONTSCR *cp_loadfont_lqscr( char *p_filename );

/** Combine upper sara and wannayok.
*  \param[in]  p_combcode       pointer to the result code.
*  \param[in]  p_sara           pointer to upper sara.
*  \param[in]  p_wannayok       pointer to wannayok. */
void cp_combine_fontlqscr( FONTSCR *p_combcode, FONTSCR *p_sara, FONTSCR *p_wannayok );

/** Create combine code printer table for easily use in print_lq function.
*  \param[in]  p_fntable        font filename.
*  \return FONTSCR              pointer to combine code table. */
FONTSCR *cp_create_lqscrcombine( FONTSCR *p_fntable );

#endif /* SCUP_PREPROC_H_INCLUDED */
