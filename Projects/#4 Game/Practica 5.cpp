//Fundamentos de Programación - Práctica 5
//Alumnas:  Irene Pastor Suárez y Fátima Rojo del Prado
//Grupo: 1º G

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Edificio.h"
#include "Jugador.h"
#include "ListaJugadores.h"
#include "ListaEdificios.h"


using namespace std;


bool cargarEdificios(tListaEdificios& listaEdificios, tEdificio& edificio);																				//Carga el archivo "edificios.txt" y devuelve un booleano indicando si está todo bien o se necesitará cargar listas vacías
bool cargarJugadores(tListaJugadores& listaJugadores, tJugador& jugador);																				//Lo mismo para "jugadores.txt"
bool logIn (tListaJugadores listaJugadores, tJugador& jugador);																							//Devuelve un booleano si el incio de sisión ha sido correcto o no
bool contraseña(tListaJugadores listaJugadores, tJugador jugador);																						//Devuelve un booleano indicando si la contraseña es correcta o no
int menuAdmin();																																		//Menú Administrador
void opcionesAdmin(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores,  tEdificio& edificio, tJugador& jugador, int& opc);				//Opciones del menú administrador
int menuUsuario(tJugador jugador);																														//Menú Usuario
void opcionesUsuario(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores,  tEdificio& edificio, tJugador& jugador, int& opc);				//Opciones del menú usuario
void verListadoEdificio(tListaEdificios listaEdificios, tEdificio& edificio);																			//Muestra la lista entera de edificios
void nuevoEdificio(tListaEdificios& listaEdificios, tEdificio& edificio);																				//Pide los datos del nuevo edificio y verifica si todo está correcto
void borrarEdificio(tListaEdificios& listaEdificios, tEdificio& edificio);																				//Borra el edificio si existe y está disponible
void verListadoUsuarios(tListaEdificios listaEdificios, tListaJugadores listaJugadores, tEdificio edificio, tJugador& jugador);							//Muestra la lista entera de jugadores
void nuevoJugador(tListaJugadores& listaJugadores, tJugador& jugador);																					//Pide los datos del nuevo jugador y verifica si todo está correcto
void borrarJugador(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio, tJugador& jugador);							//Borra el jugador si existe y si tuviera edificios, éstos pasan a estado disponible
void ejecutarTurno(tListaEdificios listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio, tJugador& jugador);							//Ejecuta un turno y actualiza los datos de las listas 
void ordenarPorDinero(tListaJugadores& listaJugadores,  tJugador& jugador);																				//Ordena un array auxiliar de mayor a menor segun el dinero de los jugadores
void mostrarOrdenarPorDinero(tListaJugadores listaJugadores,  tJugador& jugador);																		//Muestra por pantalla el array ordenado
void ordenarPorPrestigio(tListaJugadores& listaJugadores, tJugador& jugador);																			//Ordena un array auxiliar de mayor a menor segun el prestigio de los jugadores
void mostrarOrdenarPorPrestigio(tListaJugadores listaJugadores, tJugador& jugador);																		//Muestra por pantalla el array ordenado
void verMisEdificios(tListaEdificios listaEdificios, tEdificio& edificio, tJugador jugador);															//Muestra los edificios comprados del jugador
void edificiosDisponibles(tListaEdificios listaEdificios, tEdificio& edificio);																			//Muestra los edificios disponibles
void compraEdificio(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio, tJugador& jugador);							//Compra el edificio y actualiza su estado y los edificios comprados por el jugador
void guardarListasEdificios(tListaEdificios listaEdificios, tEdificio&edificio);																		//Guarda en "edificios.txt" los datos actualizados
void guardarListasJugadores(tListaJugadores listaJugadores, tJugador& jugador);																			//Guarda en "jugadores.txt" los datos actualizados
void importarArchivosTexto(tListaJugadores& listaJugadores, tListaEdificios& listaEdificios, tJugador& jugador, tEdificio& edificio);					//Importa los archivos de texto al array
bool importarJugadores(tListaJugadores& listaJugadores, tJugador& jugador);
bool importarEdificios(tListaEdificios& listaJugadores, tEdificio& edificio);

int main() {
	tEdificio edificio;
	tJugador jugador;
	tListaJugadores listaJugadores;
	tListaEdificios listaEdificios;
	int opc;

	if(!cargarEdificios(listaEdificios, edificio) && !cargarJugadores(listaJugadores, jugador)) cout <<  "Listas cargadas.\n" << endl;
	else {										//Inicializamos los array con tamaño 10 si las listas están vacias
		listaEdificios.N = 10;
		listaJugadores.N = 10;
		listaEdificios.cont = 0;
		listaJugadores.cont = 0;
		listaEdificios.registro = new tEdificio[listaEdificios.N];
		listaJugadores.registro = new tJugador[listaJugadores.N];

		cout << "Se ha producido un error al cargar las listas, empezamos con listas vacias.\n"  << endl;
	}
	
	cout << "\nBIENVENIDO A CAMPUS VILLE" << endl;
	cout << "=========================\n" << endl;
	cout << "Escribe 'salir' o 's' para cerrar el programa..." << endl;


	while(!logIn(listaJugadores, jugador)){
		if(strcmp(jugador.usuario, "admin") == 0){
			do {
				opc = menuAdmin();
				opcionesAdmin(listaEdificios, listaJugadores, edificio, jugador, opc);
			} while(opc != 0);
		}
		else{
			do{
				opc = menuUsuario(jugador);
				opcionesUsuario(listaEdificios, listaJugadores, edificio, jugador, opc);
			} while(opc != 0);
		}
	} 

	guardarListasEdificios(listaEdificios, edificio);
	delete [] listaEdificios.registro;				//Borramos el array dinámico
	guardarListasJugadores(listaJugadores, jugador);
	delete [] listaJugadores.registro;				//Borramos el array dinámico
	cout << "\nListas guardadas." << endl;


system("pause");
}

bool cargarEdificios(tListaEdificios& listaEdificios, tEdificio& edificio){

	bool salir = false;
	listaEdificios.cont = 0;
	int centinelaEdif = -1;
	const int SIZE = sizeof(tEdificio);  //Devuelve el número de bytes que ocupa en memoria tEdificio.
	int aux;
		
	fstream edif;
	edif.open("edificios.dat", ios::in | ios::binary);			//Abrimos archivo en modo lectura y binario
	edif.read((char *) &edificio, SIZE);
	if (edif.gcount() < SIZE){			
		cout << "Fallo en la lectura. " << endl;
		salir = true;
	}
	else {
		edif.seekg(0, ios::end);
		int pos = edif.tellg();			
		int numReg = pos / SIZE;		//Calculamos el número de edificios que hay en la lista
		aux = numReg / 10;
		listaEdificios.N = (aux + 1) * 10;		//Redondeamos el tamaño del array a la siguiente décima
		listaEdificios.registro = new tEdificio[listaEdificios.N];
		listaEdificios.cont = 0;
		tEdificio edificio;
		edif.seekg(0, ios::beg);
		for(int i = 0; i < numReg; i++) {
			edif.read( (char *) &edificio, SIZE);
			listaEdificios.registro[listaEdificios.cont] = edificio;
			listaEdificios.cont++;
		}
	}
	edif.close();

	return salir;
}
bool cargarJugadores(tListaJugadores& listaJugadores, tJugador& jugador){
	
	bool salir = false;
	listaJugadores.cont = 0;
	const int SIZE = sizeof(tJugador);			//Devuelve el número de bytes que ocupa en memoria tJugador
	int aux;
		
	fstream jug;
	jug.open("jugadores.dat", ios::in | ios::binary);  //Abrimos archivo en modo lectura y binario
	jug.read((char *) &jugador, SIZE);
	if (jug.gcount() < SIZE){
		cout << "Fallo en la lectura. " << endl;
		salir = true;
	}
	else {
		jug.seekg(0, ios::end);
		int pos = jug.tellg();
		int numReg = pos / SIZE;			//Calculamos el número de jugadores que hay en la lista
		aux = numReg / 10;
		listaJugadores.N = (aux + 1) * 10;		//Redondeamos el tamaño del array a la siguiente décima
		listaJugadores.registro = new tJugador[listaJugadores.N];
		listaJugadores.cont = 0;
		jug.seekg(0, ios::beg);
		for(int i = 0; i < numReg; i++) {
			jug.read( (char *) &jugador, SIZE);
			listaJugadores.registro[listaJugadores.cont] = jugador;
			listaJugadores.cont++;
		}
	}
	return salir;
}
bool logIn(tListaJugadores listaJugadores, tJugador& jugador){

	bool usuarioEncontrado = false, encontrado = false;
	bool fin = false;

	do{
		cout << "Usuario: ";
		cin >> jugador.usuario;
		if((strcmp(jugador.usuario, "s") == 0) || (strcmp(jugador.usuario, "salir") == 0))
			fin = true;		
		else{
			if (strcmp(jugador.usuario, "admin") == 0){
				strcpy(jugador.contraseña, "12345");
				usuarioEncontrado = true;
			}
			else{ 
				for(int i = 0; i < listaJugadores.cont; i++){
					if(strcmp(jugador.usuario, listaJugadores.registro[i].usuario) == 0){
						jugador = listaJugadores.registro[i];
						usuarioEncontrado = true;
					}
				}
			}
		}
			

		if(usuarioEncontrado){
			if(contraseña(listaJugadores, jugador))
				encontrado = true;
			else {
				encontrado = false;
				usuarioEncontrado = false;
			}
		}
		
		

} while(!fin && !encontrado);


 return fin;
	
}
bool contraseña(tListaJugadores listaJugadores, tJugador jugador){

	typedef char tCadenaContraseña [40];
	tCadenaContraseña clave;
	bool claveCorrecta = false;
	int j = 3;

	while (!claveCorrecta && j != 0){
		cout << "Contraseña (" << j << " intentos): ";
		cin >> clave;
		if (!(strcmp(clave, jugador.contraseña)))
			claveCorrecta = true;
		else j--;
	}

	return claveCorrecta;
}
int menuAdmin(){

	int opc;

	cout << "\nMenu de administracion" << endl;
	cout << "======================" << endl;
	
	do{
		cout << "\n1. Ver el listado de edificios" << endl;
		cout << "2. Nuevo edificio" << endl;
		cout << "3. Borrar un edificio" << endl;
		cout << "4. Ver el listado de jugadores" << endl;
		cout << "5. Nuevo jugador" << endl;
		cout << "6. Borrar un jugador" << endl;
		cout << "7. Ejecutar un turno" << endl;
		cout << "8. Ver la clasificación" << endl;
		cout << "9. Importar datos de archivos de texto" << endl;
		cout << "0. Cerrar la sesión" << endl;
		cin >> opc;
			if (opc < 0 || opc > 9)
			cout << "Opcion no valida." << endl;
	} while(opc < 0 || opc > 9);

	return opc;

}
void opcionesAdmin(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio,tJugador& jugador, int& opc)
{
	switch (opc){
		case 0: 
			cout << "\nFin de la sesion\n" << endl;
			break;
		case 1:
			verListadoEdificio(listaEdificios, edificio);
			break;
		case 2:
			nuevoEdificio(listaEdificios, edificio);
			break;
		case 3:
			borrarEdificio(listaEdificios, edificio);
			break;
		case 4: 
			verListadoUsuarios(listaEdificios, listaJugadores, edificio, jugador);
			break;
		case 5:
			nuevoJugador(listaJugadores, jugador);
			break;
		case 6: 
			borrarJugador(listaEdificios, listaJugadores, edificio, jugador);
			break;
		case 7:
			ejecutarTurno(listaEdificios, listaJugadores, edificio, jugador);
			break;
		case 8:
			ordenarPorDinero(listaJugadores, jugador);
			mostrarOrdenarPorDinero(listaJugadores, jugador);
			break;
		case 9:
			importarArchivosTexto(listaJugadores, listaEdificios, jugador, edificio);
			break;
		}

}
int menuUsuario(tJugador jugador){
	int opc;

	cout << "\nMenu de juego" << endl;
	cout << "=============" << endl;
	cout << "Bienvenido " << jugador.usuario << ", elige una opcion:" << endl;
	do{
		cout << "\n1. Ver mis edificios" << endl;
		cout << "2. Ver los edificios disponibles" << endl;
		cout << "3. Comprar un edificio" << endl;
		cout << "4. Ver la clasificación (ordenada por dinero)" << endl;
		cout << "5. Ver la clasificación (ordenada por prestigio)" << endl;
		cout << "0. Cerrar la sesión" << endl;
		cin >> opc;
		if (opc < 0 || opc > 5)
			cout << "Opcion no valida." << endl;
	} while(opc < 0 || opc > 5);
	
	return opc;
}
void opcionesUsuario(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio,tJugador& jugador, int& opc){

		switch (opc){
		case 0:
			cout << "\nFin de la sesion\n" << endl;
			break;
		case 1:
			verMisEdificios(listaEdificios, edificio, jugador);
			break;
		case 2: 
			edificiosDisponibles(listaEdificios, edificio);
			break;
		case 3:
			compraEdificio(listaEdificios, listaJugadores, edificio, jugador);
			break;
		case 4: 
			ordenarPorDinero(listaJugadores, jugador);
			mostrarOrdenarPorDinero(listaJugadores, jugador);
			break;
		case 5:
			ordenarPorPrestigio(listaJugadores, jugador);
			mostrarOrdenarPorPrestigio(listaJugadores, jugador);
			break;
		}
	}
void verListadoEdificio(tListaEdificios listaEdificios, tEdificio& edificio){

	if(listaEdificios.cont == 0)
		cout << "No hay edificios" << endl;
	else{
		for(int i = 0; i < listaEdificios.cont; i++){
			edificio = listaEdificios.registro[i];
			mostrarEdificio(edificio);
		}
	}
}
void nuevoEdificio(tListaEdificios& listaEdificios, tEdificio& edificio){

	int posEdificio;
	
	if (listaEdificiosLlena(listaEdificios))
		listaEdificios.N = ((listaEdificios.N * 3) / 2) + 1; //Actualiza tamaño del array si está lleno

	edificio = nuevoEdificio();
	posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
	if(posEdificio != -2)
		cout << "ERROR. Codigo de edificio duplicado. " << endl;
	else {
		listaEdificios = insertarEdificio(listaEdificios, edificio);
		cout << "Edificio insertado con exito." << endl;
	}
}
void borrarEdificio(tListaEdificios& listaEdificios, tEdificio& edificio){

	cout << "Introduzca codigo del edificio a borrar: ";
	cin >> edificio.codigo;
	if(bajaEdificio(listaEdificios, edificio))
		cout << "\nEdificio borrado con exito. " << endl;
	else cout << "ERROR. El edificio no existe o no esta disponible" << endl;
}
void verListadoUsuarios(tListaEdificios listaEdificios, tListaJugadores listaJugadores, tEdificio edificio, tJugador& jugador){

	if(listaJugadores.cont == 0)
		cout << "No hay jugadores" << endl;
	else{
		for(int i = 0; i < listaJugadores.cont; i++){
			jugador = listaJugadores.registro[i];
			mostrarJugador(jugador, edificio, listaEdificios);
		}
	}
}
void nuevoJugador(tListaJugadores& listaJugadores, tJugador& jugador){

	int posJugador;

	if (listaJugadoresLlena(listaJugadores))
		listaJugadores.N = ((listaJugadores.N * 3) / 2) + 1;   //Actualiza tamaño del array si está lleno

	jugador = nuevoJugador();
	posJugador = buscarJugador(listaJugadores, jugador);
	if(posJugador != -2)
		cout << "ERROR. El usuario esta duplicado." << endl;
	else {
		listaJugadores = insertarJugador(listaJugadores, jugador);
		cout << "Nuevo jugador insertado correctamente. " << endl;
	}
}
void borrarJugador(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio, tJugador& jugador){

	cout << "Introduzca nombre del usuario que quiere borrar: ";
	cin >> jugador.usuario;
	if(bajaJugador(listaJugadores, jugador, listaEdificios, edificio))
		cout << "Jugador borrado." << endl;
	else cout << "El jugador no existe." << endl;
}
void ejecutarTurno(tListaEdificios listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio, tJugador& jugador){

	int posEdificio;
	if(listaJugadores.cont == 0)
		cout << "No existe ningun jugador" << endl;
	else{
		for(int i = 0; i < listaJugadores.cont; i++){
			jugador = listaJugadores.registro[i];
			cout << "\nProcesando jugador: " << jugador.universidad << endl;
			cout << "=====================================" << endl;
			if(jugador.contComprados != 0){
				for(int j = 0; j < jugador.contComprados; j++){
					edificio.codigo = jugador.comprados[j];
					posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
					if(posEdificio != -2){
						edificio = listaEdificios.registro[posEdificio];
						jugador.dinero = jugador.dinero + edificio.dinero;
						jugador.prestigio = jugador.prestigio + edificio.prestigio;
						listaJugadores.registro[i] = jugador;
						cout << "Edificio: " << edificio.nombre << "(D: " << edificio.dinero << ", P: " << edificio.prestigio << ")" << endl;
					}
				
				}
			}
		}
	}
}
void ordenarPorDinero(tListaJugadores& listaJugadores, tJugador& jugador){

	//Método de la burbuja

	listaJugadores.registroCopia = new tJugador[listaJugadores.N];
	for(int i = 0; i < listaJugadores.cont; i++)
		listaJugadores.registroCopia[i] = listaJugadores.registro[i];
	for(int i = 0; i <listaJugadores.cont; i++) {
		jugador = listaJugadores.registroCopia[i];
		for(int j = listaJugadores.cont - 1; j > i; j--) {
			if(listaJugadores.registroCopia[j].dinero > listaJugadores.registroCopia[j - 1].dinero) {
				jugador = listaJugadores.registroCopia[j - 1];
				listaJugadores.registroCopia[j - 1] = listaJugadores.registroCopia[j];
				listaJugadores.registroCopia[j] = jugador;
			}
		}
	}
}
void mostrarOrdenarPorDinero(tListaJugadores listaJugadores, tJugador& jugador){

	cout << "Posicion  " << "Dinero" <<"   Nombre" << endl;
	cout << "========  ======   ======" << endl;

	for(int i = 0; i < listaJugadores.cont; i++){
		jugador = listaJugadores.registroCopia[i];
		cout << right << setw(5) << i + 1  << right << setw(10)<< jugador.dinero << "    " <<left <<setw(18) << jugador.universidad << endl;
	}

	delete [] listaJugadores.registroCopia;  //Borramos el contenido del array copia
}
void ordenarPorPrestigio(tListaJugadores& listaJugadores, tJugador& jugador){

	//Método de la burbuja

	listaJugadores.registroCopia = new tJugador[listaJugadores.N];
	for(int i = 0; i < listaJugadores.cont; i++)
		listaJugadores.registroCopia[i] = listaJugadores.registro[i];
	for(int i = 0; i <listaJugadores.cont; i++) {
		jugador = listaJugadores.registroCopia[i];
		for(int j = listaJugadores.cont - 1; j > i; j--) {
			if(listaJugadores.registroCopia[j].prestigio > listaJugadores.registroCopia[j - 1].prestigio) {
				jugador = listaJugadores.registroCopia[j - 1];
				listaJugadores.registroCopia[j - 1] = listaJugadores.registroCopia[j];
				listaJugadores.registroCopia[j] = jugador;
			}
		}
	}
}
void mostrarOrdenarPorPrestigio(tListaJugadores listaJugadores, tJugador& jugador){

	cout << "Posicion  Prest.   Nombre" << endl;
	cout << "========  ======   ======" << endl;

	for(int i = 0; i < listaJugadores.cont; i++){
		jugador = listaJugadores.registroCopia[i];
		cout << right << setw(5) << i + 1  << right << setw(10)<< jugador.prestigio << "    " <<left <<setw(18) << jugador.universidad << endl;
	}

	delete [] listaJugadores.registroCopia;  //Borramos el contenido del array copia

}
void verMisEdificios(tListaEdificios listaEdificios, tEdificio& edificio, tJugador jugador){

	int posEdificio;

	cout << "\n" << jugador.universidad << " (Dinero: " << jugador.dinero << ", Prestigio: " << jugador.prestigio << ")" << endl;
	cout << "\nTienes " << jugador.contComprados << " edificio(s).\n" << endl;

	if (jugador.contComprados != 0) {

		for(int i = 0; i < jugador.contComprados; i++){
			edificio.codigo = jugador.comprados[i];
			posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
			if(posEdificio != -2){
				edificio = listaEdificios.registro[posEdificio];
				mostrarEdificio(edificio);
			}
		}
	}
}
void edificiosDisponibles(tListaEdificios listaEdificios, tEdificio& edificio){

	cout << "\nEdificios disponibles:" << endl;

	for (int i = 0; i < listaEdificios.cont; i++) {
		edificio = listaEdificios.registro[i];
		if(edificio.estado == 0)
			mostrarEdificio(edificio);
	}
}
void compraEdificio(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, tEdificio& edificio, tJugador& jugador){

	int posJugador;

	cout << "Introduzca el codigo del edificio: ";
	cin >> edificio.codigo;

	if(comprarEdificio(jugador, edificio, listaEdificios)){
		posJugador = buscarJugador(listaJugadores, jugador);
		listaJugadores.registro[posJugador] = jugador;
		cout << "Edificio comprado con éxito. " << endl;
	}
	else cout << "No ha sido posible comprar el edificio" << endl;

}
void guardarListasEdificios(tListaEdificios listaEdificios, tEdificio& edificio){

	fstream fOut;
	const int SIZE = sizeof(tEdificio);
	fOut.open("edificios.dat", ios::out | ios::binary | ios::trunc); //Abrimos el archivo vacío en modo escritura y binario

	for(int i = 0; i < listaEdificios.cont; i++){
		fOut.write( (char *) &listaEdificios.registro[i], SIZE);
	}
	fOut << "-1" << endl;
	fOut.close();
}
void guardarListasJugadores(tListaJugadores listaJugadores, tJugador& jugador){


	fstream fOut;
	const int SIZE = sizeof(tJugador);
	fOut.open("jugadores.dat", ios::out | ios::binary | ios::trunc);	 //Abrimos el archivo vacío en modo escritura y binario

	for(int i = 0; i < listaJugadores.cont; i++){
		fOut.write( (char *) &listaJugadores.registro[i], SIZE);
	}
	fOut << "X" << endl;
	fOut.close();

}
bool importarJugadores(tListaJugadores& listaJugadores, tJugador& jugador){


	bool fin = false;
	int aux;

		
	ifstream fIn;
	fIn.open("jugadores.txt");
	if(!fIn.is_open())
		fin = true;
	else {
		delete [] listaJugadores.registro; //Borramos lo que había antes en array
		fIn >> listaJugadores.cont;
		aux = listaJugadores.cont / 10;
		listaJugadores.N = (aux + 1) * 10; //Actualizamos el tamaño del array
		listaJugadores.registro = new tJugador[listaJugadores.N];
		listaJugadores.cont = 0;
		fIn >> jugador.usuario;
		while ((strcmp(jugador.usuario, "X")) && (!fin)) {
			fIn >> jugador.contraseña;
			fIn.ignore();
			fIn.getline(jugador.universidad, 50);
			fIn >> jugador.dinero;
			if (jugador.dinero < 0) {
				cout << "ERROR. Dinero de jugador ambiguo." << endl;
				fin = true;
			}
			else {
				fIn >> jugador.prestigio;
				jugador.contComprados = 0;
				fIn >> jugador.comprados[jugador.contComprados];
				while ((jugador.comprados[jugador.contComprados] != -1) && (jugador.contComprados <= MaxComprados)) {
					jugador.contComprados++;
					fIn >> jugador.comprados[jugador.contComprados];
				}
				if (jugador.comprados[jugador.contComprados] == -1) {
					listaJugadores.registro[listaJugadores.cont] = jugador;
					listaJugadores.cont++;
					fIn >> jugador.usuario;
				}
			}
		}

		fIn.close();
	}
	 return fin;
}
bool importarEdificios(tListaEdificios& listaEdificios, tEdificio& edificio){ 

	int centinelaEdif = -1;
	int aux;
	

	bool salir = false;
	ifstream edif;
	edif.open("edificios.txt");
	if (!edif.is_open())
		salir = true;
	else {
		delete [] listaEdificios.registro;			//Borramos lo que había antes en array
		edif >> listaEdificios.cont;
		aux = listaEdificios.cont / 10;
		listaEdificios.N = (aux + 1) * 10;			//Actualizamos el tamaño del array
		listaEdificios.registro = new tEdificio[listaEdificios.N];
		listaEdificios.cont = 0;
		edif >> edificio.codigo;
		while ((edificio.codigo != centinelaEdif) && (!salir)) {
			if (edificio.codigo < centinelaEdif) {
				cout << "ERROR. Codigo de edificio ambiguo." << endl;
				salir = true;
			}
			else {
				edif.ignore();
				edif.getline(edificio.nombre, 50);
				edif >> edificio.precio;
				if (edificio.precio < 0) {
					cout << "ERROR. Precio de edificio ambiguo." << endl;
					salir = true;
				}
				else {
					edif >> edificio.dinero;
					edif >> edificio.prestigio;
					edif >> edificio.estado;
					if ((edificio.estado != 0) && (edificio.estado != 1) && (edificio.estado != 2)) {
						cout << "ERROR. Estado de edificio ambiguo." << endl;
						salir = true;
					}
					else {
						listaEdificios.registro[listaEdificios.cont] = edificio;
						listaEdificios.cont++;
						edif >> edificio.codigo;
					}
				}
			} 
		}
	}

	edif.close();

	return salir;

}
void importarArchivosTexto(tListaJugadores& listaJugadores, tListaEdificios& listaEdificios, tJugador& jugador, tEdificio& edificio){


	if(!importarEdificios(listaEdificios, edificio))
		cout << "Edificios importados correctamente" << endl;
	else cout << "ERROR. No ha sido posible importar los edificios. " << endl;

	if(!importarJugadores(listaJugadores, jugador))
		cout << "Jugadores importados correctamente" << endl;
	else cout << "ERROR. No ha sido posible importar los jugadores. " << endl;

}
