#include <stdio.h>
#include <stdlib.h>
#include <time.h>
        
int main(){
  int guess, random, no_of_guess = 0;
  srand(time(NULL));

  printf("\nWelcome to the world of guessing Numbers.\n");
  random = rand() %100 +1;           
  do{
    printf("\nPlease enter your guess between(1 to 100): ");
    scanf("%d", &guess);  
    no_of_guess ++;

    if(guess<random){
      printf("Guess a larger number. \n");
    } else if(guess > random){
      printf("Guess a smaller number. \n");
    } else{
      printf("Congratulations!!! You have successfully guessed the correct number in %d attempts.  \n", no_of_guess);
    }
    

  } while( guess != random);
  printf("\n Bye Bye, Thanks for Playing the game.");
  printf("\n Game developed by Ayush Verma.\n");

  return 0;
}