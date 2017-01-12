#ifndef SCUP_CPI_H_INCLUDED
#define SCUP_CPI_H_INCLUDED

/** Routine to set actual character width (character per inch).
*   characters per inch (cpi) is stored in global int 'cpi'.
*   the parameter is the buffer store dot data size[1920,3264].
*   -------------------------------------------------------------
*   ch/inch    dot/char    increasingdot    process(after/before)
*   1            240            216          10/1
*   2            120             96           5/1
*   3             80             56          10/3
*   4             60             36           5/2
*   5             48             24           2/1
*   6             40             16           5/3
*   7             34             10          17/12
*   8             30              6           5/4
*   9             27              3           9/8
*   ---------------------------------------------------
*   10            24              0          NONE
*   ---------------------------------------------------
*   11            22            - 2          11/12
*   12            20            - 4           5/6
*   13            18            - 6           3/4
*   14            17            - 7          17/24
*   15            16            - 8           2/3
*   16            15            - 9          15/24
*   17            14            -10           7/12
*   18            13            -11          13/24
*   19            12            -12           1/2
*   20            12            -12           1/2 */
void charwidth( char *p_buffer );

#endif /* SCUP_CPI_H_INCLUDED */