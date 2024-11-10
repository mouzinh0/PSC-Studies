#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

// Definição das estruturas conforme o código original
struct data {
    unsigned short flags_length;
    short vals[];
};

struct info {
    double ref;
    struct data **data;
    int valid;
};

// Declaração da função em assembly
short *get_val_ptr(struct info items[],
                   size_t item_idx, size_t data_idx, size_t val_idx, short mask);

// Macro para empacotar flags e length em um valor de 16 bits
#define PACK_FLAGS_LENGTH(flags, length) ((flags & 0x3F) | ((length & 0x3FF) << 6))

int main() {
    // Definição de estruturas de dados estáticas
    static struct data data0 = { .flags_length = PACK_FLAGS_LENGTH(0b000001, 5), .vals = {10, 20, 30, 40, 50} };
    static struct data data1 = { .flags_length = PACK_FLAGS_LENGTH(0b000011, 5), .vals = {60, 70, 80, 90, 100} };
    static struct data data2 = { .flags_length = PACK_FLAGS_LENGTH(0b001111, 5), .vals = {110, 120, 130, 140, 150} };
    static struct data data3 = { .flags_length = PACK_FLAGS_LENGTH(0b111111, 5), .vals = {160, 170, 180, 190, 200} };

    static struct data *datas[] = { &data0, &data1, &data2, &data3 };

    static struct info items[] = {
        { .ref = 3.5, .data = datas, .valid = 1 },
        { .ref = 1.5, .data = datas, .valid = 1 },
        { .ref = 2.5, .data = datas, .valid = 0 }, // Entrada inválida
    };

    // Parâmetros de teste
    size_t item_idx = 0;
    size_t data_idx = 2;
    size_t val_idx = 3;
    short mask = 0b001000;

    // Cálculo do resultado esperado
    short *expected_result = NULL;
    if (items[item_idx].valid) {
        struct data *data_ptr = items[item_idx].data[data_idx];
        unsigned short flags_length = data_ptr->flags_length;
        unsigned short flags = flags_length & 0x3F;
        unsigned short length = (flags_length >> 6) & 0x3FF;
        if (val_idx < length && (flags & mask)) {
            expected_result = &data_ptr->vals[val_idx];
        }
    }

    // Chamada da função em assembly
    short *result = get_val_ptr(items, item_idx, data_idx, val_idx, mask);

    // Verificação do resultado
    if (result == expected_result) {
        printf("Teste passou.\n");
    } else {
        printf("Teste falhou.\n");
        printf("Esperado: %p, Obtido: %p\n", (void *)expected_result, (void *)result);
    }

    // Se o resultado não for NULL, imprime o valor
    if (result != NULL) {
        printf("Valor no endereço retornado: %d\n", *result);
    } else {
        printf("Resultado é NULL.\n");
    }

    return 0;
}
