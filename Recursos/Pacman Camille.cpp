//#include <allegro.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>
#include <allegro.h>

#define delayRefresh 0.3 //segundos;

void init ();
void cargarmapa1(int matrizjuego[][30]);
void motordejuego();
void imprimirMapa(int matrizjuego[20][30], BITMAP *buffer);
int movimientoPacman(int matrizjuego[][30], int posPacman[2]);
void IFmove(int matrizjuego[][30], int tecla, int posPacman[2]);
void spawnFruta(int matrizjuego[][30]);
void OcultaCursor();
int clydeNaranja(int matrizjuego[][30], int fantasmaPos[][2], int auxClyde);
void fantasmaExit(int matrizjuego[][30], int fantasmaPos[][2], int fantasmaForExit);
int muerte(int matrizjuego[][30], int fantasmaPos[][2], int posPacman[2], int ticks);
int muerteIF(int matrizjuego[][30], int fantasmaPos[][2], int posPacman[2], int fantasma, int ticks);
void reinicio(int matrizjuego[][30], int fantasmaPos[][2], int posPacman[2]);
void declararFantasmas(int fantasmaPos[][2]);

/*0 -> PACMAN
1 -> Bloque
2 -> Punto chico
3 -> Fruta
4 -> Espacio libre
5 -> punto grande 
6 -> Blinky -> ROJO  -> PERSIGUE LOCAMENTE AL PACMAN 			--fantasmaPos[0][];
7 -> Inky -> AZULITO  -> SE MUEVE AL AZAR PERO MÁS LENTO		--fantasmaPos[1][];
8 -> Pinky -> ROSA ->PERSIGUE IGUAL PERO MÁS LENTO				--fantasmaPos[2][];
9 -> Clyde -> NARANJA -> SE MUEVE AL AZAR RAPIDO				--fantasmaPos[3][];
*/
int main(){
	srand(time(NULL)); //declarar random
	init();
	motordejuego();
	//deinit();
	return 0;
}
END_OF_MAIN();

void init () { //inicializar allegro
	
	int depth, res,cancion;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 635, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	set_window_title("Pac_Man Game");

	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
}

void cargarmapa1(int matrizjuego[20][30]){
	int i,j;
//declarar mapa
	int mapa[20][30]{
		//1 2 3 4 5 6 7 8 9 
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},//2
		{1,2,1,2,1,1,2,1,1,1,1,2,1,2,1,1,2,1,2,1,1,1,1,2,1,1,2,1,2,1},//3
		{1,2,1,2,1,1,2,1,1,2,2,2,1,2,2,2,2,1,2,2,2,1,1,2,1,1,2,1,2,1},//4
		{1,2,1,2,1,1,2,2,2,2,1,2,1,2,1,1,2,1,2,1,2,2,2,2,1,1,2,1,2,1},//5
		{1,2,2,2,2,2,2,1,2,1,1,2,1,2,2,2,2,1,2,1,1,2,1,2,2,2,2,2,2,1},//6
		{1,2,1,1,2,1,1,1,2,2,1,2,1,2,1,1,2,1,2,1,2,2,1,1,1,2,1,1,2,1},//7
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},//8
		{1,2,1,1,1,2,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,2,1,1,1,2,1},//9
		{1,2,1,1,1,2,1,2,1,1,1,1,2,1,8,7,1,2,1,1,1,1,2,1,2,1,1,1,2,1},//10
		{2,2,2,2,2,2,1,2,2,1,1,1,2,1,9,6,1,2,1,1,1,2,2,1,2,2,2,2,2,2},//11
		{1,2,1,1,1,2,1,1,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1,1,2,1,1,1,2,1},//12
		{1,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,1,2,1},//13
		{1,2,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,2,1},//14
		{1,2,1,2,1,2,2,2,1,2,2,2,2,2,0,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1},//15
		{1,2,1,2,2,2,1,2,2,2,1,1,2,1,1,1,1,2,1,1,2,2,2,1,2,2,2,1,2,1},//16
		{1,2,1,2,1,2,2,2,1,2,1,1,2,2,2,2,2,2,1,1,2,1,2,2,2,1,2,1,2,1},//17
		{1,2,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,2,1},//18
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},//19
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//20
	};
//pasa mapa 1 a matriz juego
	for (i=0; i<=19; i++){
		for (j=0; j<=29; j++){
			matrizjuego[i][j]=mapa[i][j];
		}
		
	}
		
}

void motordejuego(){
	
	int matrizjuego[20][30], posPacman[2]={14, 14}, tecla, fantasmaPos[4][2], fantasmaForExit=3, auxClyde=2, ticks=0;; //declarar variables de juego
	//OcultaCursor(); //oculta cursor
	
	cargarmapa1(matrizjuego); //declara mapa 1 y pasa mapa 1 a matriz juego
	BITMAP *buffer = create_bitmap(960,660);
	
	declararFantasmas(fantasmaPos);
	spawnFruta(matrizjuego); //genera fruta de forma aleatoria
	do{
		tecla = movimientoPacman(matrizjuego, posPacman);
		if(ticks>50){
			auxClyde = clydeNaranja(matrizjuego, fantasmaPos, auxClyde);
		}
		if(ticks==50){
			fantasmaExit(matrizjuego, fantasmaPos, fantasmaForExit);
		}
		ticks = muerte(matrizjuego, fantasmaPos, posPacman, ticks);
		clear(buffer);
		imprimirMapa(matrizjuego,buffer); //imprime matriz juego
		printf("\nClyde: %d, %d\n",fantasmaPos[3][0],fantasmaPos[3][1]);
		blit(buffer,screen,0,0,0,0,960,660);
		if(ticks<51){
		ticks++;	
		}
		printf("Ticks: %d",ticks);
	}while(true); //CICLO INFINITO

	//
	
}

void imprimirMapa(int matrizjuego[20][30], BITMAP *buffer){
	int i,e;
	BITMAP *vectorMapa[15];
	vectorMapa[0] = load_bitmap("CuerpoPacman_II.bmp",NULL);
	vectorMapa[1] = load_bitmap("Bloques_1.bmp",NULL);
	vectorMapa[2] = load_bitmap("PuntosChicos.bmp",NULL);
	vectorMapa[3] = load_bitmap("Fruta 1.bmp",NULL);
	vectorMapa[4] = load_bitmap("Espacio.bmp",NULL);
	vectorMapa[5] = load_bitmap("PuntosGrandes.bmp",NULL);
	vectorMapa[6] = load_bitmap("FantasmaBlinky_I.bmp",NULL);
	vectorMapa[7] = load_bitmap("FantasmaInky_I.bmp",NULL);
	vectorMapa[8] = load_bitmap("FantasmaPinky_I.bmp",NULL);
	vectorMapa[9] = load_bitmap("FantasmaClyde_I.bmp",NULL);
	for(i=0;i<20;i++){
		for(e=0;e<30;e++){
			draw_sprite(buffer,vectorMapa[matrizjuego[i][e]],e*30,i*30+35);
		}
	}
	
}

int movimientoPacman(int matrizjuego[20][30], int posPacman[2]){
	int tecla = readkey() >> 8;
	IFmove(matrizjuego, tecla, posPacman); //comprueba la tecla de movimiento del usuario
	return tecla;
}

void IFmove(int matrizjuego[20][30],int tecla,int posPacman[2]){
	switch(tecla){
		case KEY_UP:
			if(matrizjuego[posPacman[0]-1][posPacman[1]] != 1){
				matrizjuego[posPacman[0]][posPacman[1]] = 4;
				posPacman[0]--;
				matrizjuego[posPacman[0]][posPacman[1]] = 0;
			}
		break;
		case KEY_LEFT:
			if(matrizjuego[posPacman[0]][posPacman[1]-1] != 1){
				matrizjuego[posPacman[0]][posPacman[1]] = 4;
				posPacman[1]--;
				matrizjuego[posPacman[0]][posPacman[1]] = 0;
			}
			else if(posPacman[1] == 0 && tecla == KEY_LEFT){//Verifico si está en el TELEPORT izquierdo
				posPacman[1]=29;
				matrizjuego[10][0]=4;
				matrizjuego[10][29]=0;
				printf("ejecucion",tecla);//debug{
			}
		break;
		case KEY_DOWN:
			if(matrizjuego[posPacman[0]+1][posPacman[1]] != 1){
				matrizjuego[posPacman[0]][posPacman[1]] = 4;
				posPacman[0]++;
				matrizjuego[posPacman[0]][posPacman[1]] = 0;
			}
		break;
		case KEY_RIGHT:
			if(matrizjuego[posPacman[0]][posPacman[1]+1] != 1){
				matrizjuego[posPacman[0]][posPacman[1]] = 4;
				posPacman[1]++;
				matrizjuego[posPacman[0]][posPacman[1]] = 0;
				}
			else if(posPacman[1] == 29 && tecla == KEY_RIGHT){//Verifico si está en el TELEPORT derecho
				posPacman[1]=0;
				matrizjuego[10][29]=4;
				matrizjuego[10][0]=0;
				printf("ejecucion",tecla);//debug{
				}
		break;
	}
	printf("%d,%d\n",posPacman[0],posPacman[1]);//debug
}

/*void OcultaCursor(){ // Oculta la flechita el cuadro que parpadea en el ejecutable y se pone antes de la generacion de cualquier cosa.
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}*/

void spawnFruta(int matrizjuego[20][30]){
	int frutaPosX, frutaPosY, flag=0;
	
	while(flag!=1){
		frutaPosX = rand() % (20-1 + 1);
		frutaPosY = rand() % (30-1 + 1);
		if(matrizjuego[frutaPosX][frutaPosY] == 2){
			matrizjuego[frutaPosX][frutaPosY]=3;
			flag++;
			break;
		}
	}
}

int clydeNaranja(int matrizjuego[20][30], int fantasmaPos[4][2], int aux){
	/*Fantasma Naranja:
	-Es random
	-No se puede comer los bloques, puntos, nada.
	- Tiene que salir de su casa despues de un tiempo, siendo el 1ro.*/
	int flag=0, random;
	while(flag!=1){
		random=rand() % (5-1 + 1);
		switch(random){
			case 1: //ariba
				if(matrizjuego[fantasmaPos[3][0]-1][fantasmaPos[3][1]] != 1){
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = aux; //aux
					fantasmaPos[3][0]--;
					aux = matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]]; //aux
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 9;
					flag++;
				}
			break;
			case 2: //izquierda
				if(fantasmaPos[3][1]==0){ //portal izquiero
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 4;
					fantasmaPos[3][1] = 29;
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 9;
				}
				else if(matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]-1] != 1){
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 4;
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = aux;
					fantasmaPos[3][1]--;
					aux = matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]];
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 9;
					flag++;
				}
			break;
			case 3: //abajo
				if(matrizjuego[fantasmaPos[3][0]+1][fantasmaPos[3][1]] != 1){
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 4;
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = aux;
					fantasmaPos[3][0]++;
					aux = matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]];
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 9;
					flag++;
				}
			break;
			case 4: //derecha
				if(fantasmaPos[3][1]==29){ //portal derecho
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 4;
					fantasmaPos[3][1] = 0;
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 9;
				}
				if(matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]+1] != 1){
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 4;
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = aux;
					fantasmaPos[3][1]++;
					aux = matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]];
					matrizjuego[fantasmaPos[3][0]][fantasmaPos[3][1]] = 9;
					flag++;
				}
			break;
		}
		printf("\nAux Clyde: %d\n",aux); //debug
		return aux;

	}
}

void fantasmaExit(int matrizjuego[20][30], int fantasmaPos[4][2], int fantasmaForExit){
	fantasmaPos[fantasmaForExit][0]=9;
	fantasmaPos[fantasmaForExit][1]=12;
	matrizjuego[fantasmaPos[fantasmaForExit][0]][fantasmaPos[fantasmaForExit][1]] = 9;
	matrizjuego[10][14]=4;
}

int muerte(int matrizjuego[20][30], int fantasmaPos[4][2], int posPacman[2], int ticks){
	ticks = muerteIF(matrizjuego, fantasmaPos, posPacman, 3, ticks);
	return ticks;
}

int muerteIF(int matrizjuego[20][30], int fantasmaPos[4][2], int posPacman[2], int fantasma, int ticks){
	if(fantasmaPos[fantasma][0]==posPacman[0]&&fantasmaPos[fantasma][1]==posPacman[1]){
		printf("\n------------ Game Over ------------\n"); //temp
		reinicio(matrizjuego, fantasmaPos, posPacman);
	}
	printf("Ejecucion");
	ticks=0;
	return ticks;
}

void reinicio(int matrizjuego[20][30], int fantasmaPos[4][2], int posPacman[2]){
	cargarmapa1(matrizjuego); //declara mapa 1 y pasa mapa 1 a matriz juego
	posPacman[0]=14;
	posPacman[1]=14;
	fantasmaPos[0][0]=11;
	fantasmaPos[0][1]=16;
	fantasmaPos[3][0]=9;
	fantasmaPos[3][1]=15;
	
	//fantasmaExit(matrizjuego, fantasmaPos, fantasmaForExit);
}

void declararFantasmas(int fantasmaPos[4][2]){
	fantasmaPos[3][0]=9;
	fantasmaPos[3][1]=15;
}
