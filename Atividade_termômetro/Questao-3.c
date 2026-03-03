#include <stdio.h>
#include <stdlib.h>

int *aloca_vetor(int n){
    int *v = (int*)calloc(n, sizeof(int));
    if(v == NULL){
        printf("Erro de alocacao\n");
        exit(1);
    }

    return v;
}

void ler_vetor(int *v, int n){
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
}

int soma_vetorial(int *v, int n){
    int soma = 0;
    for(int i = 0; i < n; i++){
        soma += v[i];
    }
    return soma;
}


int main() {

    int n, soma;

    printf("Digite o numero de elementos do array: ");
    scanf("%d", &n);
    int *v;
    v = aloca_vetor(n);

    ler_vetor(v, n);
    soma = soma_vetorial(v, n);
    printf("Soma dos elementos do vetor: %d\n", soma);
    
    free(v);

    return 0;
}