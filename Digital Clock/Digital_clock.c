#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //has a sleep function that can lead to program sleep for that duration you want.

void fill_time(char* buffer, size_t buffer_size, int choice){
  time_t raw_time;
  struct tm *current_time;
  time(&raw_time);
  current_time = localtime(&raw_time);

  if(choice == 1){
    strftime(buffer, buffer_size, "%H : %M : %S ", current_time);
  } else{
    strftime(buffer, buffer_size, "%I : %M : %S %p", current_time);
  }
}

void input_format(){
  printf("\nChose the Time format: \n");
  printf("\n1. 24 Hours format \n");
  printf("2. 12 Hours fromat (default) \n");
  printf("Make a Choice (1/2) :");
}

void fill_date(char* buffer, size_t buffer_size){
  time_t raw_time;
  struct tm *current_time;
  time(&raw_time);

  current_time = localtime(&raw_time);
  
  strftime(buffer, buffer_size, "%A  %B  %d %Y ", current_time);

}

void clear_scren(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

int main(){
  int choice;
  input_format();
  scanf("%d", &choice);

  char date[100];
  char time[50]; 
  
  while(1){
    fill_time(time, sizeof(time), choice);
    fill_date(date, sizeof(date));
    clear_scren();
    printf("\nCurrent Time : %s\n", time);    
    printf("Date : %s\n", date);
    sleep(1);
  }
  return 0;
}