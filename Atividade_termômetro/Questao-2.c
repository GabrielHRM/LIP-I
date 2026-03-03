#include <stdio.h>

int main() {
    int n;
    long int prod = 1;
    printf("Digite um numero para calcular seu fatorial: ");
    scanf("%d", &n);

    while(n > 0){
        prod *= n;
        n--;

    }
    printf("O fatorial eh: %ld\n", prod);
    return 0;
}