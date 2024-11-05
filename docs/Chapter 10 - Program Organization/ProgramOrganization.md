# Program Organization

**Outline to this Chapter**

| Section                                 | Description                                                                                                                     |
| --------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| [Section 10.1](#local-variables)        | Discussion about the local variables                                                                                            |
| [Section 10.2](#external-variables)     | Discussion about the external variables                                                                                         |
| [Section 10.3](#blocks)                 | Discussion about the blocks                                                                                                     |
| [Section 10.4](#scope)                  | Tackles the scope rules that apply to local names, external names, and names declared in blocks                                 |
| [Section 10.5](#organizing-a-c-program) | Suggests a way to organize function prototypes, function definitions, variable declarations, and the other parts of a C program |

## Local Variables

A variable declared in the body of a function is said the be **_local_** to the function. In the following function, `sum` is a local variable.

```c
int sum_digits(int n) {
  int sum = 0; /* local variable */

  while (n > 0) {
    sum += n % 0;
    n /= 10;
  }

  return sum;
}
```

By default, local variables have the following properties:

- **_Automatic storage duration._**
  The _storage duration_ of a variable is the portion of program execution during which storage for the variable exists. Storage for a local variable is "automatically" allocated when the enclosing function is called and deallocated when the function returns, so the variable is said to have _automatic storage duration_.
  A local variable doesn't retain its value when its enclosing function returns. When function is called again, there's no guarantee that the variable will still have its old value.

- **_Block Scope._**
  The _scope_ of a variable is the portion of the program text in which the variable can be referenced. A local variable has _block scope:_ it is visible from its point of declaration to the end of the enclosing function body.
  Since the scope of a local variable doesn't extend beyond the function to which it belongs, other functions can use the same name for other purposes.

#### Static Local Variables

Putting the word `static` in the declaration of a local variable causes it to have **_static storage duration_** instead of automatic storage duration.
A variable with static storage duration has a permanent storage location, so it retains its value throughout the execution of the program.

```c
void f(void) {
  static int i; /* static local variable */
  ...
}
```

Since the local variable `i` has been declared `static`, it occupies the same memory location throughout the execution of the program. When `f` returns, `i` won't lose its value.
A static local variable still has block scope, so it's not visible to other functions.

In a nutshell, a static variable is a place to hide data from other functions but retain it for future calls of the same function.

#### Parameters

Parameters have the same properties - automatic storage duration and block scope - as local variables. In fact, the only real difference between parameters and local variables is that each parameter is initialized automatically when a function is called.

## External Variables

Passing arguments is one way to transmit information to a function. Functions can also communicate through **_external variables_** - variables that are declared outside the body of any function.

- **_Static storage duration._**
  External variables have static storage duration, just like local variables that have been declared `static`. A value stored in an external variable will stay there indefinitely.
- **_File Scope._**
  An external variable has _file scope_: it is visible from its point of declaration to the end of the enclosing file. As a result, an external variable can be accessed, and potentially modified, by all functions that follow its declaration.

#### Pros and Cons of External Variables

External variables are convenient when many functions must share a variable or when a few functions share a large number of varaibles.
In most cases, however, it's better for functions to communicate through parameters rather than by sharing varaibles. Here's why:

- If we change an external variable during progrma maintenance (by altering its type, say), we'll need to check every function in the same file to see how the change affects it.
- If an external variable is assigned an incorrect value, it may be difficult to identify the guilty function.
- Functions that rely on external variables are hard to reuse in other programs. A function that depends on external variables isn't self-contained; to reuse the function, we'll have to drag along any external variables that it needs.

When you use external variables, make sure they have meaningful names. Local variables don't always need meaningul names: it's often fard to think of a bettern name than `i` for the control variable in a `for` loop.

> [!WARNING]
> Making variables external when they should be local can lead to some rather frustrating bugs.

## Blocks

```
{ declarations statements }
```

```c
if (i > j) {
  /* swap values of i and j */
  int temp = i;
  i = j;
  j = tem;
}
```

**_Blocks_** are the compound statments inside the `{}`.
By default, the storage duration of a variable declared in a block is automatic: storage for the variable is allocated when the block is entered and eeallocated when the block is exited.

## Scope

In a C program, the same identifier may have several different meanings. C's scope rules enable the programmer, and the compiler, to determin which meaning is relevant at a given point in the program.

Here's the most important scope rule: When a declaration inside a block names an identifier that's already visible (because it has file scope or because it's declared in an enclosing block), the new declaration termporarily "hides" the old one, and the identifier takes on a new meaning.
At the end of the block, the identifier regains its old meaning.

```c
int i ; /* Declaration 1 */

void f(int i) { /* Declaration 2 */
  i = 1;  /* From Declaration 2 */
}

void g(void) {
  int i = 2; /* Declaration 3 */

  if (i > 0) {  /* From Declaration 3 */
    int i; /* Declaration 4 */
    i = 3;  /* From Declaration 4 */
  }
}

void h(void) {
  i = 5;  /* From Declaration 1 */
}
```

In Declaration 1 - `i` is a variable with static storage duration and file scope.
In Declaration 2 - `i` is a parameter with block scope
In Declaration 3 - `i` is an automatic variable with block scope
In Declaration 4 - `i` is also automatic and has block scope.

## Organizing a C Program

C imposes only a few rules on the order of these items: A preprocessing directive doesn't take effect until the line on which it appears. A type name can't be used until it's been defined. A variable can't be used until it's declared.

There are several ways to organize a program so that these rules are obeyed. Here's one possible ordering:

```
  #include directives
  #define directives
  Type definitions
  Declarations of external variables
  Prototypes for functions other than main
  Definition of main
  Definition of other functions
```

Also a suggestion: Precede each function definition by a boxed comment that gives that name of the function, explains its purpose, discusses the meaning of each parameter, describes its return value (if any), and lists any side effects it has (such as modifying external variables).
