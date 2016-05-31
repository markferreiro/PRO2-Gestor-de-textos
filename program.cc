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
			//cout << "Reading first word... ";
	    iss >> paraula;
			//cout << ": " << paraula << endl;
	    if (paraula == "afegir"){
			gestor.afegir(linia.substr(paraula.size()));
		} else if (paraula == "eliminar") {
			gestor.eliminar(linia.substr(paraula.size()));
		} else if (paraula == "triar") {
			gestor.triar_text(linia.substr(paraula.size()));
			//cout << "Text triat: " << gestor.obtenir_conjunt_autors().obtenir_autor_text_seleccionat() << " - " << gestor.obtenir_conjunt_autors().obtenir_text_seleccionat() << endl;
		} else if (paraula == "substitueix") {
			gestor.substituir_paraules(linia.substr(paraula.size()));
		} else {
			gestor.consultes.processar_consulta(linia, gestor.obtenir_conjunt_autors(), gestor.obtenir_conjunt_cites());
		}
		//cout << "Reading new line..." << endl;
		paraula = "";
		linia = "";
		//cout << "Autors (" << gestor.obtenir_conjunt_autors().tots_autors().size() << ")" << endl;
		getline(cin, linia);
	}
}
