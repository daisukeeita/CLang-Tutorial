/*
 * Challenge: Write a C program that prompts the user for their name, age, and
 * height (in meters). Store these values in appropriate variables and then
 * print them in a formatted manner.
 */

#include <stdio.h>

#define MAX_CHARACTER 100

int main(void) {
  char name[MAX_CHARACTER];
  int age;
  float height;

  printf("Please enter you Name: ");
  scanf("%[^\n]", name); // Reads full name including spaces

  printf(("Please enter your age: "));
  if (scanf("%d", &age) != 1) {
    printf("Invalid input for age.\n");
    return 1; // Exit with an error code.
  }

  printf("Please enter your height in meters: ");
  if (scanf("%f", &height) != 1) {
    printf("Invalid input for height.\n ");
    return 1; // Exit with an error code.
  }

  printf("Here are your details: \n Name: %s\n Age: %d\n Height: %.2f\n", name,
         age, height);

  return 0;
}
