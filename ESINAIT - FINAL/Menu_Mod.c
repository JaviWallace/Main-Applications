#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Carga_Mod.h"
#include "Menu_Mod.h"

void menu_compra(int* tam_obj, r_jugador* jug, r_objeto* v_obj){
    int i, n;
    char c[10];
    do
    {
        puts("");
        puts("Indique el indice del elemento a comprar");
        printf("O introduzca %i para salir\n", *tam_obj + 1);
        scanf("%i", &n);
    }
    while(n < 1 || n > (*tam_obj + 1));
    if(n != (*tam_obj + 1))
    {
        i = n-1;
        if(jug->dinero >= v_obj[i].coste){      // Si tiene suficiente dinero
            puts("Objeto comprado");
            jug->dinero -= v_obj[i].coste;      // Le restamos el coste
            jug->tamMochila += 1;               // Aumentamos el tamaño de la mochila
            jug->v_mochila = (r_mochila*) realloc (jug->v_mochila,jug->tamMochila*sizeof(r_mochila));   // Reasignamos el v_mochila del jugador
            strcpy(jug->v_mochila[jug->tamMochila-1].id,v_obj[i].identificador);    // Lo cargamos
            if(!strcmp(v_obj[i].tipo, "accesorio")){
                jug->v_mochila[jug->tamMochila-1].unidades = 2;
            }else if(!strcmp(v_obj[i].tipo, "arma")){
                jug->v_mochila[jug->tamMochila-1].unidades = 30;
            }else if(!strcmp(v_obj[i].tipo, "skin")){
                jug->v_mochila[jug->tamMochila-1].unidades = 1;

            }
        }else{                          // Si no tiene suficiente dinero
            puts("");
            puts("No tienes suficiente dinero");
            fflush(stdin);
            gets(c);
            menu_compra(tam_obj, jug, v_obj);   // Vuelve al menu de compra
        }
    }
}

void menu_tienda (int* tam_obj, r_objeto* v_obj, r_jugador* jug, r_config* config){
    int i, n = 0;
    do
    {
        system("cls");
        puts("Este es el listado de objetos disponibles: ");
        puts("");
        for(i = 0; i < *tam_obj; i++)   // Recorremos el vector de objetos
        {
            printf("%i .- %17s - %17s         %s\n", i+1, v_obj[i].identificador,v_obj[i].nombre, v_obj[i].tipo);   // Mostramos sus características generals
            printf("Coste: %i monedas\n", v_obj[i].coste);  // Sus características específicas
            printf("Alcance: %i\n", v_obj[i].alcance);
            printf("Dano: %i\n\n", v_obj[i].dano);
        }
        printf("\nMochila de %s        ocupado: %i/%i     Cartera: %i monedas\n",jug->nick, jug->tamMochila, config->maxSpMoch, jug->dinero);
        imprimir_mochila(jug);      // Mostramos la mochila del jugador
        puts("");
        puts("");
        puts("Que desea hacer?");
        puts("1 .- Comprar objeto");
        puts("2 .- Vender objeto");
        puts("3 .- Salir");
        puts("Introduzca la opcion");
        fflush(stdin);
        scanf("%i", &n);            // Solicitamos la opción a elegir
    }
    while(n < 1 || n > 3);
    switch(n)
    {
    case 1:
        if(jug->tamMochila >= config->maxSpMoch)        // Si tiene el tamaño máximo de mochila ocupado
        {
            puts("Espacio insuficiente");
            fflush(stdin);
            menu_tienda(tam_obj, v_obj, jug, config);   // Vuelve al menu de tienda
        }
        else
        {
            menu_compra(tam_obj,  jug, v_obj);          // Si no, entra al menú de compra
            menu_tienda(tam_obj, v_obj, jug, config);
        }
        break;
    case 2:
            menu_venta(*tam_obj, jug, v_obj);           // Si queremos vender, vamos al menú de venta
            menu_tienda(tam_obj, v_obj, jug, config);
        break;
    case 3:
        break;

    }
}

void menu_venta(int tam_obj, r_jugador* jug, r_objeto* v_obj){
    int n, i, j;
    do{
    system("cls");
    imprimir_mochila(jug);                  // Mostramos la mochila del jugador
    puts("Que elemento quieres vender? ");
    scanf("%i",&n);
    }while(n < 1 || n > jug->tamMochila);

    if(n == 1){     // Si ha elegido el cuchillo, no se lo permitimos vender
        puts("El cuchillo no se puede vender");
    }else{
        jug->tamMochila -= 1;
        i = n - 1;
        for(j = 0; j < tam_obj; j++){
            if(!strcmp(jug->v_mochila[i].id,v_obj[j].identificador)){   // Si existe el objeto, devolvemos el coste inicial
                jug->dinero += v_obj[j].coste;
                j = tam_obj + 10;
            }
        }

        if(j == tam_obj){
                jug->dinero += 15;      // En caso de que no exista el objeto
                j = tam_obj;
        }
        while(i < jug->tamMochila){     // Movemos cada objeto de la mochila un lugar a la izquierda
            jug->v_mochila[i] = jug->v_mochila[i+1];
            i++;
        }
        jug->v_mochila = (r_mochila*) realloc(jug->v_mochila, jug->tamMochila * sizeof(r_mochila));     // Reasignamos el tamaño de la mochila
    }

}

void mostrar_perfil(r_jugador *jug){
        int j;

        printf("Estos son tus datos personales:                   %s\n\n", jug->nombre);
        printf("Jugador: %s \n", jug->nick);
        printf("Nombre: %s\n", jug->nombre);
        printf("Nivel: %i\n", jug->nivel);
        printf("Dinero: %i\n", jug->dinero);
        printf("Partidas jugadas: %i\n", jug->partJugadas);
        printf("Partidas ganadas: %i\n", jug->partGanadas);
        for(j = 0; j < jug->tamMochila;j++){
            printf("\nArma o utilidad %i :\n\n", j+1);
            printf("ID: %s\n",jug->v_mochila[j].id);
            printf("Unidades/Municion: %i\n", jug->v_mochila[j].unidades);
        }
        puts("");
}

void cerrar_sesion(r_jugador* jug, int *conectado){
    strcpy(jug->estado,"OFF");
    *conectado = 0;
}

r_jugador* iniciar_sesion(r_jugador* v_jug, int tam_v, int* conectado, r_jugador* jug){
    int i, n= 0;
    int iaux = -1;                          /* Guardará el indice del vector de jugadores que coincide con el nick leido*/
    int tipoError = 0;                      /* Lo usaremos para saber que tipo de error ha dado*/
    char nick[TAM], ctrs[TAM];              /* Cadenas auxiliares para leer nick y contraseña*/
    do{
            iaux= -1;
        switch(tipoError){
            case 1:                                 /* Aqui habrán dos errores*/
                puts("No existe dicho usuario");
            case 2:                                 /* Aqui solo existe un error*/
                puts("Contrasena incorrecta");
                do{
                    puts("¿Quieres volver a intentarlo?");
                    puts("1 .- Si, volver a intentar");
                    puts("2 .- No, salir");
                    fflush(stdin);
                    scanf("%i", &n);
                }while(n != 1 && n!= 2);
                if(n == 2) return jug;                   /* Salimos con r_jugador = NULL*/

            default:                                /* En caso de que no se haya intentado iniciar aun, o se quiere volver a intentar*/
                tipoError = 0;
                puts("Introduzca su Nick");
                fflush(stdin);
                gets(nick);
                puts("Introduzca su Contrasena");
                fflush(stdin);
                gets(ctrs);
                for(i = 0; i < tam_v; i++){                 /* Una vez leido recorremos vector para ver si coincide con algun jugador existente el nick*/
                    if(!strcmp(nick, v_jug[i].nick)){
                        iaux = i;
                        i = tam_v;
                    }
                }
                if(iaux == -1) tipoError = 1;               /* Si no ha coincidido tenemos un error de tipo 1, no existe el usuario*/
                else{
                    for(i = 0; i < tam_v; i++) {
                        if(!strcmp(v_jug[i].pass, ctrs)){
                            puts("Has iniciado sesion correctamente");
                            puts("Presione enter para continuar");
                            fflush(stdin);
                            gets(nick);
                            if(strcmp(v_jug[iaux].estado,"EJ") && strcmp(v_jug[iaux].estado,"EE"))strcpy(v_jug[iaux].estado, "ON");
                            jug = &v_jug[iaux];
                            *conectado = 1;
                            i = tam_v+10;           // Identificar si ha iniciado sesion
                            tipoError = 0;
                        }
                    }
                    if(i < tam_v+10) tipoError = 2;    // Identficiador de error en la contraseña
                }

            }   /* Final del switch*/

    }while (tipoError > 0);
    return jug;
}

int registrar_usuario(r_jugador* v_jug, int tam_v, r_config* config){
    int n = 0, k = 0, i = 0;
    char contra[TAM], nombre[TAM], nick[TAM];
    do{
        do{
        puts("Para registrar un nuevo usuario deberá indicar su nick, nombre y contrasena");    // Pedimos los datos
        puts("Introduzca su nombre:");
        fflush(stdin);
        gets(nombre);
        puts("Introduzca el nick:");
        gets(nick);
        fflush(stdin);
        puts("Introduzca la contrasena:");
        gets(contra);
        fflush(stdin);
        puts("Estos son sus datos:");       // Mostramos datos escogidos
        printf("Nombre: %s\n", nombre);
        printf("Nick: %s\n", nick);
        printf("Contrasena: %s\n\n",contra);

        puts("Desea cambiarlos?");  // Vemos si desea cambiar alguno
        puts("1 .- Si");
        puts("2 .- No");
        puts("3 .- Salir");
        puts("");
        fflush(stdin);
        scanf("%i", &k);

        }while(k != 2 && k != 3);

            if(k == 1){
            while(i < tam_v && !strcmp(v_jug[i].nick,nick)) i++;    // Vemos si coincide con algun nick ya existente

            if(i >= tam_v){         // En caso de que exista preguntamos que quiere hacer
                puts("El nick ya existe");
                puts("");
                puts("Desea volver a intentarlo?");
                puts("1 .- Si");
                puts("2 .- No");
                puts("Introduzca la decision");
                scanf("%i", &n);
            }else {
                n = 0;
                puts("Se ha creado su usuario");
            }
            }else if (k == 3) n = 2;
        }while(n==1);

    if(n == 0){     // Si ha sido creado rellenamos los demas datos restantes

        i = tam_v-1;
        strcpy(v_jug[i].nombre, nombre);
        strcpy(v_jug[i].nick, nick);
        v_jug[i].nivel = 1;
        v_jug[i].vida = 100;
        v_jug[i].escudo = 0;
        v_jug[i].dinero = config->defMon;
        strcpy(v_jug[i].estado, "OFF");
        v_jug[i].partJugadas = 0;
        v_jug[i].partGanadas = 0;
        strcpy(v_jug[i].tipoUsuario, "JGD");
        strcpy(v_jug[i].pass, contra);
        v_jug[i].posTurno = 0;
        v_jug[i].tamMochila = 1;
        strcpy(v_jug[i].v_mochila[0].id,"CUCH");
        v_jug[i].v_mochila[0].unidades= 0;
        v_jug[i].acciones = 5;
        return n;
    }else return n;

}

void modificar_jugadores(r_jugador *v_jug, int tam_v){
    int n, i;

    do{
        system("cls");
        puts("Que jugador desea cambiar?");
        for (i = 0; i < tam_v; i++){    // Mostramos los datos generalizados que puede cambiar
            printf("%i .- %s/%s/%i/%i/%i/%s/%i/%i/%i/%s/%s\n",i+1,
                    v_jug[i].nick,
                    v_jug[i].nombre,
                    v_jug[i].nivel,
                    v_jug[i].vida,
                    v_jug[i].escudo,
                    v_jug[i].estado,
                    v_jug[i].dinero,
                    v_jug[i].partJugadas,
                    v_jug[i].partGanadas,
                    v_jug[i].tipoUsuario,
                    v_jug[i].pass);
        }

        printf("%i .- Ninguno/salir\n", tam_v+1);     // Ultima opcion es salir
        fflush(stdin);
        scanf("%i", &n);
    }while(n < 1 || n > (tam_v+1));
    if(n!= tam_v+1){
        i = n-1;
        menu_modificar_jugador(v_jug, i, tam_v);        // Si ha decidido cambiar uno de los jugadores vamos al segundo menu
    }
}

void menu_modificar_jugador(r_jugador* v_jug, int i, int tam_v){
    int n,h, auxNum, m;
    char aux[TAM];
    do{
        puts("Estos son sus datos, cual deseas cambiar?");      // Mostramos todos los datos especificos a poder cambiar
        printf("1 .- Jugador: %s \n", v_jug[i].nick);
        printf("2 .- Nombre: %s\n", v_jug[i].nombre);
        printf("3 .- Nivel: %i\n", v_jug[i].nivel);
        printf("4 .- Vida: %i\n", v_jug[i].vida);
        printf("5 .- Escudo: %i\n", v_jug[i].escudo);
        printf("6 .- Estado: %s\n", v_jug[i].estado);
        printf("7 .- Dinero: %i\n", v_jug[i].dinero);
        printf("8 .- Partidas jugadas: %i\n", v_jug[i].partJugadas);
        printf("9 .- Partidas ganadas: %i\n", v_jug[i].partGanadas);
        printf("10 .- Tipo de usuario: %s\n", v_jug[i].tipoUsuario);
        printf("11.- Contrasena: %s\n", v_jug[i].pass);
        printf("12 .- La mochila: \n");
        puts("13 .- Salir");
        puts("");
        fflush(stdin);
        scanf("%i",&n);
    }while(n < 1 || n > 13);
        switch(n){
    case 1:
    case 2:
    case 6:
    case 11:    // Si es uno de los campos de cadena de caracteres
        do{
        puts("Introducir cadena de caracteres: ");
        fflush(stdin);
        gets(aux);
        printf("\nEsta de acuerdo con su eleccion? - %s\n", aux);   // Opcion a poder deshacer los cambios
        puts("1 .- Si");
        puts("2 .- No, volver a introducir dato");
        puts("3 .- No, salir");
        fflush(stdin);
        scanf("%i", &h);
        }while(h == 2);
        if(h == 1){
            switch(n){
                case 1:
                    strcpy(v_jug[i].nick,aux);
                    break;
                case 2:
                    strcpy(v_jug[i].nombre,aux);
                    break;
                case 6:
                    strcpy(v_jug[i].estado,aux);
                    break;

                case 11:
                    strcpy(v_jug[i].pass,aux);
                    break;
            }
        }
        menu_modificar_jugador(v_jug, i, tam_v);
        break;
    case 10:

        do{
        puts("Seleccione:");
        puts("1 .- Admin");
        puts("2 .- Jugador normal");
        fflush(stdin);
        scanf("%i", &m);
        }while(m < 1 || m > 2);
        if(m == 1){
                strcpy(v_jug[i].tipoUsuario,"ADM");
        }else{
                strcpy(v_jug[i].tipoUsuario,"JGD");
        }

        break;
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:     // Si es uno de los campos numéricos
        do{
        puts("Introducir un entero: ");
        fflush(stdin);
        scanf("%i",&auxNum);
        printf("\nEsta de acuerdo con su eleccion? - %i\n", auxNum);    // Opción a deshacer los cambios
        puts("1 .- Si");
        puts("2 .- No, volver a introducir dato");
        puts("3 .- No, salir");
        fflush(stdin);
        scanf("%i", &h);
        }while(h == 2 || auxNum < 0);
        if(h == 1){
            switch(n){
                case 3:
                    v_jug[i].nivel = auxNum;
                    break;
                case 4:
                    v_jug[i].vida = auxNum;
                    break;
                case 5:
                    v_jug[i].escudo = auxNum;
                    break;
                case 7:
                    v_jug[i].dinero = auxNum;
                    break;
                case 8:
                    v_jug[i].partJugadas = auxNum;
                    break;
                case 9:
                    v_jug[i].partGanadas = auxNum;
                    break;
            }
        }
        menu_modificar_jugador(v_jug, i, tam_v);    // Siempre volvemos al mismo menu
        break;

    case 12:
        modificar_mochila_jugador(v_jug, i, tam_v); // En caso de que quiera cambiar la mochila vamos a un menu específico
        menu_modificar_jugador(v_jug, i, tam_v);
        break;
    case 13:
        modificar_jugadores(v_jug,tam_v);
        break;


        }
}

void modificar_mochila_jugador(r_jugador* v_jug, int i, int tam_v){
    int j, n, h, auxNum;
    do{
        system("cls");
        puts("Que elemento deseas cambiar?");
        for(j = 0; j < v_jug[i].tamMochila;j++){        // Mostramos la mochila del jugador
            imprimir_mochila(&v_jug[i]);
        }
        puts("");
        printf("%i .- para salir", j+1);                // Para poder salir
        puts("Introduzca su numero");
        scanf("%i,", &n);
    }while(n < 1 || n > (v_jug[i].tamMochila+1));
    if(n == (v_jug[i].tamMochila+1)){                   // Si hemos decidido salir llamamos al menu anterior
        menu_modificar_jugador(v_jug, i, tam_v);
    }
    else{
        system("cls");
        do{
            printf("Arma o utilidad %i :\n\n", n);      // Mostramos el elemento especifico a modificar
            printf("ID: %s\n",v_jug[i].v_mochila[n-1].id);
            printf("Unidades/Municion: %i\n", v_jug[i].v_mochila[n-1].unidades);
            puts("Introduzca el numero de unidades nuevo: ");   // Solo podremos cambiar el numero de unidades
            fflush(stdin);
            scanf("%i", &auxNum);
            printf("Estas de acuerdo con tu dato? - %i\n", auxNum); // En caso de que quiera cambiar su seleccion
            puts("1 .- Si");
            puts("2 .- No, volver a introducir");
            puts("3 .- No, Salir");
            fflush(stdin);
            scanf("%i", &h);
        }while(h == 2);
        if(h == 1) v_jug[i].v_mochila[n-1].unidades = auxNum;
        modificar_mochila_jugador(v_jug, i, tam_v);     // Volvemos al menu anterior
    }
}

void modificar_objetos(r_objeto *v_obj, int tam_v, r_config *config){
    int i, n, numAux, h;
    char strAux[TAM];
    do{
        system("cls");
        puts("Que objeto desea cambiar");
        for(i = 0; i < tam_v; i++){                     // Mostramos todos los objetos de forma generalizada
            printf("%i .- %s/%s/%s/%i/%i/%i\n", i+1,
                   v_obj[i].identificador,
                    v_obj[i].nombre,
                    v_obj[i].tipo,
                    v_obj[i].coste,
                    v_obj[i].alcance,
                    v_obj[i].dano);
        }
        printf("%i .- Salir\n", tam_v+1);                 // Mostramos opcion pa salir
        fflush(stdin);
        scanf("%i", &n);
    }while(n < 1 || n > (tam_v+1));
    if(n != (tam_v+1)){                       // Si no salimos entonces mostramos el objetos a cambiar
        i = n-1;
        do{
        system("cls");
        puts("Introduce el numero del elemento que quieras cambiar");
        printf("1 .- Identificador: %s\n", v_obj[i].identificador);
        printf("2 .- Nombre: %s\n", v_obj[i].nombre);
        printf("3 .- Tipo : %s\n", v_obj[i].tipo);
        printf("4 .- Coste: %i\n", v_obj[i].coste);
        printf("5 .- Alcance: %i\n", v_obj[i].alcance);
        printf("6 .- Dano: %i\n", v_obj[i].dano);
        puts(" 7 .- Salir");
        fflush(stdin);
        scanf("%i", &h);
        }while(h < 1 || h > 7); // Mientras que no sea una de nuestras opciones

        switch(h){  // Mostramos el parametro a cambiar
        case 1:
        puts("Introduce identificador");
        fflush(stdin);
        gets(strAux);
        strcpy(v_obj[i].identificador,strAux);
        break;
        case 2:
        puts("Introduce nombre");
        fflush(stdin);
        gets(strAux);
        strcpy(v_obj[i].nombre,strAux);
        break;
        case 3:
        puts("Introduce tipo");
        fflush(stdin);
        gets(strAux);
        strcpy(v_obj[i].tipo,strAux);
        break;
        case 4:

        puts("Introduce coste");
        do{
        fflush(stdin);
        scanf("%i", &numAux);
        }while(numAux < 0);
        v_obj[i].coste = numAux;
        break;
        case 5:

        puts("Introduce alcance");
        do{

        printf("\n Tiene que ser menor que %i\n", config->disMaxAt);
        fflush(stdin);
        scanf("%i", &numAux);
        }while(numAux < 0 || numAux > config->disMaxAt);
        v_obj[i].alcance = numAux;
        break;
        case 6:

        puts("Introduce dano/curacion");
        do{
        fflush(stdin);
        scanf("%i", &numAux);
        }while(numAux < 0);
        v_obj[i].dano = numAux;

        break;
        case 7:
        break;


        }
        modificar_objetos(v_obj, tam_v,config);    // Volvemos al mismo menu

    }
}

void anadir_objeto(r_objeto *v_obj, int tam_v, r_config* config){
    int i = tam_v-1, numAux;
    char strAux[TAM];
    system("cls");
    puts("El formato estandar es:");     // Mostramos el formato estandar de un objeto cualesquiera
        printf("1 .- Identificador: %s\n", v_obj[0].identificador);
        printf("2 .- Nombre: %s\n", v_obj[0].nombre);
        printf("3 .- Tipo : %s\n", v_obj[0].tipo);
        printf("4 .- Coste: %i\n", v_obj[0].coste);
        printf("5 .- Alcance: %i\n", v_obj[0].alcance);
        printf("6 .- Dano: %i\n", v_obj[0].dano);

        puts("Introduce identificador");
        fflush(stdin);
        gets(strAux);
        strcpy(v_obj[i].identificador,strAux);

        puts("Introduce nombre");
        fflush(stdin);
        gets(strAux);
        strcpy(v_obj[i].nombre,strAux);

        printf("Que tipo es? \n 1 .- Arma\n 2 .- Accesorio\n 3 .- Skin\n\n");       // Para evitar conflictos de tipos
        fflush(stdin);
        scanf("%i", &numAux);
        switch(numAux){
            case 1:
                strcpy(v_obj[i].tipo,"arma");
                break;
            case 2:
                strcpy(v_obj[i].tipo,"accesorio");
                break;
            case 3:
                strcpy(v_obj[i].tipo,"skin");
                break;
        }

        puts("Introduce coste");
        fflush(stdin);
        scanf("%i", &numAux);
        v_obj[i].coste = numAux;

        do{
        printf("Introduce alcance, tiene que ser menor que %i\n", config->disMaxAt);
        fflush(stdin);
        scanf("%i", &numAux);
        v_obj[i].alcance = numAux;
        }while(numAux > config->disMaxAt);

        puts("Introduce dano/curacion");
        fflush(stdin);
        scanf("%i", &numAux);
        v_obj[i].dano = numAux;

}

int quitar_objeto(r_objeto* v_obj, int tam_v){
    int res = 0, n, i;

    do{
        system("cls");
        puts("Que objeto desea eliminar") ;
        for(i = 0; i < tam_v; i++){                 // Mostramos los objetos posibles
            printf("%i .- %s/%s/%s/%i/%i/%i\n", i+1,
                   v_obj[i].identificador,
                    v_obj[i].nombre,
                    v_obj[i].tipo,
                    v_obj[i].coste,
                    v_obj[i].alcance,
                    v_obj[i].dano);
        }
        printf("%i .- Salir\n", tam_v+1);
        fflush(stdin);
        scanf("%i", &n);
    }while(n < 1 || n > (tam_v+1));
    if(n != (tam_v+1)){
        for(i = n-1; i < tam_v-1; i++){
            v_obj[i] = v_obj[i+1];
        }
        res = 1;
    }
    return res;
}

void modificar_mapa(tipo_posicion *v, int N){
    char cambio[TAM];
    int i,buscado=-1;
    do{
        printf("Los datos actuales son los siguientes:\n");
        mostrar_mapa(v,N);
        fflush(stdin);
        do{
            printf("Introduce la id/nick del registro que quieres cambiar\n");
            fflush(stdin);
            gets(cambio);
            for(i=0;i<N;i++) //Buscamos un elemento en el vector cuyo nombre o id sea el mismo
            {
                if(strcmp(v[i].id_nick,cambio)==0) buscado=i;
            }
            if (buscado==-1) printf("No se ha encontrado a ningún jugador con ese nick\n");
        }while(buscado==-1);
        //A partir de aquí, si se ha encontrado dicho elemento, se guia al usuario para que modifique el registro
        do{
            fflush(stdin);
            printf("Pulsa 0 para ponerlo como jugador o 1 para objeto");
            scanf("%d",&i);
        }while((i!=0)&&(i!=1));
        v[buscado].tipo=i;

        fflush(stdin);
        printf("Introduce la coordenada x\n");
        scanf("%d",&i);
        v[buscado].coordenada_x=i;

        fflush(stdin);
        printf("Introduce la coordenada y\n");
        scanf("%d",&i);
        v[buscado].coordenada_y=i;

        fflush(stdin);
        printf("Pulsa -1 para salir o cualquier otra tecla para volver a cambiar un registro");
        scanf("%d",&i);
    }while(i!=-1);
}

void agregar_elemento_al_mapa(tipo_posicion *v,int N){
    int i=N-1,j; //Añadimos un elemento más a la estructura habiendole hecho anteriormente un realloc al vector
    char nombre[TAM];
    printf("Introduce el nombre del elemento");
    fflush(stdin);
    scanf("%s",nombre);
    strcpy(v[i].id_nick,nombre);
    do{
        fflush(stdin);
        printf("Pulsa 0 para ponerlo como jugador o 1 para objeto");
        scanf("%d",&j);
    }while((j!=0)&&(j!=1));
    v[i].tipo = j;
    printf("Introduce la coordenada x\n");
    scanf("%d",&j);
    v[i].coordenada_x=j;
    printf("Introduce la coordenada y\n");
    scanf("%d",&j);
    v[i].coordenada_y=j;
}

void modificar_tormenta(tipo_estadotormenta *v, int N){
    int i,buscado=-1;

        printf("Los datos actuales son los siguientes:\n");
        mostrar_tormenta(v,N);
        fflush(stdin);
        printf("0 .- Salir\n");

        do{
            fflush(stdin);
            printf("Introduce el numero del estado que quieres cambiar\n"); //Buscamos el estado que nos indique el usuario
            scanf("%d",&buscado);
            buscado--;
        }while(buscado>=N || buscado < -1);

        //Si dicho estado existe, procedemos a hacer una modificación guiada del registro
        if(buscado != -1){
        fflush(stdin);
        printf("Introduce la coordenada x\n");
        scanf("%d",&i);
        v[buscado].coordenada_x=i;

        fflush(stdin);
        printf("Introduce la coordenada y\n");
        scanf("%d",&i);
        v[buscado].coordenada_y=i;

        fflush(stdin);
        printf("Introduce el radio de la tormenta\n");
        scanf("%d",&i);
        v[buscado].radio=i;

        fflush(stdin);
        printf("Introduce los turnos que hacen falta para que se reduzcan\n");
        scanf("%d",&i);
        v[buscado].turnos=i;
        }
}

void agregar_estado_a_tormenta(tipo_estadotormenta *v,int N){
    //Añadimos un elemento más a la estructura habiendole hecho anteriormente un realloc al vector
    int i=N-1,j;
    printf("Introduce la coordenada x\n");
    scanf("%d",&j);
    v[i].coordenada_x=j;
    printf("Introduce la coordenada y\n");
    scanf("%d",&j);
    v[i].coordenada_y=j;
    printf("Introduce el radio de la tormenta\n");
    scanf("%d",&j);
    v[i].radio=j;
    v[i].turnos=0;
}

void menuConfig(r_config *conf){
	int fin=0;
	do{
		switch(printMenuConfig(conf))       // Llamamos a la funcion para ver que aspecto se va a cambiar
		{
		case 1:
			printf("\nIntroduzca nuevo valor para radio del mapa: ");
			fflush(stdin);
			scanf("%i",&conf->radMap);
			break;
		case 2:
			printf("\nIntroduzca nuevo valor para distancia minima para coger objeto: ");
			fflush(stdin);
			scanf("%i",&conf->disMinObj);
			break;
		case 3:
			printf("\nIntroduzca nuevo valor para distancia maxima de ataque del arma por defecto: ");
			fflush(stdin);
			scanf("%i",&conf->disMaxAt);
			break;
		case 4:
			printf("\nIntroduzca nuevo valor para monedas por defecto: ");
			fflush(stdin);
			scanf("%i",&conf->defMon);
			break;
		case 5:
			printf("\nIntroduzca nuevo valor para minimo de jugadores por partida: ");
			fflush(stdin);
			scanf("%i",&conf->minJug);
			break;
		case 6:
			printf("\nIntroduzca nuevo valor para distancia recorrida por movimiento: ");
			fflush(stdin);
			scanf("%i",&conf->disPMov);
			break;
		case 7:
			printf("\nIntroduzca nuevo valor para espacio maximo en mochila: ");
			fflush(stdin);
			scanf("%i",&conf->maxSpMoch);
			break;
		case 8:
			printf("\nIntroduzca nuevo valor para minimo de partidas a ganar por nivel: ");
			fflush(stdin);
			scanf("%i",&conf->minPartPNiv);
			break;
		case 9:
			printf("\nIntroduzca nuevo valor para maximo numero de acciones por turno: ");
			fflush(stdin);
			scanf("%i",&conf->maxAccPTurno);
			break;
		case 0:
			fin=1;      // Salimos
			break;
		default:
			fin=0;
			break;
		}
	}while(fin!=1);
}

int printMenuConfig(r_config *config){
	int opc;
	system("cls");
	printf("1.-Radio del mapa: %i\n2.-Distancia minima para coger objeto: %i\n3.-Distancia maxima de ataque del arma por defecto: %i\n4.-Monedas por defecto: %i\n5.-Minimo jugadores por partida: %i\n6.-Distancia recorrida por movimiento: %i\n7.-Espacio maximo de mochila: %i\n8.-Partidas minimas a ganar para subir de nivel: %i\n9.-Maximo de acciones por turno: %i\n0.-Salir\n\nQue variable desea modificar? ",config->radMap,config->disMinObj,config->disMaxAt,config->defMon,config->minJug,config->disPMov,config->maxSpMoch,config->minPartPNiv,config->maxAccPTurno);
	fflush(stdin);
	scanf("%i",&opc);
	return opc;
}

void printConfig(r_config *config){

	printf("1.-Radio del mapa: %i\n2.-Distancia minima para coger objeto: %i\n3.-Distancia maxima de ataque del arma por defecto: %i\n4.-Monedas por defecto: %i\n5.-Minimo jugadores por partida: %i\n6.-Distancia recorrida por movimiento: %i\n7.-Espacio maximo de mochila: %i\n8.-Partidas minimas a ganar para subir de nivel: %i\n9.-Maximo de acciones por turno: %i\n\n",config->radMap,config->disMinObj,config->disMaxAt,config->defMon,config->minJug,config->disPMov,config->maxSpMoch,config->minPartPNiv,config->maxAccPTurno);

}

int eliminar_estado_tormenta(tipo_estadotormenta *v,int N){
    int i,j, res = 0;
    system("cls");
    mostrar_tormenta(v,N);
    printf("%i .- Para salir", N+1);
    do{
        printf("\n¿Que estado quieres eliminar?\n");
        fflush(stdin);
        scanf("%d",&j);
    }while(j<1||j > (N+1));
    if(j!=N+1)
    {
        j--; //Ya que, por ejemplo, el estado numero 2 se corresponde con el indice 1
        i=j+1;
        while(j<N)
        {
            v[j].coordenada_x=v[i].coordenada_x;
            v[j].coordenada_y=v[i].coordenada_y;
            v[j].radio=v[i].radio;
            v[j].turnos=v[i].turnos;
            j++;
            i++;
        }
        res = 1;
        printf("Se ha eliminado el estado");
    }
    return res;
}
