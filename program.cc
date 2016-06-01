#include <iostream>
#include "Gestor_de_textos.hh"
using namespace std;

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
		} else if (paraula == "substitueix") {
			gestor.substituir_paraules(linia.substr(paraula.size()));
		} else {
			gestor.consultes.processar_consulta(linia, gestor.obtenir_conjunt_autors(), gestor.obtenir_conjunt_cites());
		}
		paraula = "";
		linia = "";
		getline(cin, linia);
	}
}
