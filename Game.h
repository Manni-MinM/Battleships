// HEADER FILE

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "Linked_List.h"

#define SIZE 15

void Show_board(user* Player , game_board* Board) {	
	printf("\e[0;33m") , printf("####### %s's Board #######\n\n" , Player->Username) , printf("\e[0m") ;
	for ( int i = 1 ; i <= 10 ; i ++ ) {
		for ( int j = 1 ; j <= 10 ; j ++ ) {
			if ( Board->Board[i][j] == 'W' )
				printf("\e[0;34m") , printf("%c " , Board->Board[i][j]) , printf("\e[0m") ;
			else if ( Board->Board[i][j] == 'E' )
				printf("\e[0;31m") , printf("%c " , Board->Board[i][j]) , printf("\e[0m") ;
			else if ( Board->Board[i][j] == 'C' )
				printf("\e[0;33m") , printf("%c " , Board->Board[i][j]) , printf("\e[0m") ;
			else if ( Board->Board[i][j] == 'B' )
				printf("\e[0;32m") , printf("%c " , Board->Board[i][j]) , printf("\e[0m") ;
			else if ( Board->Board[i][j] == 'N' )
				printf("\e[0;37m") , printf("%c " , Board->Board[i][j]) , printf("\e[0m") ;
		}
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

void Place_ship(user* Player , int Size , int type) {
	game_board* Board = Player->Battle_Board ;
	if ( strcmp(Player->Username , "Bot") && !type )
		Show_board(Player , Board) ;
	// get valid input and check if placement is valid
	ship My_Ship ;
	srand(time(0)) ;
	if ( !strcmp(Player->Username , "Bot") ) {
		while ( true ) {
			My_Ship.St.X = (rand() % 10) + 1 ;
			My_Ship.St.Y = (rand() % 10) + 1 ;
			My_Ship.En.X = (rand() % 10) + 1 ;
			My_Ship.En.Y = (rand() % 10) + 1 ;
			if ( Check_placement(Board , Size , My_Ship) != -1 )
				break ;
		}
	}
	else {
		if ( !type ) {
			printf("\e[1;32m") , printf("Enter the start and end location of the ship with size %d\n" , Size) , printf("\e[0m") ;
			while ( true ) {
				printf("\e[1;36m") , printf("(i1,j1) (i2,j2) : ") , printf("\e[0m") ;
				scanf("(%d,%d) (%d,%d)" , &My_Ship.St.X , &My_Ship.St.Y , &My_Ship.En.X , &My_Ship.En.Y) ; getchar() ;
				if ( My_Ship.St.X > My_Ship.En.X )
					Swap_int(&My_Ship.St.X , &My_Ship.En.X) ;
				if ( My_Ship.St.Y > My_Ship.En.Y )
					Swap_int(&My_Ship.St.Y , &My_Ship.En.Y) ;
				if ( Check_placement(Board , Size , My_Ship) == -1 )
					printf("\e[1;31m") , printf("### Invalid INPUT ###\n") , printf("\e[0m") ;
				else
					break ;
			}
		}
		else {
			while ( true ) {
				My_Ship.St.X = (rand() % 10) + 1 ;
				My_Ship.St.Y = (rand() % 10) + 1 ;
				My_Ship.En.X = (rand() % 10) + 1 ;
				My_Ship.En.Y = (rand() % 10) + 1 ;
				if ( Check_placement(Board , Size , My_Ship) != -1 )
					break ;
			}
		}
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
	Player->Turn = 0 ;
	Player->head = (node**)malloc(sizeof(node*)) ;
	Player->tail = (node**)malloc(sizeof(node*)) ;
	*(Player->head) = NULL ;
	*(Player->tail) = NULL ;
	// build the boards
	Player->Battle_Board = (game_board*)malloc(sizeof(game_board)) ;
	Player->Shadow_Board = (game_board*)malloc(sizeof(game_board)) ;
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
	int condition = 0 ;
	if ( strcmp(Player->Username , "Bot") ) {
		printf("\e[1;94m") , printf("####### User : %s #### Coins : %d #### Current Score : %d #######\n\n" , Player->Username , Player->Score , Player->Cur_Score) , printf("\e[0m") ;
		printf("\e[1;32m") , printf("Enter 1 for auto initialization of the board and 0 for manual initialization\n\n") , printf("\e[0m") ;
		printf("\e[1;36m") , printf("input : ") , printf("\e[0m") , scanf("%d" , &condition) , getchar() , printf("\n") ;
	}
	// place the ships
	Place_ship(Player , 5 , condition) ;
	Place_ship(Player , 3 , condition) ;
	Place_ship(Player , 3 , condition) ;
	Place_ship(Player , 2 , condition) ;
	Place_ship(Player , 2 , condition) ;
	Place_ship(Player , 2 , condition) ;
	Place_ship(Player , 1 , condition) ;
	Place_ship(Player , 1 , condition) ;
	Place_ship(Player , 1 , condition) ;
	Place_ship(Player , 1 , condition) ;
	// show the board one last time
	if ( strcmp(Player->Username , "Bot") )
		Show_board(Player , Player->Battle_Board) ;
	// visual mambo-jambo
	sleep(2) ;
	system("clear") ;

	return ;
}

int Game_load(user* Player1 , user* Player2) {
	// init Player1
	Player1->head = (node**)malloc(sizeof(node*)) ;
	Player1->tail = (node**)malloc(sizeof(node*)) ;
	*(Player1->head) = NULL ;
	*(Player1->tail) = NULL ;
	Player1->Score = User_Score(Player1->Username) ;
	for ( int i = 0 ; i < 10 ; i ++ ) {
		if ( Player1->Battleship[i].St.X == -1 && Player1->Battleship[i].St.Y == -1 && Player1->Battleship[i].En.X == -1 && Player1->Battleship[i].En.Y == -1 )
			continue ;
		else
			Append(Player1 , Player1->Battleship[i]) ;
	}
	
	// init Player2 
	Player2->head = (node**)malloc(sizeof(node*)) ;
	Player2->tail = (node**)malloc(sizeof(node*)) ;
	*(Player2->head) = NULL ;
	*(Player2->tail) = NULL ;
	Player2->Score = User_Score(Player2->Username) ;
	for ( int i = 0 ; i < 10 ; i ++ ) {
		if ( Player2->Battleship[i].St.X == -1 && Player2->Battleship[i].St.Y == -1 && Player2->Battleship[i].En.X == -1 && Player2->Battleship[i].En.Y == -1 )
			continue ;
		else
			Append(Player2 , Player2->Battleship[i]) ;
	}
	
	// return player starting the next turn
	if ( Player1->Turn == 1 )
		return 1 ;
	else if ( Player2->Turn == 1 )
		return 2 ;
	return 0 ;
}

int Game_turn(user* Attacker , user* Defender , int Di , int Dj) {
	// return 1 if Defender loses otherwise returns 0
	game_board* Board_Defender = Defender->Battle_Board ;
	game_board* Board_Attacker = Attacker->Shadow_Board ;
	if ( Board_Defender->Board[Di][Dj] == 'B' ) {
		Board_Attacker->Board[Di][Dj] = 'E' ;
		Attacker->Cur_Score += 1 ;
	}
	else {
		Board_Attacker->Board[Di][Dj] = 'W' ;
	}
	// if ship is completely destroyed change E with C and change barriers to W
	node* cur = *(Defender->head) ;
	while ( cur != NULL ) {
		int STi = cur->Battleship.St.X , ENi = cur->Battleship.En.X ;
		int STj = cur->Battleship.St.Y , ENj = cur->Battleship.En.Y ;
		if ( STi == ENi ) {
			int flag = 1 ;
			for ( int j = STj ; j <= ENj ; j ++ )
				if ( Board_Attacker->Board[STi][j] != 'E' )
					flag = 0 ;
			if ( flag ) {
				if ( ENj - STj == 5 )
					Attacker->Cur_Score += 5 ;
				else if ( ENj - STj == 3 )
					Attacker->Cur_Score += 8 ;
				else if ( ENj - STj == 2 )
					Attacker->Cur_Score += 12 ;
				else if ( ENj - STj == 1 )
					Attacker->Cur_Score += 25 ;
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
				break ;
			}
		}
		else if ( STj == ENj ) {
			int flag = 1 ;
			for ( int i = STi ; i <= ENi ; i ++ )
				if ( Board_Attacker->Board[i][STj] != 'E' )
					flag = 0 ;
			if ( flag ) {
				if ( ENi - STi == 5 )
					Attacker->Cur_Score += 5 ;
				else if ( ENi - STi == 3 )
					Attacker->Cur_Score += 8 ;
				else if ( ENi - STi == 2 )
					Attacker->Cur_Score += 12 ;
				else if ( ENi - STi == 1 )
					Attacker->Cur_Score += 25 ;
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
				break ;
			}
		}
		if ( cur == *(Defender->tail) )
			break ;
		cur = cur->next ;
	}
	if ( strcmp(Attacker->Username , "Bot") && strcmp(Defender->Username , "Bot") )
		Show_board(Attacker , Board_Attacker) ;
	if ( *(Defender->head) == NULL )
		return 1 ;
	return 0 ;
}

