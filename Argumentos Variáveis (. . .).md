Em C, os argumentos variáveis permitem que uma função receba um número indefinido de argumentos.
Essas funções utilizam macros definidas no cabeçalho **<stdarg.h>**, que fornece um conjunto de ferramentas para lidar com esses argumentos.

O exemplo clássico disso é a função **printf**, que aceita um formato de string seguido de uma quantidade variável de argumentos que correspondem aos especificadores de formato.

Em C, para implementar funções assim, usamos um conjunto de macros:

* **va_list**: Para declarar uma lista de argumentos variáveis.
* **va_start**: Para inicializar a lista de argumentos variáveis.
* **va_arg**: Para acessar um argumento da lista.
* **va_end**: Para finalizar o processamento da lista de argumentos variáveis.

## va_list
va_list é um tipo de dado especial definido em <stdarg.h>.
Ele é usado para armazenar o estado e a posição atual da lista de argumentos variáveis.
Em outras palavras, ele atua como uma "estrutura" que mantém o controle dos argumentos passados para a função depois dos parâmetros fixos.

> Exemplo: va_list args;

## va_start

A macro va_start inicializa a lista de argumentos variáveis. Ela deve ser chamada antes de começar a acessar os argumentos variáveis.
O primeiro parâmetro de va_start é o objeto va_list que você deseja inicializar (neste caso, args).
O segundo parâmetro (format) é o último argumento fixo da função. 
va_start usa essa informação para calcular o endereço na memória do primeiro argumento variável, que vem imediatamente após o argumento format.

> va_start(args, format);

### Exemplo:

> mini_snprintf(buffer, 100, "%d %x", 42, 255);

Aqui, os parâmetros fixos são buffer, 100 e "%d %x". 
A partir de **va_start(args, format);** , a macro va_start calcula onde estão localizados os argumentos variáveis (42 e 255) na memória,
e prepara args para iterar sobre eles.

## va_arg(args, int);

A macro va_arg extrai o próximo argumento variável da lista args.
Como os argumentos variáveis não têm tipos predefinidos (diferente dos parâmetros fixos de uma função), é necessário informar a va_arg qual é o tipo do argumento que estamos extraindo da lista. 
A macro então extrai o valor, avança o ponteiro interno de args para o próximo argumento na lista e devolve o valor que foi recuperado.

```
Exemplo (dando continuidade ao anterior):

Após va_start, se a lista contiver os valores 42 e 255, a linha:

int value = va_arg(args, int);

Recupera o valor 42 da lista de argumentos variáveis e o armazena em value.
O ponteiro interno de args agora aponta para o próximo argumento (no caso, 255).
```

## va_end(args);

Necessário para liberar qualquer recurso que possa ter sido alocado para a estrutura va_list. 
Embora muitas vezes va_end não faça nada específico em muitas implementações de compiladores, ele ainda é uma prática recomendada para garantir que o código esteja correto e portável.








