#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int difficulty;

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
int PlayerWon ;
int computerwon;
int draw;

} Score; 

Score score = {.PlayerWon = 0, .computerwon = 0, .draw = 0};

void clear_screen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]){
  clear_screen();
  printf("\nScore - Player X: %d, Computer : %d, Draws: %d", score.PlayerWon, score.computerwon, score.draw);

  printf("\nTIC-TAC-TOE\n");
  
  for(int i = 0; i<BOARD_SIZE; i++){
    printf("\n");
    for(int j = 0; j<BOARD_SIZE; j++){
      printf(" %c ", board[i][j]);
      if(j<BOARD_SIZE - 1){
        printf("|");
      }
    }
    if(i<BOARD_SIZE -1){
      printf("\n---+---+---");
    }
  }
  printf("\n");
}

int print_menu(){
  while(1){
    printf("\nSelect Difficulty Level: ");
    printf("\n1. Human (standard)");
    printf("\n2. God (Impossible to win)");
    printf("\nEnter your choice: ");
    scanf("%d", &difficulty); 

    if(difficulty != 1 && difficulty != 2){
      printf("\nIncorrect choice enter (1/2): ");
    } else{
      break;
    }
  }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player){
  for(int i = 0; i<BOARD_SIZE; i++){ 
    if(board[i][0] == player && board[i][1] == player && board[i][2] == player){ 
      print_board(board); // Checking if in same row only one player is present
      return 1;                  
    }
    if(board[0][i] == player && board[1][i] == player && board[2][i] == player){// Checking if in same column only one player is present
      print_board(board);
      return 1;                  
    }
    if((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player )){
      return 1; // checking diagonal
    }
  }
  return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]){
  for(int i = 0; i<BOARD_SIZE; i++){
    for(int j = 0; j<BOARD_SIZE ; j ++){
      if(board[i][j] == ' '){
        return 0;
      }
    }
  }
  return 1;
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int column){
  return !(row<0 || column <0 || 
           row>2 || column >2 || 
           board[row][column] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]){
  int row, column;
  do{
    printf("\nPlayer X's turn\n");
    printf("\nEnter row and column(1-3): for X: ");
    scanf("%d", &row);
    scanf("%d", &column);

    row--; column --;
  } while(!is_valid_move(board, row, column));
  board[row][column] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]){
  // 1. Play for Immediate win
  for(int i = 0; i<BOARD_SIZE; i++){
    for(int j = 0; j< BOARD_SIZE; j++){
      if(board[i][j] == ' '){
        board[i][j] = O;
        if(check_win(board, X)){
          return;
        }
        board[i][j] = ' ';
      }
    }
  }  

  // 3. God mode
  if(difficulty == 2){
    // play center if available
    if(board[1][1] == ' '){
      board[1][1] = O;
      return;
    }
  }

  // Play corner if available
  int corner[4][2] = {
    {0,0},
    {0,2},
    {2,0},
    {2,2}
  };
  for(int i = 0; i<4; i++){
    if( board[corner[i][0]][corner[i][1]] == ' '){
      board[corner[i][0]][corner[i][1]] = O;
      return;
    }
  }



  // 2. play for Immediate Block
  for(int i = 0; i<BOARD_SIZE; i++){
    for(int j = 0; j< BOARD_SIZE; j++){
      if(board[i][j] == ' '){
        board[i][j] = X;
        if(check_win(board, X)){
          board[i][j] = O;
          return;
        }
        board[i][j] = ' ';
      }
    }
  } 

  // 5. Play first available move
  for(int i = 0; i<BOARD_SIZE; i++){
    for(int j = 0; j< BOARD_SIZE; j++){
      if(board[i][j] == ' '){
        board[i][j] = O;
        return;
      }
    }
  } 

  
}

void play_game(){
  char board [BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };

  char current_player = rand()% 2 == 0? X : O;
 
  print_board(board); 
  while(1){

    if(current_player == X){
      player_move(board);
      print_board(board);
      if(check_win(board, X)){
        score.PlayerWon++;
        print_board(board);
        printf("Congrats! Player X wins.\n");
        break;
      }
      current_player = O;
    } else{
      computer_move(board);
      print_board(board);
      if(check_win(board, O)){
        score.computerwon++;
        print_board(board);
        printf("I won!! but you played well...");
        break;
      }
      current_player = X;
    }
    
    if(check_draw(board)){
      score.draw++;
      print_board(board);
      printf("\nIts a draw!\n");
      break;
    }
  } 
    
}  






int main(){
  srand(time(NULL));
  int choice;
  print_menu();
  
  do{
    play_game();
    printf("\nPlay again? (1 for yes 0 for no): ");
    scanf("%d", &choice);
  } while(choice ==1);

  printf("\nBye-Bye.. Thanks for playing!!\n\n");
}