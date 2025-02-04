#include <stdio.h>

int puzzle[9][9] = {

  {0,0,3,2,4,0,0,0,0},
  {2,5,0,0,0,3,1,0,7},
  {6,0,7,1,0,0,0,0,0},
  {0,3,8,0,0,0,0,0,0},
  {0,0,2,0,0,8,7,3,0},
  {4,0,0,0,1,2,0,8,5},
  {0,0,5,7,0,0,0,0,6},
  {0,0,6,0,0,9,8,0,0},
  {0,9,1,0,2,0,0,0,0},

};

void print_puzzle(int puzzle[9][9]){
  
  printf("\n+-------+-------+-------+");
  for(int row =0; row<9;row++){
    if(row % 3 == 0 && row !=0){
      printf("\n|-------+-------+-------|");
    }
    printf("\n");
    for(int column = 0; column<9; column++){
      if(column %3 == 0){
        printf("| ");
      }
      if(puzzle[row][column] !=0){
        printf("%d ", puzzle[row][column]);
      }else{
        printf("  ");
      }
    }
    printf("|");
  }
  printf("\n+-------+-------+-------+\n");
}

int valid_move(int puzzle[9][9], int row, int column, int val){

  for(int i = 0; i<9; i++){
    if(puzzle[row][i] == val){
      return 0;
    }
  }

  for(int i = 0; i<9; i++){
    if(puzzle[i][column] == val){
      return 0;
    }
  }

  int r = row - row%3;
  int c = column - column %3;

  for(int i =0; i<3; i++){
    for(int j = 0; j<3; j++){
      if(puzzle[r+i][c+j] == val){
        return 0;
      }
    }
  }
  return 1;
}

int solve_puzzle(int puzzle[9][9], int row, int column){
   

  if(column == 9){
    if(row == 8){
    return 1; // Puzzle solved
    }
    row++;
    column =0;
  }

  if(puzzle[row][column]>0){
    return solve_puzzle(puzzle, row,column +1);
  }

  for(int i =1; i<=9; i++){
    if(valid_move(puzzle, row,column,i)){
      puzzle[row][column] = i;
      if(solve_puzzle(puzzle,row,column +1)){
        return 1;
      }
      puzzle[row][column] = 0;
    }
  }
  return 0;
}

int main(){
  printf("\n________________________________________________________\n");
  printf("               Welcome to SUDOKU Solver !!!\n\n");
  printf("Original Puzzle: ");
  print_puzzle(puzzle);

  if(solve_puzzle(puzzle, 0,0)){
    printf("\nThe puzzle is solved: \n");
    print_puzzle(puzzle);
  } else {
    printf("\nThis puzzle cannot be solved.\n");
  }
  
}