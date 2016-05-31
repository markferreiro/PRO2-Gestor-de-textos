#include "Conjunt_cites.hh"

//Conjunt_cites::p_cita() : frases(2){ }

Conjunt_cites::Conjunt_cites() {
	cites = map<string, Cita>();
	max_ref = map<string, int>();
}

bool Conjunt_cites::afegir_cita(int x, int y, Text text, string nom_autor, string referencia, map<int, string> frases) {
	//Comprovar si el rang de frases es correcte ( 1 <= x <= y <= n� frases )
	//Comprovant aix� primer, en certs casos ens estalviarem la comprovaci� seg�ent.
	//cout << "frases a llegir: " << x << " - " << y << endl;
	if (!existeix_cita(text.consultar_titol(), x, y)) {
		Cita cita = Cita(nom_autor, text.consultar_titol(), referencia, x, y, frases);
		/*map<int, string> frases2 = cita.obtenir_frases();
		cout << "Frases: " << endl;
		map<int, string>::iterator it = frases2.begin();
		while(it != frases2.end()) {
			cout << it->first << ": " << it->second << endl;
			it++;
		}*/
		cites.insert(pair<string, Cita>(referencia + IntToString(maxima_referencia(referencia)), cita));
		cout << "Cita afegida." << endl;
		return true;
	} /*else {
		cout << "La cita ja existeix." << endl;
	}*/
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
	map<string, Cita>::iterator it = cites.begin();
	for (int i = 0 ; i < size ; i++) {
		Cita cita = it->second;
		/*Text text = autors.obtenir_text_autor(cita.consultar_nom_autor(), cita.consultar_titol());
		pair<int, int> pair = cita.consultar_x_y();
		map<int, string> frases = text.consultar_frases(pair.first, pair.second);
		Cita c = Cita(cita.consultar_nom_autor(), cita.consultar_titol(), it->first, pair.first, pair.second, frases);*/
		cites_to_return[i] = cita;
		it++;
	}
	return cites_to_return;
}
vector<Cita> Conjunt_cites::cites_autor(string referencia, Conjunt_autors autors) {
	vector<Cita> cites_to_return;
	referencia = referencia.substr(0,referencia.size()-2);
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		Cita cita = iterator->second;
		if (cita.consultar_nom_autor() == referencia) {
			/*Text text = autors.obtenir_text_autor(cita.consultar_nom_autor(), cita.consultar_titol());
			pair<int, int> pair = cita.consultar_x_y();
			map<int, string> frases = text.consultar_frases(pair.first, pair.second);
			Cita c = Cita(cita.consultar_nom_autor(), cita.consultar_titol(), iterator->first, pair.first, pair.second, frases);*/
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
			/*Text text = autors.obtenir_text_autor(cita.consultar_nom_autor(), cita.consultar_titol());
			pair<int, int> pair = cita.consultar_x_y();
			map<int, string> frases = text.consultar_frases(pair.first, pair.second);
			Cita c = Cita(cita.consultar_nom_autor(), cita.consultar_titol(), iterator->first, pair.first, pair.second, frases);*/
			return cita;
		}
		iterator++;
	}
	return Cita();
}
vector<Cita> Conjunt_cites::cites_text_seleccionat(string titol_text_seleccionat, Conjunt_autors autors) {
	vector<Cita> cites_to_return;
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end()) {
		Cita cita = iterator->second;
		if (cita.consultar_titol() == titol_text_seleccionat) {
			/*Text text = autors.obtenir_text_autor(cita.consultar_nom_autor(), cita.consultar_titol());
			pair<int, int> pair = cita.consultar_x_y();
			map<int, string> frases = text.consultar_frases(pair.first, pair.second);
			Cita c = Cita(cita.consultar_nom_autor(), cita.consultar_titol(), iterator->first, pair.first, pair.second, frases);*/
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
	//cout << "Nova referencia maxima: " << max_ref[inicials] << endl;
	return to_return;
}

bool Conjunt_cites::existeix_cita(string titol_text, int x, int y) {
	bool resultat = false;
	map<string, Cita>::iterator iterator = cites.begin();
	while (iterator != cites.end() && !resultat) {
		Cita cita = iterator->second;
		if (cita.consultar_titol() == titol_text && cita.consultar_x_y().first == x && cita.consultar_x_y().second == y) {
			//cout << "la cita existeix!" << endl;
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
