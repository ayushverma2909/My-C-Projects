#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>


#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

#define RESET 7
#define PINK 13
#define RED 4
#define GREEN 2
#define BLUE 1
#define YELLOW 14
#define WHITE 15


void setColor(int color){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


typedef struct
{
  char text[MAX_QUES_LEN];
  char options[4][MAX_OPTION_LEN];
  char correct_option;
  int timeout;
  int prize_money;
} Question;


void print_formatted_question(Question question){
  setColor(YELLOW);printf("\n%s", question.text);setColor(RESET);
  setColor(BLUE);
  for(int i = 0; i<4; i++){
    if(question.options[i][0] != '\0'){
      printf("%c. %s", ('A' + i), question.options[i]);
    }
  }
  setColor(RESET);
  setColor(YELLOW);printf("\nHurry!! You have only %d Seconds to answer..\n", question.timeout);setColor(RESET);

  setColor(GREEN);printf("Enter your answer (A, B, C or D) or L for lifeline: ");
  setColor(RESET);
}

int read_questions(char* file_name, Question** questions){
  FILE *file = fopen(file_name, "r");

  if(file == NULL){
    printf("\nUnable to open the question bank.\n");
    exit(0);
  }

  char str[MAX_QUES_LEN];
  int no_of_lines = 0;
  while (fgets(str, MAX_QUES_LEN, file)){
    no_of_lines++;
  }
  int no_of_questions = no_of_lines /8;
  *questions = (Question *)malloc(no_of_questions * sizeof(Question));
   
  rewind(file); 
  for(int i = 0; i<no_of_questions; i++){ // get line no.1 Question
    fgets((*questions)[i].text, MAX_QUES_LEN, file);
    for(int j = 0; j<4; j++){ // get options
      fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);

    }
    char option[10];
    fgets(option, 10, file);
    (*questions)[i].correct_option = option[0];

    char timeout[10];
    fgets(timeout, 10, file);
    (*questions)[i].timeout = atoi(timeout); // atoi string to number

    char prize_money[10];
    fgets(prize_money, 10, file);
    (*questions)[i].prize_money = atoi(prize_money);
  }
  fclose(file);
  return no_of_questions;
}

int use_lifeline(Question* question, int* lifeline){
  char ch;
  setColor(PINK);printf("\nAvailable Lifelines: ");
  if(lifeline[0]) printf("\n1. Fifty-Fifty(50/50)"); 
  if(lifeline[1]) printf("\n2. Skip the question");
  printf("\nChoose a lifeline or 0 to return: ");setColor(RESET); 

  scanf(" %c", &ch);

  switch(ch){
    case '1':
      if(lifeline[0]){
        lifeline[0] = 0;
        int removed = 0;
        while(removed <2){
          char num =(rand()%4);
          if((num + 'A' )!= question->correct_option){
            question->options[num][0] != '\0';
            question->options[num][0] = '\0';
            removed++;
          }

        }
      }
      return 1;
    case '2':
    if(lifeline[1]){
      lifeline[1] = 0;
      return 2;
    }
      break;
    case '0':
      break;
    default:
      printf("\nReturning to the question");
  }
  return 0;
}

void play_game(Question* questions, int no_of_questions){
  int money_won = 0;
  int lifeline[] = {1,1};

  for(int i = 0; i<no_of_questions; i++){
    print_formatted_question(questions[i]);

    char ch = _getch();
    printf("%c", ch);
    ch = toupper(ch);
    while (_getch() != '\r');


    if(ch == 'L'){
      int value = use_lifeline(&questions[i], lifeline);
      if(value != 2){
        i--; 
      }       
      continue;
    }



    if(ch == questions[i].correct_option){
      setColor(GREEN);printf("\nCorrect!");
      money_won = questions[i].prize_money;
     setColor(BLUE); printf("\nYou have won: Rs. %d.\n", money_won);setColor(RESET);
    } else{
      setColor(RED);printf("\n\nWrong! Correct answer is %c", questions[i].correct_option);setColor(RESET);
      break;
    }
  }
  setColor(BLUE);printf("\nGame Over! Your total winnings are: Rs.%d\n", money_won);setColor(RESET);
}



int main(){
  srand(time(NULL));
  setColor(PINK);
  printf("\n\t           KAUN BANEGA COROEPATI !!!\n");
  setColor(RESET);

int blink = 1;
while (1) {  // Infinite loop until Enter is detected
    printf("\r%s", blink ? "Press ENTER key to start..  " : "                           ");
    blink = !blink;  
    fflush(stdout);  // Ensure immediate printing
    Sleep(700);

    // Check if a key is pressed
    if (_kbhit()) {
        // Read the key but only break if it's Enter
        if (_getch() == '\r') break;
    }
}

// Clear the message completely
printf("\r                           \n");

  Question* questions;
  int no_of_questions = read_questions("question.txt",&questions);
  play_game(questions, no_of_questions);

}
