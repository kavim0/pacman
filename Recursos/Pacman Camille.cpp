//#include <allegro.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cargarmapa1(int matrizjuego[][30]);
void motordejuego();
void imprimirMapa(int matrizjuego[][30]);
void movimientoPacman(int matrizjuego[][30]);
void IFmove(int matrizjuego[][30], char tecla, int posPacman[2]);
/*0 -> PACMAN
1 -> Bloque
2 -> Espacio libre 
3 -> Fruta
4 -> Punto chico
5 -> punto grande 
6 -> Blinky -> ROJO  -> PERSIGUE LOCAMENTE AL PACMAN 
7 -> Inky -> AZULITO  -> SE MUEVE AL AZAR PERO MÁS LENTO
8 -> Pinky -> ROSA ->PERSIGUE IGUAL PERO MÁS LENTO
9 -> Clyde -> NARANJA -> SE MUEVE AL AZAR RAPIDO*/

int main(){
	motordejuego();
	
	return 0;
}

void cargarmapa1(int matrizjuego[20][30]){
	int i,j;

	int mapa[20][30]{
		//1 2 3 4 5 6 7 8 9 
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},//2
		{1,2,1,2,1,1,2,1,1,1,1,2,1,2,1,1,2,1,2,1,1,1,1,2,1,1,2,1,2,1},//3
		{1,2,1,2,1,1,2,1,1,2,2,2,1,2,2,2,2,1,2,2,2,1,1,2,1,1,2,1,2,1},//4
		{1,2,1,2,1,1,2,2,2,2,1,2,1,2,1,1,2,1,2,1,2,2,2,2,1,1,2,1,2,1},//5
		{1,2,2,2,2,2,2,1,2,1,1,2,1,2,2,2,2,1,2,1,1,2,1,4,2,2,2,2,2,1},//6
		{1,2,1,1,2,1,1,1,2,2,1,2,1,2,1,1,2,1,2,1,2,2,1,1,1,2,1,1,2,1},//7
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},//8
		{1,2,1,1,1,2,1,2,1,1,1,1,2,3,3,3,3,2,1,1,1,1,2,1,2,1,1,1,2,1},//9
		{1,2,1,1,1,2,1,2,1,1,1,1,2,3,9,8,3,2,1,1,1,1,2,1,2,1,1,1,2,1},//10
		{2,2,2,2,2,2,1,2,2,1,1,1,2,3,10,7,3,2,1,1,1,2,2,1,2,2,2,2,2,2},//11
		{1,2,1,1,1,2,1,1,2,2,2,2,2,3,3,3,3,2,2,2,2,2,1,1,2,1,1,1,2,1},//12
		{1,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,1,2,1},//13
		{1,2,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,2,1},//14
		{1,2,1,2,1,2,2,2,1,2,2,2,2,2,0,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1},//15
		{1,2,1,2,2,2,1,2,2,2,1,1,2,1,1,1,1,2,1,1,2,2,2,1,2,2,2,1,2,1},//16
		{1,2,1,2,1,2,2,2,1,2,1,1,2,2,2,2,2,2,1,1,2,1,2,2,2,1,2,1,2,1},//17
		{1,2,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,2,1},//18
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},//19
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//20
	};
	
	for (i=0; i<=19; i++){
		for (j=0; j<=29; j++){
			matrizjuego[i][j]=mapa[i][j];
		}
		
	}
		
}

void motordejuego(){
	
	int matrizjuego[20][30];
	
	cargarmapa1(matrizjuego);
	
	imprimirMapa(matrizjuego);
	
	movimientoPacman(matrizjuego);
	
}

void imprimirMapa(int matrizjuego[20][30]){
	int i,e;
	
	for(i=0;i<20;i++){
		for(e=0;e<30;e++){
			printf("%d ",matrizjuego[i][e]);
		}
		printf("\n");
	}
	
}

void movimientoPacman(int matrizjuego[20][30]){
	int posPacman[2]={14, 14};
	float delayRefresh=1; //segundos;
	char tecla;
	do{
		clock_t tstart = clock();
		while((clock() - tstart) / CLOCKS_PER_SEC < delayRefresh){
			if(_kbhit()){
	     		tecla=_getch();
			}
		}
		IFmove(matrizjuego, tecla, posPacman);
		//no jalo >:( int matrizjuego[20][30];
		system("cls");
		imprimirMapa(matrizjuego);
	}while(tecla != '1');
}

void IFmove(int matrizjuego[20][30],char tecla, int posPacman[2]){
	switch(tecla){
		case 'w':
			matrizjuego[posPacman[0]][posPacman[1]] = 2;
			posPacman[0]--;
			matrizjuego[posPacman[0]][posPacman[1]] = 0;
			break;
		case 'a':
			matrizjuego[posPacman[0]][posPacman[1]] = 2;
			posPacman[1]--;
			matrizjuego[posPacman[0]][posPacman[1]] = 0;
			break;
		case 's':
			matrizjuego[posPacman[0]][posPacman[1]] = 2;
			posPacman[0]++;
			matrizjuego[posPacman[0]][posPacman[1]] = 0;
			break;
		case 'd':
			matrizjuego[posPacman[0]][posPacman[1]] = 2;
			posPacman[1]++;
			matrizjuego[posPacman[0]][posPacman[1]] = 0;
			break;
	}
	printf("\n%d, %d",posPacman[0],posPacman[1]);//debug
}
