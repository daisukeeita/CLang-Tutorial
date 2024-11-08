# Pointers and Arrays

This chapter covers another application for pointers. When pointers point to array elements, C allows us to perform arithmetic - addition and subtraction - on the pointers, which leads to an alternative way of processing arrays in which pointers take the place of array subscript.

Understanding the connection between pointers and arrays is critical for mastering C: it will give you insight into how C was designed and help you understand existing programs.

**Outline to this Chapter**

| Section                                                                               | Description                                                                                                      |
| ------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| [Section 12.1](#pointer-arithmetic)                                                   | Discusses pointer arithmetic and shows how pointers can be compared using the relational and equality operators. |
| [Section 12.2](#using-pointers-for-array-processing-combining-the-*-and-++-operators) | Demonstrates how we can use pointer arithmetic for processing array elements.                                    |
| [Section 12.3](#using-an-array-name-as-pointer)                                       | Reveals a key fact about arrays and uses it to show how array arguments really work                              |
| [Section 12.4](#pointers-and-multidimensional-arrays)                                 | Shows how to topics of the first three sections apply to multidimensional arrays.                                |
| [Section 12.5](#pointers-and-variable-length-arrays)                                  | Exploring the relationship between pointers and variable-length arrays                                           |

## Pointer Arithmetic

We saw that pointers can point to array elements.

```c
int a[10], *p;

p = &a[0];
```

We can now access `a[0]` through `p`, we can now also sotre the value 5 in `a[0]`.

```c
*p = 5;
```

Making a pointer `p` point to an element of an array `a` isn't particularly exciting. However, by performing **_pointer arithmetic_** (or **_address arithmetic_**) on `p`, we can access the other elements of `a`.

C supports only three forms of pointer arithmetic:

- Adding an integer to a pointer
- Subtracting an integer from a pointer
- Subtracting one pointer from another

### Adding an Integer to a Pointer

```c
int a[10], *p, *q, i;
```

/_ j = an integer _/

Adding an integer "j" to a pointer `p` yields a pointer to the element "j" places after the one that `p` points to. More precisely, if `p` points to the array element `a[i]`, then `p + j` point to `a[i + j]`.

```c
p = &a[2]; /* points to the address of the third element of the array */

q = p + 3; /* points to the address of the sixth element of the array */

p += 6; /* points to the address of the ninth element of the array */
```

### Subtracting an Integer from a Pointer

If `p` points to the array element `a[i]`, then `p - j` points to `a[i - j]`.

```c
p = &a[8]; /* points to the address of the ninth element of the array */

q = p - 3; /* points to the address of the sixth element of the array */

p -= 6; /* points to the address of the third element of the array */
```

### Subtracting One Pointer from Another

When one pointer is subtracted from another, the result is the distance between the pointers. Thus if `p` points to `a[i]` and `q` points to `a[j]`, the `p - q` is equal to `i - j`.

```c
p = &a[5]; /* points to the address of the sixth element of the array */
q = &a[1]; /* points to the address of the second element of the array */

i = p - q; /* i is 4 */
i = q - p; /* i is -4 */
```

> [!WARNING]
> Peforming arithmetic on a pointer that doesn't point to an array element causes undefined behavior. Furthermore, the effect of subtracting one pointer from another is undefined unless both point to elements of the _same_ array.

### Comparing Elements

We can compare pointers using the relational operators(<, <=, >, >=) and the equality operators (== and !=). Using the relational operators to compare two pointers is meaningful only when both point to elements of the same array.

The outcome of the comparison depends on the relative positions of the two elements in the array.

```c
p = &a[5]; /* points to the address of the sixth element of the array */
q = &a[1]; /* points to the address of the second element of the array */
```

The value of `p <= q` is `0` and the value of `p >= q` is `1`.

### Pointers to Compound Literals

It's legal for a pointer to point to an element within an array created by a compound literal.

```c
int *p = (int []){3, 0, 3, 4, 1};
```

`p` points to the first element of a five-element array containing the integers 3, 0, 3, 4, 1.
Using a compound literal save us the trouble of first declaring an array variable and then making `p` point to the first element of that array:

```c
int a[] = {3, 0, 3, 4, 1};
int *p = &a[0];
```

## Using Pointers for Array Processing

Pointer arithmetic allows us to visit the elements of an array by repeatedly incrementing a pointer variable.

```c
#define N 10

int a[N], sum, *p;

sum = 0;

for (p = &a[0]; p < &a[N]; p++) {
  sum += *p;
}
```

The pointer variable `*p` initially points to `a[0]`. Each time through the loop, `p` is incremented; as a result, it points to `a[1]`, then `a[2]`, and so forth. Thee loop terminates when `p` steps past the last element of `a`.

We could just as easily have written the loop without pointers, of course, using subscripting instead. The argument most often cited in support of pointer arithmetic is that it can save execution time. However, that depends on the implementation - some C compilers actually produce better code for loops that rely on subscripting.

### Combining the \* and ++ Operators

C programmers often combine the `*` (indirection) and `++` operators in statements that process array elements. Consider the simple case of storing a value into an array element and then advancing to the next element.

Using array subscripting, we may write:

```c
a[i++] = j;
```

If `p` is pointing to an array element, the corresponding statement would be:

```c
*p++ = j;
```

Because the postfix version of `++` takes precedence over `*`, the compiler sees this as:

```c
*(p++) = j;
```

The value of `p++` is `p`. Thus, the value of `*(p++)` will be `*p` - the object which `p` is pointing.

Of course, `*p++` isn't the only legal combination of `*` and `++`. We could write `(*p)++`, for example, which returns the value of the object that `p` points to, and then increments that object (`p` itself is unchanged).

| Expression       | Meaning                                                        |
| ---------------- | -------------------------------------------------------------- |
| \*p++ or \*(p++) | Value of expression is \*p before increment; increment p later |
| (\*p)++          | Value of expression is *p before increment; increment *p later |
| \*++p or \*(++p) | Increment p first; value of expression is \*p after increment  |
| ++*p or ++(*p)   | Increment *p first; value of expression is *p after increment  |

The one we'll see most frequently is `*p++`, which is handy in loops.

Instead of writing:

```c
for (p = &a[0]; p < &a[N]; p++) sum += *p;
```

We could write:

```c
p = &a[0];
while (p < &a[N]) sum += *p++;
```

The `*` and `--` operators mix in the same way as `*` and `++`.

## Using An Array Name as a Pointer

Pointer arithmetic is one way in which arrays and pointers are related, but it's not the only connection between the two.

Here's another key relationship:

> The name of an array can be used as a pointer to the first element in the array.

This relationship simplifies pointer arithmetic and makes both array and pointers more versatile.

```c
int a[10];

*a = 7; /* stores 7 in a[0] */

*(a + 1) = 12; /* stores 12 in a[1] */
```

Using `a` as a pointer to the first element in the array, we can modify `a[0]`.
We can also modify `a[1]` through the pointer `a + 1`.

In general, `a + i` is the same as `&a[i]` and `*(a + i)` is equivalent to `a[i]`. In other words, array subscripting can be viewed as a form of pointer arithmetic.

The fact that an array name can serve as a pointer makes it easier to write loops that step through an array.

```c
for (p = &a[0]; p < &a[N]; p++)
sum += *p;
```

To simplify the loop, we can replace `&a[0]` by `a` and `&a[N]` by `a + N`.

```c
for (p = a; p < a + N; p++) sum += *p;
```

> [!WARNING]
> Although an array name can be used as a pointer, it's not possible to assign it a new value.
> Attempting to make it point elsewhere is an error.
>
> ```c
> while (*a != 0) a++; /* WRONG */
> ```

## Pointers and Multidimensional Arrays

Just as pointers can point to elements of one-dimensional arrays, they can also point to elements of multidimensional arrays.

### Processing the Elements of a Multidimensional Array

We saw that C stores two-dimensional arrays in row-major order; in other words, the elements of row 0 comes first, followed by the elements or row 1, and so forth.

We can take advantage of this layout when working with pointers. If we make a pointer `p` point to the first element in a two-dimensional array, we can visit every element in the array by incrementing `p` repeatedly.

To initialize all elements of two-dimensional array to zero, the obvious technique would be the nested `for` loops.

```c
int a [NUM_ROWS][NUM_COLS];

int row, col;

for (row = 0; row < NUM_ROWS; row++){
  for (col = 0; col < NUM_COLS; col++) a[row][col] = 0;
}
```

But if we view `a` as one-dimensional array of integers, we can replace the pair of loops by a single loop.

```c
int *p;

for (p = *a[0][0]; p <= &a[NUM_ROWS - 1][NUM_COLS - 1]; p++) +p = 0;
```

The loop begins with `p` pointing to `a[0][0]`. Successive increments of `p` make it point to `a[0][1]`, `a[0][2]`, `a[0][3]`, and so on. When `p` reaches to `a[0][NUM_COLS - 1]`, incrementing it again make `p` point to `a[1][0]`. The process continues until `p` goes past `a[NUM_ROWS -1 ][NUM_COLS - 1]`, the last element in the array.

### Processing the Rows of a Multidimensional Array

To visit the elements of row `i`, we'd initialize `p` to point to element 0 in row `i` in the array `a`.

```c
p = &a[i][0];

/* Or we could simply write */

p = a[i];
```

For any two-dimensional array `a`, the expression `a[i]` is a pointer to the first element in row `i`.

```c
int a[NUM_ROWS][NUM_COLS], *p, i;

for (p = a[i]; p < a[i] + NUM_COLS; p++) +p = 0;
```

Since `a[i]` is a pointer to row `i` of the array `a`, we can pass `a[i]` to a function that's expecting a one-dimensional array as its argument. In other words, a function that's designed to work with one-dimensional arrays will also work with a row belonging to a two-dimensional array.

### Processing the Columns of a Multidimensional Array

Processing the elements in a _column_ of a two-dimensional array isn't as easy, because arrays are stored by row, not by column.

Here's a loop that clears column `i` of the array `a`:

```c
int a [NUM_ROWS][NUM_COLS], (*p)[NUM_COLS], i;

for (p = &a[0]; p < &a[NUM_ROWS]; p++) (*p)[i] = 0;
```

### Using the Name of a Multidimensional Array as a Pointer

Just as the name of a one-dimensional array can be used as a pointer, so can the name of _any_ array, regardless of how many dimensions it has. Some care is required, though.

```c
int a[NUM_ROWS][NUM_COLS];

for (p = *a[0]; p < &a[NUM_ROWS]; p++) (*p)[i] = 0;
```

`a` is not a pointer to `a[0][0]`; instead, it's a pointer to `a[0]`.

This makes more sense if we look at it from the standpoint of C, which regards `a` not as a two-dimensional array but as a one-dimensional array whose elements are one-dimensional arrays.

When used as a pointer, `a` has type `int (*) [NUM_COLS]`.

Knowing that `a` points to `a[0]` is useful for simplifying loops that process the elements of a two-dimensional array.
