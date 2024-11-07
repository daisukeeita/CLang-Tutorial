# Pointers

Pointers are one of C's most inmportant - and most often misunderstood - features.

_Outline to this Chapter_

| Section                                                | Description                                                               |
| ------------------------------------------------------ | ------------------------------------------------------------------------- |
| [Section 11.1](#pointer-variables)                     | Discussion of memory addresses and their relationsip to pointer variables |
| [Section 11.2](#the-address-and-indirection-operators) | Introduces the address and indirection operator                           |
| [Section 11.3](#pointer-assignment)                    | Covers Pointer Assignment                                                 |
| [Section 11.4](#pointers-as-arguments)                 | Explains how to pass pointer to functions                                 |
| [Section 11.5](#pointers-as-return-values)             | Discusses returning pointers from functions                               |

## Pointer Variables

The first step in understanding pointers is visualizing what they represent at the machine level.
In most modern computers, main memory is divided into **_bytes_**, with each byte capable of storing eight bits of information.

-- 0 -- 1 -- 0 -- 1 -- 0 -- 0 -- 1 -- 1 --

Each byte has a unique **_address_** to distinguish it from the other bytes in memory.
If there are _n_ bytes in memory, we can thinks of addresses as numbers that range from 0 to n-1.

| Address | Content  |
| :-----: | :------: |
|    0    | 01010011 |
|    1    | 01110101 |
|    2    | 01110011 |
|    3    | 01100001 |
|    4    | 01101110 |
|         |   ...    |
|   n-1   | 01000011 |

An executable program consists of both code and data. Each variable in the program occupies one or more bytes of memory; the address of the first byte is said to be the address of the variable.

| Address | Content      |
| ------- | ------------ |
| 1999    | ...          |
| 2000    | variable `i` |
| 2001    | variable `i` |
| 2002    | ...          |

In the figure above, the variable `i` occupies the bytes at addresses `2000` and `2001`, so `i`'s address is `2000`.

Here's where pointers come in. Although addresses are represented by numbers, their range of values may differ from that of integers, so we can't necessarily store them in ordinary integer variables.
We can, however, store them in special **_pointer variables_**.

When we store the address of a variable `i` in the pointer variable `p`, we say that `p` "points to " `i`.
In other words, a pointer is nothing more than an address, and a pointer variable is just a variable that can store and address.

#### Declaring Pointer Variables

A pointer variable is declared in much the same way as an ordinary variable. The only difference is that the name of a pointer variable must be preceeded by an asterisk.

```c
int *p;

int i, j, a[10], b[20], *p, *q;
```

This declaration states that `p` is a pointer variable capqable of pointing to **_objects_** of type `int`.
Pointer variables can appear in declarations along with other variables.

C requires that every pointer variable point only to objects of a particular type (the **_referenced type_**):

```c
int *p; /* points only to integers */
double *q; /* points only  to double */
char *r; /* ponits only to characters */
```

## The Address and Indirection Operator

C provides a pair of operators designed specifically for use with pointers.
To find the address of a variable, we use the `&` (address) operator. If `x` is a variable, then `&x` is the address of `x` in memory.
To gain access to the object that a pointer points to, we use the `*` (indirection) operator. If `p` is a pointer, the `*p` represents the object to which `p` currently points.

#### The Address Operator

Declaring a pointer varaible sets aside space for a pointer but doesn't make it point to an object.

```c
int *p; /* points nowhere in particular */
```

It's crucial to initialize `p` before we use it. One way to initialize a pointer variable is to assign it the address of some variable using the `&` operator.

```c
int i, *p;

i = &i;
```

By assigning the address of `i` to the variable `p`, this statement make `p` points to `i`.

It's also possible to initialize a pointer variable at the time we declare it:

```c
int i;
int *p = &i;

int i, *p = &i;
```

#### The Indirection Operator

Once apointer varaible points to an object, we can use the `*` (indirection) operator to access what's stored in the object.
If `p` points to `i`, we can print the value of `i` as follows:

```c
printf("%d\n", *p);
```

`printf` will display the _value_ of `i`, not the _address_ of `i`.

As long a `p` point to `i`, `*p` is an **_alias_** for `i`. Not only does `*p` have the same value as `i`, but changing the value of `*p` also changes the value of `i`.

> [!WARNING]
> Never apply the indirection operator to an uninitialized pointer variable. If point variable `p` hasn't been initialized, attempting to use the value of `p` in any way causes undefined behavior.
>
> Assigning a value to `*p` is particularly dangeroud. If `p` happens to contain a valid memory address, the following assignment will attempt to modify the data stored at that address.
>
> If the location modified by this assignment belongs to the program, it may behave erratically; if it belong to the operating system, the program will most likely crash.
> The compiler may issue a warning that `p` is uninitialized, so pay close atention to any warning message it'll output.

## Pointer Assignment

C allows the use of the assignment operator to copy pointers, provided that they have the same type.

```c
int i, j, *p, *j;

p = &i;
```

The statement `p = &i` is an example of pointer assignment; the address of `i` is copied into `p`.

Another example of pointer assignment is `q = p`. This statement copies the contents of `p` (the address if `i`) into `q`, in effect making `q` point to the same place as `p`.

Both `p` and `q` now point to `i`, so we can change `i` by assigning a new value to either `*p` or `*q`.

```c
*p = 1;

// or

*q = 2;
```

Any number of pointer variables may point to the same object. Be careful not to confuse.

## Pointers as Arguments

We saw in Section 9.3 that a variable supplied as an argument in a function call is protected against change, because C passess arguments by value. This property of C can be a nuisance if we want the function to be able to be able to modify the variable.

```c
void decompose (double x, long int_part, double frac_part) {
  int_part = (long) x; /* drops the fractional part of x */
  frac_part = x - int_part;
}

decompose(3.14159, i, d);
```

At the beginning of the call, `3.14159` is copied into `x`, `i`'s value is copied into `int_part`, and `d`'s value is copied into `frac_part`. The statements inside `decompose` then assign 3 to `int_part` and `.14159` to `frac_part`, and the function returns.
Unfortunately, `i` and `d` weren't affected by the assignments to `int_part` and `frac_part`, so they have the same values after the call as they did before the call.

If the goal is to modify the arguments itself, this method could pose a problem.

Pointers offer a solution to this problem: instead of passing a variable `x` as the argument ot a function, we'll supply `&x`, a pointer to `x`. We'll declare the corresponding parameter `p` to be a pointer.

When a function is called, `p` will have the value `&x`, hence `*p` (the object that `p` points to) will be and alias for `x`. Each appearance of `*p` in the body of the function will be an indirect refernce to `x`, allowing the function both to read `x` and to modify it.

```c
void decompose (double x, long *int_part, double *frac_part) {
  *int_part = (long) x;
  *frac_part = x - *int_part;
}

decompose(3.14159, &i, &d);
```

Because of the `&` operator in front of `i` and `d`, the arguments to `decompose` are _pointers_ to `i` and `d`, not the _values_ of `i` and `d`.
When `decompose` is called, the value `3.14159` is copied into `x`, a pointer `i` is stored in `int_part`, and a pointer `d` is stored in `frac_part`.

The first assignemnt in the body of `decompose` converts the value of `x` to type `long` and stores it in the object pointed to by `int_part`. since `int_part` points to `i`, the assignment put the value `3` in `i`.

```
x = 3.14159
int_part -> i = 3
frac_part -> d = ?
```

The second assignment fetches the value that `int_part` points to, which is `3`. This value is converted to type `double` and subtracted from `x`, giving `0.14159`, which is then store in the object that `frac_part` points to.

```
x = 3.14159
int_part -> i = 3
frac_part -> d = 0.14159
```

When `decompose` returns, `i` and `d` will have the values `3` and `0.14159`.

> [!WARNING]
> Failing to pass a pointer to a function when one ex expected can have disastrous results.

## Pointers as Return Values

We can not only pass pointers to functions but also write functions that _return_ pointers.

```c
int *p, i, j;

int *max (int *a, int *b) {
  if (*a > *b) {
    return a;
  } else {
    return b;
  }
}

p = max(&i, &j);
```

During the call of `max`, `*a` is an alias for `i`, while `*b` is an alias for `j`. If `i` has larger value that `j`, `max` returns the address of `i`; otherwise, it returns that address of `j`. After the call, `p` points to either `i` or `j`.

Although the `max` function returns one of the pointers passed to it as an argument, that's not the only possibility. A function could also return a pointer to an external variable or to a local varaible that's been declared `static`.

> [!WARNING]
> Never return a pointer to an _automatic_ local variable:
>
> ```c
> int *f(void) {
>   int i;
>   ...
>   return &i;
> }
> ```
>
> The variable `i` doesn't exist once `f` returns, so the pointer to it will be invalid. Some compilers issue a warning such as "_function returns address of lcal variable_" in this situation.

Pointers can point to array elements, not just ordinary variables. If `a` is an array, then `&a[i]` is a pointer to element `i` of `a`. When a function has an array argument, it's sometimes useful for the function to return a pointer to one of the elements in the array.

```c
int *find_middle(int a[], int n) {
  return &a[n/2];
}
```
