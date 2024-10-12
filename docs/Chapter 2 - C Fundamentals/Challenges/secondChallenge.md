# Arithmetic Operations

**Challenge**: Create a program that calculates the area and circumference of a circle. The program should ask the user for the radius and then display the results using the formulas:

- Area = π \* r²
- Circumference = 2 \* π \* r

My initial solutions to the problem:

```c
  #include <stdio.h>

  int main(void) {
    double radius;
    double area;
    double circumference;

    printf("Please enter the radius: ");
    scanf("%lf", &radius);

    area = 3.14159 * (radius * radius);
    circumference = 2 * 3.14159 * radius;

    printf("The area of your radius: %.2f\nThe circumference to your radius: "
          "%.2f\n",
          area, circumference);

    return 0;
  }
```

Upon asking ChatGPT on what to improve based on my approach to the problem:

1. **Input Validation** - I forgot about this one as I'm focusing on the implementation of the formula for the results. I also need to read my code first before sending it for review.

```c
  if (scanf("%lf", &radius) != 1) {
    printf("Invalid input for radius.\n");
    return 1; // Exit with an error code
  }
```

2. **Clearer Output Message** - Clarification of the output messages. Instead of saying "The area of your radius", I could say "The area of the circle with radius...".

```c
  printf("The area of the circle with radius %.2f: %.2f\n", radius, area);
  printf("The circumference of the circle with radius %.2f: %.2f\n", radius,     circumference);
```

3. **Constants** - Instead of hard coding the PI, I could define it as constant at the beginning of the program.

```c
  #define PI 3.14159
```

Reflecting on this, I should have written this if I reviewed my code more carefully. Need to improve more.

Final solution:

```c
  #include <stdio.h>

  #define PI 3.14159

  int main(void) {
    double radius;
    double area;
    double circumference;

    printf("Please enter the radius: ");
    if (scanf("%lf", &radius) != 1) {
      printf("Invalid input for radius.\n");
      return 1; // Exit with an error code
    }

    area = PI * (radius * radius);
    circumference = 2 * PI * radius;

    printf("The area of the circle with radius %.2f: %.2f\n", radius, area);
    printf("The circumference of the circle with radius %.2f: %.2f\n", radius,
          circumference);

    return 0;
  }
```

Upon reading the `float` vs `double`, which is bothering me:

- **Precision**: The main difference between `float` and `double`is precision. A `float` typically has about 7 decimal places of precision, while `double` has about 15 decimal places. This means that `double` can represent larger numbers and maintain accuracy for more decimal places.

- **Memory**: `float` usually takes up 4 bytes, while `double` takes up 8 bytes. If memory usage is a concern, using `float` might be preferable, but for most applications especially where precision is crucial, `double` is the better choice.
