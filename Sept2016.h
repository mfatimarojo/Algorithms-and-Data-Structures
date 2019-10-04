#pragma once
#ifndef __PEDIDOS_H
#define __PEDIDOS_H

#include <iostream>
#include <string>
#include "DiccionarioHash.h"
#include "diccionario.h"
#include "lista.h"
#include "Fecha.h"
using namespace std;

typedef string Objeto;
typedef struct {
	float precio;
	float peso;
	int numUnidades;
} InfoObjeto;

class Pedidos {
public:
	void nuevoPedido(const Lista<Objeto> &pedido, const Fecha &fecha) {
		if (!_pedidos.contiene(fecha)) {
			_pedidos.inserta(fecha, pedido);
		}
		else {
			Diccionario<Fecha, Lista<Objeto>>::ConstIterator cit = _pedidos.cbusca(fecha);
			bool encontrado = false;
			Fecha f = cit.clave();
			while (cit != _pedidos.cend() && !encontrado) {
				f = cit.clave();
				if (!f.esMenorIgualQue(fecha)) encontrado = true;
				cit.next();
			}
			_pedidos.inserta(f.siguienteFecha(f), pedido);

 
		}
	}
private:
	DiccionarioHash<Objeto, InfoObjeto> _objetos;
	Diccionario<Fecha, Lista<Objeto>> _pedidos;

	

};
#endif // !__PEDIDOS_H
