#include" main.h"

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

int print_char(va_list args) {
    char ch = (char)va_arg(args, int);
    write(STDOUT_FILENO, &ch, 1);
    return 1;
}

int print_string(va_list args) {
    const char *str = va_arg(args, const char *);
    int count = 0;
    while (*str) {
        write(STDOUT_FILENO, str, 1);
        str++;
        count++;
    }
    return count;
}

int print_percent(va_list args) {
    write(STDOUT_FILENO, "%", 1);
    return 1;
}

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;

    while (*format) {
        if (*format == '%') {
            format++; // Move past '%'
            if (*format == 'c') {
                count += print_char(args);
            } else if (*format == 's') {
                count += print_string(args);
            } else if (*format == '%') {
                count += print_percent(args);
            } else {
                // Invalid format specifier, print it as is
                write(STDOUT_FILENO, "%", 1);
                write(STDOUT_FILENO, format, 1);
                count += 2;
            }
        } else {
            // Print non-format characters
            write(STDOUT_FILENO, format, 1);
            count++;
        }

        format++;
    }

    va_end(args);
    return count;
}

int main() {
    int num = 42;
    char ch = 'A';
    const char *str = "Hello, World!";
    
    int count = _printf("This is a number: %d, a character: %c, and a string: %s%%\n", num, ch, str);
    printf("\nTotal characters printed: %d\n", count);

    return 0;
}

