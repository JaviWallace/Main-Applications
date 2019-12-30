#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Carga_Mod.h"


void imprimir_jugador(r_jugador jug){
    int j;

    puts("Estos son todos tus datos");
    printf("Jugador: %s \n", jug.nick);
    printf("Nombre: %s\n", jug.nombre);
    printf("Nivel: %i\n", jug.nivel);
    printf("Vida: %i\n", jug.vida);
    printf("Escudo: %i\n", jug.escudo);
    printf("Estado: %s\n", jug.estado);
    printf("Dinero: %i\n", jug.dinero);
    printf("Partidas jugadas: %i\n", jug.partJugadas);
    printf("Partidas ganadas: %i\n", jug.partGanadas);
    printf("Tipo de usuario: %s\n", jug.tipoUsuario);
    printf("Contrasena: %s\n", jug.pass);
    printf("Tamano mochila: %i\n", jug.tamMochila);
    for(j = 0; j < jug.tamMochila;j++){                     /* Por cada elemento de su mochila */
        printf("ID: %s\n",jug.v_mochila[j].id);
        printf("Unidades/Municion: %i\n", jug.v_mochila[j].unidades);
    }
    puts("");
}

void guardar_jugador(r_jugador* v_jug, int totJugadores){
     int i;
    FILE *jugador;
    jugador = fopen(JUGADORES,"w");
    if(jugador!= NULL){

        for(i = 0; i < totJugadores;i++){     /* Por cada jugador */
            fprintf(jugador,"%s/%s/%i/%i/%i/%s/%i/%i/%i/%s/%s/%i/%i\n",
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
                    v_jug[i].pass,
                    v_jug[i].posTurno,
                    v_jug[i].acciones);
            }
        fclose(jugador);
    }else{
        puts("Error al cargar el archivo en modo escritura Jugadores.txt");

    }
}

void guardar_mochila(r_jugador *v_jug, int totJugadores){
    int i, j;
    FILE *mochila;
    mochila = fopen(MOCHILA,"w");
    if(mochila!= NULL){
        for(i = 0; i < totJugadores;i++){     /* Por cada jugador */
            for(j = 0; j < v_jug[i].tamMochila; j++){      /* Por cada elemento de su mochila */
                fprintf(mochila,"%s/%s/%i\n",v_jug[i].nick,
                        v_jug[i].v_mochila[j].id,
                        v_jug[i].v_mochila[j].unidades);
            }
        }
        fclose(mochila);
    }else{
        puts("Error al cargar el archivo en modo escritura Mochila.txt");

    }
}

void cargar_jugador(r_jugador* v_jug, int tam_v){
    FILE * jugador;
    jugador = fopen(JUGADORES,"r");
    char c, num[TAM_RED];
    int i, j;
    for(i = 0; i < tam_v; i++)
    {
        Sleep(10);
        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el nick */
        {
            v_jug[i].nick[j] = c;
            j++;
        }
        v_jug[i].nick[j] = '\0';

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el nombre */
        {
            v_jug[i].nombre[j] = c;
            j++;
        }
        v_jug[i].nombre[j] = '\0';

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el nivel */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].nivel = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos la vida */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].vida = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el escudo */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].escudo = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el estado */
        {
            v_jug[i].estado[j] = c;
            j++;
        }
        v_jug[i].estado[j] = '\0';

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el dinero */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].dinero = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el numero de partidas jugadas */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].partJugadas = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos numero de partidas ganadas */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].partGanadas = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos el tipo de usuario */
        {
            v_jug[i].tipoUsuario[j] = c;
            j++;
        }
        v_jug[i].tipoUsuario[j] = '\0';

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos la contraseña */
        {
            v_jug[i].pass[j] = c;
            j++;
        }
        v_jug[i].pass[j] = '\0';

        j = 0;
        while((c=fgetc(jugador))!= '/')     /* Cargamos la posicion del turno */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].posTurno = atoi(num);

        j = 0;
        while((c=fgetc(jugador))!= '\n')     /* Cargamos numero de acciones */
        {
            num[j] = c;
            j++;
        }
        num[j] = '\0';
        v_jug[i].acciones = atoi(num);


        v_jug[i].tamMochila = numero_filas_mochila_de_jugador(v_jug[i].nick);        /* Cargamos el tamaño de la mochila */

    }
}

void cargar_mochila(r_mochila * v_mochila, int tam_v, char nick[]){
    int totFilas = numero_filas(MOCHILA);
    int i, j, totAnadido = 0;
    char c, auxNick[TAM], num[TAM_RED];
    FILE *mochila;
    mochila = fopen(MOCHILA,"r");
    if(mochila != NULL)
    {
        for(i = 0; i < totFilas; i++){
            j = 0;
            while ((c=fgetc(mochila))!= '/'){           /* Cargamos el nick del elemento */
                auxNick[j] = c;
                j++;
            }
            auxNick[j] = '\0';

            if(!strcmp(auxNick,nick)){                  /* Si coincide con nuestro nick, empezamos a cargarlo en mochila*/
                j = 0;
                while((c=fgetc(mochila))!= '/')         /* Cargamos el id del objeto*/
                {
                    v_mochila[totAnadido].id[j] = c;
                    j++;
                }
                v_mochila[totAnadido].id[j] = '\0';

                j = 0;
                while((c=fgetc(mochila))!= '\n')        /* Cargamos el total de unidades*/
                {
                    num[j] = c;
                    j++;
                }
                num[j] = '\0';
                v_mochila[totAnadido].unidades = atoi(num);
                totAnadido++;
            }else{
                while((c=fgetc(mochila))!= '\n');       /* Nos saltamos la linea si no coincide*/
            }
        }
        if(totAnadido != tam_v)printf("Error al cargar los datos de %s\n", nick);  /* Si ha habido un error de carga lo avisamos*/
        fclose(mochila);
    }
}

int numero_filas_mochila_de_jugador(char nick[]){
    int totFilas = numero_filas(MOCHILA), i, j, totMochila = 0;
    char c, straux[TAM];
    FILE * mochila;
    mochila = fopen(MOCHILA, "r");
    if(mochila!=NULL)
    {
        for(i = 0; i < totFilas; i++)
        {
            j = 0;

            while((c=fgetc(mochila))!= '/')         /* Cargamso primero el nombre del jugador de cada linea en straux*/
            {
                straux[j] = c;
                j++;
            }
            straux[j] = '\0';
            if(!strcmp(straux,nick))                /* Si coincide con el nick, sumamos una fila mas a su total*/
                totMochila++;

            while((c=fgetc(mochila))!= '\n');       /* Pasamos a la siguiente fila*/
        }
        fclose(mochila);
    }
    return totMochila;
}

int numero_filas(char nombre[]){
    FILE * farchivo;
    farchivo = fopen(nombre,"r");
    char c;
    int tot = 0;
    if(farchivo!= NULL)
    {
        while((c=fgetc(farchivo)) != EOF )      /* Mientras no llegue el final del archivo */
        {
            if (c == '\n')                      /* Cada salto de linea es una fila nueva*/
                tot++;
        }
        fclose(farchivo);
    }
    return tot;
}

void cargaConfig(r_config *config){
	FILE *f;
	if((f=fopen(CONFIGURACION,"r"))!=NULL)	// Aquí abrimos el fichero "configuracion.txt" y procedemos a cargar sus campos en el mismo orden que ha sido establecido en la definición de estructura en el ".h"
	{
		fscanf(f,"%i/%i/%i/%i/%i/%i/%i/%i/%i/%i/%i/%i",&config->radMap,&config->disMinObj,&config->disMaxAt,&config->defMon,&config->minJug,&config->disPMov,&config->maxSpMoch,&config->minPartPNiv,&config->maxAccPTurno,&config->turnoActual,&config->tormentaActual,&config->numJugadoresPartida);
	}
	else
	{
		puts("Error de apertura de fichero \"Configuracion.txt\"");
	}
	fclose(f);
}

void guardaConfig(r_config config){
	FILE *f;
	if((f=fopen(CONFIGURACION,"w"))!=NULL)	// Aquí abrimos el fichero "configuracion.txt" y procedemos a cargar sus campos en el mismo orden que ha sido establecido en la definición de estructura en el ".h"
	{
		fprintf(f,"%i/%i/%i/%i/%i/%i/%i/%i/%i/%i/%i/%i",config.radMap,config.disMinObj,config.disMaxAt,config.defMon,config.minJug,config.disPMov,config.maxSpMoch,config.minPartPNiv,config.maxAccPTurno,config.turnoActual,config.tormentaActual,config.numJugadoresPartida);
	}
	else
	{
		puts("Error de creacion de fichero \"Configuracion.txt\"");
	}
	fclose(f);
}

void cargar_objetos(r_objeto *v_obj, int tam_v){
    FILE *objetos;
    int i, j;
    char c, num[TAM_RED];
    if((objetos=fopen(OBJETOS,"r"))!=NULL){
        for(i = 0; i < tam_v; i++){

            Sleep(10);
            j = 0;
            while((c=fgetc(objetos))!= '/')     /* Cargamos el nick */
            {
                v_obj[i].identificador[j] = c;
                j++;
            }
            v_obj[i].identificador[j] = '\0';
            j = 0;
            while((c=fgetc(objetos))!= '/')     /* Cargamos el nombre */
            {
                v_obj[i].nombre[j] = c;
                j++;
            }
            v_obj[i].nombre[j] = '\0';
            j = 0;
            while((c=fgetc(objetos))!= '/')     /* Cargamos el tipo */
            {
                v_obj[i].tipo[j] = c;
                j++;
            }
            v_obj[i].tipo[j] = '\0';

            j = 0;
            while((c=fgetc(objetos))!= '/')     /* Cargamos el numero de partidas jugadas */
            {
                num[j] = c;
                j++;
            }
            num[j] = '\0';
            v_obj[i].coste = atoi(num);

            j = 0;
            while((c=fgetc(objetos))!= '/')     /* Cargamos el numero de partidas jugadas */
            {
                num[j] = c;
                j++;
            }
            num[j] = '\0';
            v_obj[i].alcance = atoi(num);

            j = 0;
            while((c=fgetc(objetos))!= '\n')     /* Cargamos el numero de partidas jugadas */
            {
                num[j] = c;
                j++;
            }
            num[j] = '\0';
            v_obj[i].dano = atoi(num);
        }
    }else{
        puts("No se ha conseguido abrir el fichero \"Objetos.txt\"");
    }
}

void guardar_objetos(r_objeto *v_obj, int tam_v){
    int i;
    FILE *objetos;

    if((objetos = fopen(OBJETOS, "w"))!=NULL){
        for(i = 0; i < tam_v; i++){
            fprintf(objetos,"%s/%s/%s/%i/%i/%i\n", v_obj[i].identificador,
                    v_obj[i].nombre,
                    v_obj[i].tipo,
                    v_obj[i].coste,
                    v_obj[i].alcance,
                    v_obj[i].dano);
        }
    }else{
        puts("Error al abrir el fichero \"Objetos.txt\"");
    }

}

void cargar_mapa(tipo_posicion *v, int N){
    int i,k,h=0;
    FILE * mapa;
    char aux[TAM],num[TAM];
    mapa=fopen(MAPA,"r");
    if((mapa)==NULL) printf("Error de apertura del fichero mapa.txt");
    else if(N > 1){
    for(i=0;i<N;i++) //Recorremos todos los elementos
    {
        fflush(stdin);
        fflush(mapa);

        fgets(aux,TAM,mapa); //Volcamos en la cadena auxiliar todo el fichero

        k=0;
        while(aux[k]!='/') //Volcamos el campo id_ nick en la estructura
        {
            v[i].id_nick[h]=aux[k];
            h++;
            k++;
        }

        v[i].id_nick[h]='\0';

        h=0;
        k++;

        fseek(mapa,1,SEEK_CUR);
        fseek(mapa,-1,SEEK_CUR);

        fflush(stdin);
        fflush(mapa);

        while(aux[k]!='/')//Volcamos el campo tipo en la estructura
        {
            num[h]=aux[k];
            h++;
            k++;
        }

        num[h]='\0';

        v[i].tipo=atoi(num);
        h=0;
        k++;

        fflush(stdin);
        fflush(mapa);

        while(aux[k]!='/') //Volcamos el campo coordenada_x en la estructura
        {
            num[h]=aux[k];
            h++;
            k++;
        }

        num[h]='\0';

        v[i].coordenada_x=atoi(num);
        h=0;
        k++;

        fflush(stdin);
        fflush(mapa);

        while(aux[k]!='/') //Volcamos el campo coordenada_y en la estructura
        {
            num[h]=aux[k];
            h++;
            k++;
        }

        num[h]='\0';
        v[i].coordenada_y=atoi(num);
        h=0;

        fflush(stdin);
        fflush(mapa);
    }
    fclose(mapa);
    }
}

void mostrar_mapa(tipo_posicion *v,int N){
    int i;
    for (i=0;i<N;i++) //Recorremos todos los elementos de la estructura y los mostramos por pantalla
    {
        printf("Elemento %d \n",i+1);
        printf("%s\n", v[i].id_nick);
        (v[i].tipo)?printf("Es un objeto\n"):printf("Es un jugador\n");
        printf("Esta en la x: %d\n", v[i].coordenada_x);
        printf("Esta en la y: %d\n", v[i].coordenada_y);
        printf("\n\n");
    }
}

void guardar_mapa(tipo_posicion *v,int N){
    int i;
    FILE * mapa;
    mapa=fopen(MAPA,"w");
    if((mapa)==NULL) printf("Error de apertura\n");
    else if(N > 1){
    for(i=0;i<N;i++) //Volcamos en el fichero todas las estructuras del vector, poniendo un salto de linea entre cada una
    {
        fprintf(mapa, "%s/%d/%d/%d/\n", v[i].id_nick, v[i].tipo, v[i].coordenada_x, v[i].coordenada_y);
    }
    fclose(mapa);
    }

}

void cargar_tormenta(tipo_estadotormenta *v,int N){
    int i,k,h=0;
    FILE * tormenta;
    char aux[TAM],num[TAM];

    tormenta=fopen(TORMENTA,"r");
    if((tormenta)==NULL) printf("Error de apertura del fichero tormenta.txt");

    for(i=0;i<N;i++) //Recorremos todos los elementos
    {
        fflush(stdin);
        fflush(tormenta);

        fgets(aux,TAM,tormenta); //Volcamos en la cadena auxiliar todo el fichero
        k=0;
        while(aux[k]!='/') //Volcamos el campo coordenada_x en la estructura
        {
            num[h]=aux[k];
            h++;
            k++;
        }

        num[h]='\0';

        v[i].coordenada_x=atoi(num);
        h=0;
        k++;

        fseek(tormenta,1,SEEK_CUR);
        fseek(tormenta,-1,SEEK_CUR);

        fflush(stdin);
        fflush(tormenta);

        num[0]='\0';

        while(aux[k]!='/') //Volcamos el campo coordenada_y en la estructura
        {
            num[h]=aux[k];
            h++;
            k++;
        }

        num[h]='\0';
        v[i].coordenada_y=atoi(num);
        h=0;
        k++;

        fflush(stdin);
        fflush(tormenta);

        num[0]='\0';

        while(aux[k]!='/') //Volcamos el campo radio en la estructura
        {

            num[h]=aux[k];
            k++;
            h++;
        }

        num[h]='\0';
        v[i].radio=atoi(num);
        h=0;
        k++;

        fflush(stdin);
        fflush(tormenta);

        num[0]='\0';

        while(aux[k]!='/') //Volcamos el campo turnos en la estructura
        {
            num[h]=aux[k];
            h++;
            k++;
        }

        num[h]='\0';
        v[i].turnos=atoi(num);
        h=0;

        fflush(stdin);
        fflush(tormenta);

        num[0]='\0';
    }
    fclose(tormenta);
}

void mostrar_tormenta(tipo_estadotormenta *v,int N){
    int i;
    printf("\nEsto es lo que hay cargado:\n");
    for (i=0;i<N;i++) //Mostramos todos los elementos almacenados en el vector
    {
        printf("Estado %d \n",i+1);
        printf("Esta en la x: %d\n", v[i].coordenada_x);
        printf("Esta en la y: %d\n", v[i].coordenada_y);
        printf("Su radio es: %d\n",v[i].radio);
        printf("Se cierra despues de %d turnos",v[i].turnos);
        printf("\n\n");
    }
}

void guardar_tormenta(tipo_estadotormenta *v, int N){
    int i;
    FILE * tormenta;
    tormenta=fopen(TORMENTA,"w");
    if((tormenta)==NULL) printf("Error de apertura\n");
    for(i=0;i<N;i++) //Volcamos en el fichero todos los elementos del vector poniendo un salto de línea entre ellos
    {
        fprintf(tormenta, "%d/%d/%d/%d/\n", v[i].coordenada_x, v[i].coordenada_y, v[i].radio, v[i].turnos);
    }
    fclose(tormenta);
}

void imprimir_mochila(r_jugador *jug){
int  j;
for(j = 0; j < jug->tamMochila;j++){    // Recorremos el vector imprimiendo cada uno de los elementos
            printf("\n\nArma o utilidad %i :\n", j+1);
            printf("ID: %s\n",jug->v_mochila[j].id);
            printf("Unidades/Municion: %i\n", jug->v_mochila[j].unidades);
        }
}
