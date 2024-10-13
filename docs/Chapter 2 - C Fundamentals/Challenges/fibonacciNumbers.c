/*
 * Challenge: Implement a program that prints the first 10 Fibonacci Numbers.
 * Use a loop to calculate and display the series.
 */

#include <stdio.h>

#define NUMBER 10

int main(void) {
  int first = 0;
  int second = 1;
  int next;

  for (int i = 0; i < NUMBER; i++) {
    if (i <= 1) {
      next = i;
    } else {
      next = first + second;
      first = second;
      second = next;
    }

    printf("Fibonacci Number: %d\n", next);
  }

  return 0;
}
