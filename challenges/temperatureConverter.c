/*
 * Topics: Input/Output, Expressions, Basic Types
 * Challenge: Create a program that converts a temperature from Celsius to
 * Fahrenheit and vice versa.
 *  - Prompt the user to choose the conversion direction.
 *  - Use the formulas:
 *      C = ( F - 32 ) x 5/9
 *      F = ( C x (9/5)) + 32
 *  - Ensure the you handle user input and provide error messages for invalid
 * inputs
 */

#include <stdio.h>

#define FAHRENHEIT_OFFSET 32
#define FAHRENHEIT_TO_CELSIUS_FACTOR 5.0 / 9.0
#define CELSIUS_TO_FAHRENHEIT_FACTOR 9.0 / 5.0

int main(void) {
  float fahrenheit;
  float celsius;
  char temperature;

  float fahrenheitToCelsius =
      (fahrenheit - FAHRENHEIT_OFFSET) * FAHRENHEIT_TO_CELSIUS_FACTOR;
  float celsiusToFahrenheit =
      (celsius * (CELSIUS_TO_FAHRENHEIT_FACTOR)) + FAHRENHEIT_OFFSET;

  printf("This a Fahrenheit or Celsius Converter\n");

  printf("Enter a temperature first THEN a value, please use \'F\' for "
         "Fahrenheit and "
         "\'C\' for Celsius \n");
  if (scanf("%c\n", &temperature) != 1) {
    if (temperature != 'C' || temperature != 'F') {
      printf("%c is not a symbol of Celsius or Fahrenheit", temperature);
    }
  }

  if (temperature == 'C') {
    scanf("%f", &celsius);
    printf("Converted to Fahrenheit: %.2f\n",
           (celsius * (CELSIUS_TO_FAHRENHEIT_FACTOR)) + FAHRENHEIT_OFFSET);
  } else if (temperature == 'F') {
    scanf("%f", &fahrenheit);
    printf("Converted to Celsius: %.2f\n",
           (fahrenheit - FAHRENHEIT_OFFSET) * FAHRENHEIT_TO_CELSIUS_FACTOR);
  }

  return 0;
}

/*
 * Upon reviewing the approach to the challenge:
 *
 * 1. Input Validation -
 * Putting the `temperature != 'C' || temperature != 'F'` under `scanf("%c\n",
 &temperature) != 1` would make would/could make an issue.
 * It should be
 * ```
 * if (scanf(" %c", &temperature) != 1 || (temperature != 'C' && temperature !=
 'F')) { printf("Invalid input: %c is not a recognized temperature symbol.\n",
 temperature); return 1; // Exit with an error code
    }
 * ```
 *
 * 2. Adding '\n' inside scanf(), not knowing what it would do can make problem
 in the program. I need to think if I'm using scanf() or printf().
 *
 * 3. Move the variables for conversion under conditional statement of
 temperatures. That way, the value after calculation will be based on the input
 of the user not in a static value.
 *
 *
 * Sample code to improve the approach to the challenge:
 *
 * ```
 * #include <stdio.h>

#define FAHRENHEIT_OFFSET 32
#define FAHRENHEIT_TO_CELSIUS_FACTOR (5.0 / 9.0)
#define CELSIUS_TO_FAHRENHEIT_FACTOR (9.0 / 5.0)

int main(void) {
    float temperatureValue;
    char temperature;
    float convertedTemperature; // Variable to store the result of the
conversion

    printf("This is a Fahrenheit or Celsius Converter\n");
    printf("Enter a temperature symbol ('C' for Celsius or 'F' for Fahrenheit)
and a value:\n");

    // Read temperature symbol
    if (scanf(" %c", &temperature) != 1 || (temperature != 'C' && temperature !=
'F')) { printf("Invalid input: %c is not a recognized temperature symbol.\n",
temperature); return 1; // Exit with an error code
    }

    // Read temperature value
    printf("Enter the temperature value: ");
    if (scanf("%f", &temperatureValue) != 1) {
        printf("Invalid input. Please enter a valid temperature number.\n");
        return 1;
    }

    // Perform the conversion
    if (temperature == 'C') {
        convertedTemperature = (temperatureValue * CELSIUS_TO_FAHRENHEIT_FACTOR)
+ FAHRENHEIT_OFFSET; printf("Converted to Fahrenheit: %.2f\n",
convertedTemperature); } else if (temperature == 'F') { convertedTemperature =
(temperatureValue - FAHRENHEIT_OFFSET) * FAHRENHEIT_TO_CELSIUS_FACTOR;
        printf("Converted to Celsius: %.2f\n", convertedTemperature);
    }

    return 0;
}

 * ```
 */
