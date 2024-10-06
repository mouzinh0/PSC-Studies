#include <stdarg.h> // Necessária para manipulação de argumentos variáveis (va_list, va_start, etc.).
#include <stdio.h> // Printf

// Static scope is not obrigatory but nice addition 

static void append_char(char **buffer, size_t *remaining, char c) {
    if (*remaining > 1) {
        **buffer = c;
        (*buffer)++;
        (*remaining)--;
    }
}

static void append_string(char **buffer, size_t *remaining, const char *str) {
    while (*str) {
        append_char(buffer, remaining, *str);
        str++;
    }
}

static void append_int(char **buffer, size_t *remaining, int value, int base) {
    char temp[32];
    char *ptr = temp + sizeof(temp) - 1; // Finnal of the buffer
    int is_negative = 0;

    *ptr = '\0';

    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;
    }

    do {
        *--ptr = "0123456789abcdef"[value % base];
        value /= base;
    } while (value != 0);

    if (is_negative) {
        *--ptr = '-';
    }

    append_string(buffer, remaining, ptr);
}


static void append_float(char **buffer, size_t *remaining, double value) {
if (value < 0) {
        append_char(buffer, remaining, '-');
        value = -value;  
    }

    // Decimal
    int integer_part = (int)value;
    append_int(buffer, remaining, integer_part, 10);

    // Dot
    append_char(buffer, remaining, '.');

    // Fractional
    double fractional_part = value - integer_part;
    fractional_part *= 1000000;  
    append_int(buffer, remaining, fractional_part, 10);  
}



size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char *output = buffer;
    size_t remaining = buffer_size;

    while (*format) {
        if (*format == '%' && *(format + 1)) {
            format++; // Jump over %
            switch (*format) {
                case 'b': {  // Binary
                    int value = va_arg(args, int);
                    append_int(&output, &remaining, value, 2);
                    break;
                }
                case 'c': {  // Char
                    char value = (char)va_arg(args, int);
                    append_char(&output, &remaining, value);
                    break;
                }
                case 's': {  // String
                    const char *str = va_arg(args, const char *);
                    append_string(&output, &remaining, str);
                    break;
                }
                case 'd': {  // Decimal
                    int value = va_arg(args, int);
                    append_int(&output, &remaining, value, 10);
                    break;
                }
                case 'x': {  // Hexa
                    int value = va_arg(args, int);
                    append_int(&output, &remaining, value, 16);
                    break;
                }
                case 'f': {  // Float
                    // warning: ‘float’ is promoted to ‘double’ when passed through ‘...’
                    float value = va_arg(args, double);
                    append_float(&output, &remaining, value);
                    break;
                }
                // Not supported formats
                default:
                    append_char(&output, &remaining, '%');
                    append_char(&output, &remaining, *format);
                    break;
            }
        } else {
            append_char(&output, &remaining, *format);
        }
        format++;
    }

    // End String
    if (remaining > 0) {
        *output = '\0';
    }

    // Not needed but good manners
    va_end(args); 

    return buffer_size - remaining;
}


int main() {
    char buffer[128]; 

    // Some variables
    int n = 42;
    char ch = 'A';
    const char *str = "Hello, World!";
    float pi = 3.14159;

    mini_snprintf(buffer, sizeof(buffer), "Float: %f", pi);
    printf("Output: %s\n", buffer);

    // String with all 
    mini_snprintf(buffer, sizeof(buffer), "Integer: %d, Hex: %x, Char: %c, String: %s, Float: %f, Binary: %b", n, n, ch, str, pi, n);
    printf("Formatted output: %s\n", buffer);

    // Non supported
    mini_snprintf(buffer, sizeof(buffer), "Not supported: %t", n);
    printf("Output: %s\n", buffer);

    // Diferent sized buffer
    //mini_snprintf(buffer, 20, "This is a long string: %s", str);
    //printf("Truncated output: %s\n", buffer);

    // String with Binary
    //mini_snprintf(buffer, sizeof(buffer), "Binary of %d: %b", n, n);
    //printf("Binary output: %s\n", buffer);

    return 0;
}
