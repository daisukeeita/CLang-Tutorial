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
