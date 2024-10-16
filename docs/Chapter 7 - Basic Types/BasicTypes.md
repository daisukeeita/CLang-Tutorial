# Basic Types

**Outline to this chapter**

| Section                              | Description                                                                                                                 |
| ------------------------------------ | --------------------------------------------------------------------------------------------------------------------------- |
| [Section 7.1](#integer-types)        | Reveals the full range of integer types                                                                                     |
| [Section 7.2](#floating-types)       | Introduces the `double` and `long double` types, which provides a larger range of values and gretaer precision than `float` |
| [Section 7.3](#character-types)      | Covers the `char` type                                                                                                      |
| [Section 7.4](#type-conversion)      | Tackles the thorny topic of converting a value of one type to an equivalent value of another                                |
| [Section 7.5](#type-definition)      | Shows how to use `typedef` to define new type names                                                                         |
| [Section 7.6](#the-sizeof-character) | Describes the `sizeof` operator, which measures the aount of storage required for a type.                                   |

## Integer Types

C supports two fundamentally different kinds of numberic types: integer types and floating types. Values of an integer type are whole number, while values of a floating type can have a fractional part as well.
The integer types, in turn, are divided into two categories: signed and unsigned.

#### Signed and Unsigned

In C, **_signed_** and **_unsigned_** integers determine how the bits of a number are interpreted, particularly for representing both positive and negative numbers or only positive ones.

1. Signed Integers:

- A signed integers can represent both negative and positive numbers.
- The **_leftmost_** bit is reserve for the **sign**; 0 for positive and 1 for negative.
- For example, in a 4-bit system, the binary representation of `-1` and `1` would be:

```diff
  +1: 0001
  -1: 1111 /* Two's Complacent representation of -1 */
```

The right side of `:` represents a number and the left side of `:` represents the bit. The leftmost part of the bit is the one that represents if the number is positive (0) or negative (1).
The `1111` presentation of negative `1` (-1) is because of "Two's Complacent Representation" that will be discussed later.

2. Unsigned Integers:

- An unsigned integer can only represent positive numbers, including 0.
- Since there is no need for a sign bit, all bits are used for the magnitude of the number.

```diff
  +1: 0001
  +15: 1111 /* Largest value representable with 4 bits */
```

The right side of `:` represents a number and the left side of `:` represents the bit.

By default, integer variables are signed in C - the leftmost bit is reserved for the sign. To tell the compiler that a variable has no sign bit, we declare it to be `unsigned`.
Unsigned numbers ar eprimarily useful for systems programming and low-level, machine-dependent applications.

---

C's integer types come in defferent sizes. The `int` type is usually 32-bits, but it may be 16-bits on older CPUs. Since some programs require numbers that are too large to store in `int` form, C laso provides **_long_** integers.
At times, we may need to conserve memory by instructing the compiler to store a number in less space that normal; such a number is called a **_short_** integer.

```c
  short int
  unsigned short int

  int
  unsigned int

  long int
  unsigned long int
```

Other combinations are synonymous for one of these six types. For example, `long signed int` is the same as `long int`, since integers are always singed unless otherwise specified. Incidentally, the order of the specifiers doesn't matter; `unsigned short int` is the same as `short unsigned int`.

The range of values represented by each of the six integer types varies from one machine to another.
However, there are couple of rules that all compilers must obey.
First, the C standard requires that `short int`, `int`, and `long int` each cover a certain minimum range of values. Second, the standard requires that `int` not be shorter that `short int`, and `long int` not be shorter that `int`. However, it's possible that `short int` represents the same range of values as `int`; also, `int` may have the same range as `long int`.

Integer Types on a 16-bit Machine: Do note that `short int` and `int` have identical ranges.

| Type               | Smallest Value | Largest Value |
| :----------------- | -------------: | ------------: |
| short int          |        -32,768 |        32,767 |
| unsigned short int |              0 |        65,535 |
| int                |        -32,768 |        32,767 |
| unsigned int       |              0 |        65,535 |
| long int           | -2,147,483,648 | 2,147,483,647 |
| unsigned long int  |              0 | 4,294,967,295 |

Integer Types on a 32-bit Machine: Do note that `int` and `long int` have identical ranges.

| Type               | Smallest Value | Largest Value |
| :----------------- | -------------: | ------------: |
| short int          |        -32,768 |        32,767 |
| unsigned short int |              0 |        65,535 |
| int                | -2,147,483,648 | 2,147,483,647 |
| unsigned int       |              0 | 4,294,967,295 |
| long int           | -2,147,483,648 | 2,147,483,647 |
| unsigned long int  |              0 | 4,294,967,295 |

Integer Types on a 64-bit Machine:
| Type | Smallest Value | Largest Value |
| :----------------- | -------------: | ------------: |
| short int | -32,768 | 32,767 |
| unsigned short int | 0 | 65,535 |
| int | -2,147,483,648 | 2,147,483,647 |
| unsigned int | 0 | 4,294,967,295 |
| long int | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 |
| unsigned long int | 0 | 18,446,744,073,709,551,615 |

The ranges shown in Tables aren't mandated by the C standard an may vary from one compiler to another. One way to determine the ranges of integer types for a particular implementation is to check the `<limits.h>` header. This header defines macros that represent the smallest and largest values of each integer type.
