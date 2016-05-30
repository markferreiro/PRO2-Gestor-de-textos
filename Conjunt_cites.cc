#include "Conjunt_cites.hh"

//Conjunt_cites::p_cita() : frases(2){ }

Conjunt_cites::Conjunt_cites() {
	cites = map<string, p_cita>();
	max_ref = map<string, int>();
}

bool Conjunt_cites::afegir_cita(int x, int y, string titol_text, string nom_autor, string referencia) {
	//Comprovar si el rang de frases es correcte ( 1 <= x <= y <= n� frases )
	//Comprovant aix� primer, en certs casos ens estalviarem la comprovaci� seg�ent.
	if ( (x >= 1 && y >= x) /*&& text->consultar_numero_frases() >= y*/) {
		if (!existeix_cita(titol_text, x, y)) {
			p_cita p = p_cita();
			p.referencia = referencia;
			p.autor = titol_text;
			p.text = nom_autor;
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
vector<Cita> Conjunt_cites::totes_cites(Conjunt_autors autors) {
	int size = cites.size();
	vector<Cita> cites_to_return(size);
	map<string, p_cita>::iterator it = cites.begin();
	for (int i = 0 ; i < size ; i++) {
		p_cita pcita = it->second;
		Text text = autors.obtenir_text_autor(pcita.autor, pcita.text);
		Cita c = Cita(pcita.autor, pcita.text, it->first, pcita.frases[0], pcita.frases[1], text.consultar_frases(pcita.frases[0], pcita.frases[1]));
		cites_to_return[i] = c;
		it++;
	}
	return cites_to_return;
}
vector<Cita> Conjunt_cites::cites_autor(string referencia, Conjunt_autors autors) {
	vector<Cita> cites_to_return;
	referencia = referencia.substr(0,referencia.size()-2);
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		p_cita p = iterator->second;
		if (p.autor == referencia) {
			Text text = autors.obtenir_text_autor(p.autor, p.text);
			Cita c = Cita(p.autor, p.text, iterator->first, p.frases[0], p.frases[1], text.consultar_frases(p.frases[0], p.frases[1]));
			cites_to_return.push_back (c);
		}
		iterator++;
	}
	return cites_to_return;
}

Cita Conjunt_cites::cita_referencia (string referencia, Conjunt_autors autors) {
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		if (iterator->first == referencia) {
			p_cita p = iterator->second;
			Text text = autors.obtenir_text_autor(p.autor, p.text);
			Cita c = Cita(p.autor, p.text, iterator->first, p.frases[0], p.frases[1], text.consultar_frases(p.frases[0], p.frases[1]));
			return c;
		}
		iterator++;
	}
	return Cita();
}
vector<Cita> Conjunt_cites::cites_text_seleccionat(string titol_text_seleccionat, Conjunt_autors autors) {
	vector<Cita> cites_to_return;
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		p_cita p = iterator->second;
		if (p.text == titol_text_seleccionat) {
			Text text = autors.obtenir_text_autor(p.autor, p.text);
			Cita c = Cita(p.autor, p.text, iterator->first, p.frases[0], p.frases[1], text.consultar_frases(p.frases[0], p.frases[1]));
			cites_to_return.push_back (c);
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

bool Conjunt_cites::existeix_cita(string titol_text, int x, int y) {
	bool resultat = false;
	map<string, p_cita>::iterator iterator = cites.begin();
	while (iterator != cites.end() && !resultat) {
		p_cita p = iterator->second;
		if (p.text == titol_text && p.frases[0] == x && p.frases[1] == y) {
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
