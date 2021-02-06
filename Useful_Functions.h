// HEADER FILE 

#include <stdlib.h>

void Swap_int(int* v , int* u) {
        // swaps two integer variables
        int temp = *u ;
        *u = *v ;
        *v = temp ;
        return ;
}

int Str_int(char* str) {
	int val = 0 ;
	while ( *str != '\0' )
		val += *str - '0' , val *= 10 , str ++ ;
	return (val / 10) ;
}

