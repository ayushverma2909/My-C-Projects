#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGHT 30


typedef struct{
  char username[CREDENTIAL_LENGHT];
  char password[CREDENTIAL_LENGHT];
} user;

user users [MAX_USERS]; //max user can accomodate is 10 in the array 
int user_count = 0; // initially no user

void print_menu(){
    printf("\nWelcome to User Management.\n");
    printf("1. Register.\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Select an option : ");
}

void fix_fgets_input(char* string){//removes \n from the string
  int index = strcspn(string, "\n"); // helps finding the given element
  string[index] = '\0';
}

void input_credentials(char* username, char* password) {
    printf("\nEnter username: ");
    fgets(username, CREDENTIAL_LENGHT, stdin);
    fix_fgets_input(username);

    // change terminal property
    int i = 0;
    printf("Enter Password: ");
    while (i < CREDENTIAL_LENGHT - 1) {
        char ch = _getch(); // reads the character without showing it to screen
        
        if (ch == '\r' || ch == '\n') { // means stop reading after enter key is pressed
            break;
        } else if (ch == '\b') { // if backspace key is pressed
            if (i > 0) { // only delete the character if needed
                i--; // removes the last line
                printf("\b \b"); // move back and print space and overwrite
            }
        } else {
            password[i++] = ch; // store the character
            printf("*");
        }
    }

    password[i] = '\0'; // Null terminate the password string
}

void register_user(){
  if(user_count == MAX_USERS){
    printf("\nMaximum %d users are supported ! No more registrations Allowed!!\n", MAX_USERS);
    return;
  }

  int new_index = user_count;
  printf("\nRegister a new User!\n");

  input_credentials(users[new_index].username, users[new_index].password);
  printf("\nRegistration Successful!\n");

  // save to file
  
  FILE *file = fopen("user.txt", "a");
  
  if(file == NULL){
    return;
  }
  fprintf(file, "%s %s\n", users[new_index].username, users[new_index].password);
  fclose(file);

  user_count++;
}

int login_user(){ //return the existing user
  char username[CREDENTIAL_LENGHT];
  char password[CREDENTIAL_LENGHT];

 

  input_credentials(username, password);

  for(int i = 0; i<user_count; i++){
                 // == 0 means equal
    if(strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) ==0){
      return i;
    }
  }
  return -1;
}

void load_file(){
  FILE *file = fopen("user.txt", "r");

  if(file == NULL){
    return;
  }

  while(fscanf(file, "%s %s", users[user_count].username, users[user_count].password) == 2){
    user_count++;
  }
  fclose(file);
}


int main(){
  load_file();

  int option;
  int user_index;
  while (1){
    print_menu();
    scanf("%d", &option);
    getchar(); // consume extra enter after scanf

    switch (option)
    {
    case 1:
      register_user();
      break;
    case 2:
      user_index = login_user();
      if(user_index >=0){ // means user exist
        printf("\nLogin Successful! Welcome %s!.\n", users[user_index].username);
      } else{ // menas user does not exist
        printf("\nLogin failed! Incorrect username of Password.\n");
      }
      break;
    case 3:
      printf("\nExiting Program!.\n");
      return 0;
      break;
    default:
      printf("Invalid option, Please enter a valid option.\n");
      break;
    }
  }
}