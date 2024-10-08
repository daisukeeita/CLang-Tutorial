#include <stdio.h>
#include <string.h>

// FIRST EXCERCISE - REVERSE A STRING
#define MAX_SIZE 100

int main() {
  char text[MAX_SIZE];
  char reverseText[MAX_SIZE];
  int i;
  int j;

  printf("Enter your word: ");
  scanf("%s", text);

  for (i = 0, j = strlen(text) - 1; text[i] != '\0'; i++) {
    reverseText[i] = text[j];
    j--;

    printf("Text: %c, ReverseText: %c\n", text[i], reverseText[i]);
  }

  reverseText[i] = '\0';
  printf("Last: %c\n", text[strlen(text) - 1]);
  printf("Text: %s\n", text);
  printf("Reverse: %s\n", reverseText);

  return 0;
}
/*
 * This is my solution to the first excercise - reverse a string
 */
