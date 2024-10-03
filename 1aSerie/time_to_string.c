#include <stdio.h>
#include <string.h>
#include <time.h>

 
// struct tm {
// int   tm_sec;
// int   tm_min;
// int   tm_hour;
// int   tm_mday;
// int   tm_mon;
// int   tm_year;
// int   tm_wday;
// int   tm_yday;
// int   tm_isdst;
// };

const char* week_days[] = {
    "domingo", "segunda-feira", "terca-feira", "quarta-feira", "quinta-feira", "sexta-feira", "sabado"
};

size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) {
    // Inicializar o buffer vazio
    buffer[0] = '\0';

    snprintf(buffer, buffer_size, "%s, %02d-%02d-%04d, %02d:%02d:%02d",
        week_days[tm->tm_wday],   
        tm->tm_mday,              
        tm->tm_mon + 1,           
        tm->tm_year + 1900,      
        tm->tm_hour,            
        tm->tm_min,              
        tm->tm_sec              
    );

    // Retorna o tamanho da string gerada
    return strlen(buffer);
}


int main() {

    // ww,dd-mm-yyyy, hh:mm:ss
    // segunda-feira, 16-09-2024, 12:45:23
    struct tm my_struct = {
        .tm_sec = 23,
        .tm_min = 45,
        .tm_hour = 12,
        .tm_mday = 16,
        .tm_mon = 8,   // Setembro (9, months since January	0-11)
        .tm_year = 2024 - 1900, //(Years since 1900)
        .tm_wday = 1,  // Segunda-feira
        .tm_yday = 0,  // Ignorado 
        .tm_isdst = 0  // Ignorado 
    };

    char buffer[100];
    size_t result = time_to_string(&my_struct, buffer, sizeof(buffer));

    printf("Resultado: %s\n", buffer);
    printf("Tamanho da string: %zu\n", result);

    return 0;
}