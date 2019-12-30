#include <iostream>
#include <fstream>
#include <cstdlib>

#define CLARO 178
#define MEDIO 177
#define OSCURO 176

#define PARED 219

#define PERS 80

#define RANG 3
#define ANCHO 10

void juego(char [ANCHO][ANCHO], int , int , int );
void mapa_general(char [ANCHO][ANCHO], int [ANCHO][ANCHO],char [ANCHO][ANCHO] , int );
void limpia(int [ANCHO][ANCHO], int );
void vision_mapa(int [ANCHO][ANCHO],char [ANCHO][ANCHO], int , int , int , int );
void carga(char [ANCHO][ANCHO], int );
void mostrar_mapa(char mapa[ANCHO][ANCHO], int n);

using namespace std;

int main(){
	
	char lab[ANCHO][ANCHO];	
	
	carga(lab, ANCHO);
	
	
	
	juego(lab, ANCHO, 1, 1);
	
	return 0;
}

void juego(char lab[ANCHO][ANCHO], int n, int posX, int posY){
	bool fin = false;
	char mov;
	int vista[ANCHO][ANCHO];
	char mapa[ANCHO][ANCHO];
	posX = 1;
	posY = 1;
	while(!fin){
		system("CLS");
		limpia(vista, n);
		vision_mapa(vista, lab, n, 3, posX, posY);
		mapa_general(lab, vista, mapa, n);
		mostrar_mapa(mapa,ANCHO);
		cin >> mov;
		switch (mov){
			case 'a':{
				if(lab[posX][posY-1] != '1') posY--;
				break;
			}
			case 's':{
				if(lab[posX+1][posY] != '1') posX++;
				break;
			}
			case 'd':{
				if(lab[posX][posY+1] != '1') posY++;
				break;
			}
			case 'w':{
				if(lab[posX-1][posY] != '1') posX--;
				break;
			}
		
		}
	}
	
	
}

void mapa_general(char lab[ANCHO][ANCHO], int vista[ANCHO][ANCHO],char mapa[ANCHO][ANCHO] , int n){
	for(int i; i < n; i++){
		for(int j = 0; j < n; j++){
			
			
				switch (vista[i][j]){
					case 0: mapa[i][j] = ' ';
					break;
					case 1: mapa[i][j] = CLARO;
					break;
					case 2: mapa[i][j] = MEDIO;
					break;
					case RANG: mapa[i][j] = PERS;
					break;
					case -1: mapa[i][j] = PARED;
					break;
				}
			
			
		}
	}
}

void limpia(int m[ANCHO][ANCHO], int n){
	for(int i = 0; i < n ; i++){
			for(int j = 0; j < n; j++) m[i][j] = 0;
		}
}

void vision_mapa(int vista[ANCHO][ANCHO], char lab[ANCHO][ANCHO], int n, int rango, int x, int y){
	if(rango >= 0){
		if( rango == RANG){
			vista[x][y] = 3;
			vision_mapa(vista,lab,n, rango-1, x+1, y);
			vision_mapa(vista,lab,n, rango-1, x-1, y);
			vision_mapa(vista,lab,n, rango-1, x, y-1);
			vision_mapa(vista,lab,n, rango-1, x, y+1);
		} else if(rango > 0 && lab[x][y] != '1' && vista[x][y] == 0) {
			if (rango >= RANG/2) vista[x][y] = 2;
			else vista[x][y] = 1;
			vision_mapa(vista,lab,n, rango-1, x+1, y);
			vision_mapa(vista,lab,n, rango-1, x-1, y);
			vision_mapa(vista,lab,n, rango-1, x, y-1);
			vision_mapa(vista,lab,n, rango-1, x, y+1);
		}else{
			if(lab[x][y] == '1') vista[x][y] = -1;
		}
		
	}
}

void carga(char lab[ANCHO][ANCHO], int n){	
	ifstream fCarga;
	fCarga.open("mapa.txt");
	char c;
	int j;
	
	for(int i = 0; i < n; i++){
		fCarga.get(c);
		j=0;
		while(c != '\n'){
			lab[i][j] = c;
			fCarga.get(c);
			j++;
		}
	}
	fCarga.close();
}

void mostrar_mapa(char mapa[ANCHO][ANCHO], int n){
	char claro = 178;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n;j++){
			cout << mapa[i][j];
		}
		cout << endl;
	}
}
