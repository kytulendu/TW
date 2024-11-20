#ifndef COMMON_VAR_H_INCLUDED
#define COMMON_VAR_H_INCLUDED

#ifdef DEFINE_VAR
#define EXTERN
#else
#define EXTERN extern
#endif

#ifndef DEFINE_VAR
EXTERN boolean thaimode;        /* current mode is Thai or English */
#else
/* EXTERN will be declared as null already */
EXTERN boolean thaimode = NO;   /* default is English mode */
#endif

#undef EXTERN /* restore it */

#endif /* COMMON_VAR_H_INCLUDED */
