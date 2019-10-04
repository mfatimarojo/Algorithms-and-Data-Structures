#pragma once
#ifndef __IPUD_H
#define __IPUD_H

#include <iostream>
#include <string>
#include "DiccionarioHash.h"
#include "lista.h"
using namespace std;

typedef string Song;
typedef string Artist;
typedef struct {
	Artist artist;
	int duration;
	bool inPlaylist;
	bool played;
}SongInfo;
typedef struct {} Nada;

class iPud {
public:
	iPud() {};

	void addSong(const Song &S, const Artist &A, const int D) {
		if (_songs.contiene(S)) throw "Error";
		SongInfo info;
		info.artist = A;
		info.duration = D;
		info.inPlaylist = false;
		info.played = false;
		_songs.inserta(S, info);
	}

	void addToPlaylist(const Song &S) {
		if (!_songs.contiene(S)) throw "Error";
		if (!_songs.valorPara(S).inPlaylist) {
			_playlist.pon_final(S);
			_songs.busca(S).valor().inPlaylist = true;
			_duration += _songs.valorPara(S).duration;
		}
	}


	void deleteSong(const Song &S) {
		if (_songs.contiene(S)) {
			if (_songs.valorPara(S).inPlaylist) {
				Lista<Song>::Iterator it = _playlist.begin();
				while (it != _playlist.end()) {
					if (it.elem() == S) {
						_playlist.eliminar(it);
						_duration += _songs.valorPara(S).duration;

					}
					it.next();
				}
			}
			if (_songs.valorPara(S).played) {
				Lista<Song>::Iterator it = _played.begin();
				while (it != _played.end()) {
					if (it.elem() == S) _played.eliminar(it);
					it.next();
				}
			}

			_songs.borra(S);
		}
	}

	void play() {
		if (_playlist.esVacia()) throw "Error";
		Song S = _playlist.primero();
		if (!_songs.valorPara(S).played) {
			_played.pon_ppio(S);
			_songs.busca(S).valor().played = true;
		}
	}

	const Song &current() const {
		if (_playlist.esVacia()) throw "Error";
		return _playlist.primero();
	}

	const int totalTime() const {
		return _duration;
	}
	
	Lista<Song> recent(const int N) {
		int i = 0;
		if (N >= _played.longitud()) return _played;
		Lista<Song> recents;
		Lista<Song>::ConstIterator cit = _played.cbegin();
		while (cit != _played.cend() && i < N) {
			recents.pon_final(cit.elem());
			i++;
			cit.next();
		}
		return recents;
	}

private:
	DiccionarioHash<Song, SongInfo> _songs;
	Lista<Song> _playlist; //la lista de reproduccion, sin repeticiones
	Lista<Song> _played; //las ya reproducidas, sin repeticiones
	DiccionarioHash<Song, Nada> _playlist2;
	DiccionarioHash<Song, Nada> _played2;
	int _duration;
};
#endif // !__IPUD_H
