#ifndef COMMON_COMMON_H_INCLUDED
#define COMMON_COMMON_H_INCLUDED

/** Change TIS-620 code character to KU code character.
*  \param[in]  p_stdcode		TIS-620 code character.
*  \return unsigned char		KU code character. */
unsigned char stdtoku( unsigned char p_stdcode );

/** Change KU code character to TIS-620 code character.
*  \param[in]  p_stdcode		KU code character.
*  \return unsigned char		TIS-620 code character. */
unsigned char kutostd( unsigned char p_kucode );

/** Change ascii value of key from english to Thai.
*   From ACOMMON.ASM
*  \param[in]  p_key			BIOS keyboard code.
*  \return int					Kedmanee keyboard code. */
int thaikey( register int p_key );

/** Check if keyboard is pressed.
*   From ACOMMON.ASM
*  \return int					0 if no key pressed.
*	keyboard scan code of the key pressed if key pressed */
int asm_keypressed( void );

/** Determining at what level a given character is.
*  \param[in]  p_char			Character.
*  \return int					Level of character.
*	0 : Ordinary (middle) level
*	1 : Lower level (สระอุ, สระอู)
*	2 : Upper level (สระอิ, สระอี)
*	3 : Top level (วรรณยุกต์) */
int whatlevel( unsigned char p_char );

#endif /* COMMON_COMMON_H_INCLUDED */
