/*
 * Challenge: Write a program that checks if a number entered by the user is
 * even or odd. If the number is even, print "The number is even." Otherwise,
 * print "The number is odd."
 */

#include <stdio.h>

int main(void) {
  int number;

  printf("Please put a number: ");
  if (scanf("%d", &number) != 1) {
    printf("Not a valid input for number\n");
    return 1;
  }

  if (number % 2 != 0) {
    printf("This number is odd: %d\n", number);
  } else {
    printf("This number is even: %d\n", number);
  }

  return 0;
}
