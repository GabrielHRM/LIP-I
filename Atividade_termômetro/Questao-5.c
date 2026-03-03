#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qtde_de_caracteres(char frase[1000]){
    int qtde = 0;
    for(int i = 0; frase[i] != '\0'; i++){
        qtde++;
    }
    return qtde;
}

int main() {
    char frase[1000];
    int total_caracteres;
    printf("Digite uma frase: ");
    fgets(frase, sizeof(frase), stdin);

    total_caracteres = qtde_de_caracteres(frase);
    printf("A frase tem %d caracteres\n", total_caracteres-1);

    return 0;
}