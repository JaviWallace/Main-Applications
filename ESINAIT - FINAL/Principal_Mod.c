#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Carga_Mod.h"
#include "Menu_Mod.h"
#include "juego_Mod.h"


// Cabecera:        void menu(int* tam_v, int conectado, int* tam_obj, int* tam_mapa, int* tam_tor, r_jugador **v_jug, r_config * config, r_jugador * jug, r_objeto ** v_obj, tipo_estadotormenta ** v_tor, tipo_posicion **v_pos, tipo_posicion ** v_jugadoresCercanos)
// Precondición:    Recibe la direccion de todos los punteros a vectores (tipo "v_") necesarios para todo el juego, cargados completamente y los tamaños de estos en los tipo "tam_"
// Postcondición:   Muestra en pantalla el menú principal del sistema e interaccionar con él

void menu(int* , int , int* , int* , int* , r_jugador **, r_config *, r_jugador *, r_objeto ** , tipo_estadotormenta ** , tipo_posicion **, tipo_posicion **);

// Cabecera:        void menu_partida(int* tam_v, int conectado, int* tam_obj, int* tam_mapa,int* tam_tor, r_jugador **v_jug, r_config * config, r_jugador * jug, r_objeto ** v_obj, tipo_estadotormenta ** v_tor, tipo_posicion **v_pos, tipo_posicion ** v_jugadoresCercanos)
// Precondición:    Recibe la direccion de todos los punteros a vectores (tipo "v_") necesarios para todo el juego, cargados completamente y los tamaños de estos en los tipo "tam_"
// Postcondición:   Muestra en pantalla el menú del juego y todas las opciones para realizar en él, es el jeugo en sí mismo

void menu_partida(int* , int , int* , int* , int* , r_jugador **, r_config *, r_jugador *, r_objeto ** , tipo_estadotormenta ** , tipo_posicion **, tipo_posicion **);


int main()
{
    int i;
    int tam_v = numero_filas(JUGADORES);        // tam_v = número de elementos del vector v_jug
    int tam_obj = numero_filas(OBJETOS);        // tam_obj = número de elementos del vector v_obj
    int tam_tor = numero_filas(TORMENTA);       // tam_tor = número de elementos del vector v_tor
    int tam_mapa = numero_filas(MAPA);          // tam_mapa = número de elementos del vector v_pos

    r_jugador *v_jug;                           // Aqui tenemos los punteros que servirán como vectores para almacenar jugadores
    r_config *config;                           // Configuración
    r_jugador *jug;                             // El jugador que en este momento esté con la sesión iniciada
    r_objeto *v_obj;                            // Objetos
    tipo_estadotormenta *v_tor;                 // Tormenta
    tipo_posicion *v_pos;                       // Elementos del mapa

    tipo_posicion *v_jugadoresCercanos;         // Jugadores cercanos al jugador que sea su turno

    srand(time(NULL));

    // Secuencia de Carga de Datos
    v_pos = (tipo_posicion*) malloc (tam_mapa * sizeof(tipo_posicion));                 // Asignamos la memoria a los vectores v_pos y v_tor
    v_tor = (tipo_estadotormenta*) malloc (tam_tor * sizeof(tipo_estadotormenta));

    cargar_mapa(v_pos, tam_mapa);
    cargar_tormenta(v_tor, tam_tor);            // Cargamos ambos vectores

    v_jugadoresCercanos = (tipo_posicion*) malloc (sizeof(tipo_posicion));
    v_obj = (r_objeto*) malloc (tam_obj*sizeof(r_objeto));
    config = (r_config*) malloc(sizeof(r_config));
    v_jug = (r_jugador*) malloc(tam_v * sizeof(r_jugador));	    // Asignamos memoria a los vectores v_jug y v_obj
    cargar_jugador(v_jug, tam_v);               // Cargamos los jugadores pero no su mochila
    for(i = 0; i < tam_v; i++)
    {
        v_jug[i].v_mochila = (r_mochila*) malloc (v_jug[i].tamMochila * sizeof(r_mochila));        // Asignamos el puntero del vector mochila
        cargar_mochila(v_jug[i].v_mochila, v_jug[i].tamMochila, v_jug[i].nick);                    // Cargamos la mochila
        v_jug[i].seleccionado = 0;  // Seleccionado su cuchillo
    }
    cargaConfig(config);                        // Cargamos la configuración y los objetos
    cargar_objetos(v_obj,tam_obj);
    jug = &v_jug[0];

    for(i = 0; i < tam_v; i++){
        v_jug[i].seleccionado = 0;
    }

    menu(&tam_v, 0, &tam_obj, &tam_mapa, &tam_tor, &v_jug, config, jug, &v_obj, &v_tor, &v_pos, &v_jugadoresCercanos);      // Entramos en el menú de juego

    // Secuencia de salvar datos y liberar memoria guardada

    guardar_objetos(v_obj, tam_obj);
    guardar_mochila(v_jug, tam_v);
    guardar_jugador(v_jug, tam_v);
    guardaConfig(*config);
    guardar_mapa(v_pos, tam_mapa);
    guardar_tormenta(v_tor, tam_tor);
    for(i = 0; i < tam_v; i++)
    {
        free(v_jug[i].v_mochila);

    }
    free(v_jug);
    free(config);
    free(v_obj);
    free(v_pos);
    free(v_tor);
    free(jug);
    free(v_jugadoresCercanos);
    return 0;
}

void menu(int* tam_v, int conectado, int* tam_obj, int* tam_mapa, int* tam_tor, r_jugador **v_jug, r_config * config, r_jugador * jug, r_objeto ** v_obj, tipo_estadotormenta ** v_tor, tipo_posicion **v_pos, tipo_posicion ** v_jugadoresCercanos)
{

    int n, i, jugEnEspera = 0, jugEnJuego = 0, h;
    int opt = 0;                    // Recoge el numero de opciones que hay en el menu
    char c[TAM_RED];
    system("cls");

    // Calculamos el nivel de cada jugador
    for (i = 0; i < *tam_v; i++){
        (*v_jug)[i].nivel = (*v_jug)[i].partGanadas/ config->minPartPNiv;       // Dividimos el total de partidas ganadas entre el nº de partidas necesarias para subir de nivel
    }
    do      // Mostramos las opcciones del menú
    {
        if(!strcmp(jug->estado,"EE")){      // Si el jugador está en espera
            printf("Nick: %s    Se encuentra en espera\n\n", jug->nick);
            puts("1 .- Cerrar sesion");
            puts("2 .- Salir sistema");
            opt = 2;
        }
        else if(conectado == 0)          // Si no hay jugador conectado
        {
            puts("1 .- Iniciar sesion");
            puts("2 .- Registrar usuario");
            puts("3 .- Salir sistema");
            opt = 3;
        }
        else if (!strcmp(jug->estado,"ON") && conectado == 1)      //Si hay jugador conectado y no esta en juego
        {
            printf("Nick: %s    \n\n", jug->nick);
            puts("1 .- Cerrar sesion");
            puts("2 .- Jugar");
            puts("3 .- Tienda");
            puts("4 .- Ver perfil");
            puts("5 .- Salir sistema");
            opt = 5;
        }
        else if (!strcmp(jug->estado,"EJ") && conectado == 1)    // Si el jugador esta en juego
        {
            printf("Nick: %s    \n\n", jug->nick);
            puts("1 .- Continuar partida");
            puts("2 .- Ver perfil");
            puts("3 .- Cerrar sesion");

            opt = 3;
        }
        if(!strcmp(jug->tipoUsuario,"ADM") && (!strcmp(jug->estado,"EJ") || !strcmp(jug->estado,"ON"))){                // Si el jugador es administrador, se le muestran las demás opciones
            puts("6 .- Anadir estado Tormenta");
            puts("7 .- Quitar estado Tormenta");
            puts("8 .- Modificar Tormenta");
            puts("9 .- Modificar Mapa");
            puts("10 .- Anadir elemento a Mapa");
            puts("11 .- Cambiar Jugador");
            puts("12 .- Modificar Objeto");
            puts("13 .- Anadir Objeto");
            puts("14 .- Quitar Objeto");
            puts("15 .- Cambiar Configuracion");
            puts("16 .- Iniciar Partida");
            opt = 16;
        }
        puts("Que deseas hacer?");          // Elige la opción
        fflush(stdin);
        scanf("%i", &n);

    }
    while(n < 1 || n > opt);

    switch(n)
    {
    case 1:
        if(conectado == 0)             // Para iniciar sesion o cambiar de usuario
        {
            jug = iniciar_sesion(*v_jug, *tam_v, &conectado, jug);
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }
        else if (conectado == 1 && (!strcmp(jug->estado,"ON") || !strcmp(jug->estado,"EE")))    // Cerrar sesión si está en espera o conectado
        {
            cerrar_sesion(jug, &conectado);
            jug = &*v_jug[0];
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }else if(conectado == 1 && !strcmp(jug->estado,"EJ")){      // Si está en juego vuelve al menu de juego

            menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }
        break;
    case 2:
        if(!strcmp(jug->estado, "EE")) break;   // Si etá en espera sale del sistema
        else if (conectado == 0)         //Registramos usuario
        {

            *tam_v += 1;
            *v_jug = (r_jugador*) realloc (*v_jug,(*tam_v)*sizeof(r_jugador));        // Asignamos memoria para el nuevo usuario
            (*v_jug)[*tam_v-1].v_mochila = (r_mochila*) malloc (sizeof(r_mochila));   // Asignamos memoria para su mochila

            if (registrar_usuario(*v_jug,*tam_v,config) == 2)                         // Si el usuario no ha sido creado deshacemos los cambios
            {
                tam_v--;
                free((*v_jug)[*tam_v].v_mochila);
                *v_jug = (r_jugador*) realloc(*v_jug, (*tam_v)*sizeof(r_jugador));
            }
            else
            {
                puts("Jugador creado");
            }
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);     // Volvemos al menú
        }
        else if (!strcmp(jug->estado,"ON") && conectado == 1)       // Si está conectado y decide jugar o continuar partida
        {
            strcpy(jug->estado,"EE");       // Entra en espera
            conectado = 0;
            jug = &*v_jug[0];
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        } else{
            mostrar_perfil(jug);            // Mostramos el perfil
            fflush(stdin);
            gets(c);
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }

        break;
    case 3:
        if(conectado == 0)                  // Si está desconectado salimos del sistema
        {
            break;                                  // Salir del sistema
        }
        else if(!strcmp(jug->estado,"ON"))  // Si está conectado, entramos en la tienda
        {
            menu_tienda(tam_obj,*v_obj,jug,config);
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }else{      // Si está en juego y sale del sistema, lo matamos y cerramos su sesión
            for(i = 0; i < *tam_v; i++){
                if(!strcmp(jug->nick,(*v_jug)[i].nick)){
                    h = i;
                    i = *tam_v;
                }
            }
            muere(tam_mapa,h, v_pos, *v_jug, *v_obj, tam_obj);       // Muere

            strcpy(jug->estado,"OFF");              // Desconectamos
            cerrar_sesion(jug, &conectado);
            jug = &*v_jug[0];
            conectado = 0;
            system("cls");
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);

        }
        break;
    case 4:
        system("cls");
        mostrar_perfil(jug);                        // Mostramos perfil
        fflush(stdin);
        gets(c);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 5:
        strcpy(jug->estado,"OFF");                  // Salir del sistema
        break;
    case 6:             // Añadir estado tormenta
        *tam_tor += 1;
        *v_tor = (tipo_estadotormenta*) realloc (*v_tor,(*tam_tor)*sizeof(tipo_estadotormenta));
        agregar_estado_a_tormenta(*v_tor, *tam_tor);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 7:         // Quitar estado tormenta
        if(eliminar_estado_tormenta(*v_tor, *tam_tor) != 0){
            *tam_tor -= 1;
            *v_tor = (tipo_estadotormenta*) realloc (*v_tor, (*tam_tor)*sizeof(tipo_estadotormenta));
        }
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 8:         // Modificar tormenta
        modificar_tormenta(*v_tor, *tam_tor);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 9:         // Modificar mapa
        modificar_mapa(*v_pos, *tam_mapa);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 10:        // Anadir elemento a mapa
        *tam_mapa += 1;
        *v_pos = (tipo_posicion*) realloc (*v_pos,(*tam_mapa)*sizeof(tipo_posicion));
        agregar_elemento_al_mapa(*v_pos, *tam_mapa);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 11:        // Cambiar jugador
        modificar_jugadores(*v_jug, *tam_v);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 12:        // Modificar objeto
        modificar_objetos(*v_obj, *tam_obj, config);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 13:        // Anadir objeto
        *tam_obj += 1;
        *v_obj = (r_objeto*) realloc (*v_obj,(*tam_obj)*sizeof(r_objeto));
        anadir_objeto(*v_obj, *tam_obj, config);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 14:        // Quitar objeto
        if(quitar_objeto(*v_obj, *tam_obj)!= 0){
            *tam_obj -= 1;
            *v_obj = (r_objeto*) realloc (*v_obj,(*tam_obj)*sizeof(r_objeto));
        }
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 15:        // Cambiar configuracion
        menuConfig(config);
        menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        break;
    case 16:        // Comenzar partida
        jugEnJuego = 0;
        for(i = 0; i < *tam_v; i++){
            if(!strcmp((*v_jug)[i].estado,"EJ")){   // Vemos si hay algun jugador en juego
                i = *tam_v;
                jugEnJuego++;

            }
        }
        if(jugEnJuego == 0){        // Si no hay jugadores en juego podemos empezar una partida


        for ( i = 0; i < *tam_v; i++) if(!strcmp((*v_jug)[i].estado,"EE")) jugEnEspera++;
        if(jugEnEspera < config->minJug){           // Vemos si hay suficientes jugadores en espera
            puts("No hay suficientes jugadores");
            fflush(stdin);
            gets(c);
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }else{                                      // Si los hay, procedemos a iniciar la partida
            comenzar_partida(tam_v,tam_obj,tam_mapa, v_pos, *v_jug, *v_obj, jug, config);
            menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
        }
        }else{  // Si hay una partida en juego preguntamos si quiere eliminarla
            printf("\nHay una partida actualmente en juego\n");
            printf("Deseas eliminar la partida que hay en juego?\n");
            do{
            puts("1 .- Si, eliminar");
            puts("2 .- No, salir");
            fflush(stdin);
            scanf("%i", &h);
            }while(h<1 || h > 2);
            if(h == 1){ // Si quiere eliminarla

                for(i = 0; i < *tam_v; i++){
                    if(!strcmp((*v_jug)[i].estado,"EJ")||!strcmp((*v_jug)[i].estado,"GO")){         // Desconectamos a todos los jugadores
                        jugEnJuego++;
                        strcpy((*v_jug)[i].estado,"OFF");

                    }

                }
                if(!strcmp(jug->estado,"OFF")) {        // Si hemos desconectado al damin, lo volvemos a conectar
                        strcpy(jug->estado,"ON");
                }
                menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);

            }

        }
        break;

    }
}

void menu_partida(int* tam_v, int conectado, int* tam_obj, int* tam_mapa,int* tam_tor, r_jugador **v_jug, r_config * config, r_jugador * jug, r_objeto ** v_obj, tipo_estadotormenta ** v_tor, tipo_posicion **v_pos, tipo_posicion ** v_jugadoresCercanos)
{

    if(conectado!=0 && strcmp(jug->estado,"OFF")){          // Si está conectado entonces:

    system("cls");

    int op=0,i,buscado=0, totJugadores = 0, iObjeto = 0;
    char c[TAM_RED];

    for(i = 0; i < *tam_obj; i++){              // Buscamos el índice del objeto seleccionado
        if(!strcmp(jug->v_mochila[jug->seleccionado].id,(*v_obj)[i].identificador)){
            iObjeto = i;
            i = *tam_obj;
        }
    }
    // Mostramos el menú de juego y las características principales del jugador que sea su turno
    printf("\n%s                           Acciones restantes  %i/%i\n",jug->nick, jug->acciones,config->maxAccPTurno);
    printf("Objeto seleccionado: %s     Unidades: %i        Alcance: %i\n", jug->v_mochila[jug->seleccionado].id, jug->v_mochila[jug->seleccionado].unidades, (*v_obj)[iObjeto].alcance);
    printf("Vida: %i    Escudo: %i\n",jug->vida, jug->escudo);
    puts("1 .- Ver mochila");
    puts("2 .- Usar objeto");
    puts("3 .- Moverse");
    puts("4 .- Soltar objeto");
    puts("5 .- Ver objetos cercanos");
    puts("6 .- Ver oponentes cercanos");
    puts("7 .- Ver posicion actual");
    puts("8 .- Ver tormenta");
    puts("9 .- Finalizar turno");
    puts("10 .- Volver al menu principal");

    do{
        // Comprobamos estado de juego
        totJugadores = 0;
        fuera_tormenta(tam_v, tam_mapa, *v_tor, config, v_pos, *v_jug, *v_obj, tam_obj);
        for(i = 0; i < *tam_v; i++){
            if(!strcmp((*v_jug)[i].estado,"EJ"))totJugadores++;

        }
        if(totJugadores == 1){   // Si solo queda un jugador con vida, ha ganado la partida
            fin_juego(tam_v, tam_obj, *v_jug, &jug, *v_obj);
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
            op = 20;
        }
        else if(totJugadores == 0){   // Si han muerto todos en la tormenta
            puts("Han muerto todos los jugadores, no hay ganador");
            fflush(stdin);
            gets(c);
            menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
            op = 20;
        }else{
            printf("\nQue quieres hacer?\n");
            fflush(stdin);
            scanf("%d",&op);
        }


        }while(op<1 || (op > 10 && op!= 20));
        switch(op)
        {
            case 1: // Ver mochila

                imprimir_mochila(jug);
                do{                         // Permitir seleccionar un objeto
                printf("¿Quieres seleccionar un objeto? \n");
                puts("1.- Si");
                puts("2 .- No, Salir");
                scanf("%d",&op);
                }while(op < 1 || op > 2);
                if(op==1)                   // Si desea seleccionarlo
                {
                    printf("\nQue objeto deseas seleccionar? (Introduce el numero del elemento)\n");
                    scanf("%d",&i);
                    jug->seleccionado=i-1;
                    printf("Se ha seleccionado el objeto %s\n", jug->v_mochila[jug->seleccionado].id);
                }
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 2:     // Usar objeto
                if(jug->acciones > 0){      // Si tiene acciones suficientes
                usar_objeto(tam_v,conectado,tam_obj,tam_mapa, tam_tor, jug, *v_obj, v_pos,v_jugadoresCercanos, config, *v_jug);
                }else{
                    printf("\nNo tienes suficientes acciones disponibles\n");
                    fflush(stdin);
                    gets(c);
                }
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);

                break;
            case 3:     // Moverse
                if(jug->acciones > 0){      // Si tiene acciones suficientes
                jug->acciones -= 1;
                movimiento(tam_mapa, *v_pos, jug, config);      // Decide donde moverse
                if(fuera_tormenta(tam_v,tam_mapa, *v_tor, config, v_pos, *v_jug, *v_obj, tam_obj)==1) fin_turno(tam_v, tam_tor, *v_jug, &jug, config);
                }else{
                    printf("\nNo tienes suficientes acciones disponibles\n");
                    fflush(stdin);
                    gets(c);
                }
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 4:     // Soltar objeto
                soltar_objeto(tam_mapa, v_pos, jug, tam_v);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 5:     // Ver objetos cercanos
                ver_objetos_cercanos(tam_v,conectado,tam_obj,tam_mapa,tam_tor, jug, *v_pos, *v_obj, config);
                fflush(stdin);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 6:     // Ver jugadores cercanos
                ver_jugadores_cercanos(tam_v,conectado,tam_obj,tam_mapa,tam_tor, *v_pos, config, v_jugadoresCercanos, jug, *v_jug);
                fflush(stdin);
                puts("Presione enter");
                gets(c);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 7:     // Mostrar posición actual del jugador
                for(i=0;i<*tam_mapa&&buscado==0;i++)
                {
                    if(!strcmp((*v_pos)[i].id_nick,jug->nick)) buscado=i;       // Encontramos su índice en el mapa
                }
                printf("\nEstas en x=%d y=%d\n",(*v_pos)[buscado].coordenada_x, (*v_pos)[buscado].coordenada_y);  // Mostramos su posición
                puts("Presione enter");
                fflush(stdin);
                gets(c);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 8:     // Mostrar posición del ojo de la tormenta
                printf("\nEl ojo de la tormenta esta en x=%d, y=%d y tiene un radio de %d\n", (*v_tor)[config->tormentaActual].coordenada_x,(*v_tor)[config->tormentaActual].coordenada_y,(*v_tor)[config->tormentaActual].radio);
                fflush(stdin);
                puts("Presione enter");
                gets(c);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 9:     // Finalizar el turno
                fin_turno(tam_v, tam_tor, *v_jug, &jug, config);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                break;
            case 10:    // Salir al menu principal
                menu(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                op = 9;
                break;
            case 20:    // Forzamos la salida
                break;
            default:    // Si hemos elegido algo que no es posible
                printf("Eso no es una opción\n");
                fflush(stdin);
                gets(c);
                menu_partida(tam_v,conectado,tam_obj, tam_mapa, tam_tor, v_jug, config, jug, v_obj, v_tor, v_pos, v_jugadoresCercanos);
                op=0;
        }

    }
}
