#pragma once
#ifndef __FALTAS_H
#define __FALTAS_H

#include <iostream>
#include <string>
#include "DiccionarioHash.h"
#include "diccionario.h"
using namespace std;

typedef string Asignatura;
typedef string Alumno;

class Faltas {
public:

	void añadirAlumno(const Alumno &A) {
		DiccionarioHash<Asignatura, DiccionarioHash<Alumno, int>>::Iterator it = _listaFaltas.begin();

		while (it != _listaFaltas.end()) {
			it.valor().inserta(A, 0);
			it.next();
		}

		_alumnoFaltas.inserta(A, 0);
	}

	void añadirFalta(const Alumno &A, const Asignatura &AS) {
		
		if (_listaFaltas.contiene(AS) && _listaFaltas.valorPara(AS).contiene(A)) {
			int faltas = _listaFaltas.valorPara(AS).valorPara(A);
			faltas++;
			_listaFaltas.busca(AS).valor().busca(A).setVal(faltas);
			_alumnoFaltas.busca(A).setVal(faltas);
		}
		
	}

	void añadirAsignatura(const Asignatura &AS) {
		DiccionarioHash<Alumno, int> alumnos;
		alumnos = _listaFaltas.cbegin().valor();

		DiccionarioHash<Alumno, int>::Iterator it = alumnos.begin();
		while (it != alumnos.end()) {
			it.setVal(0);
			it.next();
		}

		_listaFaltas.inserta(AS, alumnos);
	}

	const int totalFaltas(const Alumno &A) const {
		return _alumnoFaltas.valorPara(A);
	}

	Lista<Alumno> noFaltas() {
		Lista<Alumno> alumnos;
		Diccionario<Alumno, int>::ConstIterator cit = _alumnoFaltas.cbegin();

		while (cit != _alumnoFaltas.cend()) {
			if (cit.valor() == 0) alumnos.pon_final(cit.clave());
			cit.next();
		}

		return alumnos;
	}

	void añadirAlumno2(const Alumno &A) {
		_alumnos.inserta(A, 0);
		_alumnosCero.inserta(A, 0);
		DiccionarioHash<Asignatura, DiccionarioHash<Alumno, int>>::Iterator it = _listaFaltas.begin();
		while (it != _listaFaltas.end()) {
			it.valor().inserta(A, 0);
			it.next();
		}

		_alumnoFaltas.inserta(A, 0);
	}

	void añadirFalta2( Alumno &A, const Asignatura &AS) {

		if (_listaFaltas.contiene(AS) && _listaFaltas.valorPara(AS).contiene(A)) {
			int faltas = _listaFaltas.valorPara(AS).valorPara(A);
			faltas++;
			_listaFaltas.busca(AS).valor().busca(A).setVal(faltas);
			_alumnoFaltas.busca(A).setVal(faltas);
		}

	}

	void añadirAsignatura2(const Asignatura &AS) {
		_listaFaltas.inserta(AS, _alumnos);
	}

	const int totalFaltas2(const Alumno &A) const {
		return _alumnoFaltas.valorPara(A);
	}

	Lista<Alumno> noFaltas2() {
		Lista<Alumno> alumnos;
		Diccionario<Alumno, int>::ConstIterator cit = _alumnoFaltas.cbegin();

		while (cit != _alumnoFaltas.cend()) {
			if (cit.valor() == 0) alumnos.pon_final(cit.clave());
			cit.next();
		}

		return alumnos;
	}



private:
	DiccionarioHash<Asignatura, DiccionarioHash<Alumno, int>> _listaFaltas;
	Diccionario<Alumno, int> _alumnoFaltas;
	DiccionarioHash<Alumno, int> _alumnos;
	Diccionario<Alumno, int> _alumnosCero;
};
#endif // !__FALTAS_H
