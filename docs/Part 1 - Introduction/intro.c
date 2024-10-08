#include <stdio.h>
#include <string.h>

// FIRST EXCERCISE - REVERSE A STRING
int main() {
  char text[] = "Hello World";
  char copy[20];
  int j = 0;

  for (int i = strlen(text); i > 0; i--) {
    copy[++j] = text[i];

    printf("Text: %c, Copy: %c\n", text[i], copy[j]);
  }

  printf("Copy: %s\n", copy);
  return 0;
}
