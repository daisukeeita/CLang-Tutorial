# Conditional Statements

**Challenge**: Write a program that checks if a number entered by the user is even or odd. If the number is even, print "The number is even". Otherwise, print "The number is odd".

My initial solution to the problem:

```c
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
```

Improvements Suggested:

- **Use Consistent Output Messages**: The output for odd and even numbers could be made more uniform.
- **Handling Edge Cases**: Consider handling other types of input that might not be integers.
- **Formatting**: I might want to add a newline after the final output for better formatting in the terminal.
- **Functional Decomposition**: For larger programs, I might want to consider separating the logic into functions.
