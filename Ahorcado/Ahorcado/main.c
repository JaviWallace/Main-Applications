#include <stdio.h>
#define N 25550
#define X 30
#define I 5
#include <string.h>
#include <conio.h>
void pantalla (char [], char[], int, int[]);
void juego(char[], char[], int[]);
int comprobar(char*, char*, char);
int main()
{

    srand (time(NULL));
    int n;
    do
    {
        n = rand() - (rand()% (N-1))* (rand() % 11) ;
    }
    while(n > N || n < 0);

    int i;
    FILE *f;
    char cad[X], conocida[X];
    for (i = 0; i < X; i++)
        conocida[i] = '\0';

    f = fopen("palabras.txt", "r");
    for(i = 0; i < n; i++)
    {
        fscanf(f,"%s\n", cad);
    }
    //printf("%i   -   %s",n, cad);
    int letras[25];
    for (i = 0; i < 25; i++) {
            letras[i] = 1;
        //printf("Hey %i\n", letras[i]);
    }
    juego(cad, conocida, letras);
}


void pantalla (char cad[], char conocida[], int intentos, int letras[])
{
    int longitud = strlen(cad), i;
    system("cls");
    puts("");
    printf("                            Intentos: %i\n", intentos);
    printf("      ");
    for(i = 0; i < 25; i++){
        if(i == 10 )printf("\n       ");
        else if( i == 19) printf("\n         ");
        if(letras[i] == 1)printf("%c ", (i + 97));
        else printf("  ");
    }
    puts("");
    puts("");
    printf("        ");
    for (i = 0; i < longitud; i++)
    {
        if (conocida[i] != '\0')
            printf("%c ", conocida[i]);
        else
            printf("_ ");

    }
    puts("");
    puts("Introduce caracter:");
}
void juego( char cad[], char conocida[], int letras[])
{
    int intentos = I, i;
    char c ;

    while (intentos > 0 && strcmp(cad, conocida) != 0)
    {
        pantalla (cad, conocida, intentos, letras);
        fflush(stdin);
        scanf("%c", &c);
        fflush(stdin);
        letras[c - 97] = 0;
        if(comprobar(cad, conocida, c) != 1)
            --intentos;
    }
    if(strcmp(cad, conocida) == 0)
    {
        pantalla (cad, conocida, intentos, letras);
        puts("");
        puts("Has ganado!");

    }
    else{
        puts("Has perdido :(");
        printf("La palabra era %s", cad);
    }
    gets(cad);
    main();
}
int comprobar(char *cad, char *conocida, char c)
{
    int res = 0, i, len;
    len = strlen(cad);
    for (i = 0; i < len; i++)
    {
        if (c == *(cad + i))
        {
            res = 1;
            *(conocida + i) = c;
        }
    }
    return res;
}
