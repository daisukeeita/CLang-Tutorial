# Arrays

So far, the only variables we've seen are **_scalar_**: capable of holding a single data item. C also supports **_aggregate_** variables, which can store collections of values.
There are two kinds of aggregates in C: arrays and structures.

**_Outline to this Chapter_**
| Section | Description |
|--------------- | --------------- |
| [Section 8.1](#one-dimensional-array) | Shows how to declare and use arrays in one-dimension |
| [Section 8.2](#multidimensional-array) | Show how to declare and user arrays in two or more dimension |
| [Section 8.3](#variable-length-arrays) | Covers Variable-Length Arrays |

## One-Dimensional Arrays

An **_array_** is a data structure containing a number of data vlues, all of which have the same type. These value, known as **_elements_**, can be individually selected by their position within the array.

The simples kind of array has just one dimension. The elements of a one-dimensional array are conceptually arranged one after another in a single row (or column).

To declare an array, we must specify the _type_ of the array's elements and the _number_ of elements.

```c
int a[10];
```

The elements of an array may be of any type; the length of the array can be specified by any integer constant expression.

```c
#define N 10

int a[N];
```

#### Array Subscripting

To access a particular element of an array, we write the array name followed by an integer value in square brackets (this referred to as **_subscripting_** or **_indexing_** the array).
Array elements are always numbered starting from 0, so the elements of an array of length `n` are indexed from 0 to n-1.

If `a` is an array with 10 elements, they're designated by `a[0]`, `a[1]`, ..., `a[9]` (9 is the last element).

Arrays and `for` loops go hand-in-hand. Many programs contain `for` loops whose job is to perform some operations on every element in an array.

```c
#define N 10

int a[N] = {0};

for (int i = 0; i < N; i++) a[i] = 0; /* clears a */

for (int i = 0; i < N; i++) scanf("%d", &a[i]); /* reads data into a */

for (int i = 0; i < N; i++) sum += a[i]; /* sums the elements of a */
```

> [!WARNING]
> C doesn't require that subscript bounds be checked; if a subscript goes out of range, the program's behaviour is undefined.
> One cause of subscript going out of bounds: forgetting that an array with `n` elements is indexed from 0 to n-1, not 1 to n.
>
> With some compilers, this kind of mistake can cause an infinite loop. When `i` reaches 10, the program stores 0 into `a[10]`. But `a[10]` doesn't exist, so 0 goes into memory immediately after `a[9]` in memory, then `i` will be reset to 0, causing the loop to start over.

An array subscript may be any integer expression:

```c
a[i + j * 10] = 0;
```

And this expression can have side effects to subscript:

```c
i = 0;
while (i < N)
  a[i++] = 0;
```

> [!WARNING]
> Be careful when an array subscript has a side effect:
>
> ```c
> i = 0;
> while (i < N)
>   a[i] = b[i++];
> ```
>
> The expression `a[i] = b[i++]` accesses the value if `i` and also modifies `i` elsewhere in the expression, which can cause undefined behaviour.

#### Array Initialization

An array, like any other variable, can be given an initial value at the time it's declared.
The most common form of **_array initializer_** is a list of constant expressions enclosed in braces and separated by commas:

```c
int a [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
```

If the initializer is shorter that the array, the remaining elements of the array are given the value of 0:

```c
int a[10] = {1, 2, 3, 4, 5, 6}; /* initial value of a is {1, 2, 3, 4, 5, 6, 0, 0, 0, 0} */
```

It's illegal for an initializaer to be completely empty. It's also illegal for an initializer to be longer that the array it initializes.

If an initializer is present, the length of the array may be omitted:

```c
int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
```

The compiler uses the length of the initializer to determine how long the array is. The array still has a fixed number of elements, just as if we had specified the length explicitly.

#### Designated Initializers

It's often the case that relatively few elements of an array need to be initialized explicitly; the other elements can be given default values.

```c
int a[15] = {0, 0, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 48}
```

We want element 2 of the array to be 29, element 9 to be 7, and element 14 to be 48, but the other valuees are just zero.
**_designated initializers_** can be used to solve this problem:

```c
int a[15] = {[2] = 29, [9] = 7, [14] = 48};
```

Each number in brackets is said to be a **_designator_**.
Designated initializers have an advantage: the order in which the elements are listed no longer matters.

```c
int a[15] = {[14] = 48, [9] = 7, [2] = 29};
```

Designators must be integer constant expressions. If the array being initialized has length n, each designator must be between 0 and n-1. However, if the length of the array is omitted, a designator can be any nonnegative integer.
An initializer may use both the older (element-by-element) technique and the new (designated) technique:

```c
int c[10] = {5, 1, 9, [4] = 3, 7, 2, [8] = 6};
```

This initializer specifies that the array's first three elements will be 5, 1, and 9. ELements 4 will have the value 3. The two elements after element 4 will be 7 and 2. Finally, element 8 will have the value 6. All elements for which no value is specified will default to zero.

#### Using the sizeof Operator with Arrays

The `sizeof` operator can determine the size of an array (in bytes). If `a` is an array of 10 integers, the `sizeof(a)` is typically 40 (assuming that each integer requires four bytes).
We can also use `sizeoof` to measure the size of an array element, such as `a[0]`. Dividing the array size by the element size gives the length of the arrays:

```
sizeof(a) / sizeof(a[0])
```

Some programmers use this expression when the length of the array is needed.

```c
for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) a[i] = 0;
```

With this technique, the loop doesn't have to be modified if the array length should change at a later date.
One minor annoyance is that some compilers produce a warning message for the expression `i < sizeof(a) / sizeof(a[0])`.
To avoid a warning, we can add a cast that converts `sizeof(a) / sizeof(a[0])` to a signed initeger:

```c
for (int i = 0; i < (int) (sizeof(a) / sizeof(a[0])); i++) a[i] = 0;
```

## Multidimensional Arrays

An array may have any number of dimensions.

```c
int m[5][9];
```

The array `m` has 5 rows and 9 columns. Bothe rows and columns are indexed from 0.

To access the element of `m` in row i, column j, we must write `m[i][j]`. The expression `m[i]` designates row i of m, and `m[i][j]` then selects element j in this row.

Although we visualize two-dimensional arrays as tables, that's not the way they're actually store in computer memory. C stores arrays in **_row-major order_**, with row 0 first, then row 1, and so forth.

Just as `for` loops go hand-in-hand with one-dimensional arrays, nested `for` loops are ideal for processing multidimensional arrays.
Multidimensional arrays play a lesser role in C than in many other programming languages, primarily because C provides a more flexible way to store multidimensional data: arrays of pointers.

#### Initializing a Multidimensional Array

We can create an initializer for a two-dimensional array by nesting one-dimensional initializers:

```c
int m[5][9] = {
  {1, 1, 1, 1, 1, 0, 1, 1, 1},
  {0, 1, 0, 1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 1, 0, 0, 1, 0},
  {1, 1, 0, 1, 0, 0, 0, 1, 0},
  {1, 1, 0, 1, 0, 0, 1, 1, 1}
}
```

Each inner initializer provides values for one row of the matrix. Initializers for higher-dimensional arrays are constructed in a similar fasion.

We can also omit the inner braces:

```c
int m[5][9] = {
  1, 1, 1, 1, 1, 0, 1, 1, 1,
  0, 1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 1, 0, 0, 1, 0,
  1, 1, 0, 1, 0, 0, 0, 1, 0,
  1, 1, 0, 1, 0, 0, 1, 1, 1
};
```

> [!WARNING]
> Omitting the inner braces in a multidimensional array initializer ca be risky, since an extra element (or missing element) will affect the rest of the initializer. Leaving out the braces causes some compilers to produce a warning message such as "missing braces around initalizer"

#### Constant Arrays

Any array, whether one-dimensional or multidimensional, ca be made "constant" by starting its declaration with the word `const`:

```c
const char hex_chars[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F'
};
```

An array that's been declared `const` should not be modified by the program; the compiler will detect direct attempts to modify an element.

Declaring an array to be `const` has a couple of primary advantages. It documents that the program won't change the array, which can be valuable information for someone reading the code later. It also helps the compiler catch errors, by informing it that we dont't intend to modify the array.

## Variable-Length Arrays
