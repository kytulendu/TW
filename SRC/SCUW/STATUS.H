#ifndef SCUW_STATUS_H_INCLUDED
#define SCUW_STATUS_H_INCLUDED

/** Display release margin status. */
void relmarstatus( void );

/** Convert Arabic number to Thai number.
*  \param[in]  p_string			Number string to convert. */
void arabictothai( char *p_string );

/** Display page number. */
void writepage( void );

/** Display line number (if display pagebreak). */
void writeline( void );

/** Display line number (if not display pagebreak). */
void writelineno( void );

/** Display pagebreak line. */
void writepageline( void );

/** Display column number.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void writecolno( unsigned int p_xCursorPos );

/** Display insert mode status. */
void writeinsmode( void );

/** Display keyboard language status. */
void writelanguage( void );

/** Display current text attribute status. */
void writeattr( void );

/** Display file name. */
void writefilename( void );

/** Display drive. */
void writedriveno( void );

/** Display status.
*  \param[in]  p_xCursorPos		Column cursor position in editing window. */
void writestatus( unsigned int p_xCursorPos );

#endif /* SCUW_STATUS_H_INCLUDED */
