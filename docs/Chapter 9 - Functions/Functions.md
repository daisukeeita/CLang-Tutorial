# Functions

Functions are the building blocks of C programs. Each function is essentially a small program, with its own declarations and statements. Using functions, we can divide a program into small pieces that are easier to understand and modify.

Functions can take some of the tedium out of programming by allowing us to avoid duplicating code that's used more than once.

Functions are reusable: we can take a function that was originally part of one program and use it in others.

| Section                                        | Description                                                                   |
| ---------------------------------------------- | ----------------------------------------------------------------------------- |
| [Section 9.1](#defining-and-calling-functions) | Learn more about the `main` itself                                            |
| [Section 9.2](#function-declaration)           | Discusses function declarations and how they differ from function definitions |
| [Section 9.3](#arguments)                      | Examines how arguments are passed to functions                                |
| [Section 9.4](#the-return-statement)           | Covers the `return` statement                                                 |
| [Section 9.5](#program-termination)            | Related issue of program termination                                          |
| [Section 9.6](#recursion)                      | Recursion                                                                     |

## Defining and Calling Functions

```
return-type function-name ( parameters ) {
  declarations
  statements
}
```

The `return-type` of a function is the type of value that the function return.
The following rules govern the return type:

- Functions may not return arrays, but there are no other restrictions on the return type.
- Specifying that the return type is `void` indicates that the function doesn't return a value.
- If the return type is omitted in C89, the function is presumed to return a value of type `int`. In C99, it is illegal to omit the return type of a function.

After the `function-name` comes a list of `parameters`. Each parameter is preceded by a specification of its type; parameters are separated by commas.
If the function has no parameters, the word `void` should appear between the parenthesis.

> [!NOTE]
> A separate type must be specified for each parameter, even when several parameters have the same type:
>
> ```c
> double average (double a, b) { /* WRONG */
>   return (a + b) / 2;
> }
> ```

The body of a function may include both `declarations` and `statements`.

```c
double average (double a, double b) {
  double sum; /* declaration */

  sum = a + b; /* statement */
  return sum / 2; /* statement */
}
```

#### Function Calls

A function call consists of a function name followed by a list of arguments enclosed in parenthesis.

```c
average(x, y);
print_count(i);
print_pun();
```

> [!WARNING]
> If the parenthesis are missing, the function won't get called.
> Some compilers issue a warning such as "_statement with no effect_"

A call of a `void` function is always followed by a semicolon to turn it into a statement:

```c
print_count(i);
print_pun();
```

A call of a non-`void` function, on the other hand, produces a value that can be stored in a variable, tested, printed, or used in some other way:

```c
avg = average(x, y);
if (average(x, y) > 0)
  printf("Average is positive\n");
printf("The average is %g\n", average(x, y));
```

The value returned by a non-`void` function can always be discarded if it's not needed.

```c
average(x, y); /* discards return value */
```

## Function Declaration

By default, the definition of each function was always placed _above_ the point at which it was called. In fact, C doesn't require that the definition of a function precede its calls. Suppose that we rearranged the `average.c` program by putting the definition of `average` _after_ the definition of `main`.

```c
#include <stdio.h>

int main(void) {
  double x, y, z;

  printf("Enter three numbers: ");
  scanf("%lf%lf%lf", &x, &y, &z);
  printf("Average of %g and %g: %g\n", x, y, average(x, y));
  printf("Average of %g and %g: %g\n", y, z, average(y, z));
  printf("Average of %g and %g: %g\n", x, z, average(x, z));

  return 0;
}

double average(double a, double b) {
  return (a + b) / 2;
}
```

When the compiler encounters the first call of `average` in `main`, it has no information about `average`: it doesn't know how many parameters `average` has, what the types of these parameters are, or what kind of value `average` returns.
Instead of producing an error message, the compiler assumes that `average` returns an `int` value. We say that the compiler has created an **_implicit declaration_** of the function.

When it encounters the definition of `average` later in the program, the compiler notices that the function's return type is actually `double`, not `int`, and so we get an error message.

One way to avoid the problem of call-before-definition is to arrange the program so that the definition of each function precedes all its calls. Unfortunately, such an arrangement doesn't always exist.
Fortunately, C offers a better solution: declare each function before calling it. A **_function declaration_** provides the compiler with a brief glimpse at a function whose full definition will appear later.

```
return-type function-name ( parameters ) ;
```

Here's how the program would look with a declaration of `average` added:

```c
#include <stdio.h>

double average (double a, double b); /* DECLARATION */

int main (void) {
  double x, y, z;

  printf("Enter three numbers: ");
  scanf("%lf%lf%lf", &x, &y, &z);
  printf("Average of %g and %g: %g\n", x, y, average(x, y));
  printf("Average of %g and %g: %g\n", y, z, average(y, z));
  printf("Average of %g and %g: %g\n", x, z, average(x, z));

  return 0;
}

double average (double a, double b) { /* DEFINITION */
  return (a + b) / 2;
}
```

Function declarations of these kind are know as **_function prototypes_** too distinguish them from an older style of function declaration in which the parenthesis are left empty.
A prototype provides a complete description of how to call a function: how many arguments to supply, what their types should be, and what type of result will be returned.

## Arguments

**_Parameters_** appear in function _definitions_; they're dummy names that represent values to be supplied when the function is called.
**_Arguments_** are expressions that appear in function _calls_.

In C, arguments are **_passed by value:_** when a function is called, each argument is evaluated and its value assigned to the corresponding parameter.
Since the parameter contains a copy of the argument's value, any changes made to the parameter during the execution of the function don't affect the argument. In effect, each parameter behaves like a variable that's been initialized to the value of the matching argument.

#### Argument Conversions

C allows function calls in which the types of the arguments don't match the types of the parameters. The rules governing how the arguments are converted depend on whether or not the compiler has seen a prototype for the function, or the function's full definition, prior to the call:

- **_The compiler has encountered a prototype prior to the call._**
  The value of each argument is implicitly converted to the type of the corresponding parameter as if by assignment.

- **_The compiler has not encountered a prototype prior to the call._**
  The compiler performs the _default argument promotions:_ (1) `float` arguments are converted to `double`. (2) The integral promotions are performed, causing `char` and `short` arguments to be converted to `int`.

> [!WARNING]
> Relying on the default argument promotions is dangerous.
>
> ```c
> #include <stdio.h>
>
> int main (void) {
>   double x = 3.0;
>   printf("Square: %d\n", square(x));
>
>   return 0;
> }
>
> int square(int n) {
>   return n * n;
> }
> ```
>
> At the time `square` is called, the compiler hasn't seen a prototype yet, so it doesn't know that `square` expects an argument of type `int`. Instead, the compiler performs the default argument promotions on `x`, with no effect.
> Since it's expecting an argument of type `int` but has been given a `double` value instead, the effect of calling `square` is undefined.

#### Array Arguments

Arrays are often used as arguments. When a function parameter is a one-dimensional array, the length of the array can be left unspecified.
There's just one problem: how will the function know how long the array is? Unfortunately, C doesn't provide any easy way for a function to determine the length of an array passed to it.

Instead, we'll have to supply the length - if the function needs it - as an additional argument.

> [!WARNING]
> Although we can use the `sizeof` operator to help determine the length of an array `variable`, it doesn't give the correct answer for an array `parameter`:
>
> ```c
> int f(int a[]) {
>   int len = sizeof(a) / sizeof(a[0]); /* WRONG: not the number of element in a */
>   ...
> }
> ```

The following function illustrates the use of one-dimensional array arguments. When given an array `a` of `int` values, `sum_array` returns the sum of the elements in `a`. Since `sum_array` needs to know the length of `a`, we must supply it as a second argument.

```c
int sum_array (int a[], int n) {
  int i, sum = 0;

  for (i = 0; i < n; i++) sum += a[i];

  return sum;
}
```

When `sum_array` is called, the first argument will be the name of an array, and the second will be its length.

```c
#define LEN 100

int main(void) {
  int b[LEN], total;

  total = sum_array(b, LEN);
}
```

An important point about array arguments: A function has no way to check that we've passed it the correct array length. We exploit this fact by telling the function that the array is smaller than it really is.

> [!WARNING]
> Be careful not to tell a function that an array argument is _larger_ than it really is:
>
> ```c
> total = sum_array(b, 150); /* WRONG */
> ```
>
> In this example, `sum_array` will go past the end of the array, causing undefined behavior.

Another important thing to know is that a function is allowed to change the elements of an array parameter, and the change is reflected in the corresponding argument.

```c
void store_zeros(int a[], int n) {
  int i;

  for (i = 0; i < n; i++) a[i] = 0;
}

store_zeros(b, 100); /* the call */
```

The call will store 0 into the first 100 elements of the array.
If a parameter is a multidimensional array, only the length of the first dimension may be omitted when the parameter is declared.

#### Variable-Length Array Parameters

Variable-Length arrays can also be parameters, as it turns out.

As it stands now, there's no direct link between `n` and the length of the array `a`. Although the function body treats `n` as `a`'s length, the actual length of the array could in fact be larger then `n` or smaller.
Using a variable-length array parameter, we can explicitly state that `a`'s length is `n`.

```c
int sum_array(int n, int a[n]) {...}
```

The value of the first parameter (`n`) specifies the length of the second parameter (`a`).
Note that the order of the parameters has been switched; order is important when variable-length array parameters are used.

There's also a method that will replace the array length by an asterisk(\*).

```c
int sum_array(int n, int a[*]);
```

The reason for using the _ notation is that parameter names are optional in function declarations. If the name of the first parameter is omitted, it wouldn't be possible to specify that the length of the array is `n`, but the _ provides a clue that the length of the array is related to parameters that come earlier in the list.

In general, the length of a variable-length array parameter can be any expression.

```c
int concatenate(int m, int n, int a[m], int b[n], int c[m+n]) {...}
```

Then length of `c` is the sum of the length of `a` and `b`. The expression used to specify the length of `c` involves two other parameters, but in general it could refer to variables outside the function or even call other functions.

It turns out that variable-length array parameters are most useful for multidimensional array. If we use a variable-length array parameter, we can generalize the function to any number of columns.

```c
int sum_two_dimensional_array (int n, int m, int a[n][m]) {
  int i, j, sum = 0;

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      sum += a[i][j];
    }
  }

  return sum;
}
```

Prototypes for this function include the following:

```c
int sum_two_dimensional_array(int n, int m, int a[n][m]);
int sum_two_dimensional_array(int n, int m, int a[*][*]);
int sum_two_dimensional_array(int n, int m, int a[][m]);
int sum_two_dimensional_array(int n, int m, int a[][*]);
```

#### Compound Literals

When `sum_array` is called, the first argument is usually the name of an array.
Then only problem with this arrangement is that variable name must be declared and then initialized prior to the call. If the variable is not needed for any other purpose, it can mildly annoying to create it solely for the purpose of calling `sum_array`.

We can avoid this annoyance by using a **_compound literal:_** an unnamed array that's created "on the fly" by simply specifying which elements it contains.

```c
total = sum_array((int []){3, 0, 3, 4, 1}, 5);
```

In this example, the compound literal creates an array containing the five integers. We didn't specify the length of the array, so it's determined by the number of elements in the literal. We also have the option of specifying a length explicitly.

```c
total = sum_array((int [4]){1, 9, 2, 1}, 5);  /* Equivalent to (int[]){1, 9, 2, 1} */
```

In general, a compound literal consists of a type name within parentheses, followed by a set of values enclosed by braces.
A compound literal may contain designators, just like a designated initializer, and it may fail to provide full initialization.

## The return Statement

A non-`void` function must use the `return` statement to specify what value it will return.

```c
return expression;
```

Then expression is often just a constant or variable.
More complex expressions are possible.

```c
return n >= 0 ? n : 0;
```

If the type of the expression in a `return` statement doesn't match the function's return type, the expression will be implicitly converted to the return type.
`return` statements may appear in functions whose return type is `void`, provided that no expression is given.

```c
return; /* return in a void function */
```

Putting an expression in such a `return` statement will get you a compile-time error.

```c
void print_int(int i) {
  if (i < 0)
    return;
  printf("%d", i);
}
```

Using `return` is unnecessary, though, since the function will return automatically after its last statement has been executed.
If a non-`void` function reaches the end of its body - that is, it fails to execute a `return` statement - the behavior of the program is undefined if it attempts to use the value returned by the function.

## Program Termination

Since `main` is a function, it must have return type. Normally, the return type of `main` is `int`, which is why the programs we've seen so far have defined `main`.
The value returned by `main` is a status code that - in some operating systems - can be tested when the program terminates. `main` should return 0 if the program terminates normally; to indicate abnormal termination, `main` should return a value other than 0.

It is a good practice to make sure that every C program returns a status code, even if there are no plans to use it, since someone running the program later may decide to test it.

#### The exit Function

Executing a `return` statement in `main` is one way to terminate a program. Another is calling the `exit` function, which belongs to `<stdlib.h>`.
The argument passed to `exit` has the same meaning as `main`'s return value: both indicate the program's status at termination.

```c
exit(0); /* normal termination */
exit(EXIT_SUCCESS); /* normal termination */

exit(EXIT_FAILURE); /* abnormal termination */
```

## Recursion

A function is **_recursive_** if it calls itself.

```c
int fact (int n) {
  if (n <= 1)
    return 1;
  else
    return n * fact(n - 1);
}
```

Some programming languages rely heavily on recursion, while others don't even allow it.
C falls somewhere in the middle: it allows recursion, but most C programmers don't use it that often.

#### The Quicksort Algorithm

Recursion is much more helpful for sophisticated algorithms that require a function to call itself two or more times.
In practice, recursion often arises naturally as a result of an algorithm design technique know as **_divide-and-conquer_**, in which a large problem is divided into smaller pieces that are then tackled by the same algorithm.

A classic example of divide-and-conquer strategy can be found in the popular sorting algorithm known as **_Quicksort_**. It goes as follows:

1.  Choose an array element _e_ (the "partitioning element"), then rearrange the array so that elements 1, ..., i-1 are less than or equal to _e_, element _i_ contains _e_, and elements _i - 1, ..., n_ are greater than or equal to _e_.
2.  Sort elements 1, ..., i - 1 by using Quicksort recursively.
3.  Sort elements i + 1, ..., n by using Quicksort recursively.

--- Too big to put it here, need to study Data Structure and Algorithm ---
