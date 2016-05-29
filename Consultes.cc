#include "Consultes.hh"
#include <set>

void Consultes::processar_consulta(string consulta, Conjunt_autors autors, Conjunt_cites cites) {
	this->autors = autors;
	this->cites = cites;
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "tots") tots(consulta.substr(paraula.size()));
	else if (paraula == "info") info(consulta.substr(paraula.size()));
	else if (paraula == "frases") frases(consulta.substr(paraula.size()));
	else if (paraula == "nombre") {
		iss >> paraula;
		nombre_de(consulta.substr(paraula.size()));
	}
	else if (paraula == "textos") {
		string nom;
		iss >> paraula;
		while (paraula != "?") {
			iss >> paraula;
			nom += " " + paraula;
		}
		textos_autor(nom.substr(1, nom.size()-2));
	}
	else if (paraula == "totes") totes_cites();
	else if (paraula == "autor") autor();
	else if (paraula == "contingut") contingut();
	else if (paraula == "taula") taula_de_frequencies();
}

void Consultes::tots(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "textos") tots_textos();
	else if (paraula == "autors") tots_autors();
}
void Consultes::tots_textos() {
	//Gestor_de_textos::set<Autor, Conjunt_autors::classcomp::operator()>::iterator it = Gestor_de_textos::autors.tots_autors();

}

void Consultes::tots_autors() {

}

void Consultes::totes_cites() {

}

void Consultes::info(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "cita") {
		string referencia;
		iss >> referencia;
		info_cita(referencia.substr(1,referencia.size()-2));
	}
	else {
		if (autors.hi_ha_text_seleccionat()) {
			Text* text = autors.obtenir_text_seleccionat();
			Autor* autor = autors.obtenir_autor_text_seleccionat();
			//info text
			cout << autor->consultar_nom() << " ";
			cout << "\"" << text->consultar_titol() << "\" ";
			cout << text->consultar_numero_frases() << " " << text->consultar_numero_paraules() << endl;
			//cites associades
			cout << "Cites Associades:" << endl;
			vector<Cita> aux = cites.cites_autor(autor->consultar_referencia());
			for (int c = 0; c < aux.size(); c++) {
				cout << aux[c].consultar_referencia();
				map <int, string> frases = aux[c].consultar_frases();
				map <int, string>::iterator it = frases.begin();
				while (it != frases.end()) {
					cout << it->first << " " << it->second << endl;
					it++;
				}
			}
		}
		else cout << "error" << endl;
	}
}

void Consultes::info_cita(string referencia) {
	referencia = "";
}

void Consultes::frases(string consulta) {
	istringstream iss(consulta);
	char lletra;
	iss >> lletra;
	if (lletra >= '0' and lletra <= '9') {

	}
	else if (lletra == '\(') {

	}
	else if (lletra == '\"') {

	}
}

void Consultes::frases_text_triat(int x, int y) {
	if (autors.hi_ha_text_seleccionat()) {
		Text* text = autors.obtenir_text_seleccionat();
		map<int, string> frases = text->consultar_frases(x, y);
		map<int, string>::iterator it = frases.begin();
		while (it != frases.end()) {
			cout << it->first << " " << it->second << endl;
			it++;
		}
	}
	else cout << "error" << endl;
}

void Consultes::frases_expressio(string expressio) {
	expressio = "";
}

void Consultes::frases_sequencia(string sequencia) {
	sequencia = "";
}

void Consultes::nombre_de(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
}

void Consultes::nombre_de_frases() {

}

void Consultes::nombre_de_paraules() {

}

void Consultes::textos_autor(string nom) {
	nom = "";
}

void Consultes::autor() {

}

void Consultes::contingut() {

}

void Consultes::taula_de_frequencies() {

}
