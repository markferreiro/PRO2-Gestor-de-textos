#include "Cita.hh"
#include <utility>

Cita::Cita() {
	this->nom_autor = "NULL";
	this->titol_text = "NULL";
	this->referencia = "NULL";
	this->x = -1;
	this->y = -1;
}
Cita::Cita (string nom_autor, string titol_text, string referencia, int x, int y, map<int, string> frases) {
	this->nom_autor = nom_autor;
	this->titol_text = titol_text;
	this->referencia = referencia;
	this->x = x;
	this->y = y;
	this->frases = frases;
}

string Cita::consultar_titol() {
	return titol_text;
}

string Cita::consultar_referencia() {
	return referencia;
}

string Cita::consultar_nom_autor() {
	return nom_autor;
}

pair<int, int> Cita::consultar_x_y() {
	return make_pair(x, y);
}

map<int, string> Cita::obtenir_frases() {
	return frases;
}
