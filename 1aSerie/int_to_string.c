#include <stdio.h>
#include <string.h>

size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size) {

    if (base != 2 && base != 8 && base != 10 && base != 16) {
        return 0;
    }

    int stored_base[32]; 
    int i = 0;
    int size = 0;
    unsigned temp = value;
    int prefix_len = 0; 

    // No space
   if (buffer_size == 0) {
        return 0;  
    }

    // Zero is a problem to fix no need to calc
    if (value == 0) {
            if (base == 2) {
                if (buffer_size >= 4) {
                    buffer[0] = '0';
                    buffer[1] = 'b';
                    buffer[2] = '0';
                    buffer[3] = '\0';
                    return 3;
                }
            } else if (base == 16) {
                if (buffer_size >= 3) {
                    buffer[0] = '0';
                    buffer[1] = 'x';
                    buffer[2] = '0';
                    buffer[3] = '\0';
                    return 3;
                }
            } else {
                if (buffer_size >= 2) {
                    buffer[0] = '0';
                    buffer[1] = '\0';
                    return 1;
                }
            }
            return 0; 
        }

    // String size calc
    while (temp > 0) {
        temp = temp / base;  
        size++;
    }

        
    if (base == 2 || base == 16) {
        prefix_len = 2;
    } else if (base == 8) {
        prefix_len = 1;
    }

    // Check Space
    if (size + prefix_len + 1 > buffer_size) { 
        return 0;  
    }

    // Base prefixes plus length
    if (base == 2) {
        buffer[0] = '0';
        buffer[1] = 'b';
    } else if (base == 16) {
        buffer[0] = '0';
        buffer[1] = 'x';
    } else if (base == 8) {
        buffer[0] = '0';
    }

    // Conversion formula plus reverse
    while (value > 0) {
        stored_base[size - i - 1] = value % base;
        value = value / base;
        i++;
    }

    // Conversion from int to char
    for (int j = 0; j < size; j++) {
        if (stored_base[j] < 10)
            buffer[prefix_len + j] = stored_base[j] + '0';  
        else
            buffer[prefix_len + j] = stored_base[j] - 10 + 'a';  // Base 16 
    }

    buffer[prefix_len + size] = '\0';

    
    //printf("Base %d: %s\n", base, buffer);

    return size + prefix_len;  // Return total string size
}
