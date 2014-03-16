#include "..\common\cwgrphc.h"

#include "var.h"

#include "scrn.h"

void cls( ) {
	clsgraph( wind.col, wind.row, wind.col + wind.length - 1, wind.row + wind.width - 1 );
}
