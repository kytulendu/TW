#ifndef SCUP_PMENU_H_INCLUDED
#define SCUP_PMENU_H_INCLUDED

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

#endif /* SCUP_PMENU_H_INCLUDED */
