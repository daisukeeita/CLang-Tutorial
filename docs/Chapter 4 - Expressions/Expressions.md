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

The additive and multiplicative operators are said to be **_binary_** because they require _two_ operands. The **_unary_** operators required _one_ operand. But unary + operator does nothing and it is used primarily to emphasize that a numberic constant is positive.
