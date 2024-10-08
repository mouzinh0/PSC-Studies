* O ponteiro triplo (char ***) é necessário porque o ficheiro CSV será armazenado como uma matriz de strings
* O primeiro ponteiro (char **) aponta para uma linha do CSV (um array de strings).
* O segundo ponteiro (char *) aponta para cada célula da linha (uma string).
* O terceiro nível (char) é usado para armazenar os caracteres individuais das strings.

### Exemplo:
```
 CSV:
A,B,C,D
E,F,G,H
I,J,K,L

 Matriz:
data[0][0] = "A", data[0][1] = "B", data[0][2] = "C", data[0][3] = "D"
data[1][0] = "E", data[1][1] = "F", data[1][2] = "G", data[1][3] = "H"
data[2][0] = "I", data[2][1] = "J", data[2][2] = "K", data[2][3] = "L"
```
