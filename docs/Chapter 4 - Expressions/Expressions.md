# Expressions

One of the C's distinguishing characteristics is its emphasis on expressions - formulas that show how to compute a value - rather than statements. The simplest expressions are variables and constants.

A _variable_ represents a value to be computed as the program runs. A _constant_ represents a value that doesn't change.

Operators are the basic tools for building expressions, and C has an unusually rich collection of them. To start off, C provides the rudimentary operators that are found in most programming languages:

- **Arithmetic Operators** including addition, subtraction, multiplication, and division.
- **Relational Operators** to perform comparisons such as "i is greater than 0".
- **Logical Operators** to build conditions such as "i is greater that 0 and i is less than 0".

**Outline to this Chapter**
| Section | Description |
| -------------- | --------------- |
| [ Section 4.1 ](#arithmetic-operators) | The Arithmetic Operators |
| [ Section 4.2 ](#assignment-operators) | The Assignment Operators |
| [ Section 4.3 ](#increment-and-decrement-operators) | The Increment and Decrement Operators |
| [ Section 4.4 ](#expression-evaluation) | How C Expressions are evaluated |

## Arithmetic Operators

The **_arithmetic operators_** - operators that perform addition, subtraction, multiplication, and division - are the workhorses of many programming languages, including C.

| Unary         | Binary        | Binary            |
| ------------- | ------------- | ----------------- |
|               | _Additive_    | _Multiplicative_  |
| + unary plus  | + addition    | \* multiplication |
| - unary minus | - subtraction | / division        |
|               |               | % remainder       |

The additive and multiplicative operators are said to be **_binary_** because they require _two_ operands. The **_unary_** operators required _one_ operand. But unary + operator does nothing and it is used primarily to emphasize that a numeric constant is positive.

The / and % require special care:

- The / operator can produce surprising results. When both of its operands are integers, the / operator "truncates" the result by dropping the fractional part. Thus, the value of 1 / 2 is 0, not 0.5.
- The % operator requires integer operands; if either operand is not an integer, the program won't compile.
- Using zero as the right operand of either / or % causes undefined behavior.
- Describing the result when / and % are used with negative operands is tricky.

#### Operator Precedence and Associativity

When an expression contains more than one operator, its interpretation may not be immediately clear. One solution to this problem is to add parentheses, writing either (i + j) _ k or i + (j _ k). As a general rule, C allows the use of parentheses for grouping in all expressions.

Like many other languages, C uses **_operator precedence_** rules to resolve a potential ambiguity. The arithmetic operators have the following relative precedence:

| Level    | Operator |        |
| -------- | -------- | ------ |
| Highest: | + -      | unary  |
|          | \* / %   |        |
| Lowest:  | + -      | binary |

Operators listed on the same line have equal precedence.

When two or more operators appear in the same expression, we can determine how to compiler will interpret the expression by repeatedly putting parentheses around subexpressions, starting with high-precedence operators and working down to low-precedence operators.

Operator precedence rules alone aren't enough when an expression contains two or more operators at the same level of precedence. In this situation, the **_associativity_** of the operators comes into play.

An operator is said to be **_left associative_** if it groups from left to right. The binary arithmetic operators (\*, /, %, +, and -) are all left associative.

i - j - k is equivalent to (i - j) - k
i _ j / k is equivalent to (i _ j) / k

An operator is **_right associative_** if it groups from right to left. The unary arithmetic operators are both right associative.

'- + i' is equivalent to - (+i)

## Assignment Operators

Once the value of an expression has been computed, we'll often need to store it in a variable for late use. The `=` (**_simple assignment_**) operator is used for that purpose. For updating a value already stored in a variable, C provides an assortment of compound assignment operators.

#### Simple Assignment

The effect of the assignment `v = e` is to evaluate the expression `e` and copy its value into `v`. `e` can be a constant, a variable, or a more complicated expression.

```c
i = 5; /*  i is now 5 */
j = i; /* j is now 5 */
k = 10 * i + j; /* k is now 55 */
```

If `v` and `e` don't have the same type, then the value of `e` is converted to the type of `v` as the assignment takes place.

```c
int i;
float f;

i = 72.99f; /* i is now 72 */
f = 136; /* f is now 136.00 */
```

In C, assignment is an _operator_, just like +. In other words, the act of addignment produces a result, just as adding two numbers prduces a result. The value of an assignment 'v = e' is the value of `v` _after_ the assignment.

Since assignment is an operator, several assignments can be chained together:

i = j = k = 0;

The `=` operator is right associative, so this assignment is equivalent to:

i = (j = (k = 0));

The effect is to assign 0 first to `k`, the to `j`, and finally to `i`.

> [!WARNING]
> Watch out for unexprected results in chained assignments as a result of type conversion:
>
> ```c
> int i;
> float f;
>
> f = i = 33.3f;
> ```
>
> `i` is assigned the value 33, then `f` is assigned '33.0', not '33.3' as you might think

#### L Values

Most C operators allow their operands to be variables, constatns, or expressions containing other operators. The assignment operator, however, requires an **_lvalue_** as its left operand. An lvalue represents an object stored in computer memory, not a constant or the result of a computation. 'Variables' are lvalues; 'Expressions' such as 10 or 2 \* i are not.

Since the assignment operator requires an lvalue as its left operand, it's illegal to put any other kind of expression on the left side of an assignment expression.

```c
112 = i;
i * j = 0;
-i = j;
```

The compiler will detect errors of this nature, and you'll get an error message such as _"invalid lvalue in assignment"_

#### Compound Assignment

Assignments that use the old value of a variable to compute its new value are commong in C programs.

```c
i = i + 2;
```

C' **_compound assignment_** operators allow us to shorten this statement and others like it. Using the `+=` operator:

```c
i += 2; /* Same as i = i + 2; */
```

The `+=` operators adds the value of the right operand to the varaible on the left.

Note that 'v += e' is not really "equivalent" to 'v = v + e'. One problem is oeprator precedence: 'i _= j + k' is not the same is i = i _ j + k. There are also rare cases in which 'v += e' differs from 'v = v + e' because v itself has a side effect.

> [!WARNING]
> When using the compound assignment operators, be careful not to switch the two characters taht make up the operator. Switching the characters may yield an expression that is acceptable to the compiler but that doesn't have the intended meaning.
>
> If you meant to write 'i += j' but typed 'i =+ j' instead, the program will still compile. Unfortunately, the latter expression is equivalent to i = (+j), which merely copies the value of `j` into `i`.

## Increment and Decrement Operators

Two of the most common operations on a variable are "incrementing" (adding 1) and "decrementing" (subtracting 1).

At first glance, the increment and decrement operators are simplicity itself: `++` adds 1 to its operand, whereas `--` substracts 1. Unfortunately, this simplicity is misleading - the increment and decrement operators can be tricky to use.

One complication is the `++` and `--` can be used as **_prefix_** operators (++i and --i) or **_postfix_** operators (i++ and i--). The correctness of a program may hinge on picking the proper version.
Another complication is that, like the assignment operators, `++` and `--` have side effects: they modify the values of their operands.

Evaluating the expression `++i` (a "pre-increment") yields 'i + 1':

```c
  int i = 1;
  printf("i is %d\n", ++i); /* prints "i is 2" */
  printf("i is %d\n", i); /* prints "i is 2" */
```

Evaluating the expression `i++` (a "post-increment") produces the result i, but causes i to be incremented afterwards:

```c
  int i = 1;
  printf("i is %d\n", i++); /* prints "i is 1" */
  printf("i is %d\n", i); /* prints "i is 2" */
```

## Expression Evaluation

| Precedence | Name                | Symbols           | Associativity |
| ---------- | ------------------- | ----------------- | ------------- |
| 1          | increment (postfix) | ++                | left          |
|            | decrement (postfix) | --                |               |
| 2          | increment (prefix)  | ++                | right         |
|            | decrement (prefix)  | --                |               |
|            | unary plus          | +                 |               |
|            | unary minus         | -                 |               |
| 3          | multiplicative      | \* / %            | left          |
| 4          | additive            | + -               | left          |
| 5          | assignment          | = \*= /= %= += -= | right         |

The table summarizes the operators that have been discussed so far.

Supposed that we run across a complicated expression such as this:

```c
  a = b += c++ - d + --e / -f
```

This expression would be easier to understand if there were parentheses to show how the expression is constructed from subexpressions. With the help of the table, adding prentheses to an expression is easy. From the table, the operator with highest precedence is `++`, used here as a postfix operator, so we put parentheses around `++` and its operand.

```c
  a = b += (c++) - d + --e / -f
```

We now spot a prefix `--` operator and a unary minus oeprator in the expression:

```c
  a = b += (c++) - d + (--e) / (-f)
```

Next is the `/` operator:

```c
  a = b += (c++) - d + ((--e) / (-f))
```

The expression contains two operators with the same precedence, substraction and addition. Whenever two operators with the same precedence are adjacent to an operand, we've got to be careful about associativity. The `-` and `+` operators group from left to right, so parentheses go around the subtraction first, then the addition:

```c
  a = b += (((c++) - d) + ((--e) / (-f)))
```

The only remaining operators are `=` and `+=`. Both operators are adjacent to `b` so we must take associativity into account. Assignment operators group from right to left, so parentheses go around the `+=` expression first, then the `=` expression:

```c
  a = (b += (((c++) - d) + ((--e) / (-f))))
```

The expression is now fully parenthesized.

#### Order of Subexpression Evaluation

C doesn't define the order in whic hsubexpressions are evaluated, with the exception of subexpressions involving the logical _and_, logic _or_, conditional, and comma operators. Thus, in the expression (a + b) \* (c - d) we dont't know whether (a + b) will be evaluated before (c - d).

Most expressions have the same value regardless of the order in whic htheir subexpressions are evaluated. However, this may not be true when a subexpression modifies one of its operands.

```c
  a = 5;
  c = (b = a + 2) - (a = 1);
```

The effect of executing the second statemnt is undefined; the C standard doesn't say what will happen.

> [!WARNING]
> Avoid writing expressions that access the value of a variable and also modify the varaible elsewhere in the expression. Some compilers may produce a warning message such as _"operation on 'a' may be undefined"_ when they encounter such an expression.

To prevent problems, it's a good idea to avoid using the assignment operators in subexpressions; instead, use a series of separate asignments.

Beside the assignment operators, the only operators that modify their operands are increment and decrement. When using these operators, be careful that your expression don't depend on a particular order of evaluation.
