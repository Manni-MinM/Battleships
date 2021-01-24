// HEADER FILE

#include <stdio.h>
#include <string.h>

#include "Game.h"

#define SIZE 15

void Scoreboard(void) {
	FILE* Input_File = fopen("User_Data.txt" , "r") ;
	char Player[100] , Score[100] ;
	while ( fscanf(Input_File , "%s" , Player) != EOF ) {
		fscanf(Input_File , "%s" , Score) ;
		printf("%s / Score : %s\n" , Player , Score) ;
	}
	fclose(Input_File) ;
	return ;
}

void PVP(void) {
	User Player1 = Signin() ;
	User Player2 = Signin() ;
	int Board1[SIZE][SIZE] ;
	int Board2[SIZE][SIZE] ;
	int* Board1_Pointer = &Board1[0][0] ;
	Board1_Pointer = Game_init(Player1 , Board1_Pointer) ;
	int* Board2_Pointer = &Board2[0][0] ;
	Board2_Pointer = Game_init(Player2 , Board2_Pointer) ;
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
		// Use Settings.h and load list of saved games
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 4 ) {
		// Use Settings.h and show the scoreboard
		Scoreboard() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 5 ) {
		// Close the program
		Exit_Code = 1 ;
	}
	return Exit_Code ;
}

