// HEADER FILE 

#include <stdlib.h>

#include "Linked_List.h"

void Push(plate** Top , point Target) {
	plate* New = (plate*)malloc(sizeof(plate)) ;
	New->Target = Target ;
	New->next = *Top ;
	*Top = New ;
	return ;
}

void Pop(plate** Top) {
	if ( *Top == NULL )
		return ;
	plate* next = (*Top)->next ;
	free(*Top) ;
	*Top = next ;
	return ;
}

