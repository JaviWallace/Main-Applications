#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define N 400
#define S 50
#include <conio.h>
int c, f;
int main()
{
    srand(time(NULL));
    int  i, j, v, vtot, x, y;
    vtot= 0;
    puts("Introduce el numero de filas");
    scanf("%i", &f);
    fflush(stdin);
    puts("Introduce el numero de columnas");
    scanf("%i", &c);
    fflush(stdin);
    int mapa[f][c];
    puts("Introduce el numero de seres vivos iniciales");
    scanf("%i", &v);
    puts("");
    for(i = 0; i < f; i++){
        for(j = 0; j < c; j++)mapa[i][j] = 0;
    }

    while (v > 0){
        v-=50;
        vtot++;
    }
    v+= 50;
    vtot--;
    while(vtot > 0){
       for (i = 0; i < 50; i++){
        x = rand()%(f+1);
        y = rand()%(c+1);
        mapa[x][y] = 1;
       }
       vtot--;
    }
    for (i = 0; i < v; i++){
        x = rand()%(f+1);
        y = rand()%(c+1);
        mapa[x][y] = 1;
    }
    juego(mapa);
    return 0;
}
void juego(int mapa[][c]){
int i;
    for (i = 0; i < N; i++){
        Sleep(S);
        mostrar(mapa);
        actualizar(mapa);
    }
}

void mostrar (int mapa[][c]){

system("cls");
int i, j;
    for (i = 0; i < f; i++){
        for(j = 0; j < c; j++){
                if(mapa[i][j] == 0)printf("  ");
                else printf("%i ", mapa[i][j]);
        }
        puts("");
    }

}
void actualizar(int mapa[f][c]){
int i, j;

for (i = 0; i < f; i++){
    for(j = 0; j < c; j++){
        if((cuantos(mapa, i, j) < 2 || cuantos(mapa, i, j) > 3)&& mapa[i][j] == 1) mapa[i][j] = 0;
        if(cuantos(mapa, i, j) == 3 && mapa[i][j] == 0) mapa[i][j] = 1;
    }
}


}
int cuantos(int mapa[][c], int x, int y){
int i, j, tot= 0;

for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
        if((x+i) < 0 || (x+i) >= f || (y+j) < 0 || (y+j) >= c || (i == 0 && j == 0)){

        }
            else if(mapa[x+i][y+j] == 1)tot++;
    }
}
return tot;
}
