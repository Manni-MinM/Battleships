// HEADER FILE

#define SIZE 15

typedef struct {
	int X , Y ;
} point ;

typedef struct {
	char Board[SIZE][SIZE] ;
} game_board ;

typedef struct {
        point St , En ;
} ship ;

struct NODE {
        ship Battleship ;
        struct NODE* prev ;
        struct NODE* next ;
} ;
typedef struct NODE node ;

typedef struct {
	int Score ;
	char Username[100] ;
	
	node** head ;
	node** tail ;
	
	game_board* Battle_Board ;
	game_board* Shadow_Board ;
} user ;

