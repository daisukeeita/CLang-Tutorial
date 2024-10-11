# Fundamentals

**Outline to this Chapter**
| Section | Description |
| -------------- | --------------- |
| [Section 2.1](#writing-a-simple-program) | Presents a small C program and describes how to compile and link it. |
| [Section 2.2](#the-general-form-of-a-simple-program) | Discusses how to generalize the program. |
| [Section 2.3](#comments) | Shows how to add explanatory remarks, know a comments. |
| [Section 2.4](#variables-and-assignment) | Intorduces variables, which store data that may change during the execution of a program. |
| [Section 2.5](#reading-input) | Shows how to use the `scnaf()` function to read data into variables. |
| [Section 2.6](#defining-names-for-constants) | Shows Constants - data that won't change during program execution |
| [Section 2.7](#identifiers) | Explains C's rules for creating name (Indentifiers). |
| [Section 2.8](#layout-of-a-c-program) | Shows the rules for laying out a program. |

## Writing a Simple Program

In contrast to programs written in some languages, C programs require little "boilerplate" - a complete program can be as short as a few lines.

#### Printing a Program

```C
  #include <stdio.h>

  int main (void) {
    printf("To C, or not ot c: that is the question. \n");
    return 0;
  }
```

The line `#include <stdio.h>` is necessary to **"include"** the information about C's standard I/O (input/output) library.
The program's executable code goes inside `main()`, which represents the **"main"** program.
`printf()` is a function from the standard I/O library that can produce nicely formatted output.
The `\n` code tells `printf()` to advance to the next line after printing the message.
The line `return 0;` indicates that the program **"returns"** the value `0` to the operating system when it terminates.

#### Compiling and Linking

To run the program, it needs to be under a files that has a `.c` extension; for example, **_main.c_**. The file name doesn't matter, but the `.c` extension is required by the compilers.
Next, you've go to convert the program to a form that the machine can read and execute that said program. For C, that usually involves three steps:

- **_Preprocessing._** The program is first given to a **preprocessor**, which obeys commands that begin with # (know as _directives_).
- **_Compiling._** The modified program now goes to a **compiler**, which translates it into machine instructions (object code).
- **_Linking._** In the final step, a **linker** combines the object code produced by the compiler with any additional code needed to yield a complete executable program. This additional code include library functions (like `printf()`) that are used in the program.

Fortunately, this process is often automated, so you won't find it too onerous.

The commands necessary to compile and link vary, depending on the compiler and operating system. Under UNIX, the C compiler is usually name `cc`. To compile and link the _main.c_ file, enter the command in a terminal or command-line:

```terminal
  cc main.c
```

After compiling and linking the program, `cc` leaves the executable program in a file named _a.out_ by default. If you the executable version of _main.c_ to be named _main_, you would enter the following command:

```terminal
  cc -o main main.c
```

> The GCC Compiler
>
> One of the most populat C ompilers is the GCC compiler, whic his supplied with Linux but is available for may other platforms as well. Using this compiler is similar to using the raditional UNIX `cc` compiler.
>
> ```terminal
>   gcc -o main main.c
> ```

## The General Form of a Simple Program

```C
  // directives

  int main (void) {
    // statements
  }
```

C Programs rely on three key language features:

1. _Directives_ - editing commands that modify the program prior to compilation
2. _Functions_ - named blocks of executable code, of which _main_ is an example
3. _Statements_ - commands to be performed when the program is run

#### Directives

Before a C program is compiled, it is first edited by a preprocessor. Commands intended for the preprocessor are called _directives_ (`#include`).

This directive `#include <stdio.h>` states that the information in `<stdio.h>` is to be "included" into the program before it is compiled.

C has a number of **_headers_** like `<stdio.h>`; each contains information about some part of the standard library. The reason we're including `<stdio.h>` is that C, unlike some programming languages, has no built-in "read" and "write" commands. The ability to perform input and output is provided instead by functions in the standard library.

Directives always begin with a `#` character, which distinguishes them form other items in a C program.

#### Functions

Functions are like "procedures" or "subroutines" in other programming languages - they're the building blocks from which programs are constructed.

Functions fall into two categories:

- Those written by the programmer
- Those provided a part of the C implementation. Can be called **library functions**, since they belong to a "library" of functions that are supplied with the compiler.

Although a C program may consist of many functions, only the main functions is mandatory. `main` is special: it gets called automatically when the program is executed.

> [!WARNING]
> The name `main` is critical; it cannot be `begin`, `start`, or even `MAIN`

The `main` function also returns a value, it returns a status code that is given to the operating system when the program terminates.

```C
  #include <stdio.h>

  int main (void) {
    return 0;
  }
```

The word `int` just before `main` indicates that the `main` function returns and integer value.
The word `void` in parenthesis indicates that `main` has no arguments.

#### Statements

A statement is a command to be executed when the program runs. The _main.c_ program uses only one kind of statement, the `return` statement.
Asking a function to perform its assigned task is known as **_function call_**. An example of a function call is the `printf()` that prints a string.

C requires that each statement end with a semicolon. The semicolon shows the compiler where the statement ends; since statements can continue over several lines, it's not always obvious where they end. Directives on the other hand, are normally on line long, and they don't end with a semicolon.

#### Printing Strings

`printf()` is a powerful function that will be examined in the later chapter. `printf()` doesn't automatically advance to the next output line when it finishes printing. To instruct `printf()` to advance on line, you must include `\n` (new-line character) in the string to be printed.

## Comments

The _main.c_ program still lacks something important: documentation.

Every program should contain identifying information:

- The Program Name
- The Date Written
- The Author
- The Purpose of the Program
- so on and so forth...

In C, this kind of information is place in **comments**. The symbol `/*` marks the beginning of a comment and the symbol `*/` marks the end:

```C
  /* This is a Comment */
```

Comments may appear almost anywhere in a program, either on separate lines or on the same lines as other program text.

Forgetting to terminate a comment may cause the compiler to ignore part of your program. Consider the following example:

```C
  printf("My"); /* Forgot to close this comment...
  printf("Cat");
```

#### C99

C99 provides a second kind of comment, which begins with `//` (two adjacent slashes):

```C
  // this is a comment
```

This style of comment ends automatically at the end of a line. To create a comment that is more than one line long, you can either use the older comment style `/**/` or put `//` at the beginning of each comment line.

## Variables and Assignment

Most programs need to perform a series of calculations before producing output, and thus need a way to store data temporarily during program execution. In C, as in most programming languages, these storage locations are called **_variables_**.

#### Types

Every variable must have a **_type_**, which specifies what kind of data it will hold. Choosing the proper type is critical, since the type affects how the variable is stored and what operations can be performed on the variable. The type of a numeric variable determines the largest and smallest numbers that the variable can store; it also determines whether or not digits are allowed after the decimal point.

A variable of type `int` (short for integer) can store a whole number such as 0, 1, 392, or -2553. The range of possible values is limited, though. The largest int value is typically 2,147,483, 647 but can be as small as 32,767.

A variable of type `float` (short for floating-point) can store much larger numbers than an int variable. Furthermore, a float variable can store numbers with digits after the decimal point, like 379.125. Arithmetic on float numbers may be slower that arithmetic on int numbers.

#### Declarations

Variables must be **_declared_** - described for the benefit of the compiler - before they can be used. To declare a variable, you first specify the type of the variable, then its name.

> Variable names are chosen by the programmer

```C
  int height;
  float profit;
```

In the first template of the `main` did not include declarations. When `main` contains declarations, these must precede statements:

```C
  int main (void) {
    // declarations

    // statements
  }
```

As a matter of style, it is a good idea to leave a blank line between the declarations and the statements.

#### Assignment

A variable can be given a value by means of **_assignment_**.

```C
  height = 8;
  length = 12;
  width = 10;
```

The statements about assign values to height, length, and width. The numbers 8, 12, and 10 are said to be **_constants_**.

A constant assigned to a float variable usually contains a decimal point.

```C
  profit = 2150.48;
```

It is best to append the letter 'f' (for "float") to a constant that contains a decimal point if the number is assigned to a float variable. Failing to include the 'f' may cause a warning from the compiler.

```C
  profit = 2150.48f;
```

An `int` variable is normally assigned a value type `int`, and a `float` variable is normally assigned a value of type `float`.
Mixing types is possible but not always safe.

Once a variable has been assigned a value, it can be used to help compute he value of another variable. In general, the right side of an assignment can be a formula (or **_expression_**) involving constants, variables, and operators.

```C
  int volume = height * length * width *; // volume is not 960
```

#### Printing the Value of a Variable

We can use the `printf()` to display the current value of a variable.

```C
  printf("Height: %d\n", height);
```

`%d` is a placeholder indicating where the value of height is to be filled in during printing. `%d` only works for int variables. To print float variable, you'd use `%f` instead. By default, `%f` displays a number with six digits after the decimal point.

To force `%f` to display 'x' digits after the decimal point, you can put `.'x'` between % and f.

```C
  printf("Profit: %.2f\n", profit);
```

#### Initializaiton

Some variables are automatically set to zero when a program begins to execure, but most are not. A variable that doesn't have a default value and hasn't yet been assigned a value by the program is said to be **_uninitialized_**.

> [!WARNING]
> Attempting to access the value of an uninitialized variable (for example, by displaying the variable using `printf()` of using it in an expression) may yield an unpredictable result such as "2568", "-30891", or some equally strange number. With some compilers, worse behaviour - even a program crash - may occur.

In C jargon, the value `8` is said to be an **_initalizer_**. Any number of variables can be initialized in the same declaration:

```C
  int height = 8, length = 12, width = 10;

  int height, length, width = 10;
```

Notice that each variable requires its own initializer. In the example above, the initializer `10` is good only for the variable `width`, not for `height` or `length`, which remains uninitialized.

#### Printing Expressions

`printf()` is not limited to displaying numbers store in variables; it can display the value any _any_ numeric expression. Taking advantage of this property can simplify a program and reduce the number of variables.

```C
  int volume = height * length * width;
  printf("%d\n", volume);
```

This can be replaced into:

```C
  printf("%d\n", height * width * length);
```

`printf()` ability to print expressions illustrates one of C's general principles: _Wherever a value is needed, any expression of the same type will do._

## Reading Input

To obtain input, you'll use the `scanf()` function, the C library's counterpart to `printf()`. The 'f' in `scanf()`, like the 'f' in `printf()`, stands for **"formatted"**; both `scanf()` and `printf()` require the use of the **_format string_** to specify the appearance of the input or output data.

```C
  scanf("%d", &i); // reads an integer and stores into i
```

The `%d` string tells `scanf()` to read input that represents an integer; `i` is an `int` varaible into which we want `scanf()` to store the input.
The `&` symbol is, for now, usually (but not always) required when using `scanf()`

```C
  scanf("%f", &x); // reads a float value and stores into x
```

Reading a `float` value requires a slightly different call of `scanf()`
The `%f` string tells `scanf()`to look for an input value in `float` format, the number may contain a decimal point, but doesn't have to.

## Defining Names for Constants

When a program contains constants, it is often good idea to give them names. Using the feature know as **_macro definition_**, you can name a constant:

```C
  #define INCHES_PER_POUND 166
```

`#define` is a preprocessing directive, just as `#include` is, so there is not semicolon at the end of the line.

When a program is compile, the preprocessor replaces each macro by the value that is prepresents.

```C
  int weight = (volume + INCHES_PER_POUND - 1) / INCHES_PER_POUND;
```

After compilation:

```C
  weight = (volume + 166 - 1) / 166;
```

The value of a macro can be an expression:

```C
  #define RECIPROCAL_OF_PI (1.0f / 3.14159f)
```

If it contains operators, the expression should be enclosed in parenthesis.
The upper-case letters in macro names is a convention that most C programmers follow, not a requirement of the language.

## Indentifiers

As you're writing a program, you'll have to choose names for variables, functions, macros, and other entities. These names are call **_identifiers_**. In C, an identifier may contain letters, digits, and underscores, but must begin with a letter or underscore.

Examples of legal identifiers:

```
  times10  get_next_char  _done
```

C is **_case-sensitive_**: it distinguishes between upper-case and lower-case letters in indentifiers.

C places no limit on the maximum length of an identifier, so don't be afraid to use long, descriptive names. A name such as `current_page` or `currentPage` is a lot easier to understand than a name like `cp`.

## Keywords

The **_keywords_** have special significance to C compilaers and therefore can't be used as identifiers.

| Column 1 | Column 2 | Column 3 | Column 4    |
| -------- | -------- | -------- | ----------- |
| auto     | enum     | restrict | unsigned    |
| break    | extern   | return   | void        |
| case     | float    | short    | volatile    |
| char     | for      | signed   | while       |
| const    | goto     | sizeof   | \_Bool      |
| continue | if       | static   | \_Complex   |
| default  | inline   | struct   | \_Imaginary |
| do       | int      | switch   |             |
| double   | long     | typedef  |             |
| else     | register | union    |             |

Because of C's case-sensitivity, keywords must appear in progrmas exactly as show in the table. Names of functions in the standard library (such as `printf()`) contain only lower-case letter.

> [!WARNING]
> Watch out for other restrictions on identifiers. Some compilers treat certain identifiers as additional keywords. Identifiers that belong to the standard library are restricted as well. Accidentally using one of these names can cause an error during compilation or linking. Identifiers that begin with an underscore are also restricted.

## Layout of a C Program
