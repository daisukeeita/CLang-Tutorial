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
| [ Section 4.5 ](#expression-statements) | Introduces the Expression Statement |

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
