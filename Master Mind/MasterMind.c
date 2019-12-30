#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <io.h>
#define N 20
int main(void)
{
    srand(time(NULL));
    int i, j, vec[4];
    for (i = 0; i < 4; i++)
        vec[i] = rand()%6 + 1;
    juego(vec);
    SetColor(i);

}



void juego(int vec[])
{
    int i, j;
    char c;
    int intentos = N, pruebas[6][N];
    for (i = 0; i < 6; i++)
        for ( j = 0; j < N; j++)
            pruebas[i][j] = 0;

    while (intentos > 0)
    {
        codcolor();
        mostrar(pruebas);
        prueba(pruebas, vec, intentos-1);
        if(pruebas[4][intentos-1] + pruebas[5][intentos-1] == 4)
        {
            puts("Has ganado!!");
            puts("");
            mostrar(pruebas);
            getc(c);
            main();
        }
        intentos --;
    }
    puts("");
    puts("Has perdido");
    puts("");
    for(i = 0; i < 4; i ++)
    {
        SetColor(vec[i]);
        printf("%c", 219);
    }
    getc(c);
    main();
}

void mostrar(int prueba[][N])
{
    int i, j;

    for(i = 0; i < 6; i++)
    {
        if(i < 4)
        {
            for ( j = 0; j < N; j++)
            {
                printf(" | ");
                SetColor(prueba[i][j]);
                printf("%c", 219);
                SetColor(15);
            }
        }
        else
        {
            for(j = 0; j < N; j++)
            {
                switch(prueba[i][j])
                {
                case 0:
                    printf(" |  ");
                    break;
                case 1:
                    printf(" | %c", 219);
                    break;
                case 2:
                    printf(" |%c%c", 219,219);
                    break;
                }
            }
        }
        puts("");

    }

}

void codcolor()
{

    system("cls");
    puts("");
    puts("1 - Azul");
    puts("2 - Verde");
    puts("3 - Cyan");
    puts("4 - Rojo");
    puts("5 - Magenta");
    puts("6 - Marron");
    puts("");
}

void prueba(int pruebas[][N], int vec[], int intento)
{
    int i, n = 0, j;
    do
    {
        i = 0;
        do{
        do
        {
            printf("Posicion %i, eliges color:\n", i+1);
            scanf("%i", &pruebas[i][intento]);
            fflush(stdin);
        }while(vec[i]<1 || vec[i]> 6);
        i++;
        }while(i < 4);
        puts("");
        for (j = 0; j < 4; j++)
        {
            SetColor(pruebas[j][intento]);
            printf("%c", 219);
        }
        SetColor(15);
        puts("");
        puts("Tu eleccion de colores es la siguiente en el orden mostrado, estas de acuerdo?");
        puts("1 - Si");
        puts("2 - No");
        puts("");
        scanf("%i", &n);

    }
    while(n == 2);

    int correctos = 0;

    for (i = 0; i < 4; i ++)
    {
        if(pruebas[i][intento] == vec[i])
            correctos++;
    }

    switch(correctos)
    {

    case 1:
        pruebas[4][intento] = 1;
        break;
    case 2:
        pruebas[4][intento] = 2;
        break;
    case 3:
        pruebas[4][intento] = 2;
        pruebas[5][intento] = 1;
        break;
    case 4:
        pruebas[4][intento] = 2;
        pruebas[5][intento] = 2;
        break;

    }

}
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
