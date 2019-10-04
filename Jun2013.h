#pragma once
#ifndef __MULTAMATIC_H
#define __MULTAMATIC_H

#include<iostream>
#include<string>
#include "DiccionarioHash.h"
#include "lista.h"
using namespace std;

typedef string Camara;
typedef struct {
	Camara ini;
	int minSecs;
} InfoCamara;

typedef string Tramo;
typedef struct {
	Camara ini;
	Camara fin;
	int minSecs;
} InfoTramo;
typedef string Matricula;
class ETramoExiste {};

class MultaMatic {
public:

	MultaMatic() {}
	
	void insertaTramo(const Tramo &T, const Camara &ini, const Camara &fin, const int secs) {
		if (_tramos.contiene(T)) throw ETramoExiste();
		InfoTramo infoT;
		infoT.ini = ini;
		infoT.fin = fin;
		infoT.minSecs = secs;
		_tramos.inserta(T, infoT);

		_camaraTramo.inserta(fin, T);

		Lista<Matricula> matriculas;
		_tramoMultas.inserta(T, matriculas);

		DiccionarioHash<Matricula, int> cochesEntrando;
		_entradaCoche.inserta(ini, cochesEntrando);
	}

	void fotoEntrada(const Camara &ini, const Matricula &M, const int secsIn) {
		//Porque ya está registrada ini y M no puede estar en dos tramos, asique lo pisa
		_entradaCoche.busca(ini).valor().inserta(M, secsIn);

		if (!_matriculaMultas.contiene(M)) {
			_matriculaMultas.inserta(M, 0);
		}
	}

	void fotoSalida(const Camara &fin, const Matricula &M, const int secsOut) {
		Tramo T = _camaraTramo.valorPara(fin);
		Camara ini = _tramos.valorPara(T).ini;
		int minSecs = _tramos.valorPara(T).minSecs;
		int secsIn = _entradaCoche.valorPara(ini).valorPara(M);
		if (secsOut - secsIn < minSecs) {
			if (_matriculaMultas.contiene(M)) {
				int multas = _matriculaMultas.valorPara(M);
				_matriculaMultas.busca(M).setVal(multas + 1);
			}
			else _matriculaMultas.inserta(M, 1);

			_tramoMultas.busca(T).valor().pon_final(M);
		}
	}

	const int multasPorMatricula(const Matricula &M) const {
		if (_matriculaMultas.contiene(M)) return _matriculaMultas.valorPara(M);
		else return 0;
	}

	const Lista<Matricula> &multasPorTramos(const Tramo &T) {
		if (_tramoMultas.contiene(T)) return _tramoMultas.valorPara(T);
		else return Lista<Matricula>();
	}

	~MultaMatic() {}
private:
	DiccionarioHash<Tramo, InfoTramo> _tramos;
	DiccionarioHash<Camara, Tramo> _camaraTramo;

	DiccionarioHash<Camara, DiccionarioHash<Matricula, int>> _entradaCoche;


	DiccionarioHash<Matricula, int> _matriculaMultas;
	DiccionarioHash<Tramo, Lista<Matricula>> _tramoMultas;
	
	
};
#endif // !__MULTAMATIC_H
