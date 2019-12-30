#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Carga_Mod.h"
#include "Juego_Mod.h"

//cabecera: int distancia (int x1,int y1,int x2,int y2)
//precondición: x1, y1, x2, y2 enteros con coordenadas de dos puntos, formato: (x1,y1) (x2, y2)
//postcondición: devuelve la distancia entre dos puntos

int distancia (int ,int ,int ,int );

void comenzar_partida(int *tam_v, int* tam_obj, int *tam_pos, tipo_posicion ** v_pos, r_jugador* v_jug, r_objeto * v_obj, r_jugador* jug, r_config* config){

    int i, j, x, y, turno = 1, totJugadores = 0;
    *tam_pos = 0;
    for(i = 0; i < *tam_obj ; i++){     // Recorremos vector v_obj
        if(strcmp(v_obj[i].tipo,"skin")){   // Si no es una skin
            for(j = 0; j < TOTAL_OBJETOS; j++){     // Colocamos TOTAL_OBJETOS de ese objeto
                *tam_pos+=1;
                *v_pos = (tipo_posicion*) realloc (*v_pos, (*tam_pos)*sizeof(tipo_posicion));   // Reasignamos memoria
                do{
                x = rand() % (config->radMap*2);        // Generamos coordenadas aleatorias
                y = rand() % (config->radMap*2);
                } while(distancia(x,y,config->radMap,config->radMap)>= config->radMap);     // Por si acaso se generan fuera del mapa circular
                (*v_pos)[*tam_pos-1].coordenada_x = x;
                (*v_pos)[*tam_pos-1].coordenada_y = y;  // Asignamos las coordenadas aleatorias
                strcpy((*v_pos)[*tam_pos-1].id_nick,v_obj[i].identificador);
                (*v_pos)[*tam_pos-1].tipo = 1;          // 1 = tipo objeto
            }
        }
    }
    // Aqui el primer jugador es el admin que es el que inicia la partida
                totJugadores++;
                strcpy(jug->estado,"EJ");
                *tam_pos+=1;
                *v_pos = (tipo_posicion*) realloc (*v_pos, (*tam_pos)*sizeof(tipo_posicion));
                do{
                x = rand() % (config->radMap*2);        // Generamos coordenadas aleatorias
                y = rand() % (config->radMap*2);
                } while(distancia(x,y,config->radMap,config->radMap)>= config->radMap);     // Por si acaso se generan fuera del mapa circular
                (*v_pos)[*tam_pos-1].coordenada_x = x;
                (*v_pos)[*tam_pos-1].coordenada_y = y;

                strcpy((*v_pos)[*tam_pos-1].id_nick,jug->nick);
                (*v_pos)[*tam_pos-1].tipo = 0;
                jug->posTurno = turno;          // Le asignamos su turno
                turno++;
                jug->seleccionado = 0;          // Selecciona su cuchillo
                jug->acciones = config->maxAccPTurno;
                jug->partJugadas += 1;
                jug->vida = 100;
    for(i = 0; i < *tam_v ; i++){
        if(!strcmp(v_jug[i].estado,"EE")){  // Todos los jugadores que están en Espera
                totJugadores++;
                strcpy(v_jug[i].estado,"EJ");   // Ahora en Juego
                *tam_pos+=1;
                *v_pos = (tipo_posicion*) realloc (*v_pos, (*tam_pos)*sizeof(tipo_posicion));
                do{
                x = rand() % (config->radMap*2);        // Generamos coordenadas aleatorias
                y = rand() % (config->radMap*2);
                } while(distancia(x,y,config->radMap,config->radMap)>= config->radMap);     // Por si acaso se generan fuera del mapa circular
                (*v_pos)[*tam_pos-1].coordenada_x = x;
                (*v_pos)[*tam_pos-1].coordenada_y = y;
                strcpy((*v_pos)[*tam_pos-1].id_nick,v_jug[i].nick);
                (*v_pos)[*tam_pos-1].tipo = 0;
                v_jug[i].posTurno = turno;          // Le asignamos su turno
                turno++;
                v_jug[i].seleccionado = 0;          // Selecciona su cuchillo
                v_jug[i].acciones = config->maxAccPTurno;
                v_jug[i].partJugadas += 1;          // Sumamos 1 al total de partidas jugadas
                v_jug[i].vida = 100;        // Vida al completo
        }
    }



    config->tormentaActual = 0;     // primera fase de la tormenta
    config->turnoActual = 1;        // Contador total de turnos
    config->numJugadoresPartida = totJugadores;     // Numero total de jugadores
}

int distancia (int x1,int y1,int x2,int y2){
    return(sqrt(pow(x1-x2,2)+pow(y1-y2,2)));    // Teorema de Pitágoras
}

void eliminar_objeto_mapa(int i,int* tam_mapa, tipo_posicion* v_pos){
    int j;
    for(j = i; j < *tam_mapa-1; j++){   // A partir de i
        v_pos[j] = v_pos[j+1];   // Asignamos a cada elemento, el valor del siguiente
    }

}

void fin_juego(int* tam_v, int *tam_obj, r_jugador* v_jug, r_jugador** jug, r_objeto* v_obj){
    int i, j = 0, h = 0, hAux = 0;
    char c[TAM_RED];
    for (i = 0; i < *tam_v;i++){  // Recorremos v_jug
        if(!strcmp(v_jug[i].estado,"GO") || !strcmp(v_jug[i].estado,"EJ")){     // Si está en juego o muerto
            for(j = 0; j< v_jug[i].tamMochila;j++){
                for(h = 0; h < *tam_obj; h++){
                    if(!strcmp(v_jug[i].v_mochila[j].id, v_obj[h].identificador)){  // Buscamos el elemento de la mochila en v_obj
                        hAux = h;
                        h = *tam_obj;
                    }
                }
                if(!strcmp(v_obj[hAux].tipo,"arma") && strcmp(v_obj[hAux].identificador,"CUCH")) {  // Vemos si es un arma, en tal caso se elimina de la mochila el objeto
                        quitar_objeto_mochila(j, &v_jug[i]);
                        (*jug)->tamMochila -= 1;
                        (*jug)->v_mochila = (r_mochila*) realloc ((*jug)->v_mochila, ((*jug)->tamMochila)*(sizeof(r_mochila)));
                }
            }
        }
        if(!strcmp(v_jug[i].estado,"EJ")){  // Si está en juego, es el único que queda en juego
            system("cls");
            puts("              VICTORIA MAGISTRAL");
            printf("\n\n Enhorabuena %s, has ganado la partida!\n Pulsa enter para volver al menu principal\n", v_jug[i].nick);
            v_jug[i].partGanadas += 1;  // Sumamos 1 al contador de partidas ganadas
            v_jug[i].dinero += 100;     // Se le da 100 monedas más
            fflush(stdin);
            gets(c);
            strcpy(v_jug[i].estado, "ON");  // Pasa a estar en linea
            *jug = &v_jug[i];


        }else if(!strcmp(v_jug[i].estado,"GO")){
            strcpy(v_jug[i].estado,"OFF");      // Desconectamos los demás jugadores
        }
    }
}

void fin_turno(int *tam_v, int *tam_tor, r_jugador* v_jug, r_jugador** jug, r_config* config){
    int i, turno = (*jug)->posTurno+1, encontrado = 0;
    i = 0;
    while(i < *tam_v || encontrado == 0){           // Recorremos v_jug para ver de quién es el turno
        if(v_jug[i].posTurno == turno && !strcmp(v_jug[i].estado,"EJ")){    // Si es su turno y está en juego
            (*jug)->acciones = config->maxAccPTurno;   // Reiniciamos las acciones totales del jugador anterior
            config->turnoActual = turno;            // Indicamos en config el turno actual
            *jug = &v_jug[i];
            (*jug)->seleccionado = 0;                  // Reiniciamos jug, dandole el valor del jugador seleccionado
            (*jug)->acciones = config->maxAccPTurno;   // Reiniciamos las acciones totales
            i = *tam_v;
            encontrado = 1;
        }
        if(i > *tam_v){                             // Si hemos dado una vuelta
            i = 0;
            turno++;                                // Le toca al siguiente jugador
        }
        if(turno > config->numJugadoresPartida){    // Si ya han jugado todos una ronda
            turno = 1;
            if(config->tormentaActual < *tam_tor-1) config->tormentaActual++;   // Avanza la tormenta
        }
        i++;
    }

}

int fuera_tormenta(int* tam_v, int* tam_mapa, tipo_estadotormenta* v_tor, r_config* config, tipo_posicion** v_pos, r_jugador* v_jug, r_objeto *v_obj, int *tam_obj){
    int x, y, i, j, jaux = 0, res = 0;
    x = v_tor[config->tormentaActual].coordenada_x;
    y = v_tor[config->tormentaActual].coordenada_y;     // Coordenadas de la tormenta

    for(i = 0; i < *tam_mapa; i++){
        if(distancia(x, y, (*v_pos)[i].coordenada_x, (*v_pos)[i].coordenada_y) > v_tor[config->tormentaActual].radio && (*v_pos)[i].tipo == 0) {    // Si el jugador está fuera de la tormenta
                for(j = 0; j < *tam_v; j++){
                    if(!strcmp((*v_pos)[i].id_nick,v_jug[j].nick)){     // Buscamos el jugador en v_pos
                        jaux = j;
                        j = *tam_v;
                    }
                }
                muere(tam_mapa, jaux, v_pos, v_jug, v_obj, tam_obj);    // Muere dicho jugador
                res = 1;
        }
    }
    return res;
}

void movimiento(int* tam_mapa, tipo_posicion* v_pos, r_jugador* jug, r_config* config){
    int op=0,j=0,jugador=-1;

    puts("");
    puts("1 .- Hacia el Norte (Aumenta la y)");         // Mostramos posibles movimientos
    puts("2 .- Hacia el Sur (Disminuye la y)");
    puts("3 .- Hacia el Este (Aumenta la x)");
    puts("4 .- Hacia el Oeste (Disminuye la x)");

    do{
        printf("¿Hacia donde te quieres mover?\n");
        scanf("%i",&op);
    }while(op<1||op>4);
    while(j<*tam_mapa&&jugador==-1)
    {
        if(!strcmp(v_pos[j].id_nick,jug->nick)) jugador=j;      // Buscamos al jugador en el mapa
        j++;
    }
    switch(op)
    {
    case 1:
        v_pos[jugador].coordenada_y += config->disPMov;     // Dependiendo de la opción elegida, aumentaremos o disminuiremos su 'x' o 'y'
        break;
    case 2:
        v_pos[jugador].coordenada_y-= config->disPMov;
        break;
    case 3:
        v_pos[jugador].coordenada_x+= config->disPMov;
        break;
    case 4:
        v_pos[jugador].coordenada_x-= config->disPMov;
        break;
    default:
        printf("\nError");
        break;
    }
}

void muere(int* tam_mapa ,int i, tipo_posicion** v_pos, r_jugador* v_jug, r_objeto *v_obj, int *tam_obj){
    int j,h, jaux = 0, hAux = 0;
    for(j = 0; j < *tam_mapa; j++){     // Recorremos el vector v_pos en busca del jugador en el mapa
        if(!strcmp(v_jug[i].nick,(*v_pos)[j].id_nick)){
            jaux= j;                    // Obtenemos su índice en el mapa
            j = *tam_mapa;
        }
    }
    v_jug[i].vida = 100;            // Reiniciamos su vida

    for (j = 0; j < v_jug[i].tamMochila; j++){  // Soltamos toda la mochila en el suelo
        for(h = 0; h < *tam_obj; h++){      // Buscamos cada objeto en el v_obj
            if(!strcmp(v_obj[h].identificador,v_jug[i].v_mochila[j].id)){
               hAux = h;
               h =*tam_obj+1;
               }
        }

        if(h != *tam_obj){      // Si existe en v_obj
                if(strcmp(v_obj[hAux].tipo,"skin") && strcmp(v_jug[i].v_mochila[j].id,"CUCH")){     // Los soltamos
                    *tam_mapa += 1;
                    *v_pos = (tipo_posicion*) realloc (*v_pos, (*tam_mapa) * sizeof(tipo_posicion));       // Reasignamos espacio a v_pos
                    (*v_pos)[*tam_mapa-1].coordenada_x = (*v_pos)[jaux].coordenada_x;
                    (*v_pos)[*tam_mapa-1].coordenada_y = (*v_pos)[jaux].coordenada_y;
                    strcpy((*v_pos)[*tam_mapa-1].id_nick, v_jug[i].v_mochila[j].id);    // El id del arma a soltar
                    (*v_pos)[*tam_mapa-1].tipo = 1;         // Es objeto
                }
        }
        if(!strcmp(v_obj[hAux].tipo,"arma") && strcmp(v_obj[hAux].identificador,"CUCH")) {  // Vemos si es un arma, en tal caso se elimina de la mochila el objeto
                        quitar_objeto_mochila(j, &v_jug[i]);
                        v_jug[i].tamMochila -= 1;
                        v_jug[i].v_mochila = (r_mochila*) realloc (v_jug[i].v_mochila, (v_jug[i].tamMochila)*(sizeof(r_mochila)));
        }

    }




    strcpy(v_jug[i].estado,"GO");       // Cambiamos su estado a muerto

    eliminar_objeto_mapa(jaux, tam_mapa, *v_pos);   // Eliminamos al jugador del mapa
    *tam_mapa -= 1;
    *v_pos = (tipo_posicion*) realloc (*v_pos, (*tam_mapa) * sizeof(tipo_posicion));       // Reasignamos espacio a v_pos
}

void quitar_objeto_mochila(int iObjeto, r_jugador* jug){
    int i;
    for(i = iObjeto; i< jug->tamMochila-1; i++){    // Recorremos la mochila desde iObjeto moviendo todo elemento un lugar a la izquierda
        jug->v_mochila[i]=jug->v_mochila[i+1];
    }

}

void soltar_objeto(int* tam_mapa, tipo_posicion ** v_pos, r_jugador* jug, int * tam_v){
    int i, n;
    imprimir_mochila(jug);      // Mostramos la mochila del jugador
    puts("0 .- Salir");
    do{
        puts("Que objeto deseas soltar?");
        fflush(stdin);
        scanf("%i", &n);        // Elige el elemento
    }while(n<0 || n>jug->tamMochila);
    if(n!=0 && n != 1){
        n--;                    // n es el indice del objeto a tirar en la mochila

        *tam_mapa += 1;
        *v_pos = (tipo_posicion*) realloc (*v_pos, (*tam_mapa)*sizeof(tipo_posicion));    // Reasignamos el tamaño del mapa

        for(i = 0; i < *tam_mapa; i++){
            if(!strcmp(jug->nick, (*v_pos)[i].id_nick)){    // Buscamos el jugador en el mapa, en el momento en el que lo encontramos copaimos los nuevos datos en el mapa
                strcpy((*v_pos)[*tam_mapa-1].id_nick, jug->v_mochila[n].id);
                (*v_pos)[*tam_mapa-1].tipo = 1;
                (*v_pos)[*tam_mapa-1].coordenada_x = (*v_pos)[i].coordenada_x;
                (*v_pos)[*tam_mapa-1].coordenada_y = (*v_pos)[i].coordenada_y;
            }
        }

        quitar_objeto_mochila(n,jug);           // Quitamos el objeto de la mochila
        jug->tamMochila -= 1;
        jug->v_mochila = (r_mochila*) realloc (jug->v_mochila, (jug->tamMochila)*(sizeof(r_mochila)));   // Reasignamos el tamaño de la mochila
        jug->seleccionado = 0;

    }
}

void usar_objeto(int* tam_v, int conectado, int* tam_obj,int* tam_mapa, int *tam_tor, r_jugador* jug, r_objeto* v_obj, tipo_posicion ** v_pos, tipo_posicion** v_jugadoresCercanos, r_config * config, r_jugador* v_jug){
int k, iaux = 0, jugador = 0;
char c[TAM_RED];
    for(k=0;k<*tam_obj;k++)
    {
        if(!strcmp(jug->v_mochila[jug->seleccionado].id,v_obj[k].identificador))
        {
            iaux = k;               // Buscamos el indice del objeto seleccionado de la mochila en el vector de objetos
            k = *tam_obj;
        }
    }
    for(k=0;k<*tam_mapa;k++)
    {
        if(!strcmp(jug->nick,(*v_pos)[k].id_nick))
        {
            jugador = k;               // Buscamos el indice del jugador en el vector de mapa
            k = *tam_mapa;
        }
    }
    if(!strcmp(v_obj[iaux].tipo, "accesorio")&&jug->v_mochila[jug->seleccionado].unidades>0){   // Si es un accesorio y tiene alguna unidad
        jug->v_mochila[jug->seleccionado].unidades-=1;      // Lo usa
        jug->acciones -= 1;
        if(!strcmp(v_obj[iaux].nombre,"Pocima")){           // La pocima aumenta escudo
            jug->escudo += v_obj[iaux].dano;
            if (jug->escudo > 100) jug->escudo = 100;
        }
        else if(!strcmp(v_obj[iaux].nombre,"Botiquin")){    // Botiquin pone la vida al 100
            jug->vida = 100;
        }
        else if(!strcmp(v_obj[iaux].nombre,"Venda")){       // La venda restaura un porcentaje de la vida
            jug->vida += v_obj[iaux].dano;
            if (jug->vida > 100) jug->vida = 100;
        }else{                                              // Si es otro acceosrio nuevo, curará vida
            jug->vida += v_obj[iaux].dano;
            if (jug->vida > 100) jug->vida = 100;
        }
        if(jug->v_mochila[jug->seleccionado].unidades <= 0) {
                quitar_objeto_mochila(jug->seleccionado, jug);
                jug->tamMochila -= 1;
                jug->v_mochila = (r_mochila*) realloc (jug->v_mochila, jug->tamMochila * sizeof(r_mochila));
                jug->seleccionado = 0;
        }
    } else if(!strcmp(v_obj[iaux].tipo, "arma")){           // Si es un arma, mostraremos el menú de opciones
        int n, enemigoSeleccionado = 0, i;
        int totJug = ver_jugadores_cercanos(tam_v,conectado,tam_obj,tam_mapa,tam_tor, *v_pos, config, v_jugadoresCercanos,jug, v_jug); // Mostramos todos los jugadores cercanos y cargamos v_jugadorescercanos
        printf("0 .- Salir\n");
        do{
            puts("A cual deseas atacar?\n");        // Tras mostrar los jugadores a los que se puede disparar, solicitamos que seleccione a alguno de ellos
            scanf("%i",&n);
        }while(n < 0 || n > totJug);
        printf("%i - %i\n", n, distancia((*v_pos)[jugador].coordenada_x,(*v_pos)[jugador].coordenada_y,(*v_jugadoresCercanos)[n-1].coordenada_x, (*v_jugadoresCercanos)[n-1].coordenada_y));
        if(n != 0 && distancia((*v_pos)[jugador].coordenada_x,(*v_pos)[jugador].coordenada_y,(*v_jugadoresCercanos)[n-1].coordenada_x, (*v_jugadoresCercanos)[n-1].coordenada_y)>v_obj[iaux].alcance){
                    // Si no tiene alcance suficiente, no le puede dar
            puts("El arma no tiene alcance suficiente");
            puts("Presiona enter");
            fflush(stdin);
            gets(c);


        }else if(n != 0 &&(!strcmp(jug->v_mochila[jug->seleccionado].id,"CUCH")|| jug->v_mochila[jug->seleccionado].unidades>0)){   // Si es el cuchillo o tiene balas suficientes, procedemos a atacar
            jug->acciones -= 1;
            if(strcmp(jug->v_mochila[jug->seleccionado].id,"CUCH")) jug->v_mochila[jug->seleccionado].unidades -= 1; // Si no es el cuchillo quitamos una bala
            n--;
            for(i = 0; i < *tam_v; i++){        // Buscamos el jugador en el vector de jugadores
                if(!strcmp((*v_jugadoresCercanos)[n].id_nick, v_jug[i].nick)){
                    enemigoSeleccionado = i;        // Seleccionamos el jugador
                    i = *tam_v;
                }
            }
            if(v_jug[enemigoSeleccionado].escudo>0){        // Si tiene escudo primero se lo quitamos
                v_jug[enemigoSeleccionado].escudo -= v_obj[iaux].dano;
                if(v_jug[enemigoSeleccionado].escudo < 0){      // Si ha perdido todo el escudo empezamos a quitar a la vida
                    v_jug[enemigoSeleccionado].vida += v_jug[enemigoSeleccionado].escudo;
                    v_jug[enemigoSeleccionado].escudo = 0;
                }
            }else {
                v_jug[enemigoSeleccionado].vida -= v_obj[iaux].dano;
            }
            if(v_jug[enemigoSeleccionado].vida <= 0) {
                printf("\n Ha muerto %s\n", v_jug[enemigoSeleccionado].nick);
                fflush(stdin);
                gets(c);
                muere(tam_mapa, enemigoSeleccionado, v_pos, v_jug, v_obj,tam_obj);
            }
        }
    } else if(!strcmp(v_obj[iaux].tipo,"skin")){        // Si intenta atacar con la skin seleccionada, no lo dejamos actuar
        printf("\n No tienes nada que hacer con la skin\n");
    } else{
        printf("\n Estas usando un objeto que ya es inexistente en el juego, debes tirarlo al suelo\n");
    }

}

int ver_jugadores_cercanos(int* tam_v, int conectado, int* tam_obj,int* tam_mapa,int* tam_tor, tipo_posicion* v_pos, r_config* config, tipo_posicion ** v_jugadoresCercanos, r_jugador *jug, r_jugador * v_jug){
    int i, iAux = 0, totJug = 0 , k;
    i = 0;
    while(i<*tam_mapa&&iAux==0)
    {
        if(!strcmp(v_pos[i].id_nick,jug->nick)) iAux=i;     // Buscamos al propio jugador en el mapa
        i++;
    }

    for(i=0;i<*tam_mapa;i++)    // Recorremos el vector mapa
    {
        if(v_pos[i].tipo==0 && distancia(v_pos[i].coordenada_x,v_pos[i].coordenada_y,v_pos[iAux].coordenada_x,v_pos[iAux].coordenada_y)<=config->disMaxAt) // Si es un jugador y está a la vista
        {
            for(k=0;k<*tam_v;k++)   // Recorremos el vector de jugadores
            {
                if(!strcmp(v_pos[i].id_nick,v_jug[k].nick) && strcmp(v_jug[k].nick,jug->nick))  // Si coincide el jugador con el elemento del mapa, y no es nuestro jugador
                {
                        totJug++;
                        printf("%i .-  %s  (x=%i ,y=%i) se encuentra a %i de distancia\n",totJug, v_jug[k].nick, v_pos[i].coordenada_x,v_pos[i].coordenada_y,distancia(v_pos[i].coordenada_x,v_pos[i].coordenada_y,v_pos[iAux].coordenada_x,v_pos[iAux].coordenada_y));
                        *v_jugadoresCercanos = (tipo_posicion*) realloc(*v_jugadoresCercanos, totJug * sizeof(tipo_posicion));  // Mostramos las posiciones y nombre de los jugadore cercanos
                        k = *tam_v;                                                                                             // Además, cargamos progresivamente v_jugadoresCercanos
                        (*v_jugadoresCercanos)[totJug-1] = v_pos[i];

                }
            }
        }
    }
    if(totJug == 0) printf("\nNo hay jugadores cercanos\n");
    return totJug;      // Devolvemos el total de jugadores cercanos
}

void ver_objetos_cercanos(int* tam_v, int conectado, int* tam_obj,int* tam_mapa,int* tam_tor, r_jugador* jug, tipo_posicion* v_pos, r_objeto* v_obj, r_config* config){
    int i, j, k, iAux = 0, totObj = 0, n;
    tipo_posicion *v_objetosCercanos;
    char c[TAM_RED];
    i = 0;
    while(i<*tam_mapa&&iAux==0)
    {
        if(strcmp(v_pos[i].id_nick,jug->nick)==0) {     // Buscamos el jugador en el vector mapa
                iAux=i;     // indice jugador
                i = *tam_mapa;
        }
        i++;
    }

    for(i=0;i<*tam_mapa;i++)    // Recorremos el vector mapa
    {
        if(v_pos[i].tipo==1 && distancia(v_pos[i].coordenada_x,v_pos[i].coordenada_y,v_pos[iAux].coordenada_x,v_pos[iAux].coordenada_y)<=config->disMinObj)
        {                               // Si es un objeto y está cerca
            for(k=0;k<*tam_obj;k++)     // Recorremos vector objeto
            {
                if(!strcmp(v_pos[i].id_nick,v_obj[k].identificador))    // Si coincide el nick del objeto con el del mapa
                {
                    if(totObj == 0){
                        v_objetosCercanos = (tipo_posicion*) malloc (sizeof(tipo_posicion));
                        totObj++;
                        printf("%i .- Tienes cerca un/una %s\n",totObj, v_obj[k].nombre);
                    }else{              // Vamos cargando el vector de objetosCercanos y mostrando en pantalla cuáles son
                        totObj++;
                        v_objetosCercanos = (tipo_posicion*) realloc(v_objetosCercanos, totObj * sizeof(tipo_posicion));
                        printf("%i .- Tienes cerca un/una %s\n",totObj, v_obj[k].nombre);
                        k = *tam_obj;

                    }   // Cargamos los objetos en el vector v_objetosCercanos

                    v_objetosCercanos[totObj-1] = v_pos[i];
                }
            }
        }
    }
    puts("Deseas coger un elemento?");
    puts("1 .- Si");
    puts("2 .- No, salir");
    scanf("%i", &n);
    if(n == 1  && totObj >= 1 && jug->acciones > 0){   // Si hemos querido cogerlo y tenemos espacio en la mochila
        jug->acciones -= 1;
        do{
            puts("Cual de ellos?");
            fflush(stdin);
            scanf("%i", &n);
        }while(n < 1 || n > totObj);    // Cual cogemos

        i = n-1;    // i es el objeto de v_objetosCercanos elegido
        j = 0;
        while(j < *tam_obj && strcmp(v_objetosCercanos[i].id_nick, v_obj[j].identificador)) {   // Mientras que sea menor que *tam_obj y diferentes los nick
                j++;
        }   // Al final j tendrá el índice del vector v_obj

        int existe = 0,h;

        for(k = 0; k < jug->tamMochila; k++){
            if(!strcmp(jug->v_mochila[k].id,v_objetosCercanos[i].id_nick)){ // Vemos si existe dicho objeto en nuestra mochila
                existe = 1;
                h = k;      // h índice de la mochila
                k = jug->tamMochila;
            }
        }
        if(existe == 1){    // Si ya existe en la mochila
            if(!strcmp(v_obj[j].tipo,"accesorio")){
                    jug->v_mochila[h].unidades += 2;                                    // Si es un accesorio le sumamos el numero de unidades
                    if (jug->v_mochila[h].unidades>2) jug->v_mochila[h].unidades = 2;   // 2 Como máximo
            }
            else if(strcmp(v_objetosCercanos[i].id_nick,"CUCH"))jug->v_mochila[h].unidades += UD_MUNICION; // Si no es el cuchillo aumentamos la municion
            for(k = 0; k < *tam_mapa; k++){
                if(!strcmp(v_objetosCercanos[n].id_nick,v_pos[k].id_nick)){             // Eliminamos del mapa el objeto que hemos cogido
                    eliminar_objeto_mapa(k, tam_mapa, v_pos);
                    *tam_mapa -= 1;
                    v_pos = (tipo_posicion*) realloc (v_pos, (*tam_mapa) * sizeof(tipo_posicion));
                    k = *tam_mapa;
                }
            }

        }

        else if(existe == 0 && !strcmp(v_objetosCercanos[i].id_nick, v_obj[j].identificador )&& jug->tamMochila < config->maxSpMoch){   // Si el objeto no existía en la mochila, metemos u nuevo elemento en la mochila del jugador
            jug->tamMochila += 1;
            jug->v_mochila = (r_mochila*) realloc (jug->v_mochila,jug->tamMochila * sizeof(r_mochila));
            if(!strcmp(v_obj[j].tipo,"accesorio")){
                    jug->v_mochila[jug->tamMochila-1].unidades = 2;                                    // Si es un accesorio le sumamos el numero de unidades
            }else{
            jug->v_mochila[jug->tamMochila-1].unidades = UD_MUNICION;
            }
            strcpy(jug->v_mochila[jug->tamMochila-1].id, v_obj[j].identificador);
        }else{      // En caso de que no exista en objetos, no lo introducimos
            puts("No existe dicho objeto");
            gets(c);
        }

        for(k = 0; k < *tam_mapa; k++){     // Recorremos el vector del mapa
            if(!strcmp(v_pos[k].id_nick,v_objetosCercanos[i].id_nick)&&v_pos[k].coordenada_x==v_objetosCercanos[i].coordenada_x) // Si es el mismo
            {
                eliminar_objeto_mapa(k, tam_mapa, v_pos);       // Eliminamos el objeto del mapa
                *tam_mapa -= 1;
                v_pos = (tipo_posicion*) realloc (v_pos, (*tam_mapa)*sizeof(tipo_posicion));
            }
        }
    }else if(jug->tamMochila >= config->maxSpMoch && n == 1){  // En caso de que no tuviese espacio
        puts("No tienes suficiente espacio en la mochila");
        gets(c);
    } else if(n == 1 && jug->acciones <= 0) puts("No tienes acciones suficientes");
}
