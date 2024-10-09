* A função malloc() (memory allocation) é usada em C para alocar dinamicamente memória em tempo de execução.
  Ela permite que o programa reserve blocos de memória do heap, em vez de usar a memória da stack, que é geralmente mais limitada e usada para variáveis locais.

#### Como o malloc() funciona:

* A função malloc() recebe como argumento o tamanho em bytes da memória que você deseja alocar e retorna um ponteiro para o primeiro byte
   do bloco de memória alocado.
  Se a alocação falhar (por exemplo, se não houver memória disponível), ela retorna NULL.

```
void *malloc(size_t size);
```
> Nota: Como o retorno de malloc() é do tipo void * (ponteiro genérico), normalmente é necessário fazer um casting para o tipo de dados desejado.
> int *array = (int *) malloc(10 * sizeof(int));
> Aqui, malloc aloca memória suficiente para armazenar 10 inteiros.

#### Vantagens da memória dinâmica com malloc():

##### Alocação de memória em tempo de execução:

* Com malloc(), você pode decidir quanto de memória o seu programa realmente precisa em tempo de execução,
   em vez de determinar tudo no momento da compilação.
  Isso é útil em situações onde o tamanho da estrutura de dados é desconhecido antecipadamente, como quando você lê dados de ficheiros,
   recebe dados de uma rede, ou processa input de utilizadores.

##### Maior flexibilidade em comparação com buffers estáticos:

* Um buffer estático é uma variável cujo tamanho é definido no momento da compilação
  char buffer[100]; -> Aqui, o buffer sempre terá 100 bytes, mesmo que apenas 10 bytes sejam usados.
* Desvantagens de buffers estáticos:
  - Desperdício de memória: Se você usar um buffer grande para acomodar o pior caso, poderá desperdiçar memória quando o pior caso não ocorrer.
  - Limitação de tamanho: Se você usar um buffer muito pequeno e receber mais dados do que o buffer pode conter, pode ocorrer overflow,
   o que pode causar comportamento inesperado ou falhas de segurança.

##### Controlar o ciclo de vida da memória:

* Com malloc(), você tem controle sobre quando a memória é alocada e quando é liberada. Para liberar a memória, usa-se a função free()


#### Desvantagens de malloc() em comparação com buffers estáticos:

* Necessidade de gerenciamento manual de memória:
  - A memória alocada por malloc() não é liberada automaticamente.
    Você deve usar free() para liberar a memória assim que ela não for mais necessária.
     Se você esquecer de liberar a memória, o programa pode ter vazamento de memória (memory leak).
    
* Sobrecarga de desempenho:
  - O uso de malloc() pode ser mais lento do que variáveis estáticas, já que o sistema operacional precisa procurar e reservar blocos de memória durante a execução.
     Em contraste, buffers estáticos são alocados no início da execução do programa e o acesso é direto.

* Fragmentação da memória:
  - A alocação dinâmica pode levar à fragmentação do heap.
     Se a memória for alocada e liberada de maneira ineficiente, pode haver muitos pequenos blocos de memória livre,
      que são inúteis porque estão fragmentados entre grandes blocos ocupados.














  
