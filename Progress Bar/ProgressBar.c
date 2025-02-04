#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

const int BAR_LENGTH  = 20;
const int MAX_TASKS =  5;

typedef struct {
  int id;
  int progress;
  int step;
} Task;

void print_bar(Task task){
  int bars_to_show = (task.progress * BAR_LENGTH) / 100 ;
  printf("\nTask %d: [", task.id);

  for (int i = 0; i<BAR_LENGTH; i++){
    if(i<bars_to_show){
      printf("=");
    } else{
      printf(" ");
    }
  }
  printf("] %d %%\n", task.progress);

}

void clear_screen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

int main(){
  srand(time(NULL));            
  Task tasks[MAX_TASKS];

  for(int i = 0; i<MAX_TASKS; i++){
    tasks[i].id = i + 1;
    tasks[i].progress = 0;
    tasks[i].step = rand() % 5 +1;
  }
   
  int tasks_incomplete = 1;
  while(tasks_incomplete){
    tasks_incomplete = 0;
    clear_screen();
    for(int i = 0; i<MAX_TASKS; i++){
      tasks[i].progress += tasks[i].step;
      if(tasks[i].progress >100){
        tasks[i].progress =  100;
      } 
      if(tasks[i].progress <100){
        tasks_incomplete = 1;
      }
      print_bar(tasks[i]);
    }
    sleep(1);
  }
  printf("All tasks completed! \n");
  return 0;          
}