# Strings

Although we've used `char` variables and arrays of `char` values, we still lack any convenient way to process a series of characters (a _string_, in C terminology).
We'll remedy that defect in this chapter, which covers both string _constants_ (or _literal_, as they're called in the C standard) and string _variables_, which can change during the execution of a program.

**Outline to this Chapter**

| Section                                               | Description                                                                                |
| ----------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| [Section 13.1](#string-literals)                      | Explains the rules that govern string literals                                             |
| [Section 13.2](#string-variables)                     | Shows how to declare string variables                                                      |
| [Section 13.3](#reading-and-writing-strings)          | Describes ways to read and write strings                                                   |
| [Section 13.4](#accessing-the-characters-in-a-string) | Shows how to write functions that process strings                                          |
| [Section 13.5](#using-the-c-string-library)           | Covers some of the string-handling functions in the C library                              |
| [Section 13.6](#string-idioms)                        | Presents idioms that are often used when working with strings                              |
| [Section 13.7](#array-of-strings)                     | Describes how to set up arrays whose elements are pointers to strings of different lengths |

## String Literals

A **_string literal_** is a sequence of characters enclosed within double quotes.

### Escape Sequences in String Literals

String literals may contain the same scape sequences as character constants. We've used character escapes in `printf` and `scanf` format strings for some time.

Although octal and hexadecimal escapes are also legal in string literals, they're not as common as character escapes.

### Continuing a String Literal

If we find that a string literal is too long to fit conveniently on a single line, C allows us to continue it on the next line, provided that we end the first line with a backslash character "\".

```c
printf("When you come to a fork in the road, take it. \
 --Yogi Berra");
```

In general, the \ character can be used to join two or more lines of a program into a single line (a process that the C standard refers to as "splicing").
The \ technique has one draw back: the string must continue at the beginning of the next line, thereby wrecking the program's indented structure.

There's better way to deal with long string literals: when two or more string literals are adjacent (separated only by white space), the compiler will join them into a single string. This rule allows us to split a string literal over two or more lines.

```c
printf("When you ome to a fork in the road, take it. "
       "--Yogi Berra");
```

### How String Literals Are Stored

We've used string literals often in calls of `printf` and `scanf`. But when we call `printf` and supply a string literal as an argument, what are we actually passing?

In essence, C treats string literals as character arrays. When a C compiler encounters a string literal of length _n_ in a program, it sets aside _n + 1_ bytes of memory for the string.
This area of memory will contain the characters in the string, plus one extra character - the **null character** - to mark the end of the string.

The null character is a byte whose bits are all zero, so it's represented by the `\0` escape sequence.

> [!WARNING]
> Don't confuse the null character ('\0') with the zero character ('0'). The null character has the code 0; the zero character has a different code (48 in ASCII).

"abc"
a | b | c | \0

The string literal "abc" is stored as an array of four characters (a, b, c, and \0).

Since a string literal is stored as an array, the compiler treats it as a pointers of type `char *`. Both `printf` and `scanf`, for example, expect a value of type `char *` as their first argument.

When `printf` is called, it's passed the address of "abc" (a pointer to where the letter `a` is stored in memory).

```c
printf("abc");
```

### Operations on String Literals

In general, we can use a string literal wherever C allows a `char *` pointer.

```c
char *p;
p = "abc";
```

This assignment doesn't copy the characters in "abc"; it merely makes `p` point to the first character of the string.

C allows pointers to be subscripted, so we can subscript string literals.

```c
char ch;
ch = "abc"[1];
```

The new value of `ch` will be the letter 'b'. The other possible subscripts are `0` (which would select the letter 'a'), 2 (the letter 'c'), and 3 (the null character).

> [!WARNING]
> Attempting to modify a string literal causes undefined behavior:
>
> ```c
> char *p = "abc";
> *p = 'd'; /* WRONG */
> ```
>
> A program that tries to change a string literal may crash of behave erratically.

### String Literals versus Character Constants

A string literal containing a single character isn't the same as a character constant.

The string literal 'a' is represented by a _pointer_ to a memory location that contains the character `a` (followed by a null character).
The character constant 'a' is represented by an _integer_ (the numerical code for the character).

> [!WARNING]
> Don't ever use a character when a string is required (vice versa).
> The call `printf("\n");` is legal, because `printf` expects a pointer as its first argument.
> The call `printf('\n');` isn't legal, however.

## String Variables

Some programming languages provide a special `string` type for declaring string variables. C takes a different tack: any one-dimensional array of characters can be used to store a string, with the understanding that the string is terminated by a null character.

This approach is simple, but has significant difficulties. It's sometimes hard to tell whether an array of characters is being used as a string. If we write out own string-handling functions, we've got to be careful that they deal properly with the null character.
Also, there's no faster way to determine the length of a string that a character-by-character search for the null character.
