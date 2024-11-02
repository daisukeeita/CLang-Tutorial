/*
 * Challenge: Array Manipulation and Analysis
 *
 * Write a C program that does the following:
 *
 * 1. Read the sequence of Numbers:
 *  - Prompt the user to enter a series of integers (positive or negative),
 * ending with zero to signal the end of input
 *  - Store these integers to an array
 *
 * 2. Calculate and Display
 *  - The sum and average of the entered numbers
 *  - The smallest and largest numbers in the array
 *  - The count of even and odd numbers
 *
 * 3. Reverse the array
 *  - Print the numbers in reverse order
 *
 * 4. Extra Challenge (Optional)
 *  - Sort the array in acending order and display it
 *
 * Tips:
 *  - Think about how you'll handle an unknown number of inputs. You might need
 * to start with a fixed sized array or dynamically handle input until reaching
 * a limit.
 *  - Be mindful of boundary cases, like if only a single integer is entered
 * before zero.
 *  - Remember to validate inputs and check array bounds if you choose a fixed
 * size.
 */

/*
 * [x] Initiate an array
 * [x] Read the input and store it in an array
 *
 * [x] Validate User Input to only Integers
 *
 * [x] Get the sum and all the numbers in the array
 * [x] Get the average of the array
 * [x] Get the smallest number inside of the array
 * [x] Get the largest number inside of the array
 * [x] Count how many even numbers inside the array
 * [x] Count how many odd numbers inside the array
 *
 * [x] Print the numbers in reverse
 */

#include <stdio.h>

#define MAX_SIZE 20
#define ARRAY_SIZE (int)(sizeof(arrayOfNumbers) / sizeof(arrayOfNumbers[0]))

int main(void) {
  int arrayOfNumbers[MAX_SIZE] = {0};
  int inputNumber;
  int countEven = 0;
  int countOdd = 0;
  double sumOfAll = 0;
  double count = 0;
  double average = 0.0;
  double lowestInteger = 1;
  double highestInteger = 0;

  printf("Enter a series of ten (20) digits, Positive or Negative. ");
  printf("Enter 0 if you want to end the program.\n");

  for (int i = 0; i < MAX_SIZE; i++) {
    while (1) {
      if (scanf("%d", &inputNumber) == 1) {
        break;
      } else {
        printf("Invalid Input. Please enter a positive or negative integer.\n");
        printf("Enter 0 if you want to end the program.\n");
        while (getchar() != '\n')
          ;
      }
    }

    if (inputNumber == 0) {
      break;
    }

    arrayOfNumbers[i] = inputNumber;
  }

  printf("Entered Numbers: ");

  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (arrayOfNumbers[i] == 0) {
      break;
    } else {
      printf("%d ", arrayOfNumbers[i]);
      count++;
    }

    if (arrayOfNumbers[i] < lowestInteger) {
      lowestInteger = arrayOfNumbers[i];
    }

    if (arrayOfNumbers[i] > highestInteger) {
      highestInteger = arrayOfNumbers[i];
    }

    if (arrayOfNumbers[i] % 2 == 0)
      countEven++;
    else
      countOdd++;

    sumOfAll += arrayOfNumbers[i];
  }

  printf("\n");

  printf("Input Number in Reverse: ");

  for (int i = MAX_SIZE; i >= 0; i--) {
    if (arrayOfNumbers[i] == 0) {
      continue;
    }

    printf("%d ", arrayOfNumbers[i]);
  }

  printf("\n");

  printf("Sum Of All: %.0lf\n", sumOfAll);
  printf("Average Number: %.1lf\n", sumOfAll / count);
  printf("Lowest Number: %.0lf\n", lowestInteger);
  printf("Highest Number: %.0lf\n", highestInteger);
  printf("Count Even: %d\n", countEven);
  printf("Count Odd: %d\n", countOdd);
  return 0;
}
