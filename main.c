// BWOTSHEWCHB

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Game.h"

#define SIZE 15

void PVP(void) {
	// sign in the players
	user Player1 = Signin() ;
	user Player2 = Signin() ;
	// init the game for both players
	Game_init(&Player1) ;
	Game_init(&Player2) ;
	// run the game
	while ( true ) {
		int condition , Di , Dj ;
		Show_board(&Player1 , Player1.Shadow_Board) ;
		printf("\e[4;32m") , printf("Enter the location you want destroyed\n") , printf("\e[0m") ;
		printf("\e[1;37m") , printf("(i,j) :\n") , printf("\e[0m") ;
		scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
		condition = Game_turn(&Player1 , &Player2 , Di , Dj) ;
		if ( condition == 1 ) {
			printf("\e[1;37m") , printf("%s Wins\n\n" , Player1.Username) , printf("\e[0m") ;
			Player1.Score += Player1.Cur_Score ;
			Player1.Cur_Score = 0 ;
			Player2.Score += Player2.Cur_Score / 2 ;
			Player2.Cur_Score = 0 ;
			break ;
		}
		Show_board(&Player2 , Player2.Shadow_Board) ;
		printf("\e[4;32m") , printf("Enter the location you want destroyed\n") , printf("\e[0m") ;
		printf("\e[1;37m") , printf("(i,j) :\n") , printf("\e[0m") ;
		scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
		condition = Game_turn(&Player2 , &Player1 , Di , Dj) ;
		if ( condition == 1 ) {
			printf("\e[1;37m") , printf("%s Wins\n\n" , Player2.Username) , printf("\e[0m") ;
			Player2.Score += Player2.Cur_Score ;
			Player2.Cur_Score = 0 ;
			Player1.Score += Player1.Cur_Score / 2 ;
			Player1.Cur_Score = 0 ;
			break ; 
		}
	}
	Change_Score(Player1.Username , Player1.Score) ;
	Change_Score(Player2.Username , Player2.Score) ;
	return ;
}
void PVE(void) {
	// sign in player and bot
	user Player = Signin() ;
	user Bot = Signin_bot() ;
	// init the game for player and bot
	Game_init(&Bot) ;
	Game_init(&Player) ;
	// run the game
	srand(time(0)) ;
	while ( true ) {
		int condition , Di , Dj ;
		Show_board(&Player , Player.Shadow_Board) ;
		printf("\e[4;32m") , printf("Enter the location you want destroyed\n") , printf("\e[0m") ;
		printf("\e[1;37m") , printf("(i,j) :\n") , printf("\e[0m") ;
		scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
		condition = Game_turn(&Player , &Bot , Di , Dj) ;
		if ( condition == 1 ) {
			printf("\e[1;37m") , printf("%s Wins\n\n" , Player.Username) , printf("\e[0m") ;
			Player.Score += Player.Cur_Score ;
			Player.Cur_Score = 0 ;
			break ;
		}
		Di = (rand() % 10) + 1 , Dj = (rand() % 10) + 1 ;
		condition = Game_turn(&Bot , &Player , Di , Dj) ;
		if ( condition == 1 ) {
			printf("\e[1;37m") , printf("Bot Wins\n\n") , printf("\e[0m") ;
			Player.Score += Player.Cur_Score / 2 ;
			Player.Cur_Score = 0 ;
			break ; 
		}
	}
	Change_Score(Player.Username , Player.Score) ;
	return ;
}

int Menu(void) {
	printf("\e[1;34m") ;
	printf("1. Play With a Friend\n") ;
	printf("2. Play With Bot\n") ;
	printf("3. Load Game\n") ;
	printf("4. Scoreboard\n") ;
	printf("5. Exit\n") ;
	printf("\e[0m") ;

	int Menu_Input , Exit_Code ;
	scanf("%d" , &Menu_Input) , getchar() ;
	if ( Menu_Input == 1 ) {
		// Use Game.h and run play with a friend
		PVP() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 2 ) {
		// Use Game.h and run play with bot
		PVE() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 3 ) {
		// load list of saved games
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 4 ) {
		// show the scoreboard
		Scoreboard() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 5 ) {
		// Close the program
		Exit_Code = 1 ;
	}
	return Exit_Code ;
}

int main() {
	while ( true ) {
	int Exit_Code = Menu() ;
		if ( Exit_Code == 1 )
			break ;
	}
	return 0 ;
}
