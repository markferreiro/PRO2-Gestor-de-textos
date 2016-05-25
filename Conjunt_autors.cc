#include "Conjunt_autors.hh"

bool Conjunt_autors::custom_sort::operator()(Autor a, Autor b) {
    return a.consultar_nom() < b.consultar_nom();
}


Conjunt_autors::Conjunt_autors() {
	autors = set<Autor, Conjunt_autors::custom_sort::operator()>;
}

bool Conjunt_autors::afegir_autor(string nom) {
	string referencia;
	for (int i = 0; i < nom.lenght(); ++i) {
		if (nom[i] >= 'A' and nom[i] <= 'Z') referencia.push_back(nom[i]);
	}
	Autor aux = Autor(nom, referencia);
	pair<set<Autor, Conjunt_autors::custom_sort::operator()>::iterator,bool> res = autors.insert(aux);
	return res.second;
}

void Conjunt_autors::eliminar_autor(string nom) {
	Autor aux = Autor (nom, "NULL");
	autors.erase(aux);
}

bool Conjunt_autors::existeix_titol(string titol) {
	set<Autor, Conjunt_autors::custom_sort::operator()>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		Autor aux = *it;
		if (aux.existeix_titol(titol)) return true;
	}
	return false;
}

Autor Conjunt_autors::obtenir_autor(string nom) {
	set<Autor, Conjunt_autors::custom_sort::operator()>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		Autor aux = *it;
		if (aux.consultar_nom() == nom) return aux;
	}
	Autor autor = Autor("NULL", "NULL");
	return autor;
}

set<Autor, Conjunt_autors::custom_sort::operator()> Conjunt_autors::tots_autors() {
	return autors;
}

bool Conjunt_autors::triar_text (vector<string> paraules) {
	set<Autor, Conjunt_autors::custom_sort::operator()>::iterator it;
	bool trobat = false;
	
	for (it = autors.begin(); it < autors.end(); it++) {
		Autor autor = *it;
		Text text = autor.existeix_text_amb_paraules(paraules);
		//Si existeix nomes un Text
		if (text.consultar_titol() != "NULL") {
			if (trobat) return false;
			else {
				trobat = true;
				//punters
			}
		}
	}
	return trobat;
}
