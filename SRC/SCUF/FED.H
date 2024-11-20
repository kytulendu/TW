#ifndef SCUF_FED_H_INCLUDED
#define SCUF_FED_H_INCLUDED

#define BYTE_X(X)   ( _ceil( ( X ), 8 ) )
#define STOP    0
#define EDIT_FONT   1
#define SELECT_FONT 2

#define MAX_X   64          /* maximum of font size */
#define MAX_Y   64

#define SCR_FONT    1
#define ITALIC_SCR_FONT 2
#define PRN_FONT    3
#define ITALIC_PRN_FONT 4
#define LQ_FONT     5
#define ITALIC_LQ_FONT  6
#define SUP_SUB_LQ_FONT 7
#define ITALIC_SUP_SUB_LQ_FONT  8
#define FED_FONT    9

extern int first_file;
extern unsigned pos_x, pos_y, BYTE, sel_x, sel_y;
extern char WIDTH_X, WIDTH_Y, X, Y;
extern char *all_font;
extern char *char_block_image;
extern int align;
extern int loaded;
extern int new_load;
extern char fname[];
extern unsigned int is_herc;
extern char cufontpath[];
extern char cuwordpath[];
extern char cuprintpath[];

#define SIGN "FONT EDITOR Version 1.0"
#define SIGN_LENGTH strlen(SIGN)

void setup_screen( void );
void init_graph_and_cursor( void );
void fed( void );
int _ceil( int x, int y );
void clearworkarea( void );
void invert( void );
void mirror( void );
void backup_char( void );
void undo( void );
void del_col( char col );
void insert_col( char col );
void del_row( char row );
void insert_row( char row );
void pan_left( void );
void pan_right( void );
void pan_up( void );
void pan_down( void );
void draw_char( void );
void update_char( char ch );
void take_char( char ch );
void blink( unsigned int x, unsigned int y );
void put_dot( unsigned int x, unsigned int y );
void xor_dot( unsigned int x, unsigned int y );
void square( unsigned int x, unsigned int y );
void draw_grid( unsigned int x, unsigned int y );
void error_write( void );
void error_read( void );
int char_per_row( void );
int char_per_col( void );
void print_page( int pageno, int char_per_page );
void draw_frame( int x1, int y1, int x2, int y2 );
void make_char_block_image( void );
void calculate_page_frame( int *x1, int *y1, int *x2, int *y2 );
void print_table( int page );
int which_page( int ch );
void insert_char( int ch );
void delete_char( int ch );
void or_char( int ch1, int ch2 );
int select_font( int *page, char *status );
void help( void );
void help_select( void );
void edit( int ch );

/** draw grid
*   malloc all_font
*   set BYTE = sizeof X in bytes*/
void setup_memo( void );
void free_all( void );
void terminate( void );
void file_menu( void );
void main_menu( void );

#endif /* SCUF_FED_H_INCLUDED */
