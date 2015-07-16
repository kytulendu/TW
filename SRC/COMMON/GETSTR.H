#ifndef SCUW_GETSTR_H_INCLUDED
#define SCUW_GETSTR_H_INCLUDED

/** Display string input box.
*   \param[in]  p_textstr		String want to get.
*   \param[in]  p_xPos			Vertical position ( 0 - 89 ).
*   \param[in]  p_yPos			Horisontal position ( 0 - 16 ).
*   \param[in]  p_maxlen		Maximum length of string.
*   \param[in]  p_attr			Attribute of string for displaying.
*   \param[in]  p_mode			THAIENG, ENGLISH, ENGUPCASE, NUMBER, ONEORTWO.
*   \return int					*/
int getstring( unsigned char *p_textstr, int p_xPos, int p_yPos, size_t p_maxlen, font_attr p_attr, strtype p_mode );

/** Display filename input box.
*   \param[in]  p_textstr		Filename.
*   \param[in]  p_xPos			Vertical position ( 0 - 89 ).
*   \param[in]  p_yPos			Horisontal position ( 0 - 16 ).
*   \param[in]  p_maxlen		Maximum length of string.
*   \param[in]  p_attr			Attribute of string for displaying.
*   \return int					*/
int getname( char *p_textstr, int p_xPos, int p_yPos, size_t p_maxlen, font_attr p_attr );

#endif /* SCUW_GETSTR_H_INCLUDED */
