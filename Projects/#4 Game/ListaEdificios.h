#ifndef LISTAEDIFICIOS_H
#define LISTAEDIFICIOS_H

#include "Edificio.h"

typedef struct {
   tRegPtr registro;
   int cont;
   int N;  //Tamaño del array dinámico
} tListaEdificios;


bool listaEdificiosLlena(tListaEdificios listaEdificios);									//Devuelve booleano indicando si la lista esta llena (supera MaxEdificios) o no
int buscarEdificio(tListaEdificios listaEdificios, tEdificio edificio, int i, int fin);		//Indica si se ha encontrado o no el edificio.  Si lo encuentra, devuelve la posicion en la que se ha encontrado
tListaEdificios insertarEdificio(tListaEdificios& listaEdificios, tEdificio edificio);		//Inserta el edificio en la lista de edificios en la posicion indicada por orden de código.  Devuelve la lista ordenada
bool bajaEdificio(tListaEdificios& listaEdificios, tEdificio& edificio);					//Devuelve un booleano indicando si se ha borrado (si es que existía o estaba disponible)


#endif