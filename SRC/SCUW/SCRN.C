/**
*   SCRN.C 15 JAN 89
*   Updated: Suttipong Kanakakorn
*            Sun  08-06-1989  09:31:59
*/

#include "..\common\cwgrphc.h"

#include "var.h"

#include "scrn.h"

void cls( ) {
	clsgraph( wind.col, wind.row, wind.col + wind.length - 1, wind.row + wind.width - 1 );
}
