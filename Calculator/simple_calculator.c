#include <stdio.h>
#include <math.h>

void print_menu()
{
  printf("\n---------------------\n");
  printf("Welcome to Simple Calculator\n");
  printf("\n1. Add\n");
  printf("2. Subtraact\n");
  printf("3. Multiply\n");
  printf("4. Division\n");
  printf("5. Modulo\n");
  printf("6. Power\n");
  printf("7. Exit\n");

  printf("Please enter your choice: ");
}

float power(float a, float b)
{
  if (a == 0)
  {
    printf("\nPlease enter a valid operator.\n");
  }
  else
  {
    printf("\n%.2f raised to the power %.2f is : %.2f", a, b, pow(a, b));
  }
  return 0;
}

float division(float a, float b)
{
  if (b == 0)
  {
    printf("\nInvalid operator, cannot divide by 0.\n");
  }
  else
  {
    printf("%.2f divided by %.2f id %.2f", a, b, a / b);
  }
  return 0;
}

float modulo(float a, float b)
{
  if (b == 0)
  {
    printf("\nInvalid operator, cannot find remainder while dividing by 0.\n");
  }
  else
  {
    printf("%.2f when divided by %.2f leaves the remainder %.2f", a, b, a / b);
  }
  return 0;
}

int main()
{
  int choice;
  double num1, num2, result;
  do
  {
    print_menu();
    scanf("%d", &choice);
    if (choice > 7 || choice <1)
    {
      printf("Please enter a valid choice(1-7).\n");
      break;
    }

    printf("\nPlease enter the first number: ");
    scanf("%lf", &num1);
    printf("Now, enter the second number: ");
    scanf("%lf", &num2);
    switch (choice)
    {
    case 1:
      result = num1 + num2;
      printf("The result is : %lf\n", result);
      break;
    case 2:
      result = num1 - num2;
      printf("The result is : %lf\n", result);
      break;
    case 3:
      result = num1 * num2;
      printf("The result is : %.2lf\n", result);
      break;
    case 4:
      division(num1, num2);
      break;
    case 5:
      modulo(num1, num2);
      break;
    case 6:
      power(num1, num2);
      break;

    default:
      printf("Please enter a valid operator.\n");
      break;
    }

  } while (choice != 7);
  return 0;
}