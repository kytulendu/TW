#include "..\common\cwtype.h"
#include "..\common\grphc.h"

/** find length of thai string
*   Updated: Suttipong Kanakakorn, use pointer instead of array
*            Sun  08-06-1989  16:32:15
*  \param[in]  p_thaistring		thai string.
*  \return int					length of thai string. */
int thaistrlen( char *p_thaistring ) {
	register int count = 0;

	while ( *p_thaistring ) {
		if ( whatlevel( *p_thaistring ) == MIDDLE ) {
			count++;
		}
		p_thaistring++;
	}
	return( count );
}
