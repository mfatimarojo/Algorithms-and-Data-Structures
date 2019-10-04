#pragma once
#ifndef __BARCOMATIC_H
#define __BARCOMATIC_H

#include <iostream>
#include "DiccionarioHash.h"
#include "lista.h"
using namespace std;

typedef string Pescador;
typedef string Especie;

typedef struct {
	Especie especie;
	int kilos;
} Pareja;

typedef struct {} Nada;

class EBodegaLlena{};

class BarcoMatic {
public:
	BarcoMatic() {};
	BarcoMatic(const int peso) {
		_capacidad = peso;
	};

	void nuevo(const int peso) const {
		new BarcoMatic(peso);
	}

	void altaPescador(const Pescador &P) {
		if (!_pescadores.contiene(P)) {
			DiccionarioHash<Especie, int> capturas;
			_pescadores.inserta(P, capturas);
			_pescadorKilos.inserta(P, 0);
		}
	}

	void nuevaCaptura(const Pescador &P, const Especie &E, const int kilos) {
		if (_pescadores.contiene(P)) {
			if (_capacidad < kilos) throw EBodegaLlena();
			if (_pescadores.valorPara(P).contiene(E)) {
				int kilosEspecie = _pescadores.valorPara(P).valorPara(E);
				kilosEspecie += kilos;
				_pescadores.busca(P).valor().busca(P).valor() = kilosEspecie;
			}
			else {
				_pescadores.busca(P).valor().inserta(E, kilos);
			}

			if (_especieKilos.contiene(E)) {
				int especieKilos = _especieKilos.valorPara(E);
				_especieKilos.busca(E).setVal(especieKilos + kilos);
			}
			else _especieKilos.inserta(E, kilos);
			_capacidad -= kilos;

			int pescadorKilos = _pescadorKilos.valorPara(P);
			_pescadorKilos.busca(P).setVal(pescadorKilos + kilos);

		}
	}

	Lista<Pareja> capturasPescador(const Pescador &P) {
		if (_pescadores.contiene(P)) {
			Lista<Pareja> resultado;
			DiccionarioHash<Especie, int>::ConstIterator cit = _pescadores.valorPara(P).cbegin();
			while (cit != _pescadores.valorPara(P).cend()) {
				if (cit.valor() > 0) {
					Pareja p;
					p.especie = cit.clave();
					p.kilos = cit.valor();
					resultado.pon_final(p);
				}
				cit.next();
			}
		}
	}

	const int kilosEspecie(const Especie &E) const {
		if (_especieKilos.contiene(E)) return _especieKilos.valorPara(E);
		else return 0;
	}

	const int kilosPescador(const Pescador &P) const {
		if (_pescadorKilos.contiene(P)) return _pescadorKilos.valorPara(P);
		else return 0;
	}

	const int bodegaRestante() const {
		return _capacidad;
	}

	~BarcoMatic() {};
private:
	int _capacidad;
	DiccionarioHash<Pescador, DiccionarioHash<Especie, int>> _pescadores;
	DiccionarioHash<Especie, int> _especieKilos;
	DiccionarioHash<Pescador, int> _pescadorKilos;

};
#endif // !__BARCOMATIC_H

