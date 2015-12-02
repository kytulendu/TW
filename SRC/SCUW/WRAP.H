#ifndef SCUW_WRAP_H_INCLUDED
#define SCUW_WRAP_H_INCLUDED

/** Insert blank code (bit 8 = 1) to justify text to right margin. Text
*   must be in workline,not linked list. */
void justify_right( void );

/** Reform paragraph from line specified to end of paragraph. */
void reform( void );

void manualwrap( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

void autowrap( unsigned int *p_xCursorPos, unsigned int *p_yCursorPos );

/** leave the leading blank alone, just compress the rest
*   and trim the trailing blank. */
void compress_blank( unsigned char *s );

#endif /* SCUW_WRAP_H_INCLUDED */
