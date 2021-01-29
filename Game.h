// HEADER FILE

#include <stdio.h>

#include "Linked_List.h"

#define SIZE 15

void Show_board(user* Player , game_board* Board) {	
	printf("###### %s's Board ###### Coins : %d ######\n" , Player->Username , Player->Score) ;
	for ( int i = 1 ; i <= 10 ; i ++ ) {
		for ( int j = 1 ; j <= 10 ; j ++ )
			printf("%c " , Board->Board[i][j]) ;
		printf("\n") ;
	}
	printf("\n") ;
	return ;
}

int Check_placement(game_board* Board , int Size , ship My_Ship) {
	// checks ship placement if invalid returns -1 else returns 0
	int STi = My_Ship.St.X , STj = My_Ship.St.Y , ENi = My_Ship.En.X , ENj = My_Ship.En.Y ;
	if ( STi > 10 || STi < 1 )
		return -1 ;
	if ( ENi > 10 || ENi < 1 )
		return -1 ;
	if ( STj > 10 || STj < 1 )
		return -1 ;
	if ( ENj > 10 || ENj < 1 )
		return -1 ;
	// horizontal
	if ( STi == ENi ) {
		// check ship length
		if ( ENj - STj + 1 != Size )
			return -1 ;
		// check ship barrier
		for ( int j = STj ; j <= ENj ; j ++ ) {
				if ( Board->Board[STi][j] == 'B' )
				return -1 ;
			else if ( Board->Board[STi - 1][j] == 'B' )
				return -1 ;
			else if ( Board->Board[STi - 1][j - 1] == 'B' )
				return -1 ;
			else if ( Board->Board[STi - 1][j + 1] == 'B' )
				return -1 ;
			else if ( Board->Board[STi + 1][j] == 'B' )
				return -1 ;
			else if ( Board->Board[STi + 1][j - 1] == 'B' )
				return -1 ;
			else if ( Board->Board[STi + 1][j + 1] == 'B' )
				return -1 ;
			else if ( Board->Board[STi][j - 1] == 'B' )
				return -1 ;
			else if ( Board->Board[STi][j + 1] == 'B' )
				return -1 ;
	}
		return 0 ;
	}
	// vertical
	else if ( STj == ENj ) {
		// check ship length
		if ( ENi - STi + 1 != Size )
			return -1 ;
		// check ship barrier
		for ( int i = STi ; i <= ENi ; i ++ ) {
			if ( Board->Board[i][STj] == 'B' )
				return -1 ;
			else if ( Board->Board[i - 1][STj] == 'B' )
				return -1 ;
			else if ( Board->Board[i - 1][STj - 1] == 'B' )
				return -1 ;
			else if ( Board->Board[i - 1][STj + 1] == 'B' )
				return -1 ;
			else if ( Board->Board[i + 1][STj] == 'B' )
				return -1 ;
			else if ( Board->Board[i + 1][STj - 1] == 'B' )
				return -1 ;
			else if ( Board->Board[i + 1][STj + 1] == 'B' )
				return -1 ;
			else if ( Board->Board[i][STj - 1] == 'B' )
				return -1 ;
			else if ( Board->Board[i][STj + 1] == 'B' )
				return -1 ;
		}
		return 0 ;
	}
	else
		return -1 ;
}

void Place_ship(user* Player , int Size) {
	game_board* Board = Player->Battle_Board ;
	Show_board(Player , Board) ;
	printf("Enter the start and end location of the ship with size %d\n" , Size) ;
	// get valid input and check if placement is valid
	ship My_Ship ;
	while ( true ) {
		printf("(i1,j1) (i2,j2) :\n") ;
		scanf("(%d,%d) (%d,%d)" , &My_Ship.St.X , &My_Ship.St.Y , &My_Ship.En.X , &My_Ship.En.Y) ; getchar() ;
		if ( My_Ship.St.X > My_Ship.En.X )
			Swap_int(&My_Ship.St.X , &My_Ship.En.X) ;
		if ( My_Ship.St.Y > My_Ship.En.Y )
			Swap_int(&My_Ship.St.Y , &My_Ship.En.Y) ;
		if ( Check_placement(Board , Size , My_Ship) == -1 )
			printf("### Invalid INPUT ###\n") ;
		else
			break ;
	}
	// add My_Ship to Linked List
	Append(Player , My_Ship) ;
	// horizontal
	if ( My_Ship.St.X == My_Ship.En.X ) {
		for ( int j = My_Ship.St.Y ; j <= My_Ship.En.Y ; j ++ )
			Board->Board[My_Ship.St.X][j] = 'B' ;
	}
	// vertical
	else if ( My_Ship.St.Y == My_Ship.En.Y ) {
		for ( int i = My_Ship.St.X ; i <= My_Ship.En.X ; i ++ )
			Board->Board[i][My_Ship.St.Y] = 'B' ;
	}
	return ;
}

void Game_init(user* Player) {
	// init Player
	Player->head = (node**)malloc(sizeof(node*)) ;
	Player->tail = (node**)malloc(sizeof(node*)) ;
	*(Player->head) = NULL ;
	*(Player->tail) = NULL ;
	// build the boards
	Player->Battle_Board = malloc(sizeof(game_board)) ;
	Player->Shadow_Board = malloc(sizeof(game_board)) ;
	// initialize the board
	game_board* Board ;
	Board = Player->Battle_Board ;
	for ( int i = 0 ; i < SIZE ; i ++ )
		for ( int j = 0 ; j < SIZE ; j ++ )
			Board->Board[i][j] = 'W' ;
	Board = Player->Shadow_Board ;
	for ( int i = 0 ; i < SIZE ; i ++ )
		for ( int j = 0 ; j < SIZE ; j ++ )
			Board->Board[i][j] = 'N' ;
	// place the ships
	Place_ship(Player , 5) ;
	Place_ship(Player , 3) ;
	Place_ship(Player , 3) ;
	Place_ship(Player , 2) ;
	Place_ship(Player , 2) ;
	Place_ship(Player , 2) ;
	Place_ship(Player , 1) ;
	Place_ship(Player , 1) ;
	Place_ship(Player , 1) ;
	Place_ship(Player , 1) ;
	// show the board one last time
	Show_board(Player , Player->Battle_Board) ;
	return ;
}

int Game_turn(user* Attacker , user* Defender , int Di , int Dj) {
	// return 1 if Defender loses otherwise returns 0
	game_board* Board_Defender = Defender->Battle_Board ;
	game_board* Board_Attacker = Attacker->Shadow_Board ;
	if ( Board_Defender->Board[Di][Dj] == 'B' )
		Board_Attacker->Board[Di][Dj] = 'E' ;
	else
		Board_Attacker->Board[Di][Dj] = 'W' ;
	// if ship is completely destroyed change E with C and change barriers to W
	node* cur = *(Defender->head) ;
	while ( cur != NULL ) {
		int STi = cur->Battleship.St.X , ENi = cur->Battleship.En.X , STj = cur->Battleship.St.Y , ENj = cur->Battleship.En.Y ;
		if ( STi == ENi ) {
			int flag = 1 ;
			for ( int j = STj ; j <= ENj ; j ++ )
				if ( Board_Attacker->Board[STi][j] != 'E' )
					flag = 0 ;
			if ( flag ) {
				Delete(Defender , cur->Battleship) ;
				for ( int j = STj - 1 ; j <= ENj + 1 ; j ++ ) {
					Board_Attacker->Board[STi - 1][j] = 'W' ;
					Board_Attacker->Board[STi][j] = 'C' ;
					Board_Attacker->Board[STi + 1][j] = 'W' ;
				}
				for ( int i = STi - 1 ; i <= STi + 1 ; i ++ ) {
					Board_Attacker->Board[i][STj - 1] = 'W' ;
					Board_Attacker->Board[i][ENj + 1] = 'W' ;
				}
			}
			break ;
		}
		else if ( STj == ENj ) {
			int flag = 1 ;
			for ( int i = STi ; i <= ENi ; i ++ )
				if ( Board_Attacker->Board[i][STj] != 'E' )
					flag = 0 ;
			if ( flag ) {
				Delete(Defender , cur->Battleship) ;
				for ( int i = STi - 1 ; i <= ENi + 1 ; i ++ ) {
					Board_Attacker->Board[i][STj - 1] = 'W' ;
					Board_Attacker->Board[i][STj] = 'C' ;
					Board_Attacker->Board[i][STj + 1] = 'W' ;
				}
				for ( int j = STj ; j <= ENj ; j ++ ) {
					Board_Attacker->Board[STi - 1][j] = 'W' ;
					Board_Attacker->Board[ENi + 1][j] = 'W' ;
				}
			}
			break ;
		}
		cur = cur->next ;
	}
	Show_board(Attacker , Board_Attacker) ;
	if ( *(Defender->head) == NULL )
		return 1 ;
	return 0 ;
}

