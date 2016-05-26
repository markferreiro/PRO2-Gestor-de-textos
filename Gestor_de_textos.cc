#include "Gestor_de_textos.hh"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Conjunt_autors Gestor_de_textos::autors;
Conjunt_cites Gestor_de_textos::cites;

Gestor_de_textos::Gestor_de_textos() {
	Gestor_de_textos::autors = Conjunt_autors();
	Gestor_de_textos::cites = Conjunt_cites();
	consultes = Consultes();
}
void Gestor_de_textos::afegir(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "text") afegir_text(consulta.substr(paraula.size()));
	else if (paraula == "cita") afegir_cita(consulta.substr(paraula.size()));
}

void Gestor_de_textos::afegir_text(string consulta) {
	istringstream iss(consulta);
	string paraula, titol_llegit, autor_llegit, frase;
	vector<string> frases(0);
	bool titol_acabat = false, autor_acabat = false;
	iss >> paraula;
	Text text = Text();
	while(paraula != "****") {
		if (!titol_acabat) {
			titol_llegit += " " + paraula;
			if (paraula[paraula.size()-1] == '\"') {
				titol_acabat = true;
				titol_llegit = titol_llegit.substr(1, titol_llegit.size()-2);
				text.modificar_titol(titol_llegit);
			}
		} else if (!autor_acabat) {
			autor_llegit += " " + paraula;
			if (paraula[paraula.size()-1] == '\"') {
				autor_acabat = true;
				autor_llegit = autor_llegit.substr(1, autor_llegit.size()-2);
			}
		} else {
			frase += " " + paraula;
			if (paraula[paraula.size()-1] == '.' || paraula[paraula.size()-1] == '?' || paraula[paraula.size()-1] == '!' ) {
				frases.push_back(frase);
				frase = "";
			}
		}
		iss >> paraula;
	}
	text.afegir_contingut(frases);
	cout << "Text llegit!" << endl;
	cout << "Titol: " << text.consultar_titol() << endl;
	cout << "Autor: " << autor_llegit << endl;
	cout << "Contingut: " << endl;
	for (int i = 0 ; i < frases.size() ; i++) {
		cout << i << ": " << frases[i] << endl;
	}

	//Gestor_de_textos::autors.afegir_text_a_autor(text, autor_llegit);
}

void Gestor_de_textos::afegir_cita(string consulta) {
	consulta = "afegint cita";
	cout << consulta << endl;
}

void Gestor_de_textos::eliminar(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "text") afegir_text(consulta.substr(paraula.size()));
	else if (paraula == "cita") afegir_cita(consulta.substr(paraula.size()));
}

void Gestor_de_textos::eliminar_text(string consulta) {
	consulta = "eliminant text";
	cout << consulta << endl;
}

void Gestor_de_textos::eliminar_cita(string consulta) {
	consulta = "eliminant cita";
	cout << consulta << endl;
}
void Gestor_de_textos::triar_text(string consulta) {
	consulta = "";
}
void Gestor_de_textos::substituir_paraules(string consulta) {
	consulta = "";
}

Conjunt_autors Gestor_de_textos::obtenir_conjunt_autors() {
	return Conjunt_autors();
}
Conjunt_cites Gestor_de_textos::obtenir_conjunt_cites() {
	return Conjunt_cites();
}

int main() {
	Gestor_de_textos gestor = Gestor_de_textos();
  string linia, paraula;
  getline(cin,linia);

  while (linia != "sortir"){
    cout << linia << endl;
    istringstream iss(linia);
    iss >> paraula;
    if (paraula == "afegir"){
			gestor.afegir(linia.substr(paraula.size()));
		} else if (paraula == "eliminar") {
			gestor.eliminar(linia.substr(paraula.size()));
		} else if (paraula == "triar") {
			gestor.triar_text(linia.substr(paraula.size()));
		} else if (paraula == "substituir") {
			gestor.substituir_paraules(linia.substr(paraula.size()));
		} else {
			gestor.consultes.processar_consulta(paraula);
		}
		getline(cin, linia);
	}
}
