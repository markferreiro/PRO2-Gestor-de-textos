#include "Cita.hh"
#include <utility>

Cita::Cita() {

}
Cita::Cita (string nom_autor, string titol_text, string referencia, int x, int y) {
	this->nom_autor = nom_autor;
	this->titol_text = titol_text;
	this->referencia = referencia;
	this->x = x;
	this->y = y;
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

pair<int, int> Cita::consultar_frases() {
	return make_pair(x, y);
}
