#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define MAX_LINE_LENGTH 1024


void print_table(char ***data, int rows, int cols, char alignment) {
    int col_widths[cols];

    // Get each column maximum size
    for (int i = 0; i < cols; i++) {
        col_widths[i] = 0;
        for (int j = 0; j < rows; j++) {
            int length = strlen(data[j][i]);
            if (length > col_widths[i]) {
                col_widths[i] = length;
            }
        }
    }

    // Top lines +---------------+----------+---------+-------+
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("+");
            for (int k = 0; k < col_widths[j] + 2; k++) {
                printf("-");
            }
        }
        printf("+\n");

    // Data and '|'
    // Printf => * is for size as argument and - is aligned to the left
        for (int j = 0; j < cols; j++) {
            printf("| ");
            if (alignment == 'l') {
                printf("%-*s", col_widths[j], data[i][j]);
            } else {
                printf("%*s", col_widths[j], data[i][j]);
            }
            printf(" ");
        }
        printf("|\n");
    }

    // Bottom line
    for (int j = 0; j < cols; j++) {
        printf("+");
        for (int k = 0; k < col_widths[j] + 2; k++) {
            printf("-");
        }
    }
    printf("+\n");
}


char ***load_csv(const char *filename, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o ficheiro");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    int row_count = 0;
    int col_count = 0;
    // Fixed size but could be changed being dinamic
    // char **data[100]; 
    // Static array like this would be easier and faster but malloc gives easier adjustments for possible future implementations
    char ***data = malloc(sizeof(char **) * 100);  

    while (fgets(line, sizeof(line), file)) {
        char **row = malloc(sizeof(char *) * 100);  
        char *token = strtok(line, ",\n");
        int col_index = 0;

        // strdup() uses malloc internally
        while (token) {
            row[col_index] = strdup(token);
            token = strtok(NULL, ",\n");
            col_index++;
        }
        // This doesnt resolve multiple size columns, first column size is chosen
        // May give some formatting problems
        if (row_count == 0) {
            col_count = col_index;
        }

        data[row_count] = row;
        row_count++;
    }

    fclose(file);

    *rows = row_count;
    *cols = col_count;
    return data;
}

// Função principal
int main(int argc, char *argv[]) {
    int opt;
    char *output_filename = NULL;
    char alignment = 'r';  
    char *csv_filename = NULL;

    // getopt returns -1, indicating no more options are present
    // argc => nr argumentos
    // argv => matriz de strings com os argumentos
    // optarg => ponteiro char com o argumento associado a uma opcao
    // optind => int com o indice do proximo elemento de argv (param. nao opcional)
    while ((opt = getopt(argc, argv, "o:a:")) != -1) {
        switch (opt) {
            case 'o':
                output_filename = optarg;
                break;
            case 'a':
                if (optarg[0] == 'l' || optarg[0] == 'r') {
                    alignment = optarg[0];
                } else {
                    fprintf(stderr, "Alinhamento inválido: %s\n", optarg);
                    return 1;
                }
                break;
            default:
                fprintf(stderr, "Uso: %s [-o <output_filename>] [-a <alignment>] <csv_filename>\n", argv[0]);
                return 1;
        }
    }

    // CSV file name (param. nao opcionais)
    if (optind < argc) {
        csv_filename = argv[optind];
    } else {
        fprintf(stderr, "Ficheiro CSV não fornecido\n");
        return 1;
    }

    // Variavel de ambiente CSV_FILE_PATH ou null
    char *csv_path = getenv("CSV_FILE_PATH");
    char full_path[MAX_LINE_LENGTH];
    if (csv_path) {
        // /usr/home/data
        snprintf(full_path, sizeof(full_path), "%s/%s", csv_path, csv_filename);
    } else {
        // pasta corrente
        snprintf(full_path, sizeof(full_path), "./%s", csv_filename); 
    }

    // Needed variables get in data for table build
    int rows, cols;
    // data[i][j]  i -> linha e j -> coluna 
    char ***data = load_csv(full_path, &rows, &cols);
    if (!data) {
        return 1;
    }

    // Console or file output
    FILE *output_file = stdout;
    if (output_filename) {
        output_file = freopen(output_filename, "w", stdout);
        if (!output_file) {
            perror("Erro ao abrir ficheiro de saída");
            return 1;
        }
    }


    // Table build
    print_table(data, rows, cols, alignment);

    // Close file
    if (output_file != stdout) {
        fclose(output_file);
    }

    // Free memory (cell, string, array)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);

    return 0;
}