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

```C
  for(int i = 0; i < 5; i++) {
    printf("%d\n", i);
  }
```

### 1.4 Symbolic constants

It is bad practice to bury "magic numbers" like 300 and 20 in a program; they convey little information to someone who might have to read the program late, and they are hard to change in a systematic way.
Fortunately, C provided a way to avoid such "magic numbers". With the `#define` construction, at the beginning of a program you can define a symbolic name or symbolic constant to be a particular string of characters.
Thereafter, the compiler will replace all unquoted occurrences of the name by the corresponding string. The replacement for the name can actually be any text at all; it is not limited to numbers.

```C
  #include <stdio.h>

  #define LOWER 0 /* Lower limit of the table */
  #define UPPER 300 /* Upper limit of the table */
  #define STEP 20 /* Step size */

  main() {
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP ) {
      printf("%4d %6.1f\n", fahr, (5.0/9.0)*(fahr - 32));
    }
  }
```

The quantities LOWER, UPPER, and STEP are constants, so they do not appear in declarations. Symbolic names are commonly written in upper case so they can be readily distinguished from lower case variable names. Notice that there is no semicolon at the end of a definition. Since the whole line after the defined name is substituted, there would be too many semicolons in the `for`.

### 1.5 A Collection of Useful Programs

**Character Input and Output**

The standard library provides functions for reading and writing a character at a time. `getchar()` fetches the _next input_ character each time it is called, and returns that character as its value. That is, after `c = getchar()`.
The variable `c` contains the next character of input. The characters normally come from the terminal.

The function `putchar(c)` is the complement of `getchar()`, it prints the contents of variable `c` on some output medium, usually the terminal.

As with `printf()`, there is nothing special about `getchar()` and `putchar()`. They are not part of the C language, but they are universally available.

**File Copying**

Given `getchar()` and `putchar()`, you can write a surprising amoount of useful code without knowing anything more about I/O. The simplest example is a program which copies to its output on character at a time. In outline,

```pseudo-code
  get a character
  while (character is not end file signal)
    output the character just read
    get a new character
```

Converting this into C:

```C
  #include <stdio.h>

  main() {
    int c = getchar();

    while (c != EOF) {
      putchar(c);
      c = getchar();
    }
  }
```

> Modern C compilers define `EOF` in the `stdio.h` include file - so you should never define `EOF` in your code. In modern C, the value of `EOF` is `-1`, but you should just include `stdio.h` and use the pre-defined `EOF` constant to check for end of file.

`c` was also declared to be an `int`, not a `char`, so it can hold the value which `getchar()` returns.

**Character Counting**

The next program counts characters; it is a small elaboration of the copy program.

```C
  #include <stdio.h>
  main() {
    long nc;

    nc = 0;
    while (getchar() != EOF)
      ++nc;

    printf("%ld\n", nc);
  }
```

The character counting program accumulates its count in a `long` variable instead of an `int`. The conversion specification `%ld` signals to `printf()` that the corresponding argument is a long integer.

To cope with even bigger numbers, you can use a `double` (double length `float`). We will also use a `for` statement instead of a `while`, to illustrate and alternative way to write the loop.

```C
  #include <stdio.h>

  main() {
    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
      ;

    printf("%.0f\n", nc);
  }
```

`printf()` uses `%f` for both `float` and `double`; `%.0f` suppresses printing of the non-existent fraction part.

The body of the `for` loop here is _empty_, because all of the work is done in the test and re-initialization parts. But the grammatical rules of C require that a `for` statement have body. The isolated semicolon, technically a _null statement_, is there to satisfy that requirement.

> Observer that if the input contains no characters, the `while` or `for` test failes on the very first call to `getchar()`, and so the program produces zero, the right answer. One of the nice things about `while` and `for` is that they test at the _top_ of the loop, before proceeding with the body. If there is nothing to do, nothing is donw, even if that means never going through the loop body. Programs should act intelligently when handed input like "no characters". The `while` and `for` statements help ensure that they do reasonable things with boundary conditions.

**Line Counting**

The next program counts _lines_ in its input. Input lines are assumed to be terminated by the newline character `\n` that has been religiously appended to every line written out.

```C
  #include <stdio.h>

  main () {
    int c, nl;

    nl = 0;
    while((c = getchar()) != EOF) {
      if (c == '\n') ++nl;
    }

    printf("%d\n", nl);
  }
```

Any single character can be written between single quotes, to produce a value equal to the numerical value of the character in the machine's caracter set; this is called a _character constant_. So, for example, 'A' is a character constant; in the ASCII character set its value is 65, the internal representation of the charater 'A'. Of course 'A' is to be preferred over 65: its meaning is obvious, and it is independent of a particualr character set.

> The numeric values that are shown for characters are using the ASCII character set. character sets in the 1970's were quite intrictate. Most were eight bits long to conserve computer memory and only support 100 or so supported Latin-like characters. This is why early programming languages use special characters like `*` and `{` in their syntax very carefully. They needed to choose characters that were commonly available on computer keyboards from different manufacturers.
>
> Modern languages like Python 3 and Ruby store internal string values using the Unicode character set so they are able to represent all characters in all languages around the world. Modern languages tend to represent eight bit values (range 0 - 256) using a `byte` or similar type.

**Word Counting**

The next program is counting lines, words, and character with the loose definition that a word is any sequence of characters that does not contain a blank, tab, or newline. (This is a bare-bones version of the UNIX utility _wc_).

```C
  #include <stdio.h>

  #define YES 1
  #define NO 0

  main() {
    int c, nl, nw, nc, inword;

    inword = NO;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
      ++nc;
      if (c == '\n') ++nl;
      if (c == ' ' || c == '\n' || c == '\t') inword = NO;
      else if (inword == NO) {
        inword = YES;
        ++nw;
      }
    }

    printf("%d %d %d\n", nl, nw, nc);
  }
```

> The `||` nad `&&` are the norm for boolean operators in "C-like" languages. When a new language was being designed, it was easy to adopt the C conventions for logical operators becuase, while they are cryptic, millions of software developers already were familiar with the operators. In this way, the relationship between C and C-like languages is like the relationsip between Latin and the Romance languages including English.

### 1.6 Arrays

> Understanding the capabilities and limitations of C arrays is one of the most importatnt topics in the historical look at the C Programming Language. Most importantly, the number of elements in an array declaration must be a _constant_ at compile time and the size of an array cannot be adjusted using an array declaration while the program is running.
>
> This inability to automatically resize C arrays as data is added, leads to a class of security flaws that are generally referred to as "buffer overflow" where a program reads more data than can fit into an array and is tricked to overwriting other data or code and compromising an application.
> Later, we will create dynamic array-like structures in C using pointers and the standard library `calloc()` function.
>
> The underlying technique that is used to implement language structures like Python's `list` is dynamic memory allocation and a "linked list" structure. Linked lists are one of the most important data structures in all of Computer Science.

### 1.7 Functions

In C, a _function_ is equivalient to a subrouting or function in Fortran, or a procedure in PL/I, Pascal, etc. A function provides a convenient way to encapsulate some computation in a black box, which can then be used without worrying about its innards. Functions are really the only way to cope withthe potential complexity of large programs. With properly designed functions, it is possible to ignore how a job is dont; knowing what is done is sufficient. C is designed to make the use of functions easy, convenient, and efficient; you will often see a function only a few lines long called only once, just becuase it clarifies some piece of code.

Here is the function `power` and a `main` program to exercise it, so you can see the whole structure at once.

```C
  #include <stdio.h>

  main () {
    int i;

    for (i = 0; i < 10; ++i) printf("%d %d %d\n", i, power(2, i), power(-3, i));
  }

  power (x, n)
  int x, n;
  {
    int i, p;

    p = 1;
    for (i = 1; i <= n; ++i) p = p * x;

    return (p);
  }
```

Each function has the same form:

```pseudo-code
  name (argument list, if any)
  argument declarations, if any
    declarations
    statements
```

The argument declarations go between the argument list and the opening left brace; each declaration is terminated by a semicolon. The names used by `power` for its arguments are purely local to `power`, and not accessible to any other function: other routines can use the same names without conflict. This is also true of the variables `i` and `p`: the `i` in `power` is unrelated to the `i` in `main`.

A function need not return a value; a `return` statement with no expression causes control, but no useful value, to be returned to the caller, as does "falling off the end" of a function by reaching the terminating right brace.

### 1.8 Arguments - Call by Value

In C, all function arguments are passed "by value". This means that the called function is given the values of its arguments in temporary variables (actually on a stack) rather than their addresses. This leads to some different properties that are seen with "call by reference" languages like Fortran nad PL/I, in which the called routine is handed the address of the argument, not its value.

> It may seem strange that the authors are calling so much attention to the fact that arguments are passed "call by value" in the first chapter. Most modern programming languages like Python, PHP, or Java pass in single value arguments "by value" by default and to pass in an argument "by reference", you need to do something special like adding the `&` in the function declaration in PHP.
>
> Passing by reference was the norm before C and passing by value was the norm after C. Since modern languages were deeply influenced by (and often written in) C, passing by value is the norm for modern languages. It is nice because it isolates the data in the calling code from the called code - so the called code can't easily mess with its arguments and create an unexpected side effect (and possibly a bug/security flaw) in the calling code.
>
> It was bit of work to make pass by value work in C. C implements a "call stack" where a bit of memory is allocated at each function call and C makes a copy of the values in the calling code to pass them into the called code in a way that the calling code can see the values and change their local copies without affecting the values in the calling code.

The main distinction is that in C, the called function _cannot_ alter a variable in the calling function; it can only alter its private, temporary copy.

When necessary, it is possible to arrange for a function to modify a variable in a calling routine. The caller must provide the _address_ of the variable to be set (technically a _pointer_ to the variable), and the called function must declare the argument to be a pointer and reference the actual variable indirectly through it.

### 1.9 Character Arrays

> Look at the next two sections as examples of C-syntax with many important concepts about character strings stored as arrays and calling patterns when passing arrays to functions as parameters, but not exactly best practice when handling dynamically sized data.

Probably the most common type of array in C is the array of characters. To illustrate the use of character arrays and functions to manipulate them, let's write a program which reads a set of lines and prints the longest.

```pseudo-code
  while (there's another line)
    if (it's longer than the previous longest)
      save the line and its length
  print the longest line
```

To convert it to C:

```C
  #include <stdio.h>

  #define MAX_CHAR 1000 /* Maximum input line size */

  main() {
    int currentLen;
    int maximumLen;
    char currentLine[MAX_CHAR];
    char maximumLine[MAX_CHAR];

    maximumLen = 0;
    while((currentLen = get_line(currentLine, maximumLine)) > 0) {
      if (currentLen > maximumLen) {
        maximumLen = currentLen;
        copy(currentLine, maximumLine);
      }
    }

    if (maximumLen > 0) printf("%s", maximumLine);
  }

  get_line(s, lim)
  char s[];
  int lim;
  {
    int c, i;

    for (i = 0; i < lim -1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
    if (c == '\n') {
      s[i] = c;
      ++i;
    }

    s[i] = '\0';

    return(i);
  }

  copy(s1, s2)
  char s1[], s2[];
  {
    int i;

    i = 0;
    while ((s2[i] == s1[i]) != '\0') ++i;
  }
```

`get_line()` puts the character `\0` (the null character, whose value is zero) at the end of the array it is creating to mark the end of the string of characters. This convention is also used by the C compiler.

When a constant like `hello\n` is written in C, the compiler creates an array of characters containing the character of the string, and terminates it with a `\0` so that functions such as `printf()` can detect the end.

| h   | e   | l   | l   | o   | \n  | \0  |
| --- | --- | --- | --- | --- | --- | --- |
| 0   | 1   | 2   | 3   | 4   | 5   | 6   |

### 1.10 Scope; External Variables

The variables in `main()` (line, save, etc.) are private or local to `main`: because they are declared within `main()`, no other functions can have direct access to them. The same is true to the other variables declared inside their functions; for example, the variable `i` in `get_line()` is unrelated to the `i` in `copy()`. Each local variable in a routine comes into existence only when the function is called, and _disappears_ when the function is exited.
It is for these reason that such variables are usually known as automatic variables.

Because automatic variables come and go with function invocation, they do not retain their values from one call to the next and must be explicitly set upon each entry. If they are not set, they will contain garbage.

As an alternative to automatic variables, it is possible to define variables which are _external_ to all functions, that is, global variables which can be accessed by name by any functions that cares to. Furthermore, because external variables remain in existence permanently, rather than appearing and disappearing as functions are called and exited, they retain their values even after the functions that set them are done.

An external variable has to be defined outside of any functions; this also allocates actual storage for it. The variable must also be declared in each function that wants to access it; this may done either by an explicit `extern` declaration or implicitly by context.

```C
  #include <stdio.h>

  #define MAXLINE 1000

  char line[MAXLINE];
  char save[MAXLINE];
  int max;

  main () {
    int len;
    extern int max;
    extern char save[];

    max = 0;

    while ((len = get_line()) > 0)
      if (len > max){
        max = len;
        copy();
      }

    if (max > 0) printf("%s", save);
  }

  get_line() {
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE - 1 && (c = getchar() != EOF && c != '\n'; ++i) line[i] = c;
    if (c == '\n') {
      line[i] = c;
      ++i;
    }

    line [i] = '\0';
    return(i)
  }

  copy() {
    int i;
    extern char line[], save[];

    i = 0;
    while ((save[i] = line[i]) != '\0') ++i;
  }
```

In certain circumstances, the `extern` declaration can be omitted: if the external definition of a variable occurs in the source file before its use in a particular function, then there's no need for an `extern` declaration in the function.
