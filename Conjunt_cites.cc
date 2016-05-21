#include "Conjunt_cites.hh"

//Conjunt_cites::p_cita() : frases(2){ }

Conjunt_cites::Conjunt_cites() {
	cites = map<string, p_cita>();
	max_ref = map<string, int>();
}
bool Conjunt_cites::afegir_cita(int x, int y) {
	Text *text_seleccionat = Gestor_de_textos::obtenir_text_seleccionat();
	Autor *autor_text_seleccionat = Gestor_de_textos::obtenir_autor_text_seleccionat();
	//Comprovar si el rang de frases es correcte ( 1 <= x <= y <= nº frases )
		//Comprovant aixó primer, en certs casos ens estalviarem la comprovació següent.
	if ( (x >= 1 && y >= x) && text_seleccionat->consultar_numero_frases() >= y) {
		if (!existeix_cita(text_seleccionat, x, y)) {
			string referencia = autor_text_seleccionat->consultar_referencia();
			p_cita p = p_cita();
			p.autor = autor_text_seleccionat;
			p.text = text_seleccionat;
			p.frases[0] = x;
			p.frases[1] = y;
			cites.insert(pair<string, p_cita>(referencia + IntToString(maxima_referencia(referencia)), p));
			return true;
		}
	}
	return false;
	//Comprovar si ja existeix una cita del text seleccionat amb les mateixes frases.
	//Afegir cita.
}
bool Conjunt_cites::eliminar_cita(string referencia) {
	int original_size = cites.size();
	int size = cites.erase(referencia);
	if (size < original_size) {
		return true;
	}
	return false;
}
vector<Cita> Conjunt_cites::totes_cites() {
	int size = cites.size();
	vector<Cita> cites_to_return(size);
	map<string, p_cita>::iterator it = cites.begin();
	for (int i = 0 ; i < size ; i++) {
		p_cita pcita = it->second;
		Cita c = Cita(pcita.autor, pcita.text->consultar_titol(), it->first, pcita.text->consultar_frases(pcita.frases[0], pcita.frases[1]));
		cites_to_return[i] = c; 
		it++;
	}
	return cites_to_return;
}
vector<Cita> Conjunt_cites::cites_autor(string nom_autor) {
	vector<Cita> cites_to_return;
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		p_cita p = iterator->second;
		if ((*p.autor).consultar_nom() == nom_autor) {
			Cita c = Cita((*p.autor).consultar_nom(), (*p.text).consultar_titol(), iterator->first, (*p.text).consultar_frases(p.frases[0], p.frases[1]));
			cites_to_return.push_back (c); 
		}
		iterator++;
	}
	return cites_to_return;
}
Cita Conjunt_cites::cita_referencia (string referencia) {
	vector<Cita> cites_to_return(size);
	map<string, p_cita>::iterator iterator = cites.begin();
	int i = 0;
	while (iterator != cites.end()) {
		if (iterator->first == referencia) {
			p_cita = iterator->second;
			Cita c = Cita(p_cita->autor, p_cita->text.consultar_titol(), iterator->first, p_cita->text.consultar_frases(p_cita->frases[0], p_cita->frases[1]));
			cites_to_return[i] = c;
			i++;
		}
		iterator++;
	}
	return cites_to_return;
}
vector<Cita> Conjunt_cites::cites_text_seleccionat() {
	Text text_seleccionat = Gestor_de_textos.obtenir_text_seleccionat();
	vector<Cita> cites_to_return();
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		p_cita = iterator->second;
		if (p_cita.text == &text_seleccionat) {
			Cita c = Cita(p_cita->autor, p_cita->text.consultar_titol(), iterator->first, p_cita->text.consultar_frases(p_cita->frases[0], p_cita->frases[1]));
			cites_to_return.push_back(c);
		}
		iterator++;
	}
	return cites_to_return;
}

int Conjunt_cites::maxima_referencia(string inicials) {
	map<string,int>::iterator it = max_ref.find(inicials); 
	if (it != max_ref.end()) {
		return (it->second) + 1;
	}
	return 1;
}

bool Conjunt_cites::existeix_cita(Text *text, int x, int y) {
	bool resultat = false;
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end() && !resultat) {
		p_cita = iterator->second;
		if (p_cita->text.consultar_titol() == text.consultar_titol() && p_cita.frases[0] == x && p_cita.frases[1] == y) {
			resultat = true;
		}
		iterator++;
	}
	return resultat;
}
string Conjunt_cites::IntToString(int a) {
	ostringstream temp;
    temp<<a;
    return temp.str();
}
