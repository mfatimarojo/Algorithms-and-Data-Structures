//Fundamentos de Programación - Práctica 3
//Alumnas:  Irene Pastor Suárez y Fátima Rojo del Prado
//Grupo:  1º G

#include <iostream>
#include <fstream>			
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

const int DIM = 20;
const int MAXBOLAS = 10;
const int LIBRE = -1;
const int PARED = -2;
const int HUECO = -3;

typedef int tTablero[DIM][DIM];						
typedef int tBolasMarcadas[MAXBOLAS];
typedef struct {
	
	tTablero tablero;
	tBolasMarcadas bolasMarcadas;
	int numBolas;
	int jugadas;
	string nombreFich;
	
} tLaberinto;


string elegirLaberinto();
bool validarNumBolas (tLaberinto& laberinto);
bool validarFronteras(const tTablero& tablero);
bool validarInteriorLaberinto (tLaberinto laberinto, tTablero tablero);
bool esBola(tTablero tablero, int i, int j);
bool Marcadas(tLaberinto laberinto, tTablero tablero, tBolasMarcadas bolasMarcadas);
void cargarTablero (tTablero& tablero, ifstream& fIn);
bool cargarLaberinto(tLaberinto& laberinto, tTablero& tablero);
void mostrarTablero(tLaberinto& laberinto, tTablero& tablero);
char menu();
void nuevoJuego(tLaberinto& laberinto, tTablero& tablero, bool& fin, tBolasMarcadas bolasMarcadas);
bool inclinarIzqda(tLaberinto& laberinto, tTablero& tablero);
bool inclinarDcha(tLaberinto& laberinto, tTablero& tablero);
bool inclinarArriba(tLaberinto& laberinto, tTablero& tablero);
bool inclinarAbajo(tLaberinto& laberinto, tTablero& tablero);
void reiniciarTablero(tLaberinto& laberinto, tTablero& tablero);
bool finJuego(tLaberinto& laberinto, tTablero& tablero, int i, int j);
void setColor(unsigned int color);


string elegirLaberinto(){

	string nombre, archivo;
	
	cout << "Nombre del laberinto (Intro-> archivo por defecto 'lab1.txt'): ";
	getline(cin, nombre);

	if (nombre == "\0") archivo = "lab1.txt";
	else archivo = nombre;
	
	return archivo;
}
bool validarNumBolas (tLaberinto& laberinto) {

	bool cargarLab = false;
	
	if ((laberinto.numBolas > MAXBOLAS || (0 >= laberinto.numBolas))) {
		cout << "ERROR. El numero de bolas no es correcto." << endl;
		cargarLab = false;
	}
	else cargarLab = true;

	return cargarLab;
}
bool validarFronteras(const tTablero& tablero){
	bool fronteras = true;

	for (int fila = 0; fila < DIM; fila++){
		if ( (tablero[fila][0] != PARED) || (tablero[fila][DIM - 1] != PARED) || (tablero[0][fila] != PARED) || (tablero[DIM - 1][fila] != PARED)) {
			fronteras = false;
		}
	}
	return fronteras;
}
bool validarInteriorLaberinto (tLaberinto laberinto, tTablero tablero) {
	
	bool interior = false;

	for (int i = 1; i < DIM - 1; i++)
		for (int j = 1; j < DIM - 1; j++)
			if ((-3 > tablero[i][j]) || (laberinto.numBolas <= tablero[i][j])) interior = true;	

	return interior;

}
bool esBola(tTablero tablero, int i, int j){
	
	bool esBola = false;

	if ((tablero[i][j] >=0) && (tablero[i][j] <= 9)) esBola = true;
	else esBola = false;

	return esBola;
}
bool Marcadas(tLaberinto laberinto, tTablero tablero, tBolasMarcadas bolasMarcadas){

	int numBola;
	bool marcadas = false;
	int contBolas = 0;

	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if(esBola(tablero, i, j)){
				numBola = tablero[i][j];
				contBolas++;
				if(bolasMarcadas[numBola] != numBola)
					bolasMarcadas[numBola] = numBola;
				else if (bolasMarcadas[numBola] == numBola){
						cout << "ERROR. Se ha detectado repeticion de bolas." << endl;
						marcadas = true;
				}
				else if (laberinto.numBolas != contBolas){
					cout << "ERROR. El numero de bolas no corresponde con el indicado." << endl;
					marcadas = true;
				}
			}

	for(int i = 0; i < MAXBOLAS; i++)				//Vaciamos el array para volver a usarlo más tarde.
		bolasMarcadas[i] = ' ';
	
	return marcadas;			
}
void cargarTablero (tTablero& tablero, ifstream& fIn) {
	
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			fIn >> tablero[i][j];
}
bool cargarLaberinto(tLaberinto& laberinto, tTablero& tablero){

	bool cargar = true;

	ifstream fIn;
	fIn.open(laberinto.nombreFich.c_str());
	
	if (!fIn.is_open()) {
		cout << "ERROR. No se pudo acceder al archivo." << endl;
		cargar = false;
	}
	else {
		fIn >> laberinto.numBolas;
		if (!(validarNumBolas(laberinto))) cargar = false;
		else {
			cargarTablero(tablero, fIn);
			cargar = true;
		}
	}

	return cargar;
}
void mostrarTablero(tLaberinto& laberinto, tTablero& tablero){

	cout << setw(60) << laberinto.jugadas << endl;
	for(int i = 0; i < DIM; i++) {
		for(int j = 0; j < DIM; j++){
			if (tablero[i][j] == LIBRE) cout << "   ";
			else if (tablero[i][j] == PARED) cout << char(219) << char(219) << char(219);
			else if (tablero[i][j] == HUECO) cout << char(176) << char(176) << char(176);
			else if (tablero[i][j] == 'fin') {
				setColor(10);
				cout << char(176) << char(176) << char(176);
				setColor(7);
			}
			else cout << " " << tablero[i][j] << " ";
		}
		cout << endl;
	}
}
char menu() {
	
	char opc;

	do {
		cout << endl;
		cout << "a - Inclinar hacia la izquierda			" << char(24) << endl;
		cout << "d - Inclinar hacia la derecha			w" << endl;
		cout << "w - Inclinar hacia arriba" << endl;		
		cout << "x - Inclinar hacia abajo		" << char (27) << " a	      d " << char(26) << endl;									
		cout << "5 - Reiniciar el tablero" << endl;
		cout << "6 - Cargar nuevo tablero			x" << endl;
		cout << "0 - Salir					" << char(25) << endl;
		cout << "Opcion: ";
		cin >> opc;
		if ( (opc != 'd') && (opc != 'w') && (opc != 'a') && (opc != 'x') && (opc != '5') && (opc != '6') && (opc != '0')) 
			cout << "Opcion no valida." << endl;

	} while ( (opc != 'd') && (opc != 'w') && (opc != 'a') && (opc != 'x') && (opc != '5') && (opc != '6') && (opc != '0')) ;

	return opc;
}
void nuevoJuego(tLaberinto& laberinto, tTablero& tablero, bool& fin, tBolasMarcadas bolasMarcadas){

	laberinto.nombreFich = elegirLaberinto();

	if(cargarLaberinto(laberinto, tablero)){
		if (!validarFronteras(tablero)){
			cout << "Fronteras no validas" << endl;
			fin = true;
		}
		else {
			if(validarInteriorLaberinto (laberinto, tablero)) {
				cout << "Error al validar el tablero." << endl;
				fin = true;
			}
			else {
				if(Marcadas(laberinto, tablero, bolasMarcadas))
					fin = true;
				else mostrarTablero(laberinto, tablero);
			}
		}
	}
	else fin = true;
}
void reiniciarTablero(tLaberinto& laberinto, tTablero& tablero){

	laberinto.jugadas = 0;

	if(cargarLaberinto(laberinto, tablero))
		mostrarTablero(laberinto, tablero);

}
bool inclinarIzqda(tLaberinto& laberinto, tTablero& tablero){

	int c;
	int tmp, col, fila;
	bool terminar = false;

	for(int i = 1; i < DIM - 1; i++){
		for(int j = 1; j < DIM - 1; j++){
			 if(esBola(tablero, i, j)){
				 c = -1;
				 while((tablero[i][j + c] != PARED) && (tablero[i][j + c] < 0)){
					 if(tablero[i][j + c] == HUECO){
						 tmp = tablero[i][j + c + 1];
						 tablero[i][j + c + 1] = LIBRE;
						 c--;
						if((tablero[i][j + c] != PARED) && (tablero[i][j + c] < 0)){
							tablero[i][j + c] = tmp;
							tablero[i][j + c + 1] = HUECO;
							c--;
						}
						else {
							fila = i;
							col = j + c + 1;
							terminar = finJuego(laberinto, tablero, fila, col);
						}
					 }
					 else if (tablero[i][j + c] == LIBRE){
					 	tablero[i][j + c] = tablero[i][j + c + 1];
						tablero[i][j + c + 1] = LIBRE;
						c--;
					}
					
				 }
			}
		}
	}
	if(!terminar){
		laberinto.jugadas++;
		mostrarTablero(laberinto, tablero);
	}
	return terminar;
}
bool inclinarDcha(tLaberinto& laberinto, tTablero& tablero){

	int c;
	int tmp, col, fila;
	bool terminar = false;

	for(int i = 1; i < DIM - 1; i++){
		for(int j = DIM - 1; j > 0; j--){
			if(esBola(tablero, i, j)){
				c = 1;
				while((tablero[i][j + c] != PARED) && (tablero[i][j + c] < 0)){
					if(tablero[i][j + c] == HUECO){
						tmp = tablero[i][j + c - 1];
						tablero[i][j + c - 1] = LIBRE;
						c++;
						if((tablero[i][j + c] != PARED) && (tablero[i][j + c] < 0)){
							tablero[i][j + c] = tmp;
							tablero[i][j + c - 1] = HUECO;
							c++;
						}
						else {
							fila = i;
							col = j + c - 1;
							terminar = finJuego(laberinto, tablero, fila, col);
						}
					}
					else if(tablero[i][j + c] == LIBRE){
						tablero[i][j + c] = tablero[i][j + c - 1];
						tablero[i][j + c - 1] = LIBRE;
						c++;
					}
				}
			}
		}
	}
	if(!terminar){
		laberinto.jugadas++;
		mostrarTablero(laberinto, tablero);
	}
	return terminar;
}
bool inclinarArriba(tLaberinto& laberinto, tTablero& tablero){

	int c;
	int tmp, col, fila;
	bool terminar = false;

	for(int i = 1; i < DIM - 1; i++){
		for(int j = 1; j < DIM - 1; j++){
			 if(esBola(tablero, i, j)){
				 c = -1;
				 while((tablero[i + c][j] != PARED) && (tablero[i + c][j] < 0)){
					 if (tablero[i + c][j] == HUECO){
						 tmp = tablero[i + c + 1][j];
						 tablero[i + c + 1][j] = LIBRE;
						 c--;
						 if((tablero[i + c][j] != PARED) && (tablero[i + c][j] < 0)){
							tablero[i + c][j] = tmp;
							tablero[i + c + 1][j] = HUECO;
							c--;
						 }
						else {
							fila = i + c + 1;
							col = j;
							terminar = finJuego(laberinto, tablero, fila, col);
						}
					 }
					else if (tablero[i + c][j] == LIBRE){
						tablero[i + c][j] = tablero[i + c + 1][j];
						tablero[i + c + 1][j] = LIBRE;
						c--;
					 }
				 }
			}
		}
	}
	if(!terminar){
		laberinto.jugadas++;
		mostrarTablero(laberinto, tablero);
	}
	return terminar;
}
bool inclinarAbajo(tLaberinto& laberinto, tTablero& tablero){

	int c;
	int tmp, col, fila;
	bool terminar = false;

	for(int i = DIM - 1; i > 0; i--){
		for(int j = 1; j < DIM - 1; j++){
			 if(esBola(tablero, i, j)){
				 c = 1;
				 while((tablero[i + c][j] != PARED) && (tablero[i + c][j] < 0)){
					if (tablero[i + c][j] == HUECO){
						tmp = tablero[i + c - 1][j];
						tablero[i + c - 1][j] = LIBRE;
						c++;
						if((tablero[i + c][j] != PARED) && (tablero[i + c][j] < 0)){
							tablero[i + c][j] = tmp;
							tablero[i + c - 1][j] = HUECO;
							c++;
						}
						else {
							fila = i + c - 1;
							col = j;
							terminar = finJuego(laberinto, tablero, fila, col);
						}
					}
					else if (tablero[i + c][j] == LIBRE){
						tablero[i + c][j] = tablero[i + c - 1][j];
						tablero[i + c - 1][j] = LIBRE;
						c++;
					}
				}
			}
		}
	}
	if(!terminar){
		laberinto.jugadas++;
		mostrarTablero(laberinto, tablero);
	}
	return terminar;
}
bool finJuego(tLaberinto& laberinto, tTablero& tablero, int i, int j){

	bool end = false;

	laberinto.jugadas++;
	tablero[i][j] = 'fin';
	mostrarTablero(laberinto, tablero);
	cout << "Felicidades!" << endl;
	cout << "Movimientos invertidos: " << laberinto.jugadas << endl;
	end = true;

	return end;

}
void setColor(unsigned int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

int main(){
	
	char opc;
	bool fin = false;
	tLaberinto laberinto;
	tTablero tablero;
	tBolasMarcadas bolasMarcadas;
	char tmp = 0;
	laberinto.jugadas = 0;


	nuevoJuego(laberinto, tablero, fin, bolasMarcadas);

	if(!fin){

		do {
			opc = menu();
			if((opc == tmp) && (tmp != 0))
				mostrarTablero(laberinto, tablero);
			else{
				switch (opc){
				case '0': 
					break;
				case 'd':
					fin = inclinarDcha(laberinto, tablero);
					break;
				case 'w': 
					fin = inclinarArriba(laberinto, tablero);
					break;
				case 'a': 
					fin = inclinarIzqda(laberinto, tablero);
					break;
				case 'x': 
					fin = inclinarAbajo(laberinto, tablero);
					break;
				case '5':
					reiniciarTablero(laberinto, tablero);
					break;
				case '6': 
					cin.ignore();
					laberinto.jugadas = 0;
					nuevoJuego(laberinto, tablero, fin, bolasMarcadas);
					break;
				}
			}
			tmp = opc;
		} while ((opc != '0') && (!fin));
	}

	system("pause");
}
