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
