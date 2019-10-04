#pragma once
#ifndef __SMARTTV_H
#define __SMARTTV_H

#include <iostream>
#include "Diccionario.h"
using namespace std;

class SmartTV {
public:

	SmartTV();

	void grabar(const SmartTV &TV, const string &N, const Fecha &F, const Hora &H, const Minutos &T);

private:
	Diccionario<string, Grabacion> _grabadas;
	Diccionario<FechaYHora, Grabacion> _programadas;


};
#endif // !__SMARTTV_H
