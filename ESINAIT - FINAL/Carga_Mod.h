
#ifndef TAM
#define TAM 60
#endif // TAM

#ifndef TAM_RED
#define TAM_RED 7
#endif // TAM_RED

#ifndef TOTAL_OBJETOS
#define TOTAL_OBJETOS 30
#endif // TOTAL_OBJETOS

#ifndef TAM_MAX
#define TAM_MAX 210
#endif // TAM_MAX

#ifndef UD_UTILIDAD
#define UD_UTILIDAD 1
#endif // UD_UTILIDAD

#ifndef UD_MUNICION
#define UD_MUNICION 15
#endif // UD_MUNICION

#ifndef MOCHILA
#define MOCHILA "Mochila.txt"
#endif // MOCHILA

#ifndef JUGADORES
#define JUGADORES "Jugadores.txt"
#endif // JUGADORES

#ifndef TORMENTA
#define TORMENTA "Tormenta.txt"
#endif // TORMENTA

#ifndef MAPA
#define MAPA "Mapa.txt"
#endif // MAPA

#ifndef CONFIGURACION
#define CONFIGURACION "Configuracion.txt"
#endif // CONFIGURACION

#ifndef OBJETOS
#define OBJETOS "Objetos.txt"
#endif // OBJETOS

#ifndef CARGA_MOD_H_
#define CARGA_MOD_H_

// Tipos de datos

/*
 * Tipo: r_config
 * 		ENTEROS:
 *
 * 		Radio del mapa									||radMap
 * 		Distancia m�nima para coger objeto				||disMinObj
 * 		Distancia m�xima de ataque del arma por defecto	||disMaxAt
 * 		Monedas por defecto								||defMon
 * 		M�nimo jugadores por partida					||minJug
 * 		Distancia recorrida por movimiento				||disPMov
 * 		Espacio m�ximo de mochila						||maxSpMoch
 * 		Partidas m�nimas a ganar para subir de nivel	||minPartPNiv
 * 		M�ximo de acciones por turno					||maxAccPTurno
 *      Turno en el que estamos actualmente             ||turnoActual
 *      Posicion de la tormenta                         ||tormentaActual
 *      Numero de jugadores en partida                  ||numJugadores en partida
 */

typedef struct
{
	int radMap,disMinObj,disMaxAt,defMon,minJug,disPMov,maxSpMoch,minPartPNiv,maxAccPTurno, turnoActual, tormentaActual, numJugadoresPartida;
}r_config;



typedef struct{
    char id[TAM];
    int unidades;
}r_mochila;

typedef struct{
	char identificador[TAM], nombre[TAM], tipo[TAM];
	int coste, alcance , dano;
}r_objeto;

typedef struct{
    char nick[TAM];
    char nombre[TAM];
    int nivel;
    int vida;
    int escudo;
    char estado[TAM_RED];
    int dinero;
    int partJugadas;
    int partGanadas;
    char tipoUsuario[TAM];
    char pass[TAM];
    r_mochila *v_mochila;
    int tamMochila;
    int seleccionado;
    int posTurno;
    int acciones;
}r_jugador;

typedef struct //Definimos la estructura de la que estar� compuesta nuestro vector mapa
    {
        char id_nick[TAM];
        int tipo; //Si es jugador ser� 0 y si es un objeto ser� 1
        int coordenada_x;
        int coordenada_y;
    } tipo_posicion;

    typedef struct //Definimos la estructura de la que estar� compuesta nuestro vector de estados de la tormenta
    {
        int coordenada_x;
        int coordenada_y;
        int radio;
        int turnos;
    } tipo_estadotormenta;

//cabecera: imprimir_mochila(r_jugador* jug)
//precondici�n: jug inicializado con uno de los jugadores
//poscondici�n: muestra todos los elementos de la mochila de un jugador

void imprimir_mochila(r_jugador*);

//   Cabecera:       void imprimir_jugador(r_jugador jug,)
//   Precondicion:   jug inicializado y cargado con todos los datos de un jugador
//   PostCondicion:  imprime en pantalla todos los datos de un jugador (jug) Es usado como pruebas

void imprimir_jugador(r_jugador);

//   Cabecera:       void guardar_jugador(r_jugador* v_jug, int totJugadores)
//   Precondicion:   v_jug y totJugadores inicializados, v_jug cargado con todos los datos de un jugador y totJugadores con el total de jugadores
//   PostCondicion:  Guarda en el fichero todos los jugadores

void guardar_jugador(r_jugador* , int );

//   Cabecera:       void guardar_mochila(r_jugador *v_jug, int totJugadores)
//   Precondicion:   v_jug y totJugadores inicializados, v_jug cargado con todos los datos de un jugador y totJugadores con el total de jugadores
//   PostCondicion:  Guarda en el fichero las mochilas de cada jugador

void guardar_mochila(r_jugador*, int );

//   Cabecera:       void cargar_jugador(r_jugador* v_jug, int tam_v)
//   Precondicion:   v_jug con memoria ya asignada y tam_v inicializado con el numero de jugadores
//   PostCondicion:  carga los datos del fichero Jugadores.txt en el vector de estructura v_jug

void cargar_jugador(r_jugador* , int );

//   Cabecera:       void cargar_mochila(r_mochila * v_mochila, int tam_v, char nick[])
//   Precondicion:   la cadena nick inicializada con el nombre del jugador a cargar, v_mochila con memoria ya asignada y tam_v inicializado con el numero de elementos en la mochila del jugador con el nick correspondiente
//   PostCondicion:  carga los datos del fichero Mochila.txt en la mochila del jugador con el nick correspondiente

void cargar_mochila(r_mochila* , int , char []);

//   Cabecera:       int numero_filas_mochila_de_jugador(char nick[])
//   Precondicion:   nick inicializado y con el nick de un jugador
//   PostCondicion:  devuelve el numero de elementos que hay en la mochila del jugador con dicho nick

int numero_filas_mochila_de_jugador(char []);

//   Cabecera:       int numero_filas(char nombre[])
//   Precondicion:   nombre inicializado con el nombre de uno de los ficheros existentes
//   PostCondicion:  devuelve el numero de filas que hay en el fichero

int numero_filas(char []);


// void cargar_objetos(r_objeto *v_obj, int tam_v)
// Precondici�n: v_obj puntero inicializado con el tama�o necesario y tam_v el tama�o del vector
// Postcondici�n: Carga los datos del fichero "Objetos.txt" en un registro del tipo r_objeto

void cargar_objetos(r_objeto*, int);

//cabecera: void guardar_objetos(r_objeto *v_obj, int tam_v)
//precondici�n: recibe v_obj inicializado y cargado y el numero de elementos del mismo
//poscondici�n: sobreescribe el fichero "Objetos.txt" con los datos de v_obj

void guardar_objetos(r_objeto*, int);

// Cabecera: void cargaConfig(r_config *config)
// Precondici�n: Introducir la direcci�n de un registro del tipo r_config
// Postcondici�n: No devuelve nada. Carga los datos del fichero "configuracion.txt" en un registro del tipo r_config

void cargaConfig(r_config*);

//   Cabecera:       void guardaConfig(r_config config)
//   Precondicion:   config inicializado y cargado
//   PostCondicion:  Guarda en el fichero "Configuracion.txt" la configuracion del juego

void guardaConfig(r_config);

//cabecera: void cargar_mapa(tipo_posicion *, int)
//precondici�n: recibe la primera posici�n del vector y el n�mero de elementos del mismo
//poscondici�n: se cargan en la estructura los datos almacenados en el fichero mapa.txt

void cargar_mapa(tipo_posicion *,int);

//cabecera: void mostrar_mapa(tipo_posicion *,int)
//precondici�n: recibe la primera posici�n del vector y el numero de elementos del mismo
//poscondici�n: muestra por pantalla los elementos del vector

void mostrar_mapa(tipo_posicion *,int);

//cabecera: void guardar_mapa(tipo_posicion *,int)
//precondici�n: recibe la primera posici�n del vector y el numero de elementos del mismo
//poscondici�n: sobreescribe el fichero mapa.txt con los datos del vector de estructuras de posici�n

void guardar_mapa(tipo_posicion *, int);

//cabecera: void cargar_tormenta(tipo_posicion *, int)
//precondici�n: recibe la primera posici�n del vector y el n�mero de elementos del mismo
//poscondici�n: se cargan en la estructura los datos almacenados en el fichero tormenta.txt

void cargar_tormenta(tipo_estadotormenta *,int);

//cabecera: void mostrar_tormenta(tipo_posicion *,int)
//precondici�n: recibe la primera posici�n del vector y el numero de elementos del mismo
//poscondici�n: muestra por pantalla los elementos del vector

void mostrar_tormenta(tipo_estadotormenta *,int);

//cabecera: void guardar_tormenta(tipo_posicion *,int)
//precondici�n: recibe la primera posici�n del vector y el numero de elementos del mismo
//poscondici�n: sobreescribe el fichero tormenta.txt con los datos del vector de estructuras de estado de la tormenta

void guardar_tormenta(tipo_estadotormenta *, int);

#endif // CARGA_MOD_H_

