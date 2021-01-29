// HEADER FILE

#include <stdio.h>
#include <string.h>

#include "Structs.h"
#include "Useful_Functions.h"

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
	// adds new user to User_Data.txt with score 0
	FILE* Output_File = fopen("User_Data.txt" , "a") ;
	fprintf(Output_File , "%s\n" , Username) ;
	fprintf(Output_File , "%d\n" , 0) ;
	fclose(Output_File) ;
	Output_File = fopen("Scoreboard.txt" , "a") ;
	fprintf(Output_File , "%s\n" , Username) ;
	fprintf(Output_File , "%d\n" , 0) ;
	fclose(Output_File) ;	
	return ;
}

user Signin(void) {
	// asks for username logs in if it already exists otherwise creates new user and the logs in
	char Username[100] ;
	printf("Enter Your Username : ") ;
	gets(Username) ;
	for ( int i = 0 ; i < strlen(Username) ; i ++ )
		if ( Username[i] == ' ' ) {
			printf("Username Cannot Contain Spaces\n") ;
			return Signin() ;
		}
	user Current_User ;
	if ( User_Score(Username) != -1 ) {
		Current_User.Score = User_Score(Username) ;
		strcpy(Current_User.Username , Username) ;
		printf("Login Successful !\n") ;
	}
	else {
		Signup(Username) ;
		Current_User.Score = 0 ;
		strcpy(Current_User.Username , Username) ;
		printf("New User Created !\n") ;
	}
	return Current_User ;
}

void Scoreboard(void) {
	FILE* Input_File = fopen("User_Data.txt" , "r") ;
	int it = 0 ;
	user User[100] ;
	char Player[100] , Score[100] ;
	while ( fscanf(Input_File , "%s" , Player) != EOF ) {
		fscanf(Input_File , "%s\n" , Score) ;
		printf("Player : %s / Score : %s\n" , Player , Score) ;
		strcpy(User[it].Username , Player) ;
		User[it].Score = Str_int(Score) ;
		it ++ ;
	}
	for ( int i = 0 ; i < it ; i ++ )
		for ( int j = i ; j < it ; j ++ )
			if ( User[i].Score < User[j].Score ) {
				int temp_Score = User[i].Score ;
				char temp_Username[100] ;
				strcpy(temp_Username , User[i].Username) ;
				User[i].Score = User[j].Score ;
				strcpy(User[i].Username , User[j].Username) ;
				User[j].Score = temp_Score ;
				strcpy(User[j].Username , temp_Username) ;
			}
	fclose(Input_File) ;
	FILE* Output_File = fopen("User_Data.txt" , "w") ;
	for ( int i = 0 ; i < it ; i ++ ) {
		fprintf(Output_File , "%s\n" , User[i].Username) ;
		fprintf(Output_File , "%d\n" , User[i].Score) ;
	}
	fclose(Output_File) ;
	return ;
}
