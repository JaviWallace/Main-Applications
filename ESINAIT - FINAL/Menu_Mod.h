
#ifndef MENU_MOD_H_
#define MENU_MOD_H_

//cabecera: void menu_compra(int* tam_obj, r_jugador* jug, r_objeto* v_obj)
//precondición: tam_obj, jug y v_obj inicializados y cargados
//postcondición: muestra el menú para poder comprar un objeto, en caso de compra, se añade al v_mochila de jug

void menu_compra(int* , r_jugador*, r_objeto*);

//cabecera: void menu_compra(int* tam_obj, r_jugador* jug, r_objeto* v_obj)
//precondición: tam_obj, jug, v_obj y config inicializados y cargados
//postcondición: muestra el menú de la tienda, permite acceder al menú de venta y compra

void menu_tienda (int*, r_objeto*, r_jugador*, r_config*);

//cabecera: void menu_venta(int tam_obj, r_jugador* jug, r_objeto* v_obj)
//precondición: tam_obj, jug y v_obj inicializados y cargados
//postcondición: muestra el menú de venta, permite vender objetos de tu mochila

void menu_venta(int , r_jugador*, r_objeto*);

//Cabecera: void mostrar_perfil(r_jugador jug,)
//Precondicion: jug inicializado y cargado con todos los datos de un jugador
//PostCondicion: imprime en pantalla todos los datos de un jugador "jug"

void mostrar_perfil(r_jugador*);

//cabecera: void cerrar_sesion(r_jugador* jug, int *conectado)
//precondición: conectado y jug inicializados
//poscondición: cierra la sesion del jugador "jug"

void cerrar_sesion(r_jugador*, int*);

//cabecera: r_jugador* iniciar_sesion(r_jugador* v_jug, int tam_v, int* conectado, r_jugador* jug)
//precondición: v_jug vector de jugadores inicializado, tam_v inicializado con tamaño del vector, conectado inicializado, jug inicializado
//poscondición: devuelve el jugador que ha iniciado sesion

r_jugador* iniciar_sesion(r_jugador*, int, int*, r_jugador*);

//cabecera: int registrar_usuario(r_jugador* v_jug, int tam_v, r_config* config)
//precondición: v_jug inicializado con un elemento de mas para introducir el nuevo jugador, tam_v inicializado, config inicializado con la configuracion del juego
//poscondición: anade un nuevo usuario al vector v_jug, devuelve 0 si se ha creado, 2 si no se ha creado

int registrar_usuario(r_jugador*, int , r_config*);

//cabecera: void modificar_jugadores(r_jugador* v_jug, int tam_v)
//precondición: v_jug inicializado con vector de jugadores, tam_v con el tamano del vector completo
//poscondición: muestra un menu con los jugadores y permite seleccionar uno de ellos para modificarlo

void modificar_jugadores(r_jugador*, int);

//cabecera: void menu modificar_jugador(r_jugador* v_jug, int i, int tam_v)
//precondición: v_jug inicializado con vector de jugadores, i con elemento del vector a cambiar, tam_v con el tamano del vector completo
//poscondición: muestra un menu con las opciones para cambiar cualquier elemento del jugador "i" del vector

void menu_modificar_jugador(r_jugador*, int, int);

//cabecera: void modificar_mochila_jugador(r_jugador* v_jug, int i, int tam_v)
//precondición: v_jug inicializado con vector de jugadores, i con elemento del vector a cambiar, tam_v con el tamaño del vector completo
//poscondición: muestra un menu con las opciones para cambiar cualquier elemento de la mochila del jugador "i" del vector

void modificar_mochila_jugador(r_jugador*, int , int);

//cabecera: int quitar_objeto(r_objeto* v_obj, int tam_v)
//precondición: v_obj inicializado con vector de objetos y tam_v con el tamano del vector
//poscondición: devuelve 0 si no se ha eliminado un elemento, 1 si se ha eliminado. En este caso se debera hacer reasignar la memoria al vector

int quitar_objeto(r_objeto* v_obj, int );

//cabecera: int anadir_objeto(r_objeto* v_obj, int tam_v, r_config* config)
//precondición: v_obj inicializado con vector de objetos y tam_v con el tamano del vector, config inicializado con la configuracion del juego
//poscondición: anade un nuevo objeto al vector

void anadir_objeto(r_objeto *, int , r_config*);

//cabecera: int modificar_objetos(r_objeto* v_obj, int tam_v, r_config*)
//precondición: v_obj inicializado con vector de objetos, tam_v con el tamano del vector y r_config* con puntero a la configuración
//poscondición: nos permite modificar uno de los objetos al completo

void modificar_objetos(r_objeto *, int,  r_config*);

//cabecera: void modificar_mapa(tipo_posicion *,int)
//precondición: recibe la primera posición del vector y el numero de elementos del mismo
//poscondición: sobreescribe el/los registro/s deseado/s del fichero mapa.txt con los datos de que introduzca el usuario

void modificar_mapa(tipo_posicion *, int);

//cabecera: void agregar_elemento_al_mapa(tipo_posicion *,int)
//precondición: recibe la primera posición del vector y el numero de elementos AUMENTADO
//poscondición: agrega un registro a la estructura que contiene las posiciones de los elementos

void agregar_elemento_al_mapa(tipo_posicion *,int);

//cabecera: void modificar_tormenta(tipo_posicion *,int)
//precondición: recibe la primera posición del vector y el número de elementos del mismo
//poscondición: sobreescribe el/los registro/s deseado/s del fichero tormenta.txt con los datos de que introduzca el usuario

void modificar_tormenta(tipo_estadotormenta *,int);

//cabecera: void agregar_estado_a_tormenta(tipo_posicion *,int)
//precondición: recibe la primera posición del vector y el número de elementos AUMENTADO
//poscondición: agrega un registro a la estructura donde se guardan los estados de la tormenta

void agregar_estado_a_tormenta(tipo_estadotormenta *,int);

//cabecera: void eliminar_estado_tormenta(tipo_estadotormento *,int)
//precondición: recibe la primera posición del vector y el numero de estados de la tormenta
//poscondición: se borra el contenido de uno de los estados al sobreescribir el del siguiente en él. IMPORTANTE hay que hacer un realloc después para reducir el tamaño en uno

int eliminar_estado_tormenta(tipo_estadotormenta *,int );

//cabecera: void menuConfig(r_config *conf)
//precondición: config inicializado y cargado
//poscondición: permite modificar los campos de la configuracion

void menuConfig(r_config*);

//cabecera: void printConfig(r_config *config)
//precondición: Config inicializado y cargado
//poscondición: Imprime en pantalla todos los aspectos de la configuracion

void printConfig(r_config *);

//int printMenuConfig(r_config *config)
//precondición: Config inicializado y cargado
//poscondición: Imprime en pantalla todos los aspectos de la configuracion y elige la opcion a cambiar

int printMenuConfig(r_config*);


#endif // MENU_MOD_H_
