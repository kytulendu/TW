#ifndef ONSCRN_H_INCLUDED
#define ONSCRN_H_INCLUDED

void writetab( void );
void centerline( unsigned int y );
void doonscrn( unsigned int key, unsigned int x, unsigned int y );
void movetotab( unsigned int *x, unsigned int y );
void onscreen( unsigned int x, unsigned int y );
void readconfig( void );

#endif
