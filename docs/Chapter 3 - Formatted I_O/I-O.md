# Formatted Input/Output

`scanf()` and `printf()`, which support formatted reading and writing, are two of the most frequently used functions in C.

**Outline to this Chapter**
| Section | Description |
| -------------- | --------------- |
| [ Section 3.1 ](#the-printf-function) | Describes `printf()` |
| [ Section 3.2 ](#the-scanf-function) | Describes `scanf()` |

## The printf Function

The `printf()` function is designed to display the contents of a string, known as the **_format string_**, with values possibly inserted at specified points in the string. When it is called, `printf` must be supplied with the format string, followed by any values that are to be inserted into the string during printing.

```c
printf(string, expression1, expression2, ...);
```

The values displayed can be constatns, variables, or more complicated expressions.

The format string may contain both ordinary characters and **_conversion specifications_**, which begin with the `%` character. It is a _placeholder_ representing a value to be filled in during printing.

The information that follows the `%` character _specifies_ how to value is _converted_ from its internal form (binary) to printed form (characters).

`%d`: specifies the `printf()` to convert an `int` value from binary to a string of decimal digits.
`%f`: specifies the `printf()` to convert a `float` value from binary to a string of point digits.

> C compilers aren't required to check that the number of conversion specifications in a format string matches the number of output items. Furthermore, compilers aren't required to check that a conversion specification is appropriate for the type of item being printed. If the programmer uses an incorrect specification, the program will simply produce meaningless output.

#### Conversion Specifications

Even though it can be complicatd and hard to read, Conversion Specifications give the programmer a great deal of control over the appearance of output.

% m . p X

**Minimum field width**(m): specifies the minimum number of characters to print. If the value to be printer requires fewer the _m_ characters, the value id right justified within the field. In other words, extra spaces precede the value. Putting a minus sign in front of _m_ cases left justification.

- The specification `%4d` would display the number `'123'` as `' 123'`.
- The specification `%-4d` would display the number `'123'` as `'123 '`

If the value to be printed requries more the _m_ characters, the field width automatically expands to the necessary size.

- The specification `%4d` would display the number `'12345'` as `'12345'`. No digits are lost.

**Precision**(p): the meaning depends on the choice of _X_.

**Conversion Specifier**(X): indicates which conversion should be applied to the value before it is printed. The most common conversion specifiers for numbers are

- `d`: Displays an integer in decimal form. _p_ indicates the minimum number of digits to display; if _p_ is omitted, it is assumed to have the value 1.
- `e`: Displays a floating-point number in exponential format. _p_ indicates how many digits should appear after the decimal point (default is 6). If _p_ is 0, the decimal point is not displayed.
- `f`: Displays a floating-point number in "fixed decimal" format, without an exponent. _p_ has the same meaning as for the `e` specifier.
- `g`: Displays a floating-point number in either exponential format or fixed decimal format, depending on the number's size. _p_ indicates the maximum number of significant digits to be displayed. Furthermore, if the value to be printed has no digits after the decimal pont, `g` doesn't display the decimal pont.

```c
/* Prints int and float values in various formats */

#include <stdio.h>

int main (void) {
  int i;
  float x;

  i = 40;
  x = 839.21f;

  printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
  printf("|%10.3f|%10.3e|%-10g\n", x, x, x);

  return 0;
}
```

#### Escape Sequences

The `\n` code that you often use in format strings is called an **_escape sequence_**. Escape sequence enable strings to contain characters that would otherwise cause problems for the compiler, including nonprinting (control) characters and characters that have a special meaning to the compiler (such as ").

- Alert(bell) | `\a`: causes an autdible beep on most machines
- Backspace | `\b`: moves the cursor back one position
- New line | `\n`: advances the cursor to the beginning of the next line
- Horizontal tab | `\t`: moves the cursor to the next tab stop

## The scanf Function

Just as `printf()` print output in a specified format, `scanf()` reads input according to a particular format. I can also contain both ordinary characters and conversion specification.

In many cases, a `scanf()` format string will contain only conversion specifications:

```c
int i, j;
float x, y;

scanf("%d%d%f%f", &i, &j, &x, &y);
```

`scanf()` will read the line, converting its characters to the numbers they represent, and then assign it to the variables respectively. `scanf()`, like `printf()` contains several traps for the unwary.

The programmer must check that the number of conversion specifications matches the number ofinput variables and that each voncersion is appropritate for the conrresponding variable, the compiler isn't required to check for a possible mismatch. Another trap involves the `&` symbol, which normally precedes each variable in a `scanf()` call. The `&` is usually required, and it's the programmer's responsibility to remember to use it.

> [!WARNING]
> Forgetting to put hte `&` symbol in front of a variable in a call of `scanf()` will have unpredictable - and possibly disastrous - results. A program crash is a common outcome. At the very least, the value that is read fromthe input won't be stored in the varaible; instead, the variable will retain its old value.

#### How scanf Works

`scanf()` can actually do much more. It is essentially a "pattern-matching" function that tries to match up groups of input characters with conversion specifications.

When it is called, `scanf()` begins processing the information in the string, starting at the left. For each conversion specification in the format string, `scanf()` tries to locate an item of the appropriate type in the input data, skipping blank space if necessary. `scanf()` then reads the item, stopping when it encounters a character that can't possibly belong to the item. If any item was read successfully, `scanf()` continues processing the rest of the the format string. If any item is not read successfully, `scanf()` returns immediately without looking at the rest of the format string, or the remaining input data.

As it searches for the beginning of a number, `scanf()` ignores **_white-space character_**. As a result, numbers can be put on a single line or spread out over several lines.

#### Ordinary Characters in Format String

The concept of pattern-matching can be taken one step further by writing format strings that contain ordinary characters in addition to conversion specifications. The action that `scanf()` takes when it processes an ordinary character in a format string depends on whether or not it's a white-space character.

- **White-space Characters**: When it encounters one or more consecutive white-space characters in a format string, `scanf()` repreatedly reads white-space characters from the input until reaches a non-white-space character, which is "put back". The number of white-space characters ihn the format string is irrelevant; one white-space character in the format string will match any number of white-space characters in the input.
- **Other characters**: when it encounters a non-white-space character in a format string, `scanf()` discards the input character and continues processing the format string. If the characters don't match, `scanf()` puts the offending character back into the input, then aborts without further processing the format stringo r reading characters from the input.

#### Confusing printf with scanf

Although calls of `scanf()` and `printf()` may appear similar, there are significant differences between the two functions; ignoring these differences can be hazardous to the health of the program.

One common mistake is to put `&` in front of variables in a call of `printf()`: `printf("%d %d\n", &i &j);`.

Since `scanf()` normally skips white-space characters when looking for data items, there's often no need for a format string to include characters other than conversion specifications. Incorrectly assuming that `scanf()` format strings should resemble `printf()` format string-another common error-may cause `scanf()` to behave in unexpected ways.

> [!WARNING]
> Although `printf()` format strings often end with `\n`, putting a new-line character at the end of `scanf()` format string is usually a bad idea. To `scanf()`, a new-line character in a format string is equivalent to a space; both cause `scanf()` to advance to the next non-white-space character.
