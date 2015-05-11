/*  dir.h

Defines structures, macros, and functions for dealing with
directories and pathnames.

Copyright (c) 1987, 1992 by Borland International
All Rights Reserved.
*/

#ifndef far
#define far
#endif

#if !defined(__DIR_H)
#define __DIR_H

#ifndef _FFBLK_DEF
#define _FFBLK_DEF
struct  ffblk {
	char        ff_reserved[21];
	char        ff_attrib;
	unsigned    ff_ftime;
	unsigned    ff_fdate;
	long        ff_fsize;
	char        ff_name[13];
};
#endif

#define WILDCARDS 0x01
#define EXTENSION 0x02
#define FILENAME  0x04
#define DIRECTORY 0x08
#define DRIVE     0x10

#define MAXPATH   80
#define MAXDRIVE  3
#define MAXDIR    66
#define MAXFILE   9
#define MAXEXT    5

int chdir( const char *__path );
int findfirst( const char *__path,
	struct ffblk *__ffblk, int __attrib );
int findnext( struct ffblk *__ffblk );
void fnmerge( char *__path,
	const char *__drive,
	const char *__dir,
	const char *__name,
	const char *__ext );
int fnsplit( const char *__path,
	char *__drive,
	char *__dir,
	char *__name,
	char *__ext );
char * getcwd( char *__buf, int __buflen );
int getdisk( void );
int setdisk( int __drive );

#endif  /* __DIR_H */
