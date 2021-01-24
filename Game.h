// HEADER FILE

#include <stdio.h>

#include "User.h"

#define SIZE 15

void Swap_int(int* v , int* u) {
	int temp = *u ;
	*u = *v ;
	*v = temp ;
	return ;
}

void Show_board(User Player , int* Board) {
	printf("###### %s's Board ###### Score : %d ######\n" , Player.Username , Player.Score) ;
	for ( int i = 1 ; i <= 10 ; i ++ ) {
		for ( int j = 1 ; j <= 10 ; j ++ )
			printf("%d " , *(Board + (i * SIZE) + j)) ;
		printf("\n") ;
	}
	printf("\n") ;
	return ;
}

int Check_placement(int* Board , int Size , int STi , int STj , int ENi , int ENj) {
	// is valid ?!
	if ( STi > 10 || STi < 1 )
		return -1 ;
	if ( ENi > 10 || ENi < 1 )
		return -1 ;
	if ( STj > 10 || STj < 1 )
		return -1 ;
	if ( ENj > 10 || ENj < 1 )
		return -1 ;
	if ( STi == ENi ) {
		if ( ENj - STj + 1 != Size )
			return -1 ;
		for ( int j = STj ; j <= ENj ; j ++ ) {
			if ( *(Board + (STi * SIZE) + j)  == 1 )
				return -1 ;
			else if ( *(Board + ((STi - 1) * SIZE) + j) == 1 )
				return -1 ;
			else if ( *(Board + ((STi - 1) * SIZE) + (j - 1)) == 1 )
				return -1 ;
			else if ( *(Board + ((STi - 1) * SIZE) + (j + 1)) == 1 )
				return -1 ;
			else if ( *(Board + ((STi + 1) * SIZE) + j) == 1 )
				return -1 ;
			else if ( *(Board + ((STi + 1) * SIZE) + (j - 1)) == 1 )
				return -1 ;
			else if ( *(Board + ((STi + 1) * SIZE) + (j + 1)) == 1 )
				return -1 ;
			else if ( *(Board + (STi * SIZE) + (j - 1)) == 1 )
				return -1 ;
			else if ( *(Board + (STi * SIZE) + (j + 1)) == 1 )
				return -1 ;
		}
		return 0 ;
	}
	else if ( STj == ENj ) {
		if ( ENi - STi + 1 != Size )
			return -1 ;
		for ( int i = STi ; i <= ENi ; i ++ ) {
			if ( *(Board + (i * SIZE) + STj)  == 1 )
				return -1 ;
			else if ( *(Board + ((i - 1) * SIZE) + STj) == 1 )
				return -1 ;
			else if ( *(Board + ((i - 1) * SIZE) + (STj - 1)) == 1 )
				return -1 ;
			else if ( *(Board + ((i - 1) * SIZE) + (STj + 1)) == 1 )
				return -1 ;
			else if ( *(Board + ((i + 1) * SIZE) + STj) == 1 )
				return -1 ;
			else if ( *(Board + ((i + 1) * SIZE) + (STj - 1)) == 1 )
				return -1 ;
			else if ( *(Board + ((i + 1) * SIZE) + (STj + 1)) == 1 )
				return -1 ;
			else if ( *(Board + (i * SIZE) + (STj - 1)) == 1 )
				return -1 ;
			else if ( *(Board + (i * SIZE) + (STj + 1)) == 1 )
				return -1 ;
		}
		return 0 ;
	}
	else
		return -1 ;
}

int* Place_ship(User Player , int* Board , int Size) {
	Show_board(Player , Board) ;
	printf("Enter the start and end location of the ship with size %d\n" , Size) ;
	int STi , STj , ENi , ENj ;
	while ( true ) {
		printf("(i1,j1) (i2,j2) :\n") ;
		scanf("(%d,%d) (%d,%d)" , &STi , &STj , &ENi , &ENj) ; getchar() ;
		if ( STi > ENi )
			Swap_int(&STi , &ENi) ;
		if ( STj > ENj )
			Swap_int(&STj , &ENj) ;
		if ( Check_placement(Board , Size , STi , STj , ENi , ENj) == -1 )
			printf("### Invalid INPUT ###\n") ;
		else
			break ;
	}
	if ( STi == ENi ) {
		// Horizontal
		for ( int i = STj ; i <= ENj ; i ++ )
			*(Board + (STi * SIZE) + i) = 1 ;
	}
	else if ( STj == ENj ) {
		// Vertical
		for ( int i = STi ; i <= ENi ; i ++ )
			*(Board + (i * SIZE) + STj) = 1 ;
	}
	return Board ;
}

int* Game_init(User Player , int* Board) {
	// initialize the board
	for ( int i = 0 ; i < SIZE ; i ++ )
		for ( int j = 0 ; j < SIZE ; j ++ )
			*(Board + (i * SIZE) + j) = 0 ;
	// place the ships
	Board = Place_ship(Player , Board , 5) ;
	Board = Place_ship(Player , Board , 3) ;
	Board = Place_ship(Player , Board , 3) ;
	Board = Place_ship(Player , Board , 2) ;
	Board = Place_ship(Player , Board , 2) ;
	Board = Place_ship(Player , Board , 2) ;
	Board = Place_ship(Player , Board , 1) ;
	Board = Place_ship(Player , Board , 1) ;
	Board = Place_ship(Player , Board , 1) ;
	Board = Place_ship(Player , Board , 1) ;
	// show the board one last time
	Show_board(Player , Board) ;
	return Board ;
}
