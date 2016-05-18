#include <iostream>
#include "Cita.hh"

using namespace std;

class Cita {
	string referencia, nom_autor, titol_text;
	map<int, string> frases;
	
	Cita (string nom_autor, string titol_text, string referencia, map<int, string> frases) {
		this->nom_autor = nom_autor;
		this->titol_text = titol_text;
		this->referencia = referencia;
		this->frases = frases;
	}
	
	public string consultar_titol() {
		return titol_text;
	}
	
	public string consultar_referencia() {
		return referencia;
	}
	
	public string consultar_ autor() {
		return nom_autor;
	}
	
	public map<int, string> consultar_frases() {
		return frases;
	}
};
