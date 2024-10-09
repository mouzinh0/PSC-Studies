### char *fgets(char *str, int n, FILE *stream);

#### Parameters:

* char *str: A pointer to an array of characters where the read string will be stored.
   This array should be large enough to hold the string, including the terminating null character.
  
* int n: The maximum number of characters to read, including the terminating null character.
   fgets will read up to n-1 characters, leaving room for the null character.
  
* FILE *stream: A pointer to a FILE object that specifies the input stream to read from.
   This can be a file pointer obtained from functions like fopen, or it can be stdin for standard input.

#### Reading a Line from Standard Input:

```
#include <stdio.h>

int main() {
   char buffer[50];

   printf("Enter a string: ");
   if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
       printf("You entered: %s", buffer);
   } else {
       printf("Error reading input.");
   }

   return 0;
}
```

#### Leitura do ficheiro linha por linha:

```
while (fgets(line, sizeof(line), file))
```
* Lê uma linha do ficheiro CSV e a armazena no array line.
  A leitura é feita até o final do ficheiro (EOF) ou até que uma linha maior que o tamanho de line seja encontrada.




