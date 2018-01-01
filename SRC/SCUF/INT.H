#ifndef SCUF_INT_H_INCLUDED
#define SCUF_INT_H_INCLUDED

/**  */
void start_clock( int func );

/**  */
int get_active_clock( );

/**  */
void stop_clock( );

/**  */
void init_clock( );

/**  */
void flush_clock( void );

#endif /* SCUF_INT_H_INCLUDED */