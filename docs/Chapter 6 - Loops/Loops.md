# Loops

A **_loop_** is a statement whose job is to repeatedly execute some other statement (the **_loop body_**). In C, every loop has a **_controlling expression_**. Each time the loop body is executed (an **_iteration_** of the loop), the controlling expression is evaluate; if the expression is true - has a value that's not zero - the loop continues to execute.

**Outline to this Chapter**

| Section                             | Description                                              |
| ----------------------------------- | -------------------------------------------------------- |
| [Section 6.1](#the-while-statement) | The `while` Statement                                    |
| [Section 6.2](#the-do-statement)    | The `do` Statement                                       |
| [Section 6.3](#the-for-statement)   | The `for` Statement                                      |
| [Section 6.4](#exiting-from-a-loop) | Describes the `break`, `continue`, and `goto` statements |
| [Section 6.5](#the-null-statement)  | Convers the null statement                               |

## The while Statement

Of all the ways to set up loops in C, the `while` statement is the simplest and most fundamental.

while ( expression ) statement

The expression inside the parentheses is the controlling expression; the statement after the parentheses is the loop body.

```c
  while (i < n) /* controlling expression */
    i = i * 2; /* loop body */
```

Note that the parentheses are mandatory and that nothing goes between the right parenthesis and the loop body.
When a `while` statement is executed, the controlling expression is evaluated first. If its value is nonzero (true), the loop body is executed and the expression is tested again. The process continues in this fashion until the controlling expression eventually has the value zero.

Although the loop body must be a single statement, that's merely a technicality. If we want more than one statement, we can just use braces to create a single compound statement.

```c
  while (i > 0) {
    printf("T minus %d and counting\n", i);
    i--;
  }
```

#### Infinite Loops

A `while` statement won't terminate if the controlling expression always has a nonzero value.

while (1)...

A `while` statement of this form will execute forever unless its body contains a statement that transfers control out of the loop (`break`, `goto`, `return`) or calls a function that causes the program to terminate.

## The do Statement

The `do` statement is closely related to the `while` statement; in fact, the `do` statement is essentially just a `while` statement whose controlling expression is tested _after_ each execution of the loop body.

do statement while ( expression ) ;

When a `do` statement is executed, the loop body is executed first, then the controlling expression is evaluated. If the values of the expression is nonzero, the loop body is executed again and then the expression is evaluated once more.
Execution of the `do` statement terminates when the controlling expression has the value 0 _after_ the loop body has been executed.

```c
  int i = 10;
  do {
    printf("T minus %d and counting\n", i);
    --i;
  } while (i > 0);
```

Incidentally, it's a good idea to use braces in _all_ `do` statements, whether or not they're needed, because a `do` statement without braces can easily be mistaken for a `while` statement.

## The for Statement

The `for` statement is ideal for loops that have a "counting" variable, but it's versatile enough to be used for other kinds of loops as well.

for (expr1 ; expr2 ; expr3 ) statement

```c
  for (int i = 10; i > 0; i--);
    printf("T minus %d and counting\n", i);
```

When `for` statement is executed, the variable `i` is initialized to 10, then `i` is tested to see if it's greater than 0. Since it is, the message `T minus 10 and counting` is printed, then `i` is decremented. The condition `i > 0` is then tested again.

#### Omitting Expressions in a for Statement

The `for` statement is even more flexible. Some `for` loops may not need all three of the expressions that normally control the loop, so C allows us to omit any or all of the expressions.

If the _first_ expression is omitted, not initialization is performed before the loop is executed:

```c
  int i = 10;
  for (; i > 0; --i)
    printf("T minus %d and counting\n", i);
```

If we omit the _third_ expression in a `for` statement, the loop body is responsible for ensuring that the value of the second expression eventually becomes false.

```c
  for (int i = 10; i > 0;)
    printf("T minus %d and counting\n", i--);
```

#### The Comma Operator

On occasion, we might like to write a `for` statement with two or more initialization expressions or one that increments several variables each time through the loop. We can do this by using a **_comma expression_** as the first or third expression in the `for` statement.

The comma operator is provided for situations where C requires a single expression, but we'd like to have two or more expressions.

```c
  for (int sum = 0, int i = 1; i <= N; i++)
    sum += i;
```

## Exiting for a Loop

Occasionally, we'll need a loop with an exit point in the middle. We may even want a loop to have more than one exit point.

#### The break Statement

The `break` statement can also be used to jump out of a `while`, `do`, or `for` loop.

```c
  for (d = 2; d < n; d++)
    if (n % d == 0)
      break;
  if (d < n)
    printf("%d is divisible by %d\n", n, d);
  else
    printf("%d is prime\n", n);
```

The `break` statement is particularly useful for writing loops in which the exit point is in the middle of the body rather than at the beginning or end.

#### The continue Statement

The `continue` statement doesn't really belong here, because it doesn't exit from a loop. It's similar to `break`, though, so its inclusion in this section isn't completely arbitrary. `break` transfers control just _past_ the end of the loop body. With `break`, control leaves the loop; with `continue`, control remains inside the loop. Another difference between `break` and `continue`: `break` can be used in `switch` statements and loops, whereas `continue` is limited to loops.

```c
  int n = 0;
  int sum = 0;
  while (n < 10) {
    scanf("%d", &i);
    if (i == 0)
      continue;
    sum += i;
    n++;
    /* continue jump to here */
  }
```

#### The goto Statement

The `goto` statement is capable of jumping to _any_ statement in a function, provided that the statement has a **_label_**.

identifier : statement

goto identifier ;

```c
  for (int d = 2; d < n; d++)
    if (n % d == 0)
      goto done;

  done:
  if (d < n)
    printf("%d is divisible by %d\n", n, d);
  else
    printf("%d is prime\n", n);
```

The `goto` statement, a staple of older programming languages, is rarely need in everyday C programming.

## The Null Statement

A statement ca be **_null_**-devoid of symbols except for the semicolon at the end.

```c
  i = 0; ; j = 1;
```

The line contains three statements: an assignment to `i`, a null statement, and an assignment to `j`.

The null statement is primarily good for one thing: writing loops whose bodies are empty.

```c
  for (int d = 2; d < n; d++)
    if (n % d == 0)
      break;

  /* Moving the n % d == 0 condition into the loop's controlling expression */
  for (int d = 2; d < n && d != 0; d++)
    ;
```

> [!WARNING]
> Accidentally putting a semicolon after the parentheses in an `if`, `while`, or `for` statement creates a null statement, thus ending the `if`, `while`, or `for` prematurely.
> Another possibility is that the loop terminates, but the statement that should be the loop body is executed only once, after the loop has terminated.
