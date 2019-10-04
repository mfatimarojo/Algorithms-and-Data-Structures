#pragma once
#ifndef __NOTICIA_H
#define __NOTICIA_H

#include "diccionario.h"
#include "DiccionarioHash.h"
#include "lista.h"

typedef string Tema;
typedef string Noticia;
typedef string Termino;
typedef struct {} Nada;

class Noticia {
public:

	Noticia() {};

	void nuevaNoticia(const Tema &T, const Noticia &N) {	//O(1)
		if (!_temaNoticias.contiene(T)) {
			Lista<Noticia> noticias;
			noticias.pon_ppio(N);
			_temaNoticias.inserta(T, noticias);
		}
		else {
			_temaNoticias.busca(T).valor().pon_ppio(N);
		}
	}

	Lista<Noticia> ultimasNoticias(const Tema &T, unsigned int n) {	//O(n)
		if (_temaNoticias.contiene(T)) {
			if (n >= _temaNoticias.valorPara(T).longitud()) return _temaNoticias.valorPara(T);
			else {
				Lista<Noticia> ultimas;
				Lista<Noticia>::ConstIterator cit = _temaNoticias.valorPara(T).cbegin();
				while (cit != _temaNoticias.valorPara(T).cend()) {
					ultimas.pon_final(cit.elem());
					cit.next();
				}
				return ultimas;
			}
		}
	}

	Lista<Noticia> noticiasTermino(const Termino& t, const Tema &T, unsigned int n) {	//O(n)
		if (_terminoTemas.contiene(t) && _terminoTemas.valorPara(t).contiene(T)) {
			if (n >= _temaNoticias.valorPara(T).longitud()) return _temaNoticias.valorPara(T);
			else {
				Lista<Noticia> ultimas;
				Lista<Noticia>::ConstIterator cit = _temaNoticias.valorPara(T).cbegin();
				while (cit != _temaNoticias.valorPara(T).cend()) {
					ultimas.pon_final(cit.elem());
					cit.next();
				}
				return ultimas;
			}
		}
	}

	void nuevoTerminoBusqueda(const Termino &t, const Tema &T) {	//O(log n)
		if (!_terminoTemas.contiene(t)) {
			DiccionarioHash<Tema, Nada> temas;
			Nada nada;
			temas.inserta(T, nada);
			_terminoTemas.inserta(t, temas);
		}
	}

	void eliminaTerminoBusqueda(const Termino &t) {	//O(log n)
		if (_terminoTemas.contiene(t)) {
			_terminoTemas.borra(t);
		}
	}

	Lista<Termino> listarTerminos(const Tema &T) {	//O(1)
		Lista<Termino> terminos;
		Diccionario<Termino, DiccionarioHash<Tema, Nada>>::ConstIterator cit = _terminoTemas.cbegin();
		while (cit != _terminoTemas.cend()) {
			if (cit.valor().contiene(T)) terminos.pon_final(cit.clave());
			cit.next();
		}
	
	}

private:
	DiccionarioHash<Tema, Lista<Noticia>> _temaNoticias;
	Diccionario<Termino, DiccionarioHash<Tema, Nada>> _terminoTemas;
};
#endif // !__NOTICIA_H
