#include <stdio.h>
#include <string.h>

size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size) {

    if (base != 2 && base != 8 && base != 10 && base != 16) {
        printf("Base %d nao faz parte\n", base);
        return 0;
    }

    int stored_base[32]; 
    int i = 0;
    int size = 0;
    unsigned temp = value;
    int prefix_len = 0; 

    // String size calc
    while (temp > 0) {
        temp = temp / base;  
        size++;
    }

    // Conversion formula plus reverse
    while (value > 0) {
        stored_base[size - i - 1] = value % base;
        value = value / base;
        i++;
    }

    // Base prefixes plus length
    if (base == 2) {
        buffer[0] = '0';
        buffer[1] = 'b';
        prefix_len = 2;
    } else if (base == 16) {
        buffer[0] = '0';
        buffer[1] = 'x';
        prefix_len = 2;
    }

    // Conversion from int to char
    for (int j = 0; j < size; j++) {
        if (stored_base[j] < 10)
            buffer[prefix_len + j] = stored_base[j] + '0';  
        else
            buffer[prefix_len + j] = stored_base[j] - 10 + 'a';  // Base 16 
    }

    // Adiciona o terminador nulo
    buffer[prefix_len + size] = '\0';

    
    printf("Base %d: %s\n", base, buffer);

    return size + prefix_len;  // Return total string size
}

int main() {
    unsigned value;
    char buffer[33];  // Buffer for string (32 bits + \0)
    int base;

    printf("Digite um número inteiro: ");
    scanf("%u", &value);

    printf("Digite a base (2, 8, 10, 16): ");
    scanf("%d", &base);

    
    int_to_string(value, base, buffer, sizeof(buffer));

    return 0;
}
