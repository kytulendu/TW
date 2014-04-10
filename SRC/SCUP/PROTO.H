/* ldfont.c */
void loadfont( void );

/* pmenu.c */
void writemenu( int row, int col, font_attr attr );
void writeallmenu( void );
void menuselect( void );
void prtwriteallmenu( void );
void prtwritemenu( int row, font_attr attr );
void prtmenuselect( void );
void setprinter( int smallpaper, int printer24pin );
void prtdocommand( int row );
void modewriteallmenu( void );
void modewritemenu( int row, int attr );
void modemenuselect( void );
void modedocommand( int row );
void titlewriteallmenu( void );
void titlewritemenu( int row, int attr );
void titlemenuselect( void );
void titledocommand( int row );

/* prt.c */
void AllocateBuffer9pin( void );
int PrinterLoadFont9pin( void );
int  islevel( int *pline );
void PrinterLoadLine( char pline[] );
void PrinterLoadLine9pin( char line[] );

/* prtt.c */
void PrinterLoadLineText( unsigned char line[] );

/* prtbuf24.c */
void PrintThree24pin( int uindex, int mindex, int lindex );
void PrintBuffer24pin( char buf1[], char buf2[], char buf3[], int maxscan );

/* prtg.c */
void PrintThree9pin( void );

/* smenu.c */
int smenu( register int x, register int y, int number,
    char *messege[], int *curmenu );
unsigned find_menu_len( register int number, char *messege[] );
