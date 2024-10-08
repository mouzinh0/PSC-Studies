* O ponteiro triplo (char ***) é necessário porque o ficheiro CSV será armazenado como uma matriz de strings
* O primeiro ponteiro (char **) aponta para uma linha do CSV (um array de strings).
* O segundo ponteiro (char *) aponta para cada célula da linha (uma string).
* O terceiro nível (char) é usado para armazenar os caracteres individuais das strings.
