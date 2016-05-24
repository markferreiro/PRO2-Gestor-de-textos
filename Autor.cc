#include "Autor.hh"

bool Autor::custom_sort::operator()(Text a, Text b) {
    return a.consultar_titol() < b.consultar_titol();
}

Autor::Autor (string nom, string referencia) {
	this->nom = nom;
	this->referencia = referencia;
}

string Autor::consultar_nom() {
	return nom;
}

string Autor::consultar_referencia() {
	return referencia;
}

set<Text> Autor::tots_textos() {
	return textos;
}

bool Autor::existeix_titol (string titol) {
	for (auto it = textos.begin() ; it != textos.end() ; it++) {
    Text text = *it;
		if (text.consultar_titol() == titol) return true;
	}
	return false;
}

Text Autor::existeix_text_amb_paraula (string paraula) {
	set<Text>::iterator it = textos.begin();
	Text aux = Text("NULL");
	//Comprova si existeix un text amb la paraula
	while (it != textos.end()) {
    Text text = *it;
    pair<int, int> result = text.existeix_paraula(paraula);
		if (result.first != -1) {
			//Comprova si s'ha trobat un text amb la paraula anteriorment
			if (aux.consultar_titol() == "NULL") {
				aux = text;
				/*aux.modificar_titol((*it).consultar_titol());
				aux.afegir_contingut((*it).consultar_contingut());*/
			}
			//Si es cert retorna un Text de titol "NULL"
			else {
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
