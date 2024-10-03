#include <stdio.h>
#include <string.h>



void shift_right(char buffer[], int size) {

    for (int j = size - 1; j >= 0; j--) {
        buffer[j + 1] = buffer[j];  // Shift element one position to the right
    }

    // Set first element to '-'
    buffer[0] = '-';  
}



size_t float_to_string(float value, char buffer[], size_t buffer_size) {

    int float_num_stored[32];
    int i = 0;
    int is_negative = 0; // False

    // Negative Check
    if (value < 0) {
        is_negative = 1; // True
        value = -value;
    }

    int decimal_part = value;
    int size_decimal_part;
    int fraction_part = (value - decimal_part) * 1000000; // 6 casas decimais
    int size_fraction_part;



    // Decimal to array
    while(decimal_part > 0) {
        float_num_stored[i] = decimal_part % 10;
        decimal_part = decimal_part / 10;
        i++;
    }

    size_decimal_part = i;

    for (int j = 0; j < size_decimal_part; j++) {
        buffer[j] = float_num_stored[size_decimal_part - 1 - j] + '0'; 
    }

    buffer[size_decimal_part] = '.';
    i = 0; // Clear pointer

    // Fraction to array
    while(fraction_part > 0) {      
        float_num_stored[i] = fraction_part % 10;
        fraction_part = fraction_part / 10;
        i++;
    }
        
    size_fraction_part = i;

    for (int j = 0; j < size_fraction_part; j++) {
        buffer[size_decimal_part + 1 + j] = float_num_stored[size_fraction_part - 1 - j] + '0'; 
    }

    int string_size = size_decimal_part + size_fraction_part + 1;
    
    if (is_negative) {
        shift_right(buffer, string_size);
    }

        // Adiciona o terminador nulo
    buffer[string_size + 1] = '\0';

    printf("Valor em string: %s\n", buffer);

    return string_size;

}



int main() {
    float value;
    char buffer[33];  // Buffer for string (32 bits + \0)
    
    printf("Digite um numero real (6 casas decimais) :");
    scanf("%f", &value);
  
    float_to_string(value, buffer, sizeof(buffer));

    return 0;
}