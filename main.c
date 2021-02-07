// BWOTSHEWCHB

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Game.h"

#define SIZE 15

void Reset(void) {
	FILE* File = fopen("Saved_Data.bin" , "wb") ;
	int init_val = 0 ;
	fwrite(&init_val , sizeof(int) , 1 , File) ;
	fclose(File) ;
	return ;
}

void Save(user* Player) {
	FILE* File ;
	int it , len = sizeof(Player->Username) ;
	// reads number of users from the file
	File = fopen("Saved_Data.bin" , "rb") ;
	fread(&it , sizeof(int) , 1 , File) ;
	fclose(File) ;
	// adds user data to the file
	File = fopen("Saved_Data.bin" , "ab") ;
	fwrite(&len , sizeof(int) , 1 , File) ;
	fwrite(Player->Username , sizeof(char) , sizeof(Player->Username) , File) ;
	fwrite(&Player->Cur_Score , sizeof(int) , 1 , File) ;
	// add the battleboard to the file
	game_board* Battle_Board = Player->Battle_Board ;
	game_board* Shadow_Board = Player->Shadow_Board ;
	for ( int i = 1 ; i <= 10 ; i ++ )
		for ( int j = 1 ; j <= 10 ; j ++ )
			fwrite(&Battle_Board->Board[i][j] , sizeof(char) , 1 , File) ;
	// add the shadowboard to the file
	for ( int i = 1 ; i <= 10 ; i ++ )
		for ( int j = 1 ; j <= 10 ; j ++ )
			fwrite(&Shadow_Board->Board[i][j] , sizeof(char) , 1 , File) ;
	// add the number of ships left to the file
	int Ship_Cnt = 0 ;
	node* cur = *(Player->head) ;
	while ( cur != NULL )
		Ship_Cnt ++ , cur = cur->next ;
	printf("Ship_Cnt is saved with value : %d\n" , Ship_Cnt) ;
	fwrite(&Ship_Cnt , sizeof(int) , 1 , File) ;
	// add the data for each ship left to file
	cur = *(Player->head) ;
	while ( cur != NULL ) {
		fwrite(&cur->Battleship.St.X , sizeof(int) , 1 , File) ;
		fwrite(&cur->Battleship.En.X , sizeof(int) , 1 , File) ;
		fwrite(&cur->Battleship.St.Y , sizeof(int) , 1 , File) ;
		fwrite(&cur->Battleship.En.Y , sizeof(int) , 1 , File) ;
		cur = cur->next ;
	}
	fclose(File) ;
	// changes number of saved games
	it ++ ;
	File = fopen("Saved_Data.bin" , "r+b") ;
	fwrite(&it , sizeof(int) , 1 , File) ;
	fclose(File) ;
	return ;
}

void Show_games(void) {
	// TODO FIX BUG : showing games and then starting a game results in the game crashing
	FILE* File = fopen("Saved_Data.bin" , "rb") ;
	// read number of players with saved games from file
        int it ;
        fread(&it , sizeof(int) , 1 , File) ;
        printf("number of Games : %d\n" , it / 2) ;
        for ( int i = 0 ; i < it ; i ++ ) {
                char Username[100] ;
                char Battle_Board[15][15] , Shadow_Board[15][15] ;
                int len , Score ;
		// reads user data
                fread(&len , sizeof(int) , 1 , File) ;
                fread(Username , sizeof(char) , len , File) ;
                fread(&Score , sizeof(int) , 1 , File) ;
		// reads user battleboard
                for ( int i = 1 ; i <= 10 ; i ++ )
                        for ( int j = 1 ; j <= 10 ; j ++ )
                                fread(&Battle_Board[i][j] , sizeof(char) , 1 , File) ;
		// reads user shadowboard
                for ( int i = 1 ; i <= 10 ; i ++ )
                        for ( int j = 1 ; j <= 10 ; j ++ )
                                fread(&Shadow_Board[i][j] , sizeof(char) , 1 , File) ;
		// reads number of ships left for user
		int Ship_Cnt ;
		ship Ships[10] ;
		fread(&Ship_Cnt , sizeof(int) , 1 , File) ;
		// reads coordinates for each ship
		for ( int i = 0 ; i < Ship_Cnt ; i ++ ) {
			fread(&Ships[i].St.X , sizeof(int) , 1 , File) ;
                	fread(&Ships[i].En.X , sizeof(int) , 1 , File) ;
                	fread(&Ships[i].St.Y , sizeof(int) , 1 , File) ;
                	fread(&Ships[i].En.Y , sizeof(int) , 1 , File) ;
		}
		// outputs result to terminal
                printf("####################################################\n") ;
                printf("Username : %s / Current Score : %d\n" , Username , Score) ;
                for ( int i = 1 ; i <= 10 ; i ++ ) {
                        for ( int j = 1 ; j <= 10 ; j ++ )
                                printf("%c " , Battle_Board[i][j]) ;
                        printf("\n") ;
                }
		printf("\n") ;
                for ( int i = 1 ; i <= 10 ; i ++ ) {
                        for ( int j = 1 ; j <= 10 ; j ++ )
                                printf("%c " , Shadow_Board[i][j]) ;
                        printf("\n") ;
                }
		printf("\n") ;
		printf("Ship Count : %d\n" , Ship_Cnt) ;
		for ( int i = 0 ; i < Ship_Cnt ; i ++ )
			printf("Ship %d : (%d,%d) (%d,%d)\n" , i + 1 , Ships[i].St.X , Ships[i].St.Y , Ships[i].En.X , Ships[i].En.Y) ;
                printf("####################################################\n") ;
        }
        fclose(File) ;
	return ;
}

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
		printf("\e[4;32m") , printf("Enter The Location You Want Destroyed Or Enter (-1,-1) To Save And Quit\n") , printf("\e[0m") ;
		printf("\e[1;37m") , printf("(i,j) :\n") , printf("\e[0m") ;
		// checks if Di and Dj are valid
		while ( true ) { 
			scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
			if ( Di == -1 && Dj == -1 ) {
				printf("\e[1;31m") , printf("\nYour Progress Has Been Saved!\n\n") , printf("\e[0m") ;
				Save(&Player1) , Save(&Player2) ;
				return ;
			}
			else if ( Di < 1 || Di > 10 || Dj < 1 || Dj > 10 )
				printf("\e[1;31m") , printf("### Invalid Input ###\n") , printf("\e[0m") ;
			else
				break ;
		}
		printf("\n") ;
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
		printf("\e[4;32m") , printf("Enter The Location You Want Destroyed Or Enter (-1,-1) To Save And Quit\n") , printf("\e[0m") ;
		printf("\e[1;37m") , printf("(i,j) :\n") , printf("\e[0m") ;
		// checks if Di and Dj are valid
		while ( true ) { 
			scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
			if ( Di == -1 && Dj == -1 ) {
				printf("\e[1;31m") , printf("\nYour Progress Has Been Saved!\n\n") , printf("\e[0m") ;
				Save(&Player1) , Save(&Player2) ;
				return ;
			}
			else if ( Di < 1 || Di > 10 || Dj < 1 || Dj > 10 )
				printf("\e[1;31m") , printf("### Invalid Input ###\n") , printf("\e[0m") ;
			else
				break ;
		}
		printf("\n") ;
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
		printf("\e[4;32m") , printf("Enter The Location You Want Destroyed Or Enter (-1,-1) To Save And Quit\n") , printf("\e[0m") ;
		printf("\e[1;37m") , printf("(i,j) :\n") , printf("\e[0m") ;
		// checks if Di and Dj are valid
		while ( true ) { 
			scanf("(%d,%d)" , &Di , &Dj) ; getchar() ;
			if ( Di == -1 && Dj == -1 ) {
				printf("\e[1;31m") , printf("\nYour Progress Has Been Saved!\n\n") , printf("\e[0m") ;
				Save(&Player) , Save(&Bot) ;
				return ;
			}
			else if ( Di < 1 || Di > 10 || Dj < 1 || Dj > 10 )
				printf("\e[1;31m") , printf("### Invalid Input ###\n") , printf("\e[0m") ;
			else
				break ;
		}
		printf("\n") ;
		condition = Game_turn(&Player , &Bot , Di , Dj) ;
		if ( condition == 1 ) {
			printf("\e[1;37m") , printf("%s Wins\n\n" , Player.Username) , printf("\e[0m") ;
			Player.Score += Player.Cur_Score ;
			Player.Cur_Score = 0 ;
			break ;
		}
		// TODO make bot smarter :)
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
	printf("4. Reset Saved Data\n") ;
	printf("5. Scoreboard\n") ;
	printf("6. Exit\n") ;
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
		Show_games() ;
		// TODO add load feature to games
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 4 ) {
		// reset saved game data
		Reset() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 5 ) {
		// show the scoreboard
		Scoreboard() ;
		Exit_Code = 0 ;
	}
	else if ( Menu_Input == 6 ) {
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
