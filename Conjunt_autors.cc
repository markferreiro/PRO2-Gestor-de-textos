#include "Conjunt_autors.hh"

Text* Conjunt_autors::text_seleccionat;
Autor* Conjunt_autors::autor_text_seleccionat;

Text* Conjunt_autors::obtenir_text_seleccionat() {
	return text_seleccionat;
}

Autor* Conjunt_autors::obtenir_autor_text_seleccionat() {
	return autor_text_seleccionat;
}

bool Conjunt_autors::classcomp::operator() (const Autor& lhs, const Autor& rhs) const
{
    return lhs.consultar_nom() < rhs.consultar_nom();
}

Conjunt_autors::Conjunt_autors() {
	autors = set<Autor, classcomp>();
}

/*Text* Conjunt_autors::obtenir_text_seleccionat() {
	Text t = Text();
	return &t;
}
Autor* Conjunt_autors::obtenir_autor_text_seleccionat() {
	Autor a = Autor("Antonio Lopes", "AL2");
	return &a;
}*/

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

Autor* Conjunt_autors::obtenir_autor(string nom) {
	set<Autor, classcomp>::iterator it;
	for (it =  autors.begin(); it != autors.end(); it++) {
		Autor* aux = it;
		if (aux.consultar_nom() == nom) return aux;
	}
	Autor autor = Autor("NULL", "NULL");
	return &autor;
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
			if (trobat) {
				autor_text_seleccionat = "NULL";
				text_seleccionat = "NULL";
				return false;
			}
			else {
				trobat = true;
				//assignar punters
				autor_text_seleccionat = &autor;
				text_seleccionat = &text;
			}
		}
	}
	if (!trobat) {
		autor_text_seleccionat = "NULL";
		text_seleccionat = "NULL";
	}
	return trobat;
}

bool Conjunt_autors::afegir_text_a_autor (Text text, string nom_autor) {
  set<Autor, Conjunt_autors::classcomp>::iterator it = autors.begin();
  bool done = false;
  while(it != autors.end()) {
    if (*it.consultar_nom() == nom_autor) {
      *it.afegir_text(text);
      it = autors.end()-1;
      done = true;
    }
    it++;
  }
  return done;
}

bool Conjunt_autors::hi_ha_text_seleccionat() {
	return text_esta_seleccionat;
}
