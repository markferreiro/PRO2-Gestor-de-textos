#include "Conjunt_autors.hh"

bool Conjunt_autors::text_esta_seleccionat;

string Conjunt_autors::obtenir_text_seleccionat() {
	return text_seleccionat;
}

string Conjunt_autors::obtenir_autor_text_seleccionat() {
	return autor_text_seleccionat;
}

bool Conjunt_autors::classcomp::operator() (const Autor& lhs, const Autor& rhs) const
{
    return lhs.consultar_nom() < rhs.consultar_nom();
}

Conjunt_autors::Conjunt_autors() {
	autors = set<Autor, classcomp>();
}

bool Conjunt_autors::afegir_autor(string nom) {
	string referencia;
	for (int i = 0; i < nom.length(); ++i) {
		if ((nom[i] >= 'A' and nom[i] <= 'Z')) referencia.push_back(nom[i]);
	}
	Autor aux = Autor(nom, referencia);
	pair<set<Autor, classcomp>::iterator,bool> res = autors.insert(aux);
	return res.second;
}

void Conjunt_autors::eliminar_autor(string nom) {
	Autor aux = Autor (nom, "NULL");
	autors.erase(aux);
}

string Conjunt_autors::existeix_titol(string titol) {
	set<Autor, classcomp>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		Autor aux = *it;

		if (aux.existeix_titol(titol)) return aux.consultar_nom();
	}
	return "NULL";
}

Autor Conjunt_autors::obtenir_autor(string nom) {
	set<Autor, classcomp>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		if (it->consultar_nom() == nom)  {
			Autor a = *it;
			return a;
		}
	}
	Autor autor = Autor("NULL", "NULL");
	return autor;
}

Text Conjunt_autors::obtenir_text_autor(string nom, string titol) {
	set<Autor, classcomp>::iterator it = autors.begin();
	Text text = Text("NULL");
	while (it != autors.end()) {
		Autor a = *it;
		if (a.consultar_nom() == nom) {
			text = a.obtenir_text(titol);
			return text;
		}
		it++;
	}
	return text;
}

bool Conjunt_autors::triar_text (vector<string> paraules) {
	set<Autor, classcomp>::iterator it;
	bool trobat = false;
	for (it = autors.begin(); it != autors.end(); it++) {
		Autor autor = *it;
		Text text = autor.existeix_text_amb_paraules(paraules);
		//Si existeix nomes un Text
		if (text.consultar_titol() != "NULL") {
			if (trobat) {
				return false;
			}
			else {
				trobat = true;
				text_esta_seleccionat = true;
				autor_text_seleccionat = autor.consultar_nom();
				text_seleccionat = text.consultar_titol();
			}
		}
	}
	if (not trobat) {
		esborrar_text_triat();
	}
	return trobat;
}

bool Conjunt_autors::afegir_text_a_autor (Text text, string nom_autor) {
	afegir_autor(nom_autor);
	bool result = false;
	set<Autor, Conjunt_autors::classcomp>::iterator it = autors.begin();
	while(it != autors.end()) {
	    if (it->consultar_nom() == nom_autor) {
			Autor a = *it;
			bool done = a.afegir_text(text);
			if (done) {
				autors.erase(it);
				it = autors.end();
				set<Autor, Conjunt_autors::classcomp>::iterator it2 = autors.insert(it, a);
				result = true;
			} else {
				result = false;
			}
			it = autors.end();
	    } else {
			it++;
		}
	}
	return result;
}

bool Conjunt_autors::eliminar_text_de_autor (string titol, string nom_autor) {
	set<Autor, Conjunt_autors::classcomp>::iterator it = autors.begin();
	bool done = false;
	while(it != autors.end()) {
    	if (it->consultar_nom() == nom_autor) {
			Autor a = *it;
			done = a.eliminar_text(titol);
			if (done) {
				autors.erase(it);
				it = autors.end();
				it = autors.insert(it, a);
			}
    		it = autors.end();
    	} else {
			it++;
		}
	}
	return done;
}

vector<string> Conjunt_autors::tots_autors() {
	vector<string> aux(autors.size());
	int i = 0;
	set<Autor, Conjunt_autors::classcomp>::iterator it = autors.begin();
	while (it != autors.end()) {
		Autor a = *it;
		aux[i] = a.consultar_nom()  + " " + IntToString(a.nombre_de_textos()) + " " + IntToString(a.nombre_de_frases()) + " " + IntToString(a.nombre_de_paraules());
		it++;
		i++;
	}
	return aux;
}

vector<string> Conjunt_autors::tots_textos() {
	vector<string> aux(0);
	set<Autor, Conjunt_autors::classcomp>::iterator it = autors.begin();
	while (it != autors.end()) {
		Autor autor = *it;
		vector <string> textos = autor.tots_textos();
		for (int i = 0; i < textos.size(); i++) {
			string linia = autor.consultar_nom() + " \"" + textos[i] + "\"";
			aux.push_back(linia);
		}
		it++;
	}
	return aux;
}

bool Conjunt_autors::hi_ha_text_seleccionat() {
	return (autor_text_seleccionat != "" && text_seleccionat != "");
}

void Conjunt_autors::esborrar_text_triat() {
	text_esta_seleccionat = false;
	autor_text_seleccionat = "";
	text_seleccionat = "";
}

string Conjunt_autors::IntToString(int a) {
	ostringstream temp;
    temp<<a;
    return temp.str();
}
