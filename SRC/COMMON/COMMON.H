#ifndef COMMON_COMMON_H_INCLUDED
#define COMMON_COMMON_H_INCLUDED

/** Change TIS-620 code character to KU code character.
*  \param[in]  p_stdcode		TIS-620 code character.
*  \return char		KU code character. */
char stdtoku( char p_stdcode );

/** Change KU code character to TIS-620 code character.
*  \param[in]  p_stdcode		KU code character.
*  \return char		TIS-620 code character. */
char kutostd( char p_kucode );

/** Change ascii value of key from english to Thai.
*   From ACOMMON.ASM
*  \param[in]  p_key		KU code character.
*  \return char				Kedmanee keyboard code. */
int thaikey( register int p_key );

/** From ACOMMON.ASM */
int asm_keypressed( void );

/** Determining at what level a given character is.
*  \param[in]  p_char		Character.
*  \return int				Level of character.
*	0 : Ordinary (middle) level
*	1 : Lower level (สระอุ, สระอู)
*	2 : Upper level (สระอิ, สระอี)
*	3 : Top level (วรรณยุกต์) */
int whatlevel( char p_char );

#endif /* COMMON_COMMON_H_INCLUDED */
