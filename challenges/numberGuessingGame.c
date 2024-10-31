/*
 * Topics: Loops, Input/Output, Conditional Statements, Basic Types
 * Challenge: Write a program where the computer randomly selects a number
 * between 1 and 100, and the user has to guess the number.
 *  - The program should give feedback: "too high" or "too low"
 *  - If the user gueses correctly, congratulate them and exit
 *  - Limit the number of guesses (e.g., 7 guesses)
 *  - Use `rand()` and `srand()` to generate random numbers
 */

/*
 * Problem 1: How to set up the range of random numbers?
 * Problem 2: How to make user input multiple values until the limit?
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_NUMBER 1
#define MAX_NUMBER 100
#define NUM_TRIES 10
#define WARNING 7

int main(void) {
  srand(time(0));

  int guessedNumber;
  int randomNumber = rand() % (MAX_NUMBER + MIN_NUMBER);

  printf("Number: %d\n", randomNumber);

  printf("You have %d tries\n", NUM_TRIES);

  for (int i = 1; i <= 10; i++) {
    printf("Guess a number between 1 and 100: ");
    scanf("%d", &guessedNumber);
    printf("You guessed %d\n", guessedNumber);

    if (guessedNumber == randomNumber) {
      printf("🎊 Congratulations, You guessed the number! 🎊\n");
      return 0;
    }

    if (guessedNumber < randomNumber)
      printf("Too low\n");

    if (guessedNumber > randomNumber)
      printf("Too high\n");

    if (i == WARNING)
      printf("You have 3 tries left\n");

    if (i == 10 && guessedNumber != randomNumber) {
      printf("You lost, please try again... 😢\n");
      break;
    } else if (i == 10 && guessedNumber == randomNumber) {
      printf("🎊 Congratulations, You guessed the number! 🎊\n");
      return 0;
    }
  }

  return 0;
}

/*
 * Upon letting someone review my approach:
 *
 * 1. Asking for srand() and rand() functions - srand() initializes the starting
 * point (or the seed) for rand(). Without the srand(), rand() will generate the
 * same sequence of numbers each time the program runs. Which is why adding
 * srand() with the current time (time(0)) makes a random starting point each
 * time.
 *
 * 2. Asking for clarification of `int = MIN_NUMBER + rand() % (MAX_NUMBER -
MIN_NUMBER + 1)` - rand() % MAX_NUMBER - MIN_NUMBER (100-1) gives a 0 to 98 only
range. That's why `+ 1` is needed to make sure that that maximum number is
included.
 * For the `MIN_NUMBER + rand()`, it is necessary since the minimum number of
rand() is 0. To set it to preferred minimum number, it needs to add to the
preferred number.
 *
 * 3. Loop and termination condition - The limit of the tries can be used in
`for` loops as long as the maximum value of the initial variable under `for`
loop is equal to the number of tries. That way, the conditional statement in the
`for` loop will still execute and won't terminate the program.
 *
 * 4. Improved prompt and Input Validation - I still need to study on how to
handle the error/s it will give whenever the user will input a value outside of
its range, not just terminate the program suddenly.
 *
 * Code given that can be used for improving the approach of the challenge:
 *
 *
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_NUMBER 1
#define MAX_NUMBER 100
#define NUM_TRIES 10
#define WARNING 7

int main(void) {
  srand(time(0));
  int guessedNumber;
  int randomNumber = MIN_NUMBER + rand() % (MAX_NUMBER - MIN_NUMBER + 1);

  printf("You have %d tries\n", NUM_TRIES);

  for (int i = 1; i <= NUM_TRIES; i++) {
    printf("Guess a number between %d and %d: ", MIN_NUMBER, MAX_NUMBER);
    scanf("%d", &guessedNumber);

    if (guessedNumber == randomNumber) {
      printf("🎊 Congratulations, You guessed the number! 🎊\n");
      return 0;
    } else if (guessedNumber < randomNumber) {
      printf("Too low\n");
    } else {
      printf("Too high\n");
    }

    if (i == WARNING)
      printf("Warning: You have only 3 tries left.\n");

    if (i == NUM_TRIES && guessedNumber != randomNumber) {
      printf("You lost, please try again... 😢\n");
    }
  }

  return 0;
}
 */
