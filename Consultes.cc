#include "Consultes.hh"
#include <set>

bool Consultes::classcomp::operator() (const Autor& lhs, const Autor& rhs) const
{
    return lhs.consultar_nom() < rhs.consultar_nom();
}
bool Consultes::classcomp::operator() (const Text& lhs, const Text& rhs) const
{
    return lhs.consultar_titol() < rhs.consultar_titol();
}

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
		consulta.substr(paraula.size());
		iss >> paraula; //llegeix de
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
	set<Autor, Consultes::classcomp>::iterator it_autors = autors.tots_autors().begin();
	while (it_autors != autors.tots_autors().end()) {
		Autor autor = *it_autors;
		set<Text, Autor::custom_sort> textos = autor.tots_textos();
		set<Text, Autor::custom_sort>::iterator it_textos = textos.end();
		while (it_textos != textos.end()) {
			Text text = *it_textos;
			cout << autor.consultar_nom() << " ";
			cout << "\"" << text.consultar_titol() << "\" " << endl;
			it_textos++;
		}
		it_autors++;
	}
}

void Consultes::tots_autors() {
	set<Autor, classcomp>::iterator it = autors.tots_autors().begin();
	while (it != autors.tots_autors().end()) {
		Autor autor = *it;
		cout << autor.consultar_nom() << " " << autor.nombre_de_textos();
		cout << " " << autor.nombre_de_frases() << " " << autor.nombre_de_paraules() << endl;
		it++;
	}
}

void Consultes::totes_cites() {
	vector<Cita> aux = cites.totes_cites();
	for (int i = 0; i < aux.size(); i++) {
		cout << aux[i].consultar_referencia() << endl;
		map<int, string> frases = aux[i].consultar_frases();
		map<int, string>::iterator it = frases.begin();
		while (it != frases.end()) {
			cout << it->first << " " << it->second << endl;
			it++;
		}
		cout << aux[i].consultar_nom_autor() << " ";
		cout << "\"" << aux[i].consultar_titol() <<"\"" << endl;
	}
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
	Cita cita = cites.cita_referencia(referencia);
	cout << cita.consultar_nom_autor() << " ";
	cout << "\"" << cita.consultar_titol() << "\"" << endl;
	cout << cita.consultar_frases().begin()->first << "-" << cita.consultar_frases().rbegin()->first << endl;
	map<int, string> frases = cita.consultar_frases();
	map<int, string>::iterator it = frases.begin();
	while (it != frases.end()) {
		cout << it->first << " " << it->second << endl;
		it++;
	}
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
		string titol_text = autors.obtenir_text_seleccionat();
		string nom_autor = autors.existeix_titol(titol_text);
		Text text = autors.obtenir_text_autor(nom_autor, titol_text);
		map<int, string> frases = text.consultar_frases(x, y);
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
	if (paraula == "frases") nombre_de_frases();
	else if (paraula == "paraules") nombre_de_paraules();
}

void Consultes::nombre_de_frases() {
	Text* text = autors.obtenir_text_seleccionat();
	cout << text->consultar_numero_frases() << endl;
}

void Consultes::nombre_de_paraules() {
	Text* text = autors.obtenir_text_seleccionat();
	cout << text->consultar_numero_paraules() << endl;
}

void Consultes::textos_autor(string nom) {
	const Autor* autor = autors.obtenir_autor(nom);
	vector<string> textos = autor->consultar_titol_textos();
	for (int i = 0; i < textos.size(); i++) {
		cout << "\"" << textos[i] << "\"" << endl;
	}
}

void Consultes::autor() {
	Autor* autor = autors.obtenir_autor_text_seleccionat();
	cout << autor->consultar_nom() << endl;
}

void Consultes::contingut() {
	Text* text = autors.obtenir_text_seleccionat();
	vector<string> frases = text->consultar_contingut();
	for (int i = 0; i < frases.size(); i++) {
		cout << i+1 << " " << frases[i] << endl;
	}
}

void Consultes::taula_de_frequencies() {
	Text* text = autors.obtenir_text_seleccionat();
	vector<list<string> > taula = text->consultar_taula_frequencies();
	for (int i = 0; i < taula.size(); i++) {
		list<string>::iterator it = taula[i].begin();
		while (it != taula[i].end()) {
			cout << *it << " " << i << endl;
			it++;
		}
	}
}
