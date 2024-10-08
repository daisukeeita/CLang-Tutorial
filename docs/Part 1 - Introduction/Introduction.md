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

### CHARACTER SETS

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

## CHAPTER 1 - TUTORIAL INTRODUCTION

### 1.1 Getting Started

The only way to learn a new programming language is by writing programs in it. The first program to write is the same for all languages:

Printing the words `Hello World!`.

In traditional C, the program to print _Hello World!_ is

```C
  main() {
    printf("Hello World!\n");
  }
```

> The Modern minimal version of this program needs a bit more syntax:
>
> ```C
>   #include <stdio.h>
>   main () {
>     printf("Hello World!\n")
>   }
> ```

Just how to run this program, it depends on the system you are using. As a specific example, on the UNIX operating system you must create the source program in a file whose name ends in `.c`, such as _hello.c_ or _main.c_, then compile it with a command:

```
  cc hello.c
```

> On Modern systems, we use `gcc` compiler with the `-ansi` option to accept the "legacy" syntax of C:
>
> ```
>   gcc -ansi hello.c
> ```
>
> To run the resulting `a.out` file, usually you need to pre-pend the local directory because most shell configurations do not include the current path in the paths to search for applications:
>
> ```
>   ./a.out
> ```

---

A C program, whatever its size, consists of one or more "functions" which specify the actual computing operations that are to be done. In the examples above, `main` is such a function. Normally you are at liberty to give functions whatever name you like, but `main` is a special name - your program begins executing at the beginning of the `main`.
This means that every program must have a `main` somewhere. It usually invoke other functions to perform its job, some coming from the same program, and others are from libraries of previously written functions.

The line that says

```
printf("hello, world\n");
```

Is a function call, which calls a function named `printf`, with the arguments `"hello, world\n"`. `printf` is a library function which prints output on the terminal.

### 1.2 Variables and Arithmetic

In C, all variables must be declared before use, usually at the beginning of the function before any executable statements. A declaration consists of a _type_ and a list of variables which have that type:

```C
  int lower, upper, step;
  float fahr, celsius;
```

The type `int` implies that the variables listed are integers; `float` stands for floating point.

C provides several other basic data types besides `int` and `float`:
| **Type** | **Description** |
| --- | ------------ |
| char | character - a single byte |
| short | short integer |
| long | long integer |
| double | double - precision floating point |

The sizes of these objects are also machine-dependent. There are also arrays, structures and unions of these basic types, pointers to them, and functions that return them.

### 1.3 The For Statement

The `for` itself is a loop, a generalization of the `while`.
The choice between `while` and `for` is arbitrary, based on what seems clearer.

> The syntax of the `for` and `while` loops is a feature of C-like languages. In modern language, we tend to have two kinds of loop structures - determinants and indeterminant. The `for` and `while` loop structure are indeterminate because you must read them closely to make sure they are properly constructed and, for example, are not unintentionally "infinite loops".
> An example of a determinant loop is the `foreach` loop in PHP and `for` loop in Python. The semantics of both of these loops is to iterate over all of the elements in a collection. Because collections are not infinite, you can be assured that these determinant loops will not run forever.
