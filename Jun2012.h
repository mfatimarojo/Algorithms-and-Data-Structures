#pragma once
#ifndef __CONSULTORIO_H
#define __CONSULTORIO_H

#include <iostream>
#include <string>
#include "DiccionarioHash.h"
#include "dcola.h"
using namespace std;

typedef string Medico;
typedef string Paciente;
typedef struct {} Nada;

class Consultorio {
public:
	Consultorio() {}

	void nuevoMedio(const Medico &M) {
		if (!_medicoPacientes.contiene(M)) {
			DCola<Paciente> pacientes;
			_medicoPacientes.inserta(M, pacientes);
		}
	}

	void pideConsulta(const Paciente &P, const Medico &M) {
		if (_medicoPacientes.contiene(M)) {
			_medicoPacientes.busca(M).valor().pon_final(P);
			if (_pacienteConsultas.contiene(P)) {
				int consultas = _pacienteConsultas.valorPara(P);
				_pacienteConsultas.busca(P).setVal(consultas + 1);
			}
			else _pacienteConsultas.inserta(P, 1);
		}
	}

	void pideConEnchufe(const Paciente &P, const Medico &M) {
		if (_medicoPacientes.contiene(M)) {
			_medicoPacientes.busca(M).valor().pon_ppio(P);
			if (_pacienteConsultas.contiene(P)) {
				int consultas = _pacienteConsultas.valorPara(P);
				_pacienteConsultas.busca(P).setVal(consultas + 1);
			}
			else _pacienteConsultas.inserta(P, 1);
		}
	}

	const bool tienePacientes(const Medico &M) const {
		if (!_medicoPacientes.contiene(M)) return false;
		else {
			if (_medicoPacientes.valorPara(M).esVacia()) return false;
			else return true;
		}
	}

	const Paciente &siguientePaciente(const Medico &M) const {
		if (_medicoPacientes.contiene(M) && !_medicoPacientes.valorPara(M).esVacia())
			return _medicoPacientes.valorPara(M).primero();
	}

	void atiendeConsulta(const Medico &M) {
		if (_medicoPacientes.contiene(M) && !_medicoPacientes.valorPara(M).esVacia()) {
			Paciente primero = _medicoPacientes.valorPara(M).primero();
			_medicoPacientes.busca(M).valor().quita_ppio();
			int consultas = _pacienteConsultas.valorPara(primero);
			if (consultas == 1) _pacienteConsultas.borra(primero);
			else _pacienteConsultas.busca(primero).setVal(consultas - 1);
		}
	}

	const int numCitas(const Paciente &P) const {
		return _pacienteConsultas.valorPara(P);
	}

	~Consultorio() {}
private:
	DiccionarioHash<Medico, DCola<Paciente>> _medicoPacientes;
	DiccionarioHash<Paciente, int> _pacienteConsultas;
};
#endif // !__CONSULTORIO_H
