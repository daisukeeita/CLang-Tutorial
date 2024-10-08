# INTRODUCTION TO C LANGUAGE

### Outline of the Book

---

- Chapter 1 to 4
  - Programming Language Syntaxes
  - Arrays, Strings and the weird fact that strings are character Arrays
- Chapter 5 - Pointers and Arrays
- Chapter 6 - Structures
- Chapter 7 - 8
  - Detailed C Features

---

> _Just a quick look:_
>
> #### Character Arrays
>
> It must be carefully understand the "size" of the character array and not exceed it - in C Language, nothing is "auto-extended"
>
> ```C
>   #include <stdio.h>
>   int main() {
>     char x[10];
>     int i;
>
>     for (i=0; i<1000; i++) x[i] = '*';
>     printf("%s\n", x);
>   }
>
>   // Output when calling the file
>   $ a.out
>   Segmentation fault: 11
> ```
>
> For more information, research about the "Buffer Overrun Errors"

## STRING / CHARACTER CONSTANTS

Languages like PHP, Python, and JavaScript treat single and double quotes nearly the same. Both create `string` constants.

In C Language, single quotes are a character and double quotes are a character array. _Neither of them are string_.
A character is a byte - a short, typically 8-bit, integer.

```C
  int main() {
    char x[3] = "Hi";
    char y[3] = {'H', 'i'};
    printf("x %s\n", x);
    printf("y %s\n", y);
    printf("%s\n", "Hi");
    printf("%c%c\n", 'H', 'i');
  }

  // Output when calling the file
  $ a.out
  x Hi
  y Hi
  Hi
  Hi
```

## CHARACTER SETS

The C `char` type is just a number - character representations depend on the character set.
Modern characters including ☺️ are represented in multi-byte sequences using Unicode nad UTF-8, but in 1978 we used ASCII and other character sets.

```C
  #include <stdio.h>
  int main () {
    printf("%c %d\n", 'A', 'A');
  }

  // Output when calling the file
  $ a.out
  A 65
```

> Do understand that in C, everytime that you see a single quote character `'a'` think of it as an integer or a number that happens to be conveniently looked up for you by the C Compiler.

### Terminating a String

The size of a `string` stored in a C `array` is not the length of the array.
C uses a special character '\0' that "marks" the string end by convention.

Character arrays need to allocate an extra byte to store the line-end character.

### String length

In C, string `length` must be computed in a loop that scans for a zero character.
Then, the `strlen()` function in `<string.h>` computes string length.

```C
  #include <stdio.h>
  int main() {
    char x[] = "Hello";
    int py_len();
    printf("%s %d\n", x, py_len(x));
  }
  int py_len(self)
    char self[];
  {
    int i;
    for (i = 0; self[i]; i++);
    return i;
  }

  // Output when calling the file
  $ a.out
  Hello 5
```
