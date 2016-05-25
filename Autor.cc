#include "Autor.hh"

bool Autor::custom_sort::operator()(const Text& a, const Text& b) const {
    return a.consultar_titol() < b.consultar_titol();
}

Autor::Autor (string nom, string referencia) {
	this->nom = nom;
	this->referencia = referencia;
}

string Autor::consultar_nom() const {
	return nom;
}

string Autor::consultar_referencia() {
	return referencia;
}

set<Text, Autor::custom_sort> Autor::tots_textos() {
	return textos;
}

bool Autor::existeix_titol (string titol) const{
	for (auto it = textos.begin() ; it != textos.end() ; it++) {
    Text text = *it;
		if (text.consultar_titol() == titol) return true;
	}
	return false;
}

Text Autor::existeix_text_amb_paraules (vector<string> paraules) {
	set<Text, custom_sort>::iterator it = textos.begin();
	Text aux = Text("NULL");
	//Comprova si existeix un text amb les paraules
	while (it != textos.end()) {
	    Text text = *it;
	    bool trobades = true;
	    for (int p = 0; p < paraules.size() and trobades; p++) {
	    	pair<int, int> result = text.existeix_paraula(paraules[p]);
			if (result.first == -1) trobades = false;
		}
		if (trobades) {
			//Comprova si s'ha trobat un text amb les paraules anteriorment
			if (aux.consultar_titol() == "NULL") {
				aux = text;
				/*aux.modificar_titol((*it).consultar_titol());
				aux.afegir_contingut((*it).consultar_contingut());*/
			}
			//Si es cert retorna un Text de titol "NULL"
			else {
				aux.modificar_titol("NULL");
				return aux;
			}
		}
	}
	return aux;
}

bool Autor::afegir_text (Text text) {
	//Comprova si existeix un text al p.i. amb el mateix titol que "text"
	if (existeix_titol(text.consultar_titol())) {
		return false;
	}
	else {
		textos.insert(text);
		return true;
	}
}

bool Autor::eliminar_text (string titol) {
	return (1 == textos.erase(titol));
}
