#ifndef SCUP_PIC_H_INCLUDED
#define SCUP_PIC_H_INCLUDED

/**  */
int is_command( char *p_string );

/**  */
void get_argument( char *arg[40], char *p_string, int *no_arg );

/**  */
int getpr( void );

/**  */
void get_graphic_data( void );

/**  */
void process_command_0( int p_printerData );

/**  */
void process_command_1( int p_printerData );

/**  */
void process_command( int p_printerData );

/**  */
void analyze_picture_file( char *p_string );

/**  */
void initialize_read( char *p_string );

/**  */
void read_picture_file( void );

#endif /* SCUP_PIC_H_INCLUDED */