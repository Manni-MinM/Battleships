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
	fwrite(&Player->Turn , sizeof(int) , 1 , File) ;
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
	while ( cur != NULL ) {
		Ship_Cnt ++ ;	
		if ( cur == *(Player->tail) )
			break ;
		cur = cur->next ;
	}
	fwrite(&Ship_Cnt , sizeof(int) , 1 , File) ;
	// add the data for each ship left to file
	cur = *(Player->head) ;
	while ( cur != NULL ) {
		fwrite(&cur->Battleship.St.X , sizeof(int) , 1 , File) ;
		fwrite(&cur->Battleship.En.X , sizeof(int) , 1 , File) ;
		fwrite(&cur->Battleship.St.Y , sizeof(int) , 1 , File) ;
		fwrite(&cur->Battleship.En.Y , sizeof(int) , 1 , File) ;
		// TODO : Fix memory leak here
		if ( cur == *(Player->tail) )
			break ;
		cur = cur->next ;
	}
	fclose(File) ;
	// changes number of saved games
	it ++ ;
	File = fopen("Saved_Data.bin" , "r+b") ;
	fwrite(&it , sizeof(int) , 1 , File) ;
	fclose(File) ;
	// free additional memory
	free(Player->head) ;
	free(Player->tail) ;
	free(Player->Battle_Board) ;
	free(Player->Shadow_Board) ;
	return ;
}

int Show_games(user* Player1 , user* Player2) {
	FILE* File = fopen("Saved_Data.bin" , "rb") ;
	// read number of players with saved games from file
	int it ;
	fread(&it , sizeof(int) , 1 , File) ;
	// build containers for storing data
	ship Ships[it][10] ;
	char Username[it][100] ;
	int Turn[it] ;
	int Ship_Cnt[it] ;
	int Cur_Score[it] ;
	game_board Battle_Board[it] ;
	game_board Shadow_Board[it] ;
	// show the number of games 
	for ( int i = 0 ; i < it ; i ++ ) {
		int len ;
		// reads user data
		fread(&len , sizeof(int) , 1 , File) ;
		fread(Username[i] , sizeof(char) , len , File) ;
		fread(&Cur_Score[i] , sizeof(int) , 1 , File) ;
		fread(&Turn[i] , sizeof(int) , 1 , File) ;
		// reads user battleboard
		for ( int j = 1 ; j <= 10 ; j ++ )
			for ( int k = 1 ; k <= 10 ; k ++ )
				fread(&Battle_Board[i].Board[j][k] , sizeof(char) , 1 , File) ;
		// reads user shadowboard
		for ( int j = 1 ; j <= 10 ; j ++ )
			for ( int k = 1 ; k <= 10 ; k ++ )
				fread(&Shadow_Board[i].Board[j][k] , sizeof(char) , 1 , File) ;
		// reads number of ships left for user
		fread(&Ship_Cnt[i] , sizeof(int) , 1 , File) ;
		// reads coordinates for each ship
		for ( int j = 0 ; j < Ship_Cnt[i] ; j ++ ) {
			fread(&Ships[i][j].St.X , sizeof(int) , 1 , File) ;
			fread(&Ships[i][j].En.X , sizeof(int) , 1 , File) ;
			fread(&Ships[i][j].St.Y , sizeof(int) , 1 , File) ;
			fread(&Ships[i][j].En.Y , sizeof(int) , 1 , File) ;
		}
	}
	fclose(File) ;
	printf("\n") ;
	char Username_Turn[100] ;
	for ( int i = 0 ; i < it / 2 ; i ++ ) {
		if ( Turn[i << 1 | 0] == 1 )
			strcpy(Username_Turn , Username[i << 1 | 0]) ;
		else if ( Turn[i << 1 | 1] == 1 )
			strcpy(Username_Turn , Username[i << 1 | 1]) ;
		printf("\e[3;33m") , printf("Game Number %d) " , i + 1) , printf("\e[0m") ;
		printf("\e[1;34m") , printf("%s VS %s [%s's Turn]\n" , Username[i << 1 | 0] , Username[i << 1 | 1] , Username_Turn) , printf("\e[0m") ;
	}
	printf("\n") ;
	printf("\e[1;35m") , printf("Enter The Number for The Game You Want Loaded or Enter -1 To Return To The Main Menu\n") , printf("\e[0m") ;
	int num ;
	scanf("%d" , &num) , getchar() ;
	if ( num != -1 ) {
		// transfer data to Player1
		num -- ;
		strcpy(Player1->Username , Username[num << 1 | 0]) ;
		Player1->Cur_Score = Cur_Score[num << 1 | 0] ;
		Player1->Turn = Turn[num << 1 | 0] ;
		Player1->Battle_Board = (game_board*)malloc(sizeof(game_board)) ;
		Player1->Shadow_Board = (game_board*)malloc(sizeof(game_board)) ;
		*Player1->Battle_Board = Battle_Board[num << 1 | 0] ;
		*Player1->Shadow_Board = Shadow_Board[num << 1 | 0] ;
		for ( int i = 0 ; i < Ship_Cnt[num << 1 | 0] ; i ++ )
			Player1->Battleship[i] = Ships[num << 1 | 0][i] ;
		for ( int i = Ship_Cnt[num << 1 | 0] ; i < 10 ; i ++ ) {
			Player1->Battleship[i].St.X = -1 , Player1->Battleship[i].St.Y = -1 ;
			Player1->Battleship[i].En.X = -1 , Player1->Battleship[i].En.Y = -1 ;
		}
		// transfer data to Player2
		strcpy(Player2->Username , Username[num << 1 | 1]) ;
		Player2->Cur_Score = Cur_Score[num << 1 | 1] ;
		Player2->Turn = Turn[num << 1 | 1] ;
		Player2->Battle_Board = (game_board*)malloc(sizeof(game_board)) ;
		Player2->Shadow_Board = (game_board*)malloc(sizeof(game_board)) ;
		*Player2->Battle_Board = Battle_Board[num << 1 | 1] ;
		*Player2->Shadow_Board = Shadow_Board[num << 1 | 1] ;
		for ( int i = 0 ; i < Ship_Cnt[num << 1 | 1] ; i ++ )
			Player2->Battleship[i] = Ships[num << 1 | 1][i] ;
		for ( int i = Ship_Cnt[num << 1 | 1] ; i < 10 ; i ++ ) {
			Player2->Battleship[i].St.X = -1 , Player2->Battleship[i].St.Y = -1 ;
			Player2->Battleship[i].En.X = -1 , Player2->Battleship[i].En.Y = -1 ;
		}
		return 1 ;
	}
	return 0 ;
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

		Player1.Turn = 1 , Player2.Turn = 0 ;
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

		Player1.Turn = 0 , Player2.Turn = 1 ;
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
void PVP_load(user* User1 , user* User2) {
	int turn = Game_load(User1 , User2) ;
	user Player1 = *User1 , Player2 = *User2 ;
	while ( true ) {
		int condition , Di , Dj ;

		if ( turn == 1 || turn == -1 ) {
			Player1.Turn = 1 , Player2.Turn = 0 ;
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
			turn = -1 ;
		}
		if ( turn == 2 || turn == -1 ) {
			Player1.Turn = 0 , Player2.Turn = 1 ;
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
			turn = -1 ;
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

		Player.Turn = 1 , Bot.Turn = 0 ;
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
		Player.Turn = 0 , Bot.Turn = 1 ;
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
void PVE_load(user* User1 , user* User2) {
	int turn = Game_load(User1 , User2) ;
	user Player = *User1 , Bot = *User2 ;
	srand(time(0)) ;
	while ( true ) {
		int condition , Di , Dj ;

		if ( turn == 1 || turn == -1 ) {
			Player.Turn = 1 , Bot.Turn = 0 ;
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
			turn = -1 ;
		}
		// TODO make bot smarter :)
		if ( turn == 2 || turn == -1 ) {
			Player.Turn = 0 , Bot.Turn = 1 ;
			Di = (rand() % 10) + 1 , Dj = (rand() % 10) + 1 ;
			condition = Game_turn(&Bot , &Player , Di , Dj) ;
			if ( condition == 1 ) {
				printf("\e[1;37m") , printf("Bot Wins\n\n") , printf("\e[0m") ;
				Player.Score += Player.Cur_Score / 2 ;
				Player.Cur_Score = 0 ;
				break ;
			}
			turn = -1 ;
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
		user* Player1 = (user*)malloc(sizeof(user)) ;
		user* Player2 = (user*)malloc(sizeof(user)) ;
		int condition = Show_games(Player1 , Player2) ;
		if ( condition ) {
			if ( !strcmp(Player2->Username , "Bot") )
				PVE_load(Player1 , Player2) ;
			else
				PVP_load(Player1 , Player2) ;
		}
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
	int it , Elements_Read ;
	FILE* File = fopen("Saved_Data.bin" , "rb") ;
	if ( File == NULL ) {
		// create the file
		File = fopen("Saved_Data.bin" , "wb") ;
	}
	Elements_Read = fread(&it , sizeof(int) , 1 , File) ;
	fclose(File) ;
	if ( Elements_Read == 0 ) {
		// initialize the file
		Reset() ;
	}
	while ( true ) {
		int Exit_Code = Menu() ;
		if ( Exit_Code == 1 )
			break ;
	}
	return 0 ;
}
