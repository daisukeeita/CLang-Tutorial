# Selection Statements

Although C has many operators, it has relatively few statements. Most of the C's statements fall into three categories, depending on how they affect the order in which statments are executed:

- **_Selection Statements_**: The `if` and `switch` statements allow a program to select a particular execution path from a set of alternative.
- **_Iteration Statements_**: The `while`, `do`, and `for` statements support iteration (looping).
- **_Jump Statements_**: The `break`, `continue`, and `goto` statements cause an unconditional jump to some other place in the program. (The `return` statemtn belongs in this category, as well).

**Outline to this Chapter**

| Section                              | Description                                                                                                                |
| ------------------------------------ | -------------------------------------------------------------------------------------------------------------------------- |
| [Section 5.1](#logical-expressions)  | Explains how logical expresions are built from the relational operators, the equality operators, and the logical operators |
| [Section 5.2](#the-if-statement)     | Covers if `if` statement and compound statement, as well as introducing the conditional operator                           |
| [Section 5.3](#the-switch-statement) | Descibes the `switch` statement                                                                                            |

## Logical Expressions

Several of C's statements, including the `if` statement, must test the value of an expression to see if it is "true" or "false". In many programming languages, an expression such as `i < j` would have a special "Boolean" and "logical" type. Such type would have only two values, `false` and `true`.
In C, however, a comparison such as `i < j` yields an integer: either 0 (false) or 1 (true).

#### Relational Operators

C's **_relational operators_** correspond to the `<, >, <=, >=` operators of mathematics, except they produce 0 (false) or 1 (true) when used in expressions.

#### Equality Operators

Although the relational operators are denoted by the same symbols as in many other programming languages, the **_equality operators_** have a unique appearance. The "equal to" operator is two adjacent `=` character, not one, since a single `=` character represents the assignment operator. The "not equal to" operator is also two characters `!` and `=`.

Like the relational operators, the equality operators are left associative and produce either 0 (false) or 1 (true) as their result.

Clever programmers sometimes exploit the fact that the relational and equality operators return integer values. For example, the value of the expressions (i >= j) + (i == j) is either 0, 1, or 2, depending on whether i is less than, greater than, or equal to j, respectively.
Tricky coding like this generally isn't a good idea.

#### Logical Operators

More complicated logical expressions ca be built from simpler ones by using the **_logical operators_**: _and_, _or_, and _not_. `!` operator is unary, while `&&` nad `||` are binary.

The logical operators produce either 0 or 1 as their result. Often, the operands will have values of 0 or 1, but this isn't a requirement; the logical operators treat any nonzero operand as tru value and any zero operand as a false value.

The logical operators behave as follows:

- `!expr` has the value 1 if `expr` has the value 0.
- `expr1 && expr2` has the value 1 if the values of `expr1` and `expr2` are both non-zero.
- `expr1 || expr2` has the value 1 if either `expr1` or `expr2` or both has non-zero value.

Both `&&` and `||` perform "short-circuit" evaluation of their operands. That is, these operators first evaluate the left operand, then the right operand. If the value of the expression can be deduced from the value of the left operand alone, then the right operand isn't evaluated.

> [!WARNING]
> Be wary of side effects in logical expressions. Thank to the short-circuit nature of the `&&` and `||` operators, side effeccts in operands may not always occur.
> `i > 0 && ++j > 0`
> Although `j` is apprently incremented as a side effect of evaluating the expression, that isn't always the case. If `i > 0` is false, then `++j > 0` is not evaluated, so `j` ins't incremented. Then problem can be fixed by changing the condition to `++j > 0 && i > 0`, or, even better, by incrementing `j` seprately.

## The if Statement

The `if` statement allows a program to choose between two alternatives by testing the value of an expression.

```c
  if ( expression ) statement
```

When a `if` statement is execured, the expression in the parenthesis is evaluated; if the value of the expression is nonzero - which C interprets as true - the statement after the parenthesis is executed.

```c
  if (line_num == MAX_LINES)
    line_num = 0;
```

#### Compound Statements

In the `if` statement template, notice that _statement_ is singular, not plural. But if we want an `if` statement to control _two_ or more statements, that's where the **_compound statement_** comes in.

```c
  if ( expression ) {
    statements
  }
```

Here's an example of a compound statement:

```c
  if ( expression ) {
    line_num = 0;
    page_num++;
  }
```

Compound statements are also common in loops and other places where the syntax of C requires a single statement.

#### The else Clause

An `if` statement may have an `else` clause:

```
  if ( expression ) statement else statement
```

The statement that follows the word `else` is executed if the expression in parentheses has the value 0.

```c
  if (i > j)
    max = i;
  else
    max = j;
```

There are no restrictions on what kind of statements can appear inside an `if` statement. In fact, it's not unusual for `if` statements to be nested inside other `if` statements.

```c
  if (i > j)
    if (i > k)
      max = i;
    else
      max = k;
  else
    if (j > k)
      max = j;
    else
      max = k;
```

`if` statements can be nested to any depth. If you still find the nesting confusin, don't hesistate to add braces. Using braces even when they're not required has two advantages.
First, the program becomes easier to modify, because more statements can easily be added to any `if` or `else` clause. Second, it helps avoid errors that can result from forgetting to use braces when adding statements to an `if` or `else` clause.

```c
  if (i > j) {
    if (i > k) {
      max = i;
    } else {
      max = k;
    }
  } else {
    if (j > k) {
      max = j;
    } else {
      max = k;
    }
  }
```

#### Cascaded if Statements

We'll often need to test a series of conditions, stopping as soon as one of them is true. A "cascaded" `if` statement is often the best way to write such a series of tests.

```c
  if (n < 0)
    printf("n is less than 0\n");
  else
    if (n == 0)
      printf("n is equal to 0\n");
    else
      printf("n is greater than 0\n");
```

The following cascaded `if` statement tests whether `n` is less that 0, equal to 0, or greater that 0. Although the second `if` statement is nested inside the first, C programmers don't usually indent it. Instead, they align each `else` with the original `if`.

```c
  if (n < 0)
    printf("n is less than 0\n");
  else if (n == 0)
    printf("n is equal to 0\n");
  else
    printf("n is greater that 0\n");
```

#### The "Dangling else" Problem

When `if` statements are nested, we've got to watch out for the notorious "dangling `else`" problem.

```c
  if (y != 0)
    if (x != 0)
      result = x / y;
  else
    printf("Error: y is equal to 0\n");
```

To which `if` statement does the `else` clause belong? The indentation suggests that it belongs to the outer `if` statement. However, C follows the rule that an `else` clause belongs to the nearest `if` sttement that hasn't already been paired with an `else`.

To make the `else` clause part of the out `if` statement, we can enclose the innter `if` statement in braces:

```c
  if (y != 0) {
    if (x != 0)
      result = x / y;
  } else {
    printf("Error: y is equal to 0\n");
  }
```

#### Conditional Expressions

C's `if` statement allows a program to perform on of two actions depending on the value of a condition. C also provides an _operator_ that allows an expression to produce on of two _values_ depending on the value of a condition.

The **_conditional operator_** consists of two symbols (? and :), which must be used together in the folowing way:

expr1 ? expr2 : expr3

The resulting expresions is said to be a **_conditional expression_**. The conditional operator is unique among C operators in that it requires _three_ operands instead of one or two. For this reason, it is often referred to as a **_ternary_** operator.
It should be read "if expr1 (is true) then expr2 else expr3".

## The switch Statement

In everyday programming, we'll often need to compare an expresison against a series of values to see which one it currently matches. We saw that a cascaded `if` statement can be used for this purpose.
As an alternative to the cascaded `if` statement, C provides the `switch` statement.

```c
  switch (grade) {
    case 4: printf("Excellent");
            break;
    case 3: printf("Good");
            break;
    case 2: printf("Average");
            break;
    case 1: printf("Poor");
            break;
    case 0: printf("Failing");
            break;
    default: printf("Illegal Grade");
            break;
  }
```

When this statemnt is executed, the value of the variable `grade` is tested against 4, 3, 2, 1, and 0. If it matches 4, the message `Excellent` is printed, then the `break` statement transfers control to the statement following `switch`.
Duplicate case labels aren't allowed. The order of the cases doesn't matter; in particular, the `default` case doesn't need to come last.
Only one constant expression may follow the word `case`; however, several case labels may preced the same group of statement.

```c
  switch (grade) {
    case 4:
    case 3:
    case 2:
    case 1: printf("Passing");
            break;
    case 0: printf("Failing");
            break;
    default: printf("Illegal Grade");
            break;
  }
```

A `switch` statement isn't required to have a `default` case. If `default` is missing and the value of the controlling expresion doesn't match any of the case labels, control simply passes to the next statement after the switch.
