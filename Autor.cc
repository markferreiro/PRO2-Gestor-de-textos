#include "Autor.hh"

bool Autor::custom_sort::operator()(const Text& a, const Text& b) const {
    return a.consultar_titol() < b.consultar_titol();
}

vector<string> Autor::split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

Autor::Autor (string nom, string referencia) {
	this->nom = nom;
	this->referencia = referencia;
}

Autor::Autor (string nom) {
	this->nom = nom;
}

string Autor::consultar_nom() const {
	return nom;
}

string Autor::consultar_referencia() {
	return referencia;
}

vector <string> Autor::consultar_titol_textos() const {
	vector<string> textos_to_return;
	set<Text, Autor::custom_sort>::iterator it = textos.begin();
	while (it != textos.end()) {
		Text text = *it;
		textos_to_return.push_back(text.consultar_titol());
		it++;
	}
	return textos_to_return;
}

set<Text, Autor::custom_sort> Autor::tots_textos() const {
	return textos;
}

int Autor::nombre_de_textos() const {
	return textos.size();
}

int Autor::nombre_de_frases() {
	int frases = 0;
	set<Text, custom_sort>::iterator it = textos.begin();
	while (it != textos.end()) {
		Text text = *it;
		frases += text.consultar_numero_frases();
		it++;
	}
	return frases;
}

int Autor::nombre_de_paraules() {
	int paraules = 0;
	set<Text, custom_sort>::iterator it = textos.begin();
	while (it != textos.end()) {
		Text text = *it;
		paraules += text.consultar_numero_paraules();
		it++;
	}
	return paraules;
}

set<Text, Autor::custom_sort>::iterator Autor::existeix_titol (string titol) const {
	for (set<Text, Autor::custom_sort>::iterator it = textos.begin() ; it != textos.end() ; it++) {
    Text text = *it;
    cout << "Comprobant " << text.consultar_titol() << "/" << titol;
		if (text.consultar_titol() == titol) return it;
	}
	return textos.end();
}

Text Autor::obtenir_text(string titol) {
  for (set<Text, Autor::custom_sort>::iterator it = textos.begin() ; it != textos.end() ; it++) {
    Text text = *it;
		if (text.consultar_titol() == titol) return text;
	}
	return Text("NULL");
}

Text Autor::existeix_text_amb_paraules (vector<string> paraules) {
	set<Text, custom_sort>::iterator it = textos.begin();
	Text aux = Text("NULL");
	//Comprova si existeix un text amb les paraules
	while (it != textos.end()) {
    Text text = *it;
    cout << "Consultant text: " << text.consultar_titol() << endl;
    bool trobades = true;
    for (int p = 0; p < paraules.size() and trobades; p++) {
      bool result2 = false;
      vector<string> par = split(nom, ' ');
      for (int i = 0 ; i < par.size() ; i++) {
        if (par[i] == paraules[p]) {
          cout << "Comprobem nom autor: " << par[i] << " - " << paraules[p] << endl;
          result2 = true;
        }
      }
      pair<int, int> result = text.existeix_paraula(paraules[p]);
      cout << "Resultat. Busqueda al titol: " << result.second << ". Busqueda al contingut: " << result2 << endl;
      if (result.second == -1 && !result2) {
          trobades = false;
      }
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
    it++;
	}
	return aux;
}

bool Autor::afegir_text (Text text) {
	//Comprova si existeix un text al p.i. amb el mateix titol que "text"
  set<Text, Autor::custom_sort>::iterator iterador_text = existeix_titol(text.consultar_titol());
	if (iterador_text == textos.end()) {
    cout << "Text " << text.consultar_titol() << " existeix..." << endl;
    textos.insert(iterador_text, text);
		return false;
	}
	else {
    //cout << "Text " << text.consultar_titol() << " afegit..." << endl;
    textos.erase(iterador_text);
    iterador_text = textos.end();
    textos.insert(iterador_text, text);
    //cout << "text insertat: " << textos.begin()->consultar_titol() << endl;
		return true;
	}
}

bool Autor::eliminar_text (string titol) {
	return (1 == textos.erase(titol));
}
