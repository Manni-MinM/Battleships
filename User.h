// HEADER FILE

#include <stdio.h>
#include <string.h>

struct USER {
	int Score ;
	char Username[100] ;
} ;
typedef struct USER User ;

int User_Score(char* Username) {
	// if user exists returns score otherwise returns -1
	FILE* Input_File = fopen("User_Data.txt" , "r") ;
	int score = -1 ;
	char input[100] ;
	while ( fscanf(Input_File , "%s" , input) != EOF ) {
		if ( strcmp(Username , input) == 0 ) {
			fscanf(Input_File , "%d" , &score) ;
			break ;
		}
	}
	fclose(Input_File) ;
	return score ;
}

void Signup(char* Username) {
	FILE* Output_File = fopen("User_Data.txt" , "a") ;
	fprintf(Output_File , "%s\n" , Username) ;
	fprintf(Output_File , "%d\n" , 0) ;
	fclose(Output_File) ;
	Output_File = fopen("Scoreboard.txt" , "a") ;
	fprintf(Output_File , "%s\n" , Username) ;
	fprintf(Output_File , "%d\n" , 0) ;
	fclose(Output_File) ;
	printf("New User Created !\n") ;
	return ;
}

User Signin(void) {
	char Username[100] ;
	printf("Enter Your Username : ") ;
	gets(Username) ;
	for ( int i = 0 ; i < strlen(Username) ; i ++ )
		if ( Username[i] == ' ' ) {
			printf("Username Cannot Contain Spaces\n") ;
			return Signin() ;
		}
	User Current_User ;
	if ( User_Score(Username) != -1 ) {
		Current_User.Score = User_Score(Username) ;
		strcpy(Current_User.Username , Username) ;
	}
	else {
		Signup(Username) ;
		Current_User.Score = 0 ;
		strcpy(Current_User.Username , Username) ;
	}
	return Current_User ;
}
