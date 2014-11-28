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
*  \param[in]  p_key		KU code character.
*  \return unsigned char	Kedmanee keyboard code. */
/*unsigned char thaikey( unsigned char p_key );*/

/** Determining at what level a given character is.
*  \param[in]  p_key		KU code character.
*  \return int				Level of character.
*	0 : Ordinary (middle) level
*	1 : Lower level (�����, �����)
*	2 : Upper level (�����, �����)
*	3 : Top level (��ó�ء��) */
int whatlevel( unsigned char p_char );

#endif /* COMMON_COMMON_H_INCLUDED */