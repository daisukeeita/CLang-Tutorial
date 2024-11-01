/*
 * Topics: Loops, Conditional Statements, Input/Output
 * Challenge: Write a program that asks the user to input an integer and then
 * calculates the sum of its digits.
 *  - Example: If the user enter 345, the program should output `12` (3 + 4 + 5
 * = 12)
 *  - Handle both positive and negative
 */

/*
 * A method of getting the last digit of a number:
 * Using the modulus operator
 * 1234 % 10 = 4
 * 1234 / 10 = 123.4
 */

#include <stdio.h>

int main(void) {
  int givenNumber;
  int sum = 0;

  printf("Please enter a number, this will sum of its digits.\n");
  scanf("%d", &givenNumber);

  while (givenNumber != 0) {
    sum += givenNumber % 10; /* This will take the last digit of the number and
                                add to the current value of sum */

    givenNumber = givenNumber / 10; /* This will remove the last digit of the
                                       number that was used to the sum */

    printf("Given Number: %d, Sum Number: %d\n", givenNumber, sum);
  }

  printf("%d\n", sum);

  return 0;
}

/*
 * Upon asking for someone to review the code:
 *
 * 1. Input Validation : Currently, if the user enters a negative number, the
program will calculate the sum of its digits as if it is positive, without
handling the sign.
 * If the intention is to use positive integers only, add a quick checking to
guide the user.
 *
 * 2. Output Clarity: If it is for debugging, the output of the sum of each step
is okay. But if its final, you need to remove that part and print only the final
sum for the users.
 *
 * ```
 * #include <stdio.h>

int main(void) {
    int givenNumber;
    int sum = 0;

    printf("Please enter a positive integer to sum its digits: ");
    if (scanf("%d", &givenNumber) != 1 || givenNumber < 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    while (givenNumber != 0) {
        sum += givenNumber % 10;  // Add the last digit to the sum
        givenNumber /= 10;         // Remove the last digit
    }

    printf("The sum of the digits is: %d\n", sum);

    return 0;
}

 * ```
 */
