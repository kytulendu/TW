#ifndef SCUP_ERROR_H_INCLUDED
#define SCUP_ERROR_H_INCLUDED

/** Display error message.
*  \param[in]  p_string         Error message string. */
void disperror( char *p_string );

/** Report error and terminate program.
*  \param[in]  p_err            General error string.
*  \param[in]  p_exterr         Extended error string. */
void execerror( char *p_err, char *p_exterr );

#endif /* SCUP_ERROR_H_INCLUDED */
