#include "Conjunt_autors.hh"



bool Conjunt_autors::classcomp::operator() (const Autor& lhs, const Autor& rhs) const
{
    return lhs.consultar_nom() < rhs.consultar_nom();
}

Conjunt_autors::Conjunt_autors() {
	autors = set<Autor, classcomp>();
}

Text* Conjunt_autors::obtenir_text_seleccionat() {
	Text t = Text();
	return &t;
}
Autor* Conjunt_autors::obtenir_autor_text_seleccionat() {
	Autor a = Autor("Antonio Lopes", "AL2");
	return &a;
}

bool Conjunt_autors::afegir_autor(string nom) {
	string referencia;
	for (int i = 0; i < nom.length(); ++i) {
		if (nom[i] >= 'A' and nom[i] <= 'Z') referencia.push_back(nom[i]);
	}
	Autor aux = Autor(nom, referencia);
	pair<set<Autor, classcomp>::iterator,bool> res = autors.insert(aux);
	return res.second;
}

void Conjunt_autors::eliminar_autor(string nom) {
	Autor aux = Autor (nom, "NULL");
	autors.erase(aux);
}

bool Conjunt_autors::existeix_titol(string titol) {
	set<Autor, classcomp>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		Autor aux = *it;
		if (aux.existeix_titol(titol)) return true;
	}
	return false;
}

Autor Conjunt_autors::obtenir_autor(string nom) {
	set<Autor, classcomp>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		Autor aux = *it;
		if (aux.consultar_nom() == nom) return aux;
	}
	Autor autor = Autor("NULL", "NULL");
	return autor;
}

set<Autor, Conjunt_autors::classcomp> Conjunt_autors::tots_autors() {
	return autors;
}

bool Conjunt_autors::triar_text (vector<string> paraules) {
	set<Autor, classcomp>::iterator it;
	bool trobat = false;

	for (it = autors.begin(); it != autors.end(); it++) {
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
