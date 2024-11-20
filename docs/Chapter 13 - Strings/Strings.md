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

Let's say that we need a variable capable of storing a string of up to 80 characters. Since the string will need a null character at the end, we'll declare the variable to be an array of 81 characters.

```c
#define STR_LEN 80

char str[STR_LEN + 1];
```

We defined `STR_LEN` to be `80` rather that `81`, thus emphasizing the fact that `str` can store strings of no more that 80 characters, and then added 1 to `STR_LEN` in declaration of `str`. This is a common practice among C programmers.

Declaring a character array to have length `STR_LEN + 1` doesn't mean that it will always contain a string of `STR_LEN` characters. The length of a string depends on the position of the terminating null character, not the length of the array in which the string is stored.

An array of `STR_LEN + 1` can hold strings of various lengths, ranging from the empty string to strings of length `STR_LEN`.

> [!WARNING]
> When declaring an array of characters that will be used to hold a string, always make the array on character long than the string, because of the C convention that every string is terminated by a null character.
> Failing to leave room for the null character may cause unpredictable results when the program is executed, since functions in the C library assume that string are null terminated.

### Initializing a String Variable

```c
char date1[8] = "June 14";
```

A string variable can be initialized at the same time it's declared.
The compiler will put the characters from `"June 14"` in the `date1` array, then add a null character so that `date1` can be used as a string.

`date1` | J | u | n | e | | 1 | 4 | \0 |

Although `"June 14"` appear to be a string literal, it's not. Instead, C view it as an abbreviation for an array initializer.

What if the initializer is too short to fill the string variable? In that case, the compiler adds extra null characters.

```c
char date2[9] = "June 14";
```

`date2` | J | u | n | e | | 1 | 4 | \0 | \0 |

This behaviour is consistent with C's treatment of array initializers in general. When an array initializer is shorter that the array itself, the remaining elements are initialized to zero.

By initializing the leftover elements of a character array to `\0`, the compiler is following the same rule.

What if the initializer is longer than the string variable? That's illegal for strings, just as it's illegal for other arrays.

> [!WARNING]
> If you're planning to initialize a character array to contain a string, be sure that the length of the array is longer that the length of the initializer. Other wise, the compiler will quietly omit the null character, making the array unusable as a string.

The declaration of a string variable may omit its length, in which case the compiler computes it.

The compiler sets aside eight characters for `date4`, enough to store the characters in `"June 14"` plus a null character. Omitting the length of a string variable is especially useful if the initializer is long, since computing the length by hand is error-prone.

The fact that the length of `date4` isn't specified doesn't mean that the array's length can be changed later. Once the program is compiled, the length of `date4` is fixed at eight.

### Character Arrays versus Character Pointers

```c
char date[] = "June 14";

char *date = "June 14";
```

Comparing the declaration of `date` as an _array_ and `date` as a _pointer_.

Thanks to the close relationship between arrays and pointers, we can use either version of `date` as a string. In particulat, any function expecting to be passed a character array or character pointer will accept either version of `date` as an argument.

However, we must be careful not to make the mistake of thinking that the two version of `date` are interchangeable. There are significant differences between the two:

- In the array version, the characters stored in `date` can be modified, like the elements of any array. In the pointer version, `date` points to a string literal, and we saw that string literals shouldn't be modified.
- In the array version, `date` is an array name. In the pointer version `date` is a variable that can be made to point to other strings during program execution.

If we need a string that can be modified, it's our responsibility to set up an array of characters in which to store the string; declaring a pointer variable isn't enough.

The `pointer` declaration causes the compiler to set aside enough memory for a pointer variable; unfortunately, it doesn't allocate space for a string. Before we can use `p` variable as a string, it must point to an array of character.

```c
char str[STR_LEN + 1], *p;

p = str;
```

`p` now points to the first character of `str`, so we can use `p` as a string.

> [!WARNING]
> Using an uninitialized pointer variable as a string is a serious error. Consider the following example, which attempts to build the string "abc":
>
> ```c
> char *p;
>
> p[0] = 'a'; /* WRONG */
> p[1] = 'b'; /* WRONG */
> p[2] = 'c'; /* WRONG */
> p[3] = '\0'; /* WRONG */
> ```
>
> Since `p` hasn't been initialized, we don't know where it's pointing. Using the pointer to write the characters `a, b, c, and \0` into memory causes undefined behaviour.

## Reading and Writing Strings

Writing a string is easy using either the `printf` or `puts` functions. Reading a string is a bit harder, primarily because of the possibility that the input string may be longer than the string variable into which it's being stored.

To read a string in a single step, we can use either `scanf` of `gets`. As an alternative, we can read strings one character at a time.

### Writing Strings Using `printf` and `puts`

The `%s` conversion specification allows `printf` to write a string.

```c
char str[] = "Are we having fun yet?";

printf("%s\n", str);

/* OUTPUT */
"Are we having fun yet?"
```

`printf` writes the characters in a string one by one until it encounters a null character.
If the null character is missing, `printf` continues past the end of the string until if finds a null character somewhere in memory.

To print just part of a string, we can use the conversion specification `%.ps`, where _p_ is the number of character to be displayed.

```c
printf("%.6s\n", str);

/* OUTPUT */
"Are we"
```

### Reading Strings Using `scanf` and `gets`

The `%s` conversion specification allows `scanf` to read a string into a character array.

```c
scanf("%s", str);
```

There's no need to put the `&` operator in front of `str` in the call of `scanf`; like any array name, `str` is treated as a pointer when passed to a function.

When `scanf` is called, it skips white space, then reads characters and stores them in `str` until in encounters a white-space character.
`scanf` always stores a null character at the end of the string.

A string read using `scanf` will never contain white space. Consequently, `scanf` won't usually read a full line of input; a new-line character will cause `scanf` to stop reading, but so will a space or tab character.
To read an entire line of input at a time, we can use `gets`. Like `scanf`, the `gets` function reads input characters into an array, then stores a null character.

However, `gets` is somewhat different from `scanf`:

- `gets` doesn't skip white space before starting to read the string, `scanf` does.
- `gets` reads until it finds a new-line character, `scanf` stops at any white-space character. Incidentally, `gets` discards the new-line character instead of storing it in the array; the null character takes its place.

```c
char sentence[SENT_LEN + 1];

printf("Enter a sentence:\n");
scanf("%s", sentence);

gets(sentence);
```

To see the difference between `scanf` and `gets`, consider the following program fragment.

Suppose that after the prompt `Enter a sentence:` the enter use enters the line `To C, or not to C: that is the question`.

`scanf` will store the string "To" in `sentence`. The next call of `scanf` will resume reading the line at the space after the word `To`.

Now suppose that we replace `scanf` by `gets`. When the use enters the same input as before, `gets` will store the string "To C, or not to C: that is the question." in `sentence`.

> [!WARNING]
> As they read characters into array, `scanf` and `gets` have no way to detect when it's full. Consequently, they may store characters past the end of the array causing undefined behaviour. `scanf` can be made safer by using the conversion specification `&ns` instead of `%s`, where _n_ is an integer indicating the maximum number of characters to be stored. `gets`, unfortunately, is inherently unsafe; `fgets` is a much better alternative.

### Reading Strings Character by Character

Since both `scanf` and `gets` are risky and insufficiently flexible for many applications, C programmers often write their own input functions. By reading strings one character at a time, these functions provide a greater degree of control than the standard input functions.

If we decide to design our own input functions, we'll need to consider the following issues:

1. Should the function skip white space before beginning to store the string?
2. What character causes the function to stop reading: a new-line character, any white-space character, or some other character? Is this character stored in the string or discarded?
3. What should the function do if the input string is too long to store: discard the extra characters or leave them for the next input operations?

```c
int read_line (char str[], int n) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n') {
    if (i < n) str[i++] = ch;
  }

  str[i] = '\0'; /* terminates string */
  return i; /* number of characters stored */
}
```

Suppose wee need a function that doesn't skip white-space characters, stops reading at the first new-line character, and discards extra characters. The function might have the prototype above.

`str` represents the array into which we'll store the input, and `n` is the maximum number of characters to be read. If the input line contains more than `n` characters, `read_line` will discard the additional characters.

`read_line` consists primarily of a loop that calls `getchar` to read a character and then stores the character in `str`, provided that there's room left. The loop terminates when the new-line character is read.

## Accessing the Characters in a String

Since strings are stores as arrays, we can use subscripting to access the characters in a string. To process every character in a string, `s` for example, we can set up a loop that increments a counter `i` and selects characters via the expressions `s[i]`.

```c
int count_spaces (const char s[]) {
  int count = 0, i;

  for (i = 0; s[i] != '\0'; i++) {
    if (s[i] == ' ') count++;
  }

  return count;
}
```

```c
int count_spaces (const char *s) {
  int count = 0;

  for (; *s != '\0'; s++) {
    if (*s == ' ') count++;
  }

  retun count;
}
```

Suppose we need a function that counts the number of spaces in a string. Using array subscripting, we might write the function in the following example above.

Note that `const` doesn't prevent `count_spaces` from modifying `s`; it's there to prevent the function from modifying what `s` points to. And since `s` is a copy of the pointer that's passed to `count_spaces`, incrementing `s` doesn't affect the original pointer.

Due to making a function that uses a pointer, some questions about how to write string functions:

1. **_Is it better to use array operations or pointer operations to access the characters in a string?_**

- We're free to use whichever is more convenient; we can even mix the two. In the second version of `count_spaces`, treating `s` as a pointer simplifies the function slightly by removing the need for the variable `i`. Traditionally, C programmers lean toward using pointer operations for processing strings.

2. **_Should a string parameter be declared as an array or as a pointer?_**

- The two versions of `count_spaces` illustrate the options: the first version declares `s` to be an array; the second version declares `s` to be a pointer. Actually, there's no difference between the two declarations - recall Section 12.3 that the compiler treats an array parameter as though it had been declared as a pointer.

3. **_Does the form of the parameter (s[] or \*s) affect what can be supplied as an argument?_**

- No. When `count_spaces` is called, the argument could be an array name, a pointer variable, or a string literal - `count_spaces` can't tell the difference.

## Using the C String Library

Some programming languages provide operators that can copy strings, compare strings, concatenate strings, select substrings, and the like. C's operators, in contrast, are essentially useless for working with strings. Strings are treated as arrays in C, so they're restricted in the same ways as arrays - in particular, they can't be copied or compared using operators.

> [!WARNING]
> Direct attempts to copy or compare strings will fail. For example, suppose that `str1` and `str2` have been declared as follows:
>
> `char str1[10], str2[10]`
>
> Copying a string into a character array using the `=` operator is not possible:
>
> ```c
> str1 = "abc"; /* WRONG */
> str2 = str1; /* WRONG */
> ```
>
> We saw in Section 12.3 that using an array name as the left operand of `=` is illegal.
> _Initializing_ a character array using `=` is legal, though:
>
> `char str1[10] = "abc`
>
> In the context of a declaration, `=` is not the assignment operator.
>
> Attempting to compare strings using a relational or equality operator is legal but won't produce the desired results.
>
> `if (str1 == str2)... /* WRONG */`
>
> This statement compares `str1` and `str2` as _pointers_; it doesn't compare the contents of the two arrays. Since `str1` and `str2` have different addresses, the expression `str1 == str2` must have the value 0.
