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

#### Integer Constants

C allows integer constants to be written in decimal, octa, or hexadecimal.

- **_Decimal_** constants contain digits between 0 and 9. but must not begin with a zero:

15 255 23767

- **_Octal_** constants contain only digits between 0 and 7, and _must_ begin with a zero:

017 0377 077777

- **_Hexadecimal_** constants contain digits between 0 and 9 and letters between 'a' and 'f', and always begin with 0x:

0xf 0xff 0x7fff

The letters in a hexadecimal constant may be either upper or lower case:

0xff 0xfF 0xFf 0xFF 0XfF 0XFf 0XFF

Keep in mind that octal and gexadecimal are nothing more than an alternative way of writing numbers; they have no effect on how the numbers are actually stored. Integers are always store in binary, regardless of what notation we'ved used to express them.

The rules for detemining the types of an _octal_ or _hexadecimal_ constant ar eslightly different: the compiler will go through the types `int`, `unsigned int`, `long int`, and `unsigned long int` until it finds one capable of representing the constant.
To force the compiler to treat a constant as a long integer, just follow it with the letter "L" or "l".

15L 0377L 0x7fffL

To indicate that a unsigned, put the letter "U" or "u" after it.

15U 0377U 0x7fffU

"L" and "U" may be used in combination to show that a constant is both `long` and `unsigned`: 0xfffffUL. The order of the "L" and "U" doesn't matter, nor does their case.

#### Integer Overflow

The behavior when integer overflow occurs depends on whether the operands were signed or unsigned. When overflow occurs furing an operation on _signed_ integers, the program's behavior may vary. Most likely theresult of the operation will simply be wrong, but the program could crash or exhibit other undesirable behavior.
When overflow occurs during an operation on _unsigned_ integers, though, the result _is_ defined: we get the correct answer modulo 2^n, where "n" is the number of bits used to store the result.

#### Reading an Writing Integers

Suppose that a program isn't working because one of its `int` varaibles is overflowing. Our first thought is to change the type of the variable from `int` to `long int`. But we also need to see how the change will affect the rest of the program.
In particular, we must check whether the variable is used in a call of `printf()` or `scanf()`.

Reading and writing unsigned, short, and long integers requires several new conversion specifiers:

- When reading or writing an _unsigned_ integer, use the letter "u", "o", or "x" instead of "d" in the conversion specification. If the "u" specifier is present, the number is read or written in decimal notation; "o" indicates octal notation, and "x" indicates hexadecimal notation.

```c
unsigned int u;

scanf("%u", &u);  /* reads u in base 10 */
printf("%u", u);  /* writes u in base 10  */
scanf("%o", &u);  /* reads u in base 8 */
printf("%o", u);  /* writes u in base 8 */
scanf("%x", &u);  /* reads u in base 16 */
printf("%x", u);  /* writes u in base 16 */
```

- When reading or writing a _short_ integer, put the letter "h" in front of "d", "o", "u", or "x".

```c
short s;

scanf("%hd", &s);
printf("%hd", s);
```

- When reading or writing a _long_ integer, put the letter "l" in front of "d", "o", "u", or "x".

```c
long l;

scanf("%ld", &l);
printf("%ld", l);
```

- When reading or writing a _long long_ integer (C99 only), put the letters "ll" in front of "d", "o", "u", or "x".

```c
long long ll;

scanf("%lld", &ll);
printf("%lld", ll);
```

## Floating Types

The integer types aren't suitable for all applications. Sometimes we'll need variables that ca store numbers with digits after the decimal point, or numbers that are exceedingly large or small. Numbers like these are store in floating-point format. C provides three **_floating types_**, corresponding to defferent floating-point formats

`float` Single-precision floating-point
`double` Double-precision floating-point
`long double` Extended-precision floating-point

`float` is suitable when the amount of precision isn't critical (calculating temperatures to one decimal point, for example).
`double` provides greater precision - enough for most programs.
`long double`, which supplies the ultimate in precision, is rarely used.

Macros that define the characteristics of the floating types can be found in the `<float.h>` header.

#### Floating Constants

Floating constants can be written in a variety of ways.

57.0 57. 57.0e0 57E0 5.7e1 5.7e+1 .57e2 570.e-1

A floating constatnt must contain a decimal point and/or an exponent; the exponent indicates the power of 10 by which the number is to be scaled. If an exponent is present, it must be preceded by the letter "E" or "e". An optional `+` or `-` sign may appear after the "E" or "e".

#### Reading and Writing Floating-Point Numbers

The conversion specifications `%e`, `%f`, and `%g` are used for reading and writing single-precision floating-point numbers. Values of types `double` and `long double` require slightly different conversions.

- When _reading_ a value of type `double`, put the letter "l" in front of "e", "f", or "g"

```c
double d;

scanf("%lf", &d);
```

Use "l" only in `scanf()` format string, not a `printf()` string. In a `printf()` format string, the "e", "f", and "g" conversions can be used to write either `float` or `double` values.

- When reading or writing a value of type `long double`, put the letter "L" in front of "e", "f", or "g".

```c
long double ld;

scanf("%Lf", &ld);
printf("%Lf", ld);
```

## Character Types

The only remaining basic type is `char`, the character type. The values of type `char` can vary from one computer to another, because different machines may have different underlying character sets.

> Character Sets
> Today's most popular character set is **_ASCII_**, a 7-bit code capable of representing 128 characters. ASCII often extended to a 256-character code know as **_Latin-1_** that provides the character necessary for Western European and many African Languages.

#### Operations on Characters

Working with characters in C is simple, becuase of one fact: C treats characters as small integers. In ASCII, for example, character codes ranges from 0000000 to 1111111, which can think of as the integers from 0 to 127. The character "a" has the value 97, "A" has the value of 65.

The connection between characters and integers in C is so strong that character constants actually have `int` type rather that `char` type.

```c
char ch;
int i;

i = 'a';  /* i is now 97 */
ch = 65;  /* ch is now 'A' */
ch = ch + 1;  /* ch is now 'B' */
ch++;   /* ch is now 'C' */
```

Characters can be compared, just as numbers can. The following `if` statemtn checks whether `ch` contains a lower-case letter; if so, it conversts `ch` to uppercase.

```c
  if ('a' <= ch && ch <= 'z')
    ch = ch - 'a' + 'A';
```

#### Signed and Unsigned Characters

Since C allows characters to be used as integers, it shouldn't be surprising that the `char` type - like the integer types - exists in both signed and unsigned version.

Signed character normally have values between -128 and 127, while unsigned characters have values between 0 and 255.

> [!TIP]
> Don't assume that `char` is either signed or unsigned by default. If it matters, use `signed char` or `unsigned char` instead of `char`.

#### Escape Sequences

A character constant is usually one character enclosed in single quotes, as we've seen in previous examples. However, certain special character - including the new-line character - can't be written in this way, becuase they're invisible or because they cna't be entered from the keyboard.

C provides a special notation, the **_escape sequence_** so that programs can deal with every character in the underlying character set.

There are two kinds of escape sequences: **_character escapes_** and **_numeric escapes_**.

| Name         | Escape Sequence |
| ------------ | :-------------: |
| Alert (bell) |       \a        |
| Backspace    |       \b        |
| Form Feed    |       \f        |
| New Line     |       \n        |

A partial list of character escapes.

Character escapes are handy, but they have a problem: the list of character escapes doesn't include all the nonprinting ASCII characters, just the most common. Character escapes are also useless for representing characters beyong the basic 128 ASCII characters. Numeric escapes, which can represent _any_ character, are the solution to this problem.

- An **_octal escape sequence_** consists of the \ character followed by an octal number with at most three digits. This number must be representable as an unsigned character, so its maximum value is normally 377 octal. Octal numbers in escape sequences - unlike octal constant - don't have to begin with 0.

- A **_hexadecimal escape sequence_** consists of \x followed by a hexadecimal number. Although C places no limit on the number of digits in the hexadecimal number, it must be representable as an unsigned character. The x must be in lower case, but the hex digits ("b") can be uppoer or lower case.

When used as a character constant, an escape sequence must be enclosed in single quotes. For example, a constant representing the escape character would be written '\33' or '\x1b'. Escape sequences tend to get a bit cryptic, so it is often a good idea to give them names using `#define`.

#### Reading and Writing Characters usng scanf and printf

The `%c` conversion specification allows `scanf()` and `printf()` to read and write single characters.

```c
  char ch;

  scanf("%c", &ch); /* reads a single character */
  printf("%c", ch); /* writes a single character */
```

`scanf()` doesn't skip white-space characters before reading a character. If the nex unread character is a space, then the variable `ch` in the example will contain a space after `scanf()` returns.

#### Reading and Writing Characters using getchar and putchar

C provides other ways to read and write single characters. In particular, we can use the `getchar()` and `putchar()` functions instead of calling `scanf()` and `printf()`.

`putchar()` writes single character.
Each time `getchar()` is called, it reads one character, which is returns. In order to save this character, we must use assignment to store it in a variable.

```c
  putchar(ch);
  ch = getchar(); /* reads a character and stores it in ch */
```

`getchar()` actually returns an `int` value rather than a `char` value. As a result, it's not unusual for a variable to have type `int` rather than `char` if it will be used to store a character read by `getchar()`. Like `scanf()`, `getchar()` doesn't skip white-space characters as it reads.

> [!WARNING]
> Be carefull if you mix `getchar()` and `scanf()` in the same program. `scanf()` has a tendency to leave behind characters that it has "peeked" at but not read, including the new-line character.
> The call of `scanf()` will leave behind any characters taht weren't consumed during the reading of `i`, including, but not limited to, the new-line character. `getchar()` will fethc the first leftover character, which wasn't what we had in mind.

## Type Conversion

Computers tend to be more restrictive that C when it comes to arithmetic. For a computer to perform an arithmetic operation, the operands must usually be of the same size (the same number of bits) and be stored in the same way.

A computer may be able to add two 16-bit integers directly, but not a 16-bit integer and a 32-bit integer or a 32-bit integer and a 32-bit floating-point number.

C, on the other hand, allows the basic types to be mixed in expressions. We can combine integers, floating-point numbers, nad even characters in a single expression.

The C compiler may then have to generate instructions that convert some operands to different types so that the hardware will be able to evaluate the xpression. If we add a 16-bit `short` and a 32-bit `int`, the compiler will arrange for the `short` value to be converted to 32 bits. if we add an `int` and a `float`, the compiler will arrange for the `int` to be converted to `float` format.

Because the compiler handles these conversions automatically, without programmer's involvement, they're known as **_implicit conversions_**. C also allows the programmer to perform **_explicit conversions_**, using the cast operator. Unfortunately, the rules for performing implicit conversions are somewhat complex, primarily becuase C has so many different arithmetic types.

Implicit conversions are performed in the following instructions:

- When the operands in an arithmetic or logical expression don't have the same type.
- When the type of the expression on the right side of an assignment doesn't match the type of the variable on the left side.
- When the type of an argument in a function call doesn't match the type of the corresponding parameter.
- When the type of the expression in a `return` statement doesn't match the function's return type.

#### The Usual Arithmetic Conversions

The usual arithmetic conversions are applied to the operands of most binary opertors, including the arithmetic, relational, and equality operators. The strategy behind the usual arithmetic conversions is to convert operands to the "narrowest" type that will safely accommodate both values.

The types of the operands can often be made to match by converting the operand of the narrower type to the type of the other operand (this act is known as **_promotion_**).
Among the most commong promotions are the **_integral promotions_**, which convert a character or short integer to type `int` (or to `unsigned int` in some cases).

We can divide the rules for performing the usual arithmetic conversions into two cases:

- **_The type of either operand is a floating type_**: that is, if one operand has type `long double`, then convert the other operand to type `long double`. Otherwise, if one operand has type `double`, convert the other operand to type `double`. Otherwise, if one operand has type `float`, convert the other operand to type `float`.

long double <- double <- float

- **_Neither operand type is a floating type_**: first perform integral promotion on both operands. Then use the following diagram to promote the operand whoe type is narrower.

unsigned long int <- long int <- unsigned int <- int

#### Conversion During Assignment

The usual arithmetic conversions don't apply to assignment. Instead, C follows the simple rule that the expression on the right side of the assignment is converted to the type of the variable on the left side.

#### Casting

Although C's implicit conversions are convenient, we sometimes need da greater degree of control over type conversion. For this reason, C provides **_casts_**.

( type-name ) expression

A cast _type-name_ specifies the type to which the expressions hould be converted.

```c
  float f, frac_part;

  frac_part = f - (int) f;
```

The cast expression `(int) f` represents the result of converting the value of `f` to type `int`. C's usual arithmetic conversions then require that `(int) f` be converted back to type `float` before the subtraction can be performed.

Cast expressions enable us to document type conversions that would take place anyway:

```c
  i = (int) f; /* f is converted to int */
```

## Type Definitions

Using `typedef` to define `Bool` causes the compiler to add `Bool` to the list of type names that it recognizes.

```c
  typedef int Bool;
```

`Bool` can now be used in the same way as the built-in type names - in variable declarations, cast expressions, and elsewhere.

```c
  Bool flag; /* same as int flag */
```

The compiler treats `Bool` as a synonym for `int`; thus, `flag` is really nothing more that an ordinary `int` variable.

#### Advantages of Type Definitions

Type definitions can make a program more understandable, assuming that the programmer has been careful to choose meaningful type names.

```c
  typedef float Dollars;

  Dollars cash_in, cash_out;
```

Type definitions can also make a program easier to modify. If we later decide that `Dollars` should really be defined as `double`, all we need do is change the type definition.

#### Type Definitions and Portability

Type definitions are an important tool for writing portable programs. One of the problems with moving a program from one computer to another is that types may have different ranges on different machines.

> [!TIP]
> For greater portability, consider using `typedef` to define new names for integer types.

The C library itself uses `typedef` to create names for typpes that can vary from one C implementation to another; these types often have names that end with `_t`, such as `ptrdiff_t`, `size_t`, and `wchar_t`.

```c
  typedef long int ptrdiff_t;
  typedef unsigned long int size_t;
  typedef int wchar_t;
```

## The sizeof Operator

The `sizeof()` operator allows a program to determine how much memory is required to store values of a particular type.

sizeof ( type-name )

The value of the expression is an unsigned integer representing the number of byts required to store a value belonging to _type-name_. `sizeof(char)` is always 1, but the sizes of the other types may vary.
On a 32-bit machine, `sizeof(int)` is normally 4.
