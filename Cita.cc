#include "Cita.hh"
	
Cita::Cita (string nom_autor, string titol_text, string referencia, map<int, string> frases) {
	this->nom_autor = nom_autor;
	this->titol_text = titol_text;
	this->referencia = referencia;
	this->frases = frases;
}

string Cita::consultar_titol() {
	return titol_text;
}

string Cita::consultar_referencia() {
	return referencia;
}

string Cita::consultar_ autor() {
	return nom_autor;
}

map<int, string> Cita::consultar_frases() {
	return frases;
}
