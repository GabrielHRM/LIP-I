#include <stdio.h>
#include <stdlib.h>

float c_f(float c){
    return (c * 9/5) + 32;
}
float f_c(float f){
    return (f - 32) * 5/9;
}

int main() {
    float temp;
    float resposta;
    printf("Digite o numero de temperaturas: ");
    scanf("%f", &temp);

    int opcao;
    printf("Digite 1 para converter de Celsius para Fahrenheit ou 2 para converter de Fahrenheit para Celsius: ");
    scanf("%d", &opcao);

    switch (opcao){
        case 1:
            resposta = c_f(temp);
            printf("%.2f graus Celsius equivalem a %.2f graus Fahrenheit\n", temp, resposta);
            break;
        case 2:
            resposta = f_c(temp);
            printf("%.2f graus Fahrenheit equivalem a %.2f graus Celsius\n", temp, resposta);
            break;
        default:
            break;
    }

    
    return 0;
}