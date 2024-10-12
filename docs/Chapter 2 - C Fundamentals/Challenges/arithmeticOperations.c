/*
 * Challenge: Create a program that calculates the area and circumference of a
 * circle. The program should ask the user for the radius and then display the
 * results using the formulas:
 *
 * Area = π * r²
 * Circumference = 2 * π * r
 */

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
