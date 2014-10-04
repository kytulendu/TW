#ifndef COMMON_EKBD_H_INCLUDED
#define COMMON_EKBD_H_INCLUDED

/** encapsulate bioskey for future expanded like macro keyboard .
*  \param[in]  p_cmd		keyboard scancode.
*  \return int				bioskey. */
int ebioskey( int p_cmd );

/** place scancode k to ebioskey keyboard buffer.
*  \param[in]  p_key		keyboard scancode. */
void placekey( int p_key );

/** check whether key is pressed or not. */
boolean keypressed( void );

#endif /* COMMON_EKBD_H_INCLUDED */
