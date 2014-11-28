/*
* ============================================================================
* VAR.C 15 JAN 89
*
* var.c combine with var.h
*  By Noom Suttipong Sun  07-30-1989  15:37:35
* Updated: Suttipong Kanakakorn
*        : Mon  07-31-1989  20:13:05
* ============================================================================
*/

#ifndef SCUF_VAR_H_INCLUDED
#define SCUF_VAR_H_INCLUDED

#ifdef  DEFINE_VAR
#define EXTERN
#else
#define EXTERN extern
#endif

/* =================================================================== */
/* First part can define and declare with the same attribute           */

EXTERN char dfont[20 * 256];
EXTERN char ditalicfont[1];

EXTERN char *progname;   /* point to argv[0] */
EXTERN char cuf_dir[MAXDRIVE+MAXDIR];  /* which directory is CW.EXE in */

#undef EXTERN /* restore it */

#endif /* SCUF_VAR_H_INCLUDED */
