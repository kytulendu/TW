#ifndef SCUP_PIC_H_INCLUDED
#define SCUP_PIC_H_INCLUDED

/**  */
int is_command( char *st );

/**  */
void get_argument( char arg[][40], char *st, int *no_arg );

/**  */
int getpr( void );

/**  */
void get_graphic_data( void );

/**  */
void process_command_0( int printer_data );

/**  */
void process_command_1( int printer_data );

/**  */
void process_command( int printer_data );

/**  */
void analyze_picture_file( char *st );

/**  */
void initialize_read( char *st );

/**  */
void read_picture_file( void );

#endif /* SCUP_PIC_H_INCLUDED */