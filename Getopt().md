* Normally, getopt is called in a loop. When getopt returns -1, indicating no more options are present, the loop terminates.
* A switch statement is used to dispatch on the return value from getopt.
 In typical use, each case just sets a variable that is used later in the program.
* A second loop is used to process the remaining non-option arguments.

## Optard e Opting:

**optarg** e **optind** são variáveis globais fornecidas pela biblioteca getopt em C,
que são usadas para processar e interpretar os argumentos passados pela linha de comando de forma padronizada. 

### Optard

* É um ponteiro (char *) que armazena o argumento associado a uma opção que requer um argumento.
* Função: Quando o getopt identifica uma opção que necessita de um valor 
(como -o seguido por um nome de ficheiro ou -a seguido por um alinhamento),
ele armazena o argumento associado nessa variável.

### Optind
* É um inteiro que indica o índice do próximo elemento de argv[] que será processado.
 O optind começa em 1 (porque argv[0] normalmente é o nome do programa).
* Função: optind é automaticamente atualizado pela função getopt para indicar a posição
 do próximo argumento que será processado.
Quando getopt termina de processar todas as opções (inicia com -), optind apontará para o primeiro argumento
 não processado, que normalmente é um parâmetro não opcional (como o nome do ficheiro no seu exemplo).

```
Exemplo:
./csv_show -o output.txt -a l stock.csv

Se todas as opções forem processadas corretamente, optind será igual ao índice de stock.csv no array argv
, ou seja, indicará que argv[optind] é "stock.csv".

```
