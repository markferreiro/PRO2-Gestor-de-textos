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

		if (aux.existeix_titol(titol)/* != aux.tots_textos().end()*/) return aux.consultar_nom();
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
			//cout << "titol: " << text.consultar_titol() << endl;
			return text;
		}
		it++;
	}
	//cout << "titol text: " << text.consultar_titol() << endl;
	return text;
}

set<Autor, Conjunt_autors::classcomp> Conjunt_autors::tots_autors() {
	return autors;
}

bool Conjunt_autors::triar_text (vector<string> paraules) {
	set<Autor, classcomp>::iterator it;
	bool trobat = false;
	//cout << "arribem aqui... sabent que autors(" << autors.size() << ")" << endl;
	for (it = autors.begin(); it != autors.end(); it++) {
		Autor autor = *it;
		//cout << "Comprovem textos de: " << autor.consultar_nom() << "(" << autor.nombre_de_textos() << ")" << endl;
		Text text = autor.existeix_text_amb_paraules(paraules);
		//cout << "titol text: " << text.consultar_titol() << endl;
		//Si existeix nomes un Text
		if (text.consultar_titol() != "NULL") {
			if (trobat) {
				return false;
			}
			else {
				trobat = true;
				//assignar punters
				autor_text_seleccionat = autor.consultar_nom();
				text_seleccionat = text.consultar_titol();
			}
		}
	}
	//cout << "autor: " << autor_text_seleccionat << " / titol: " << text_seleccionat << endl;
	if (not trobat) {
		autor_text_seleccionat = "";
		text_seleccionat = "";
	}
	text_esta_seleccionat = trobat;
	//else cout << "TRIAT" << endl;
	return trobat;
}

bool Conjunt_autors::afegir_text_a_autor (Text text, string nom_autor) {
	afegir_autor(nom_autor);
	bool result = false;
	//cout << "insert autor result: " << result << endl;
	set<Autor, Conjunt_autors::classcomp>::iterator it = autors.begin();
	while(it != autors.end()) {
	    if (it->consultar_nom() == nom_autor) {
			Autor a = *it;
			//cout << "intentem afegir 2...: " << it->consultar_nom() << "/" << nom_autor << "||" << a.nombre_de_textos() << endl;
			bool done = a.afegir_text(text);
			if (done) {
				//cout << "inserted! Autor textos...(" << a.nombre_de_textos() << "): ";
				//cout <<  "eliminem autor: " << it->consultar_nom() << " / " << it->tots_textos().size() <<  endl;
				autors.erase(it);
				//cout << "estem afegint un autor amb " << a.tots_textos().size() << " textos..." << endl;
				it = autors.end();
				set<Autor, Conjunt_autors::classcomp>::iterator it2 = autors.insert(it, a);
				result = true;
				//cout <<  "autor inserted: " << it2->consultar_nom() << " / " << it2->tots_textos().size() <<  endl;
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
    		//done = (*it).eliminar_text(titol); //aixo igual que l'anterior
    		it = autors.end();
    	} else {
			it++;
		}
	}
	return done;
}

bool Conjunt_autors::hi_ha_text_seleccionat() {
	return (autor_text_seleccionat != "" && text_seleccionat != "");
}

void Conjunt_autors::esborrar_text_triat() {
	autor_text_seleccionat = "";
	text_seleccionat = "";
}
