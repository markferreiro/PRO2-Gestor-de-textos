#include "Conjunt_cites.hh"


Conjunt_cites::Conjunt_cites() {
	cites = map<string, Cita>();
	max_ref = map<string, int>();
}

bool Conjunt_cites::afegir_cita(int x, int y, string titol_text, string nom_autor, string referencia, map<int, string> frases) {
	if (!existeix_cita(titol_text, x, y)) {
		Cita cita = Cita(nom_autor, titol_text, referencia + IntToString(maxima_referencia(referencia)), x, y, frases);
		cites.insert(pair<string, Cita>(cita.consultar_referencia(), cita));
		return true;
	}
	return false;
}
bool Conjunt_cites::eliminar_cita(string referencia) {
	int original_size = cites.size();
	int elementa_eliminats = cites.erase(referencia);
	if (elementa_eliminats == 0) {
		return false;
	}
	return true;
}

vector<Cita> Conjunt_cites::totes_cites(Conjunt_autors autors) {
	int size = cites.size();
	vector<Cita> cites_to_return(size);
	map<string, Cita>::iterator it = cites.begin();
	for (int i = 0 ; i < size ; i++) {
		Cita cita = it->second;
		cites_to_return[i] = cita;
		it++;
	}
	return cites_to_return;
}
vector<Cita> Conjunt_cites::cites_autor(string nom, Conjunt_autors autors) {
	vector<Cita> cites_to_return;
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		Cita cita = iterator->second;
		if (cita.consultar_nom_autor() == nom) {
			cites_to_return.push_back (cita);
		}
		iterator++;
	}
	return cites_to_return;
}

Cita Conjunt_cites::cita_referencia (string referencia, Conjunt_autors autors) {
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		if (iterator->first == referencia) {
			Cita cita = iterator->second;
			return cita;
		}
		iterator++;
	}
	return Cita();
}
vector<Cita> Conjunt_cites::cites_text_seleccionat(string titol_text_seleccionat, Conjunt_autors& autors) {
	vector<Cita> cites_to_return;
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		Cita cita = iterator->second;
		if (cita.consultar_titol() == titol_text_seleccionat) {
			cites_to_return.push_back (cita);
		}
		iterator++;
	}
	return cites_to_return;
}

int Conjunt_cites::maxima_referencia(string inicials) {
	map<string,int>::iterator it = max_ref.find(inicials);
	int to_return = 1;
	if (it != max_ref.end()) {
		to_return = (it->second) + 1;
	}
	max_ref[inicials] = to_return;
	return to_return;
}

bool Conjunt_cites::existeix_cita(string titol_text, int x, int y) {
	bool resultat = false;
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end() && !resultat) {
		Cita cita = iterator->second;
		if (cita.consultar_titol() == titol_text && cita.consultar_x_y().first == x && cita.consultar_x_y().second == y) {
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
