#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ehprimo(int n){
    if(n < 0){
        n*=-1;
    }
    if(n == 1){
        return 0;
    }
    if(n == 2){
        return 1;
    }else{
        for(int i = 2; i<=n; i++){
            if(n%i == 0){
                return 0;
            }else{
                return 1;
            }
        }
    }
    return 1;
}

int main(){
    int n;
    printf("Digite um numero primo:\n");
    scanf("%d", &n);
    if(ehprimo(n)){
        printf("%d eh primo\n", n);
    }else{
        printf("%d nao eh primo\n", n);
    }
    return 0;
}