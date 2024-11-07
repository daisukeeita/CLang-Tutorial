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
