#ifndef COMMON_EKBD_H_INCLUDED
#define COMMON_EKBD_H_INCLUDED

/** Encapsulate bioskey for future expanded like macro keyboard .
*  \param[in]  p_cmd            Keyboard scancode.
*  \return int                  Bioskey. */
int ebioskey( int p_cmd );

/** Place scancode k to ebioskey keyboard buffer.
*  \param[in]  p_key            */
void placekey( int p_key );

/** Check whether key is pressed or not. */
int keypressed( void );

#endif /* COMMON_EKBD_H_INCLUDED */
