#include "Gestor_de_textos.hh"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Conjunt_autors Gestor_de_textos::autors;
Conjunt_cites Gestor_de_textos::cites;

Gestor_de_textos::Gestor_de_textos() {
	Gestor_de_textos::autors = Conjunt_autors();
	Gestor_de_textos::cites = Conjunt_cites();
	Gestor_de_textos::consultes = Consultes();
}
void Gestor_de_textos::afegir(string consulta) {
	consulta = "";
}

void Gestor_de_textos::afegir_text(string consulta) {
	consulta = "";
}

void Gestor_de_textos::afegir_cita(string consulta) {
	consulta = "";
}

void Gestor_de_textos::eliminar(string consulta) {
	consulta = "";
}

void Gestor_de_textos::eliminar_text(string consulta) {
	consulta = "";
}

void Gestor_de_textos::eliminar_cita(string consulta) {
	consulta = "";
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
	Gestor_de_textos gestor();
  string linia, paraula;
  getline(cin,linia);
  while (linia != "sortir"){
    cout << linia << endl;
    istringstream iss(linia);
    iss >> paraula;
    if (paraula == "afegir"){
			gestor.afegir(linia);
		} else if (paraula == "eliminar") {
			gestor.eliminar(linia);
		} else if (paraula == "triar") {
			gestor.triar_text(linia);
		} else if (paraula == "substituir") {
			gestor.substituir_paraules(linia);
		} else {
			Gestor_de_textos::consultes.processar_consulta(linia);
		}
	}
}
