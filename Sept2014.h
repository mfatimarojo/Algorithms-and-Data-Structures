#ifndef __CIUDADMATIC_H
#define __CIUDADMATIC_H

#include <iostream>
#include "DiccionarioHash.h"
#include "lista.h"
using namespace std;

typedef string Tipo;
typedef struct {
	int coste;
	int impuestos;
	int calidadBase; //Máximo de turnos sin reparar (decrementar)

} InfoTipo;
typedef string Edificio;
typedef struct {
	Tipo tipo;
	int calidad;
	int impuestosGenerados;
} InfoEdificio;

class CiudadMatic {
public:
	CiudadMatic(const int fondo) { //O(1)
		_fondo = fondo;
	};

	void nuevoTipo(const Tipo &T, const int coste, const int impuestos, const int calidadBase) { //O(1)
		if (!_tipos.contiene(T)) {
			InfoTipo info;
			info.coste = coste;
			info.impuestos = impuestos;
			info.calidadBase = calidadBase;
			_tipos.inserta(T, info);
			Lista<Edificio> edificios;
			_tipoEdificios.inserta(T, edificios);
		}
	}

	void insertaEdificio(const Edificio &E, const Tipo &T) {	//O(1)
		if (_tipos.contiene(T) && (_fondo >= _tipos.valorPara(T).coste)) {
			InfoEdificio info;
			info.tipo = T;
			info.calidad = _tipos.valorPara(T).calidadBase;
			info.impuestosGenerados = 0;
			_edificios.inserta(E, info);
			_fondo -= _tipos.valorPara(T).coste;
			_tipoEdificios.busca(T).valor().pon_final(E);
		}
	}

	void reparaEdificio(const Edificio &E) {	//O(1)
		if (_edificios.contiene(E)) {
			Tipo tipo = _edificios.valorPara(E).tipo;
			int coste = (_tipos.valorPara(tipo).coste)*(0.1);
			if (_fondo >= coste) {
				_edificios.busca(E).valor().calidad = _tipos.valorPara(tipo).calidadBase;
				_fondo -= coste;
			}
		}
	}

	int finTurno() {	//O(n) ó O(n2)
		int impuestosGenerados = 0;
		DiccionarioHash<Edificio, InfoEdificio>::Iterator it = _edificios.begin();
		while (it != _edificios.end()) {
			impuestosGenerados += _tipos.valorPara(it.valor().tipo).impuestos;
			it.valor().impuestosGenerados += _tipos.valorPara(it.valor().tipo).impuestos;
			it.valor().calidad--;
			if (it.valor().calidad == 0) {
				_edificios.borra(it.clave());
				//borrar de lista O(n2)
			}
			it.next();
		}
		return _fondo + impuestosGenerados;
	}

	const Lista<Edificio> &listaEdificiosCte(const Tipo &T) const {	//O(1) 
		return _tipoEdificios.valorPara(T);
	}

	Lista<Edificio> listaEdificios(const Tipo &T)  {	//O(n)
		Lista<Edificio> edificios;
		Lista<Edificio> edificosTipo = _tipoEdificios.valorPara(T);
		Lista<Edificio>::ConstIterator cit = edificosTipo.cbegin();
		while (cit != edificosTipo.cend()) {
			if (_edificios.contiene(cit.elem())) edificios.pon_final(cit.elem());
			cit.next();
		}
		return edificios;
	}


private:
	int _fondo;
	DiccionarioHash<Tipo, InfoTipo> _tipos;
	DiccionarioHash<Edificio, InfoEdificio> _edificios;
	DiccionarioHash<Tipo, Lista<Edificio>> _tipoEdificios;
};

#endif // !__CIUDADMATIC_H
