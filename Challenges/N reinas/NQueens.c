#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Tiro(int* i);
int ParImpar(int i);

void main(){
int n;
int *i;
srand(time(NULL));
i = &n;
Tiro(i);
ParImpar(n);

}

int Tiro(int* i){
*i = rand()%37;
printf("Su bola ha caido en el numero: %i", *i);

}

int ParImpar(int i){

if(i%2==0){
    printf("El numero es par");
    }else if(i%2!=0){
            printf("El numero es impar");
    }else printf("Es 0");
}
