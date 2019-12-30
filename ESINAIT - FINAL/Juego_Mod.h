
#ifndef JUEGO_MOD_H_
#define JUEGO_MOD_H

//cabecera: void soltar_objeto(int* tam_mapa, tipo_posicion ** v_pos, r_jugador* jug, int * tam_v)
//precondición: tam_mapa, v_pos, tam_v y jug inicializados y cargados
//postcondición: Muestra menú para soltar objeto de la mochila en el mapa

void soltar_objeto(int*, tipo_posicion **, r_jugador*, int*);

//cabecera: void fin_juego(int* tam_v, int *tam_obj, r_jugador* v_jug, r_jugador** jug, r_objeto* v_obj)
//precondición: tam_v, tam_obj, v_jug, v_obj, jug, inicializados y cargados
//postcondición: muestra la pantalla de victoria, finaliza el juego y elimina todas las armas del inventario del jugador

void fin_juego(int*, int*, r_jugador*, r_jugador**, r_objeto*);

//cabecera: void comenzar_partida(int *tam_v, int* tam_obj, int *tam_pos, tipo_posicion ** v_pos, r_jugador* v_jug, r_objeto * v_obj, r_jugador* jug, r_config* config)
//precondición: tam_v, tam_obj, tam_pos, v_pos, v_jug, v_obj, jug, config inicializados y cargados
//postcondición: Inicia la partida, carga el vector del mapa "v_pos" con los jugadores y objetos, asignandoles un lugar en el mapa y actualiza el registro "config"

void comenzar_partida(int *, int* , int *, tipo_posicion ** , r_jugador* , r_objeto * , r_jugador* , r_config* );

//cabecera: int fuera_tormenta(int* tam_v, int* tam_mapa, tipo_estadotormenta* v_tor, r_config* config, tipo_posicion** v_pos, r_jugador* v_jug, r_objeto *v_obj, int *tam_obj)
//precondición: tam_v, tam_mapa, v_obj, tam_obj v_jug, v_tor, v_pos y config inicializados y cargados
//postcondición: comprueba qué jugadores están fuera de la tormenta, y en tal caso los elimina y devuelve 1

int fuera_tormenta(int*, int*, tipo_estadotormenta*, r_config*, tipo_posicion**, r_jugador*,r_objeto *, int *);

//cabecera: void muere(int* tam_mapa ,int i, tipo_posicion** v_pos, r_jugador* v_jug, r_objeto *v_obj, int *tam_obj)
//precondición: tam_mapa, i, v_pos, v_obj y v_jug inicializados y cargados
//postcondición: Elimina al jugador v_jug[i] del mapa

void muere(int* ,int , tipo_posicion**, r_jugador*,r_objeto *, int *);

//cabecera: void usar_objeto(int* tam_v, int conectado, int* tam_obj,int* tam_mapa, int *tam_tor, r_jugador* jug, r_objeto* v_obj, tipo_posicion ** v_pos, tipo_posicion** v_jugadoresCercanos, r_config * config, r_jugador* v_jug)
//precondición: tam_v, conectado, tam_obj, tam_mapa, tam_tor, v_pos, v_jug, v_obj, jug, v_jugadoresCercanos y config inicializados y cargados
//postcondición: Muestra menú para usar el objeto seleccionado de la mochila y permite usarlo

void usar_objeto(int* , int , int*,int*, int *, r_jugador* , r_objeto* , tipo_posicion **, tipo_posicion**, r_config*, r_jugador*);

//cabecera: void movimiento(int* tam_mapa, tipo_posicion* v_pos, r_jugador* jug, r_config* config)
//precondición: tam_mapa, v_pos, jug y config inicializados y cargados
//postcondición: Mueve al jugador en una dirección en el mapa

void movimiento(int*, tipo_posicion*, r_jugador*, r_config*);

//cabecera: int ver_jugadores_cercanos(int* tam_v, int conectado, int* tam_obj,int* tam_mapa,int* tam_tor, tipo_posicion* v_pos, r_config* config, tipo_posicion ** v_jugadoresCercanos, r_jugador *jug, r_jugador * v_jug)
//precondición: tam_v, conectado, tam_obj, tam_mapa, tam_tor, v_pos, v_jug, jug y config inicializados y cargados, v_jugadoresCercanos inicializado
//postcondición: carga v_jugadoresCercanos con los jugadores de v_pos que estén en el rango de visión del jugador

int ver_jugadores_cercanos(int* , int , int* ,int* ,int*, tipo_posicion*, r_config*, tipo_posicion **, r_jugador*, r_jugador*);

//cabecera: void eliminar_objeto_mapa(int i,int* tam_mapa, tipo_posicion* v_pos)
//precondición: i índice de v_pos inicializados junto a tam_mapa
//postcondición: elimina el elemento v_pos[i] del mapa

void eliminar_objeto_mapa(int ,int* , tipo_posicion*);

//cabecera: void ver_objetos_cercanos(int* tam_v, int conectado, int* tam_obj,int* tam_mapa,int* tam_tor, r_jugador* jug, tipo_posicion* v_pos, r_objeto* v_obj, r_config* config)
//precondición: tam_v, conectado, tam_obj, tam_mapa, tam_tor, v_pos, v_jug, jug y config inicializados y cargados
//postcondición: muestra los objetos cercanos y muestra menú para cogerlos

void ver_objetos_cercanos(int* , int , int* ,int* ,int* , r_jugador* , tipo_posicion* , r_objeto* , r_config*);

//cabecera: void fin_turno(int *tam_v, int *tam_tor, r_jugador* v_jug, r_jugador** jug, r_config* config)
//precondición: tam_v, tam_tor, v_jug, jug y config inicializados y cargados
//postcondición: Finaliza el turno de un jugador, si ya han jugado todos la ronda, avanza la tormenta

void fin_turno(int *, int *, r_jugador*, r_jugador**, r_config*);

//cabecera: void quitar_objeto_mochila(int iObjeto, r_jugador* jug)
//precondición: iObjeto y jug inicializados y cargados
//postcondición: Quita el objeto con índice iObjeto en la mochila del jugador jug

void quitar_objeto_mochila(int, r_jugador*);

#endif // JUEGO_MOD_H_
