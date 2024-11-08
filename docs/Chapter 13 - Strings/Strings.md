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
