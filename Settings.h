// HEADER FILE

#include <stdio.h>
#include <string.h>

void Scoreboard(void) {
	FILE* Input_File = fopen("Scoreboard.txt" , "r") ;
	char input[100] ;
	while ( fscanf(Input_File , "%s" , input) != EOF )
		printf("%s\n" , input) ;
	fclose(Input_File) ;
	return ;
}

void PVP(void) {
	User Player1 = Signin() ;
	User Player2 = Signin() ;
	printf("Player1 :\n") ;
	printf("\t Username : %s\n" , Player1.Username) ;
	printf("\t Score : %d\n" , Player1.Score) ;
	printf("Player2 :\n") ;
	printf("\t Username : %s\n" , Player2.Username) ;
	printf("\t Score : %d\n" , Player2.Score) ;
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

