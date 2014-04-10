#ifndef SCUP_GETSTR_H_INCLUDED
#define SCUP_GETSTR_H_INCLUDED

int getstring( char textst[], int x, int y, int maxlen, font_attr attr );
int getname( char textst[], int x, int y, int maxlen, font_attr attr );
int getnumber( char textst[], int x, int y, int maxlen, font_attr attr );

#endif /* SCUP_GETSTR_H_INCLUDED */