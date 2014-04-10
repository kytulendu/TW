#ifndef SCUP_ATTR_H_INCLUDED
#define SCUP_ATTR_H_INCLUDED

FONT *cp_lqscr_blank( FONT *buf );
FONT *cp_sub_middle_lower( FONT *buf, FONTSCR *middle, FONTSCR * lower );
FONT *cp_sub_upper_middle( FONT *buf, FONTSCR *upper, FONTSCR *middle );
FONT *cp_super_upper_middle( FONT *buf, FONTSCR *upper, FONTSCR *middle );
FONT *cp_super_middle_lower( FONT *buf, FONTSCR *middle, FONTSCR *lower );
FONT *cp_underline( FONT *newchar, FONT *oldchar );
FONT *cp_doubleline( FONT *newchar, FONT *oldchar );
int cp_enlarge( struct cp_grlqbuf buf, int index );
void cp_bold( struct cp_grlqbuf buf, int index );

#endif /* SCUP_ATTR_H_INCLUDED */