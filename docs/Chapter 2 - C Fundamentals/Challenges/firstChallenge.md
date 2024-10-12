# Basic Data Types and Variables

**Challenge**: Write a C Program that prompts the user for their name, age, and height in meters. Store these values in appropriate variables and then print them in a formatted manner.

My initial solution to the problem:

```c
  #include <stdio.h>

  #define MAX_CHARACTER 100

  int main(void) {
    char name[MAX_CHARACTER];
    int age;
    float height;

    printf("Please enter you Name: ");
    scanf("%[^\n]s", name);

    printf(("Please enter your age: "));
    scanf("%d", &age);

    printf("Please enter your height: ");
    scanf("%f", &height);

    printf("Here are your details: \n Name: %s\n Age: %d\n Height: %.4f\n", name,
          age, height);

    return 0;
  }
```

First problem I got - How to read the input of a user that will include the space?

Because the `scanf("%s", name)` will only read the first string. As an example:

```c
  scanf("%s", name); // user input: Hello World

  printf("%s\n", name); // name output: Hello
```

Upon researching on how to read the inputs of a user, including the spaces, I got the answer to the problem:

Resource/s:
[GeeksforGeeks - Format Specifier in C](https://www.geeksforgeeks.org/format-specifiers-in-c/)
[GeeksforGeeks - Scansets in C](https://www.geeksforgeeks.org/scansets-in-c/)

The `scanf()` function supports the scanset specifier which represented by `%[]`. Inside the scanset, you can specify a single character or a range of characters. `scanf()` will process only those characters which are part of scanset.

Please take note that scansets are case-sensitive.

If the first character of scanset is `^`, then the specifier will stop reading after the first occurrence of that character.

```c
  scanf("%[^\n]", name);
```

This way, the `scanf()` will put the array of characters to the `name` variable, including the space (or whitespace character).

After solving the problem, I ask ChatGPT to analyze my answer to the problem.

These are the improvements it suggested:

- **Minor Correction/s**: In my `scanf()`for the name, I have unnecessary `s` in the format specifier. It should be:

```c
 scanf("%[^\n]", name):
```

- **Input Validation**: It is a good practice to check the return value of the `scanf()` to ensure that the input was successful. This prevents issues if the user enters unexpected data.

```c
 if (scanf("%d", &age) != 1) {
   printf("Invalid input for age.\n");
   return 1;
 }
```

- **Clearer Output Messages**: Consider making the output message a bit clearer. For instance, specify the units when asking for height:

```c
  printf("Please enter your height in meters: ");
```

- **Code Readability**: I can improve readability by adding some comments explaining the different parts of your code. This is especially useful as I progress the work with more complex code.
- **Formatting**: When printing the height, I might want to consider how many decimal places are appropriate. Using `%.2f` instead of `%.4f` might be more standard for height.

Upon reading the suggestions, I got to another problem - Input Validation (P.S. I'm not reading carefully at all ○( ＾皿＾)っ Hehehe…).

I understand that if a user typed a letter instead of a number, it'll return an error. What I can't wrap around my head is that why is it accepting the values lower than and greater than `1` if the logic is `scanf("%d", &age) != 1`.

And here's what I learned:

`scanf()` have return values, and that is `1`, `0`, and `-1` or `EOF`.
**1**: successfully reads an integer (assuming that the specifier is "%d")
**0**: failed to read an integer (if the user inputs a letter, for example)
**-1**: an error occurred (End of File)

What `scanf()`'s returning is like `true` or `false` sequence; or `success` or `fail` as analogy.

So `(scanf("%d", age) != 1)` can be used as a logic for input validation.

Another thing upon reading from the explanation:

The return statement inside if-block has the same concept as the main-block function:
`return 0`: it indicates that the program executed successfully without any errors
`return 1`: it indicates there is an error or that something went wrong during execution

So if I use `return 1;` inside the if-block after checking the `scanf()` return value, I'm giving a signal that the execution inside the if-block encountered an error (input value, for example).

```c
  if (scanf("%d", age) != 1) {
    printf("Invalid input for age!");
    return 1;
  }
```

Final code for the challenge (considering my approach and solution to this challenge):

```c
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
```
