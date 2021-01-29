// BWOTSHEWCHB

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
		printf("Enter the location you want destroyed\n") ;
		printf("(i,j) :\n") ;
		scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
		condition = Game_turn(&Player1 , &Player2 , Di , Dj) ;
		if ( condition == 1 ) {
			printf("%s Wins\n\n" , Player1.Username) ;
			break ;
		}
		Show_board(&Player2 , Player2.Shadow_Board) ;
		printf("Enter the location you want destroyed\n") ;
		printf("(i,j) :\n") ;
		scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
		condition = Game_turn(&Player2 , &Player1 , Di , Dj) ;
		if ( condition == 1 ) {
			printf("%s Wins\n\n" , Player2.Username) ;
			break ; 
		}
	}
	return ;
}

int Menu(void) {
	printf("1. Play With a Friend\n") ;
	printf("2. Play With Bot\n") ;
	printf("3. Load Game\n") ;
	printf("4. Scoreboard\n") ;
	printf("5. Exit\n") ;

	int Menu_Input , Exit_Code ;
	scanf("%d" , &Menu_Input) , getchar() ;
	if ( Menu_Input == 1 ) {
		// Use Game.h and run play with a friend
		PVP() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 2 ) {
		// Use Game.h and run play with bot
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
