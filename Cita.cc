#include "Cita.hh"

Cita::Cita() {
	
}
Cita::Cita (string nom_autor, string titol_text, string referencia, pair<int, int> interval, map<int, string> frases) {
	this->nom_autor = nom_autor;
	this->titol_text = titol_text;
	this->referencia = referencia;
	this->interval = interval;
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

int Cita::consultar_x() {
	return interval->first;
}

int Cita::consultar_y() {
	return interval->second;
}

map<int, string> Cita::consultar_frases() {
	return frases;
}
