// BWOTSHEWCHB

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "User.h"
#include "Settings.h"

int main() {
	while ( true ) {
		int Exit_Code = Menu() ;
		if ( Exit_Code == 1 )
			break ;
	}
	return 0 ;
}
