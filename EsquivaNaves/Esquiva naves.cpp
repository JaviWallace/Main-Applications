#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define Filas 7
#define Columnas 20
#define maxPuntuacion 20
#define maxEnemigos 15
#define iteracionEnemigo 5
#define Wait 100
#define maxBalas 4

#define caracterJugador 219
#define caracterEnemigo 215
#define caracterBala 175
typedef struct{
	int posX;
	int posY;
	int vivo;
	int puntuacion;
}player;
typedef struct{
	int posX;
	int posY;
	int vivo;
}bullet;
typedef struct {
	int vivo;
	int posX;
	int posY;
	int iteracion;
}enemy;

int totEnemigos;
int iteracion;

void dispara(player jugador, bullet balas[], int totBalas){
	
	int i;
	for(i = 0; i < maxBalas; i++){
		if(balas[i].vivo == 0){
			balas[i].vivo = 1;
			balas[i].posX = jugador.posX;
			balas[i].posY = 1;
			i = maxBalas;
		}
	}
	totBalas++;
}
void mostrar(player jugador, enemy enemigos[], int tot, bullet balas[]){
	int i, j;
	system("cls"); // Limpia pantalla
	char mapa[Filas][Columnas];
	for(i = 0; i < Filas; i++) for(j = 0; j < Columnas; j++) mapa[i][j] = ' '; // Inicializamos mapa
	
	mapa[jugador.posX][jugador.posY] = caracterJugador; // Ponemo jugador
	
	for(i = 0; i < tot; i++) mapa[enemigos[i].posX][enemigos[i].posY] = caracterEnemigo; // Ponemos enemigos
	for(i = 0; i < maxBalas; i++){
		if(balas[i].vivo==1) mapa[balas[i].posX][balas[i].posY] = caracterBala;
	}
	for(i = 0; i < Filas;i ++){
		for (j = 0; j< Columnas; j++){
			printf("%c", mapa[i][j]);
		}
		puts("");
	}
	puts("");
	printf("%i vidas\n", jugador.vivo);
}
void creaEnemigo(enemy *enemigos, int pos){
	enemigos = (enemy*) realloc(enemigos, (pos+1)*sizeof(enemy));
	int x;
	x = rand()% (Filas + 1);
	enemigos[pos].posX = x;
	enemigos[pos].posY = Columnas-1;
	enemigos[pos].vivo = 1;
	enemigos[pos].iteracion = 0;
}

void juego(){
	int i, j;
	char mapa[Filas][Columnas];
	char mapaSec[Filas][Columnas];
	for(i = 0; i < Filas; i++){ // Inicializamos las matrices a espacios
		for(j = 0; j < Columnas; j++){
			mapa[i][j] = ' ';
			mapaSec[i][j] = ' ';
		}
	}
	// Inicializamos variables globales y locales importantes
	
	enemy *enemigos;
	enemigos = (enemy*) malloc (1 * sizeof(enemy));
	
	totEnemigos = 0;
	iteracion = 0;
	
	bullet balas[maxBalas];
	for(i = 0; i < maxBalas; i++){
		balas[i].vivo = 0;
		balas[i].posX = Filas;
	}
	int totBalas = 0;
	// Generamos la posicion del jugador
	player jugador;
	jugador.posX = Filas/2;
	jugador.posY = 0;
	jugador.vivo = 1;
	jugador.puntuacion = 0;
	while (jugador.puntuacion < maxPuntuacion && jugador.vivo == 1){ // Bucle del juego
		Sleep(Wait); // Tiempo entre cada iteracion
		iteracion++;
		
		char mov;
		
		for(i = 0; i < totEnemigos; i++) enemigos[i].iteracion++; // Aumentamo la iteracion de cada enemigo
		
		if(totEnemigos < maxEnemigos && iteracion == iteracionEnemigo){ // Si no hay el maximo de enemigos y han pasado las iteraciones
			creaEnemigo(enemigos, totEnemigos); // Creamos enemigo
			iteracion = 0;
			totEnemigos++;
		}
		mostrar(jugador, enemigos, totEnemigos, balas);
		for(i = 0; i<totEnemigos;i++){
			if(enemigos[i].vivo == 1){ // Movemos al enemigo
				if(enemigos[i].iteracion >= 2){
					enemigos[i].iteracion = 0;
					enemigos[i].posY--;
				}else{
					enemigos[i].iteracion++;
				}
			}
			else{ // Quitamos el enemigo
				totEnemigos--;
				enemigos[i] = enemigos[totEnemigos];
				enemigos = (enemy*) realloc(enemigos, (totEnemigos)*sizeof(enemy));
			}
			if(enemigos[i].posY < 0) enemigos[i].vivo = 0;
		}
		
		
		
		// Colisiona con enemigo la bala?
		
		for(i = 0; i < maxBalas; i++){
			for(j = 0; j<totEnemigos ; j++){
				if(balas[i].posX == enemigos[j].posX && balas[i].posY == enemigos[j].posY && balas[i].vivo==1){
					jugador.puntuacion++;
					balas[i].vivo = 0;
					balas[i].posX = Filas;
					enemigos[j].vivo = 0;
				}
			}
		}
		// Movemos la bala
		int tot = 0;
		for(i = 0; i < maxBalas; i++){
			if(balas[i].vivo == 1) balas[i].posY++;
			if(balas[i].posY >= Columnas) balas[i].vivo = 0;
			if(balas[i].vivo == 1) tot++;
		}
		totBalas = tot;
		
		
		
		// ------------- //
		fflush(stdin);
		mov = getch(); // Leemos caracter
		fflush(stdin);
		
		// Muere el jugador?
		
		for(i = 0; i < totEnemigos; i++){
			if(enemigos[i].posX == jugador.posX && jugador.posY == enemigos[i].posY && enemigos[i].vivo == 1) jugador.vivo = 0;
		}
		if(iteracion % 2 == 0 && jugador.vivo == 1){
			switch(mov){
				case 'w':
					if(jugador.posX != 0)jugador.posX--;
					break;
				case 's':
					if(jugador.posX != Filas-1)jugador.posX++;
					break;
				case 'd':
					if(totBalas < maxBalas)dispara(jugador, balas, totBalas);
					break;
			}
		}
	}
	puts("");
	puts("Fin, presiona enter");
	char c;
	scanf("%c", &c);	
	system("cls");
	
	if(jugador.vivo == 0){ // Comprobamos el resultado
		puts("Lo siento, has perdido");
	}
	else if(jugador.puntuacion >= maxPuntuacion){
		puts("Ole, ganaste!");
	}
	int n;
	do{
		puts("Reiniciar?");
		puts("1.- Si");
		puts("2.- No");
		scanf("%i", &n);
	}while(n != 1 && n != 2);
	switch(n){
		case 1: juego();
		break;
		case 2: puts("Hasta luego!");
		break;
	}
	fflush(stdin);
	scanf("%c", &c);
	
}


int main(){
	int n;
	
	//srand(time(NULL));
	
	do{
	system("cls");
	puts("Decide que hacer:");
	puts("1.- Jugar");
	puts("2.- Salir");
	scanf("%i", &n);
	fflush(stdin);
	}while(n != 1 && n!= 2);
	switch (n){
		case 1: 
		juego();
		break;
		case 2: 
		puts("Talue!");
		break;
	}
	return 0;
}

