// HEADER FILE

#include <stdlib.h>

#include "User_Functions.h"

node* Search(user* Player , ship My_Ship) {
	node* cur = *(Player->head)  ;
	while ( cur != NULL ) {
		if ( cur->Battleship.St.X == My_Ship.St.X && cur->Battleship.St.Y == My_Ship.St.Y )
			if ( cur->Battleship.En.X == My_Ship.En.X && cur->Battleship.En.Y == My_Ship.En.Y )
				return cur ;
		if ( cur == *(Player->tail) )
			break ;
		cur = cur->next ;
	}
	return NULL ;
}

void Append(user* Player , ship My_Ship) {
	node** head = Player->head ;
	node** tail = Player->tail ;
	if ( Search(Player , My_Ship) != NULL )
		return ;
	node* New = (node*)malloc(sizeof(node)) ;
	New->Battleship = My_Ship ;
	if ( *head == NULL )
		*tail = New ;	
	New->next = *head ;
	if ( *head != NULL ) {
		(*head)->prev = New ;
	}
	*head = New ;
	return ;
}

void Delete(user* Player , ship My_Ship) {
	node** head = Player->head ;
	node** tail = Player->tail ;
	node* cur = Search(Player , My_Ship) ;
	if ( cur == NULL )
		return ;
	if ( cur == *head ) {
		*head = cur->next ;
		free(cur) ;
		return ;
	}
	if ( cur == *tail ) {
		*tail = cur->prev ;
		free(cur) ;
		return ;
	}
	if ( cur->prev != NULL )
		(cur->prev)->next = cur->next ;
	if ( cur->next != NULL )
		(cur->next)->prev = cur->prev ;
	free(cur) ;
	return ;
}

