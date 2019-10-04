#pragma once
#ifndef __ESPACIOMATIC_H
#define __ESPACIOMATIC_H

#include <iostream>
#include <string>
#include "DiccionarioHash.h"
#include "diccionario.h"
#include "lista.h"
using namespace std;

typedef int Nave;
typedef string Modulo;

class ENaveExiste {};
class ENaveNoExiste {};

class EspacioMatic {
public:

	EspacioMatic() {}

	void nuevaNave(const Nave &N) {	//O(log n)
		if (_naves.contiene(N)) throw ENaveExiste();
		Diccionario<Modulo, int> modulos;
		_naves.inserta(N, modulos);
	}

	void equipaNave(const Nave &N, const Modulo &M, const int nivel) {	//O(log n)
		if (!_naves.contiene(N)) throw ENaveNoExiste();
		if (_naves.valorPara(N).contiene(M)) {
			int nivelModulo = _naves.valorPara(N).valorPara(M);
			if (nivelModulo == 0) {
				//Como nivel >= 1, restar un modulo defectuoso de la nave si lo estaba
				//Ya que damos por hecho que esta registrada en ese HashMap
				int modulosDef = _navesDefectuosas.valorPara(N);
				modulosDef--;
				if (modulosDef == 0) _navesDefectuosas.borra(N);
				else _navesDefectuosas.busca(N).setVal(modulosDef);
			}
			nivelModulo += nivel;
			_naves.busca(N).valor().busca(M).setVal(nivelModulo);
			
		}
		else {
			_naves.busca(N).valor().inserta(M, nivel);
		}

	}

	bool estropeaNave(const Nave &N, const Modulo &M) {	//O(n)
		bool result = false;
		if (_naves.contiene(N) && _naves.valorPara(N).contiene(M)) {
			int nivelModulo = _naves.valorPara(N).valorPara(M);
			if (nivelModulo > 0) {
				nivelModulo--;
				_naves.busca(N).valor().busca(M).setVal(nivelModulo);
				if (nivelModulo == 0) {
					if (_navesDefectuosas.contiene(N)) {
						int modulosDef = _navesDefectuosas.valorPara(N);
						modulosDef++;
						_navesDefectuosas.busca(N).setVal(modulosDef);
					}
					else _navesDefectuosas.inserta(N, 1);
				}
				return true;
			}
			else return false;
		}
		else return false;
	}

	Lista<Nave> navesDefectuosas() { //O(n)
		//Para que no sea O(n2) con _naves
		//Añadir _navesDefectuosas y actualizar en equipaNave/estropeaNave y solo devolver O(n)
		Lista<Nave> navesDef;
		DiccionarioHash<Nave, int>::ConstIterator cit = _navesDefectuosas.cbegin();

		while (cit != _navesDefectuosas.cend()) {
			navesDef.pon_final(cit.clave());
			cit.next();
		}

		return navesDef;
	}	


	Lista<Modulo> modulosNave(const Nave &N) { //O(n)
		Lista<Modulo> modulos;
		Diccionario<Modulo, int > ::ConstIterator cit = _naves.valorPara(N).cbegin();
		while (cit != _naves.valorPara(N).cend()) {
			modulos.pon_final(cit.clave());
			cit.next();
		}
		
		return modulos;
	}

private:
	DiccionarioHash<Nave, Diccionario<Modulo, int>> _naves;
	DiccionarioHash<Nave, int> _navesDefectuosas;
	

};
#endif __ESPACIOMATIC_H