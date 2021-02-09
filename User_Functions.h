// HEADER FILE

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Structs.h"
#include "Useful_Functions.h"

int User_Score(char* Username) {
	// if user exists returns score otherwise returns -1
	FILE* Input_File = fopen("User_Data.txt" , "r") ;
	int score = -1 ;
	char input[100] ;
	while ( fscanf(Input_File , "%s" , input) != EOF ) {
		if ( !strcmp(Username , input) ) {
			fscanf(Input_File , "%d" , &score) ;
			break ;
		}
	}
	fclose(Input_File) ;
	return score ;
}

void Change_Score(char* Username , int Score) {
	FILE* File = fopen("User_Data.txt" , "r+") ;
	char input[100] ;
	while ( fscanf(File , "%s" , input) != EOF ) {
		if ( !strcmp(Username , input) ) {
			fprintf(File , "\n%d\n" , Score) ;
			break ;
		}
	}
	fclose(File) ;
	return ;
}

void Signup(char* Username) {
	// adds new user to User_Data.txt with score 0
	FILE* Output_File = fopen("User_Data.txt" , "a") ;
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
	if ( !strcmp(Username , "Bot") ) {
		printf("\e[1;31m") , printf("Username cannot be \"Bot\"\n") , printf("\e[0m") ;
		return Signin() ;
	}
	for ( int i = 0 ; i < strlen(Username) ; i ++ )
		if ( Username[i] == ' ' ) {
			printf("\e[1;31m") , printf("Username Cannot Contain Spaces\n") , printf("\e[0m") ;
			return Signin() ;
		}
	user Current_User ;
	if ( User_Score(Username) != -1 ) {
		Current_User.Score = User_Score(Username) ;
		Current_User.Cur_Score = 0 ;
		strcpy(Current_User.Username , Username) ;
		printf("\e[1;35m") , printf("Login Successful !\n") , printf("\e[0m") ;
	}
	else {
		Signup(Username) ;
		Current_User.Score = 0 ;
		Current_User.Cur_Score = 0 ;
		strcpy(Current_User.Username , Username) ;
		printf("\e[1;35m") , printf("New User Created !\n") , printf("\e[0m") ;
	}
		
	return Current_User ;
}

user Signin_bot(void) {
	char Username[100] ;
	strcpy(Username , "Bot") ;
	user Bot ;
	if ( User_Score(Username) == -1 )
		Signup("Bot") ;
	Bot.Score = 0 ;
	Bot.Cur_Score = 0 ;
	strcpy(Bot.Username , Username) ;
	return Bot ;
}

void Scoreboard(void) {
	FILE* Input_File = fopen("User_Data.txt" , "r") ;
	int it = 0 ;
	user User[100] ;
	char Player[100] , Score[100] ;
	while ( fscanf(Input_File , "%s" , Player) != EOF ) {
		fscanf(Input_File , "%s\n" , Score) ;
		strcpy(User[it].Username , Player) ;
		User[it].Score = Str_int(Score) ;
		it ++ ;
	}
	for ( int i = 0 ; i < it ; i ++ )
		for ( int j = i + 1 ; j < it ; j ++ )
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
	Input_File = fopen("User_Data.txt" , "r") ;
	printf("\e[1;31m") ;
	printf("#####################################################\n") ;
	while ( fscanf(Input_File , "%s" , Player) != EOF ) {
		fscanf(Input_File , "%s\n" , Score) ;
		printf("Player : %s / Score : %s\n" , Player , Score) ;
	}
	printf("#####################################################\n") ;
	printf("\e[0m") ;
	fclose(Input_File) ;
	return ;
}
