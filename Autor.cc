#include "Autor.hh"

bool Autor::operator()(Text a, Text b) {
    return a.consultar_titol() < b.consultar_titol();
}

bool Autor::operator()(Text a, Text b) {
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
		if ((*it).consultar_titol() == titol) return true;
	}
	return false;
}

Text Autor::existeix_text_amb_paraula (string paraula) {
	set<Text>::iterator it = textos.begin();
	Text("NULL") aux;
	//Comprova si existeix un text amb la paraula
	while (it != textos.end()) {
		if ((*it).existeix_paraula(paraula)) {
			//Comprova si s'ha trobat un text amb la paraula anteriorment
			if (aux.consultar_titol() == "NULL") {
				aux = (*it);
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
	if (textos.existeix_titol(text.consultar_titol())) {
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
