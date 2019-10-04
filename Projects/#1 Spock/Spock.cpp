#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

typedef enum {piedra, papel, tijeras, lagarto, spock} tJugada;
tJugada humano, pc;

typedef enum {N, S, E, O, n, s, o, e} tVoltear;
tVoltear cardinal;




void bienvenido();
bool apodoEncontrado(string& apodo, string& usuarios, string& contraseña, bool& jugar);
void usuarioRegistrado(string contraseña, bool& jugar);
void registroContraseña(string apodo, bool& jugar);
void login(bool& jugar);
int menu();
void opcionesMenu(int& opc, string nombre, tJugada& humano, tJugada& pc, int& empateSpock, int& ganarSpock, int& perderSpock, int& partidasSpock, int& partidasDado, int& ganarDado, int& perderDado, tVoltear& cardinal);
void lectura(string nombre);
void bienvenidoSpock();
string eleccionHumanoSpock (tJugada& humano);
string eleccionPcSpock (tJugada& pc);
void condicionesSpock(tJugada& humano, tJugada& pc, int& empateSpokc, int& ganarSpock, int& perderSpock, int& partidasSpock);
void Spock(tJugada& humano, tJugada& pc, int& empateSpock,int& ganarSpock, int& perderSpock, int& partidasSpock);
void bienvenidoDado();
int turnoInicial();
void iniciarDado(int& num1, int& num2, int& num3, int& cont);
void dibujoDado(int& num1, int& num2, int& num3, int& cont);
void turnoUsuario(string nombre, string& direccion, int& num1, int& num2, int& num3, int& cont, int& perderDado, int& partidasDado, tVoltear& cardinal);
string eleccionDireccionUsuario();
void condicionesDireccionUsuario(string& direccion, string& nombre, tVoltear& cardinal);
void turnoMaquina(tVoltear& cardinal, int& num1, int& num2, int& num3, int& cont, int& ganarDado, int& partidasDado);
void voltearDado(string nombre, int& partidasDado, int& ganarDado, int& perderDado, tVoltear& cardinal);
void condicionesVoltear(tVoltear& cardinal, int& num1, int& num2, int& num3, int& cont);
void juego(int& turno, string nombre, int& partidasDado, int& ganarDado, int& perderDado, tVoltear& cardinal);
void salir(int partidasDado, int ganarDado, int perderDado, int partidasSpock, int ganarSpock, int perderSpock, int empateSpock);


int main(){

	string nombre;																																			//Declaraciones
	int ganarDado = 0, perderDado = 0, partidasDado = 0;
	int empateSpock = 0, ganarSpock = 0, perderSpock = 0, partidasSpock = 0;
	bool jugar = false;
	int opc;
	
	bienvenido();																																			//Llamada a funcion tipo void
	login(jugar);																																			//Llamada a funcion tipo void que contiene todo lo necesario acceder o no al juego
		
	if(jugar){																																				//Si después del login, jugar = true, accedemos al portal de juegos
		do {																
			opc = menu();																																	//Llamada a funcion tipo int, que devuelve un entero y se lo asignamos a la variable opc
			opcionesMenu(opc, nombre, humano, pc, empateSpock, ganarSpock, perderSpock, partidasSpock, partidasDado, ganarDado, perderDado, cardinal);		//Llamada a funcion tipo void que contiene las distintas opciones del menú
		} while (opc != 0);																																	//Mientras que opc != 0, volvemos a mostrar el menú para elegir opción.
	}
	
	system("pause");
}
void bienvenido() {
	cout << "-------------------------------------" << endl;
	cout << "   BIENVENIDO AL PORTAL DEL JUEGOS   " << endl;
	cout << "-------------------------------------" << endl;
}
void login(bool& jugar){

string apodo, usuarios, contraseña, copia, clave;
bool encontrado = false;

	cout << "Por favor, introduce tu apodo: ";
	cin >> apodo;
	
	if (apodoEncontrado(apodo, usuarios, contraseña, jugar))																								//Llamada a funcion tipo bool, que devuelve un booleano, si el booleano es true
		usuarioRegistrado(contraseña, jugar);																												//(usuario encontrado), accedemos a pedir la contraseña mediante esta funcion tipo void
	else if(!apodoEncontrado(apodo, usuarios, contraseña,jugar))
		registroContraseña(apodo, jugar);																													//Si usuario no encontrado accedemos a registrarlo mediante esta funcion tipo void.
}
bool apodoEncontrado(string& apodo, string& usuarios, string& contraseña, bool& jugar) {
	bool encontrado = false;

	ifstream registros;																																		//Abrimos el fichero que contiene la lista de usuarios.
	registros.open("registro.txt");
	if (!registros.is_open()) {
		cout << "ERROR. Archivo no encontrado." << endl;
		jugar = false;
	}

	else if (registros.is_open()){																															//Si encontramos el archivo, leemos su contenido y buscamos el usuario.
		getline(registros, usuarios);
		while (!encontrado && usuarios != "XXX") {
			getline(registros, contraseña);
			if (usuarios == apodo) {																														//Si encontramos el usuario, cerramos el fichero.
				cout << "Usuario ya registrado." << endl;
				encontrado = true;
			}
			else getline(registros, usuarios);																												//Si no, seguimos leyendo mientras que no le encontremos ni llegemos al centinela.
		}
		registros.close();																																	//Cerramos el fichero.
	}

	return (usuarios == apodo);																																//Devolvemos true si usuarios == apodo
}
void usuarioRegistrado(string contraseña, bool& jugar){
	//Si el usuario se ha encontrado en el archivo, accedemos a pedir la contraseña sin necesidad de añadir un nuevo registro.
	int intentos = 0;
	string clave;

	cout << "Contrasena: ";
	cin >> clave;
	if (contraseña != clave) {
		intentos++;
		do{
			cout << "Contrasena incorrecta, le quedan " << 3 - intentos++ << " intentos. Pruebe de nuevo: ";
			cin >> clave;
			if (contraseña == clave) jugar = true;																									//Si la clave es correcta accedemos al portal de juegos.
		}while ((contraseña != clave) && (intentos < 3));
		if ((contraseña != clave) && (intentos == 3)) {
				cout << "Lo siento, has fallado demasiadas veces." << endl;
				cout << "Hasta pronto!" << endl;
				jugar = false;																														//Si la clave no es correcta tras 3 intentos, finalizamos ejecución.
		}
	}
	else if (contraseña == clave) jugar = true;																										//Si la clave es correcta desde un principio, accedemos al portal de juegos.
}
void registroContraseña(string apodo, bool& jugar){
	//Si el usuario introducido no se ha encontrado en el fichero, accedemos a registrar el usuario junto con su nueva contraseña
	string usuarios, copia, clave;
	cout << "Elija una contrasena: ";
	cin >> clave;

	ifstream registros;
	ofstream temporales;
	registros.open("registro.txt");
	temporales.open("temporal.txt");												//Abrimos los ficheros de entrada y salida y copiamos
	getline(registros, usuarios);													//el contenido de registro en el temporal para no perderlo.
	while (usuarios != "XXX") {
		temporales << usuarios << endl;
		getline(registros, usuarios);
	}
	temporales << apodo << endl;													//Añadimos el nuevo usuario con su correspondiente contraseña.
	temporales << clave << endl;
	temporales << "XXX" << endl;
	registros.close();
	temporales.close();																//Una vez copiado, cerramos los ficheros.
			
	ifstream temp;																	//Ahora el archivo de entrada será el temporal
	ofstream reg;																	//y el archivo de salida será el registro.
	temp.open("temporal.txt");
	reg.open("registro.txt");
	while (!temp.eof()) {															//Leemos el todo el contenido del temporal
		getline(temp, copia);														//y lo copiamos en registro.
		reg << copia << endl;
	}
	temp.close();																	//Cerramos los archivos.
	reg.close();
	jugar = true;																	//Accedemos al portal de juegos.
}
int menu(){
	//Nos muestra el menú, y nos pide la opción a elegir, la cual será devuelta como tipo int.
	int opcion;
	cout << endl;
	cout << "Elige lo que quieres hacer: " << endl;
	cout << "1. Ver instrucciones de Rock-Paper-Scissors-Lizard-Spock" << endl;
	cout << "2. Jugar a Rock-Paper-Scissors-Lizard-Spock" << endl;
	cout << "3. Ver instrucciones de Voltear el dado" << endl;
	cout << "4. Jugar a Voltear el dado" << endl;
	cout << "0. Salir" << endl;
	cout << "Opcion: " ;
	cin >> opcion;
	
	return opcion;
}
void opcionesMenu(int& opc, string nombre, tJugada& humano, tJugada& pc, int& empateSpock, int& ganarSpock, int& perderSpock, int& partidasSpock, int& partidasDado, int& ganarDado, int& perderDado, tVoltear& cardinal){
	//Contiene los distintos casos de la opción elegida en el menú.
	if ((opc < 0) || (opc > 4))
		cout << "Opcion incorrecta. Intentelo de nuevo." << endl;

	switch(opc){
		case 1:																										//1. Ver instrucciones de Rock-Paper-Scissors-Lizzard-Spock
			nombre = "reglasSpock.txt";																				//Asignamos la variable nombre el archivo de texto al que queremos acceder
			lectura (nombre);																						//Llamada a funcion void que da paso a la lectura del archivo.
			break;
		case 2:																										//2. Jugar a Rock-Paper-Scissors-Lizzard-Spock
			Spock(humano, pc, empateSpock, ganarSpock, perderSpock, partidasSpock);									//Llamada a funcion void que da paso al juego.
			break;
		case 3:																										//3. Ver instrucciones de Voltear el dado
			nombre = "reglasDado.txt";																				//Realizamos los mismos pasos que en el caso 1 pero con otro archivo.
			lectura (nombre);
			break;
		case 4:																										//4. Jugar a Voltear el dado
			voltearDado(nombre, partidasDado, ganarDado, perderDado, cardinal);										//Llamada a funcion void que da paso al juego.
			break;
		case 0:																										//0. Salir
			salir(partidasDado, ganarDado, perderDado, partidasSpock, ganarSpock, perderSpock, empateSpock);		//Llamada a funcion void que antes de salir nos muestra nuestras estadísticas tras el juego
			break;
		}
}
void lectura(string nombre){
	//Nos da acceso al fichero "nombre" que queramos para acceder a su lectura
	string reglas;
	ifstream fichero;										
	fichero.open(nombre.c_str());	
	if (!fichero.is_open())
		cout << "No se encontro el fichero." << endl;
	do{
		cout << reglas << endl;
		getline (fichero, reglas);
	}while (!fichero.eof());
	fichero.close();
}
void bienvenidoSpock() {
	cout << "\n---------------------------------------" << endl;
	cout << "          BIENVENIDO AL JUEGO          " << endl;
	cout << "   ROCK-PAPER-SCISSORS-LIZZARD-SPOCK   " << endl;
	cout << "---------------------------------------" << endl;
}
string eleccionHumanoSpock(tJugada& humano){
	//Función tipo string que nos devuelve cadenaHumano, y ademas asigna a cada cadenaHumano su corresponiende en tJugada
	string cadenaHumano;
	do{
		cout << "\nElija elemento (piedra, papel, tijeras, lagarto o spock): ";
		cin >> cadenaHumano;												
		if (cadenaHumano == "piedra")									
			humano = piedra;												
		else if (cadenaHumano == "papel")
			humano = papel;
		else if (cadenaHumano == "tijeras")
			humano = tijeras;
		else if (cadenaHumano == "lagarto")
			humano = lagarto;
		else if (cadenaHumano == "spock")
			humano = spock;
		else cout << "Elemento desconocido. Intentelo de nuevo." << endl;				
	} while (cadenaHumano != "piedra" && cadenaHumano != "papel" && cadenaHumano != "tijeras" && cadenaHumano != "lagarto" && cadenaHumano != "spock");																			

	return cadenaHumano;
}
string eleccionPcSpock(tJugada& pc){
	//Función tipo string que devuelve cadenaPc,  Realiza la jugada aleatoria del PC y le asigna su corresponiete tJugada
	string cadenaPc;
	srand(time(NULL));				
	pc = (tJugada)((rand() % 5) + 1);												
	switch (pc) {
		case 1:
			pc = piedra;
			cadenaPc = "piedra";
			break;
		case 2:
			pc = papel;
			cadenaPc = "papel";
			break;
		case 3:
			pc = tijeras;
			cadenaPc = "tijeras";
			break;
		case 4:
			pc = lagarto;
			cadenaPc = "lagarto";
			break;
		case 5:
			pc = spock;
			cadenaPc = "spock";
			break;
	}
	
	return cadenaPc;
}
void condicionesSpock(tJugada& humano, tJugada& pc, int& empateSpock, int& ganarSpock, int& perderSpock, int& partidasSpock){
	//Funcion tipo void que contiene todas las condiciones de las jugadas en Spock
	if (humano == pc) {															
		cout << "Empate!" << endl;
		empateSpock++;
		partidasSpock++;
	}
	else if ((humano == piedra) && ((pc == tijeras) || (pc == lagarto))) {
		cout << "Tu ganas!" << endl;
		ganarSpock++;
		partidasSpock++;
	}	
	else if ((humano == papel) && ((pc = piedra) || (pc == spock))) {
		cout << "Tu ganas!" << endl;
		ganarSpock++;
		partidasSpock++;
	}
	else if ((humano == tijeras) && ((pc == papel) || (pc == lagarto))) {
		cout << "Tu ganas!" << endl;
		ganarSpock++;
		partidasSpock++;
	}	
	else if ((humano == lagarto) && ((pc == papel) || (pc == spock))) {
		cout << "Tu ganas!" << endl;
		ganarSpock++;
		partidasSpock++;
	}	
	else if ((humano == spock) && ((pc == piedra) || (pc == tijeras))) {
		cout << "Tu ganas!" << endl;
		ganarSpock++;
		partidasSpock++;
		}
	else {
		cout << "Gano yo!" << endl;
		perderSpock++;
		partidasSpock++;
	}
}
void Spock(tJugada& humano, tJugada& pc, int& empateSpock, int& ganarSpock, int& perderSpock, int& partidasSpock){
	//Función tipo void que contiene toda la base del juego con los subprogramas requeridos
	bienvenidoSpock();	
	string elementoHumano, elementoPc;
	elementoHumano = eleccionHumanoSpock(humano);
	elementoPc = eleccionPcSpock(pc);

	cout << "Mi eleccion: " << elementoPc << endl;							
	cout << "Tu eleccion: " << elementoHumano << endl;						
	cout <<	"........." << endl;
	condicionesSpock(humano, pc, empateSpock, ganarSpock, perderSpock, partidasSpock);
}
void bienvenidoDado() {
	cout << "\n-------------------------" << endl;
	cout << "   BIENVENIDO AL JUEGO   " << endl;
	cout << "     VOLTEAR EL DADO     " << endl;
	cout << "-------------------------" << endl;
}
int turnoInicial() {
	//Función tipo int que elige al azar de quién será el turno inicial y nos devuelve dicho int
	int turnoIni;
	srand(time(NULL));															
	turnoIni = ((rand() % 2) + 1);
	return turnoIni;
}
void iniciarDado(int& num1, int& num2, int& num3, int& cont){
	//Función tipo void que realiza la tirada inicial aleatoria del dado
	int aleatorio;
	srand(time(NULL));															
	aleatorio = ((rand() % 6) + 1);
	switch (aleatorio){
		case 1:
			num1 = 1;
			num2 = 2;
			num3 = 4;
			break;
		case 2:
			num1 = 2;
			num2 = 6;
			num3 = 4;
			break;
		case 3:
			num1 = 3;
			num2 = 2;
			num3 = 1;
			break;
		case 4:
			num1 = 4;
			num2 = 2;
			num3 = 6;
			break;
		case 5:
			num1 = 5;
			num2 = 1;
			num3 = 4;
			break;
		case 6:
			num1 = 6;
			num2 = 2;
			num3 = 3;
			break;
	}
	cont += num1;
	dibujoDado(num1, num2, num3, cont);								//Llamada a la función tipo void que contiene el dibujo del dado
}
void dibujoDado(int& num1, int& num2, int& num3, int& cont){
	//Función tipo void que dibuja el dado y nos muestra el contador
	cout << "   " << "_"<< endl;
	cout << " / " <<  num1  << " / " << "|"  << endl; 
	cout << " - -" << "|" << " " << num2 << "|" << "             Contador: " << cont << endl;
	cout << "| "  << num3 << " |" << " /" <<  endl;
	cout << " " << "- -" << endl;
	cout << endl;
}
void turnoUsuario(string nombre, string& direccion, int& num1, int& num2, int& num3, int& cont, int& perderDado, int& partidasDado, tVoltear& cardinal){
	//Función tipo void para el turno del usuario
	int temp;
	cout << "\nTe toca elegir jugada." << endl;
	do{
		direccion = eleccionDireccionUsuario();							//Llamada a función tipo string que asigna el mismo a la variable dirección
		condicionesDireccionUsuario(direccion, nombre, cardinal);		//Llamada a función tipo void que contiene las condicones de dicha elección
	} while ((direccion != "N") && (direccion != "n") && (direccion != "S") && (direccion != "s") && (direccion != "E") && (direccion != "e") && (direccion != "O") && (direccion != "o") && (direccion != "0"));

	condicionesVoltear(cardinal, num1, num2, num3, cont);				//Llamada a funcion tipo void, dependiendo de la elección del usuario, así se volteará el dado
	
	if (direccion != "0") {
		dibujoDado(num1, num2, num3, cont);
	}
	if (cont >= 50){
		cout << "HAS PERDIDO!!!" << endl;
		perderDado++;
		partidasDado++;
	}
}
string eleccionDireccionUsuario() {
	//Función tipo string que pide la dirección al usuario y la devuelve
	string direction;
	cout << "\nIndica el giro que quires hacer mediante un punto cardinal (N, S, O, E)" << endl;
	cout << "Si quieres ver las instrucciones pulsa 1. Si quieres terminar pulsa 0. " << endl;
	cout << "Eleccion: ";
	cin >> direction;

	return direction;
}
void condicionesDireccionUsuario(string& direccion, string& nombre, tVoltear& cardinal) {
	//Función tipo void que contiene las condiciones de la elección del usuario
	if (direccion == "1"){
			nombre = "reglasDado.txt";
			lectura (nombre);
		}
		else if ((direccion == "N") || (direccion == "n")) cardinal = N;
		else if ((direccion == "S") || (direccion == "s")) cardinal = S;
		else if ((direccion == "E") || (direccion == "e")) cardinal = E;
		else if ((direccion == "O") || (direccion == "o")) cardinal = O;
		else if ((direccion != "N") && (direccion != "n") && (direccion != "S") && (direccion != "s") && (direccion != "E") && (direccion != "e") && (direccion != "O") && (direccion != "o") && (direccion != "0") && (direccion != "1")) cout << "ERROR! Introduce la inicial del punto cardinal." << endl;
}
void condicionesVoltear(tVoltear& cardinal, int& num1, int& num2, int& num3, int& cont){
	//Función tipo void que contiene los distintos movimientos del dados según la dirección elegida 
	int temp;
	
	if (cardinal == O){
		temp = num1;
		num1 = num2;
		num2 = 7 - temp;
	}
	else if (cardinal == S){
		temp = num1;
		num1 = 7 - num3;
		num3 = temp;
	}
	else if (cardinal == N){
		temp = num1;
		num1 = num3;
		num3 = 7 - temp;
	}
	else if (cardinal == E){
		temp = num1;
		num1 = 7 - num2;
		num2 = temp;
	}
	cont += num1;
}
void turnoMaquina(tVoltear& cardinal, int& num1, int& num2, int& num3, int& cont, int& ganarDado, int& partidasDado){
	//Función tipo void del turno de la máquina
	int temp;
	string cadenaMaquina;

	cout << "\nMe toca a mi." << endl;
	/*if (((num1 = 1) && (num2 = 3) && (num3 = 2)) || ((num1 = 2) && (num2 = 4) && (num3 = 1)) || ((num1 = 3) && (num2 = 2) && (num3 = 1)) || ((num1 = 4) && (num2 = 5) && (num3 = 1)) || ((num1 = 5) && (num2 = 3) && (num3 = 1)) || ((num1 = 6) && (num2 = 4) && (num3 = 2))) {
		cardinal == N;
		cadenaMaquina = "Norte";
	}
	else if (((num1 = 1) && (num2 = 4) && (num3 = 5)) || ((num1 = 2) && (num2 = 3) && (num3 = 6)) || ((num1 = 3) && (num2 = 5) && (num3 = 6)) || ((num1 = 4) && (num2 = 2) && (num3 = 6)) || ((num1 = 5) && (num2 = 4) && (num3 = 6)) || ((num1 = 6) && (num2 = 3) && (num3 = 5))) {
		cardinal == S;
		cadenaMaquina = "Sur";
	}
	else if (((num1 = 1) && (num2 = 5) && (num3 = 3)) || ((num1 = 2) && (num2 = 6) && (num3 = 4)) || ((num1 = 3) && (num2 = 6) && (num3 = 2)) || ((num1 = 4) && (num2 = 6) && (num3 = 5)) || ((num1 = 5) && (num2 = 6) && (num3 = 3)) || ((num1 = 6) && (num2 = 5) && (num3 = 4))) {
		cardinal == E;
		cadenaMaquina = "Este";
	}
	else if (((num1 = 1) && (num2 = 2) && (num3 = 4)) || ((num1 = 2) && (num2 = 1) && (num3 = 3)) || ((num1 = 3) && (num2 = 1) && (num3 = 5)) || ((num1 = 4) && (num2 = 1) && (num3 = 2)) || ((num1 = 5) && (num2 = 1) && (num3 = 4)) || ((num1 = 6) && (num2 = 2) && (num3 = 3))) {
		cardinal == O;
		cadenaMaquina = "Oeste";
	}*/

		
	srand(time(NULL));													//La máquina elegirá aleatoriamente la dirección del dado
	cardinal = (tVoltear)((rand() % 4) + 1);
	switch (cardinal){
		case 1:
			cardinal = N;
			cadenaMaquina = "Norte";
			break;
		case 2:
			cardinal = S;
			cadenaMaquina = "Sur";
			break;
		case 3:
			cardinal = E;
			cadenaMaquina = "Este";
			break;
		case 4:
			cardinal = O;
			cadenaMaquina = "Oeste";
			break;
	}
	
	cout << "Mi jugada es " << cadenaMaquina << endl;
	condicionesVoltear(cardinal, num1, num2, num3, cont);
	dibujoDado(num1, num2, num3, cont);

	if (cont >= 50){
		cout << "HAS GANADO!!!" << endl;
		ganarDado++;
		partidasDado++;
	}		
}
void voltearDado(string nombre, int& partidasDado, int& ganarDado, int& perderDado, tVoltear& cardinal){
	
	int turno;
	bienvenidoDado();
	
	cout << "\nCOMIENZA EL JUEGO... Quien empieza?" << endl;
	turno = turnoInicial();																				//Llamada a la funcion tipo int que nos devuelve el entero y se lo asignamos a la variable turno
	
	juego(turno, nombre, partidasDado, ganarDado, perderDado, cardinal);								//Llamada a la funcion tipo void que contiene todo el juego
}

void juego(int& turno, string nombre, int& partidasDado, int& ganarDado, int& perderDado, tVoltear& cardinal){
	//Función tipo void que contiene toda la base del juego con los subprogramas requeridos
	int num1 = 0, num2 = 0, num3 = 0, cont = 0;
	string direccion;

	if (turno == 1){
		cout << "Empiezo yo." << endl; // maquina
		cout << "Mi tirada ha sido:" << endl;	
		iniciarDado(num1, num2, num3, cont);
		while ((cont < 50) && (direccion != "0")){
			turnoUsuario(nombre, direccion, num1, num2, num3, cont, perderDado, partidasDado, cardinal);
			if ((cont < 50) && (direccion != "0"))
				turnoMaquina(cardinal, num1, num2, num3, cont, ganarDado, partidasDado);
		}
	}
	if (turno == 2) {
		cout << "Empiezas tu" << endl; // yo
		cout << "Tu tirada ha sido" << endl;
		iniciarDado(num1, num2, num3, cont);
		while (cont < 50 && direccion != "0"){
			turnoMaquina(cardinal, num1, num2, num3, cont, ganarDado, partidasDado);
			if (cont < 50 && direccion != "0")
				turnoUsuario(nombre, direccion, num1, num2, num3, cont, perderDado, partidasDado, cardinal);
		}
	}

	cont = 0;
}
void salir(int partidasDado, int ganarDado, int perderDado, int partidasSpock, int ganarSpock, int perderSpock, int empateSpock){	
	//Función tipo void que muestra al usuario sus estadísticas al salir del juego
	cout << endl;
	cout << "Numero de partidas jugadas a Voltear el dado: " << partidasDado << endl;
	cout << "Numero de partidas ganadas: " << ganarDado << endl;
	cout << "Numero de partidas perdidas: " << perderDado << endl;
	cout << "Hasta pronto!" << endl;		cout << endl;
	cout << "Numero de partidas jugadas a Rock-Paper-Scissors-Lizard-Spock: " << partidasSpock << endl;
	cout << "Numero de partidas ganadas: " << ganarSpock << endl;
	cout << "Numero de partidas empatadas: " << empateSpock << endl;
	cout << "Numero de partidas perdidas: " << perderSpock << endl;
}
