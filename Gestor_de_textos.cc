#include "Gestor_de_textos.hh"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Gestor_de_textos::Gestor_de_textos() {
	autors = Conjunt_autors();
	cites = Conjunt_cites();
	consultes = Consultes();
}
void Gestor_de_textos::afegir(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	//cout << "call afegir text..." << endl;
	if (paraula == "text") afegir_text(consulta.substr(paraula.size()+1));
	else if (paraula == "cita") afegir_cita(consulta.substr(paraula.size()+1));
}

void Gestor_de_textos::afegir_text(string consulta) {
	istringstream iss(consulta);
	string paraula, titol_llegit, autor_llegit, frase;
	Text text = Text();
	while (iss >> paraula){
		titol_llegit += " " + paraula;
		if (paraula[paraula.size()-1] == '\"') {
			titol_llegit = titol_llegit.substr(2, titol_llegit.size()-3);
			text.modificar_titol(titol_llegit);
		}
	}
	//cout << titol_llegit<< endl;
	string linia;
	getline(cin,linia);
	istringstream iss2(linia);
	iss2 >> paraula; //llegim la paraula "autor".
	while (iss2 >> paraula) {
		autor_llegit += " " + paraula;
		if (paraula[paraula.size()-1] == '\"') {
			autor_llegit = autor_llegit.substr(2, autor_llegit.size()-3);
		}
	}
	//cout << autor_llegit << endl;
	vector<string> frases(0);
	getline(cin, linia);
	while (linia != "****") {
		istringstream iss3(linia);
		while(iss3 >> paraula) {
			frase += " " + paraula;
			if (paraula[paraula.size()-1] == '.' || paraula[paraula.size()-1] == '?' || paraula[paraula.size()-1] == '!') { //aquesta linia tampoc compila, he intentat mirar perq pero no hi ha manera
				frase = frase.substr(1, frase.size()-1);
				frases.push_back(frase);
				frase = "";
			}
		}
		getline(cin, linia);
	}
	text.afegir_contingut(frases);
	if (!autors.afegir_text_a_autor(text, autor_llegit)) {
		cout << "error" << endl;
	}
}

void Gestor_de_textos::afegir_cita(string consulta) {
	istringstream iss(consulta);
	int x, y;
	iss >> x >> y;
	if(!autors.hi_ha_text_seleccionat())
		cout << "error" << endl;
	else {
		Autor autor = autors.obtenir_autor(autors.obtenir_autor_text_seleccionat());
		Text text = autor.obtenir_text(autors.obtenir_text_seleccionat());
		if (text.rang_correcte(x, y)) {
			map<int, string> frases = text.consultar_frases(x, y);
			cites.afegir_cita(x, y, text.consultar_titol(), autor.consultar_nom(), autor.consultar_referencia(), frases);
		} else {
			cout << "error" << endl;
		}
	}
}

void Gestor_de_textos::eliminar(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "text") eliminar_text();
	else if (paraula == "cita") eliminar_cita(consulta.substr(paraula.size()+1));
}

void Gestor_de_textos::eliminar_text() {
	string titol_text = autors.obtenir_text_seleccionat();
	string nom_autor = autors.obtenir_autor_text_seleccionat();
	bool result = autors.eliminar_text_de_autor(titol_text, nom_autor);
	autors.esborrar_text_triat();
	if (result) {
		cout << "Text eliminat" << endl;
	} else {
		cout << "No hi ha text seleccionat" << endl;
	}

}

void Gestor_de_textos::eliminar_cita(string consulta) {
	istringstream iss(consulta);
	string referencia;
	iss >> referencia;
	referencia = referencia.substr(1, referencia.size()-2);
	if (!cites.eliminar_cita(referencia)) cout << "error" << endl;
	else {
		consulta = "Cita eliminada.";
		cout << consulta << endl;
	}
}
void Gestor_de_textos::triar_text(string consulta) {
	istringstream iss(consulta);
	bool final = false;
	string paraula;
	iss >> paraula;
	vector<string> paraules(0);
	do {
		iss >> paraula;
		if (paraula[0] == '{') {
			paraula = paraula.substr(1, paraula.size()-1);
			//cout << "primera: " << paraula << endl;
		}
		if (paraula[paraula.size()-1] == '}') {
			final = true;
			paraula = paraula.substr(0, paraula.size()-1);
			//cout << "ultima : " << paraula << endl;
		}
		//cout << "paraula: " << paraula << endl;
		paraules.push_back(paraula);
	} while (!final);

	if(!autors.triar_text(paraules)) cout << "error" << endl;
	else {
		consulta = "text triat";
		cout << consulta << endl;
	}
}
void Gestor_de_textos::substituir_paraules(string consulta) {
	istringstream iss(consulta);
	string paraula1, paraula2;
	iss >> paraula1;
	iss >> paraula2; //llegint per
	iss >> paraula2;
	paraula1 = paraula1.substr(1, paraula1.size()-2);
	paraula2 = paraula2.substr(1, paraula2.size()-2);
	//cout << "paraula1: " << paraula1 << endl;
	//cout << "paraula2: " << paraula2 << endl;
	Autor a = autors.obtenir_autor(autors.obtenir_autor_text_seleccionat());
	Text text = autors.obtenir_text_autor(autors.obtenir_autor_text_seleccionat(), autors.obtenir_text_seleccionat());
	//cout << "Text sense substituir: " << "titol: " << text.consultar_titol() << " / " << text.consultar_contingut()[0] << " / " << text.consultar_contingut()[1] << " / " << text.consultar_contingut()[2] << endl;
	text.substitueix_paraula(paraula1, paraula2);
	a.afegir_text(text);
	cout << "Substitució correcte." << endl;
	//cout << "Text substituit: " << "titol: " << text.consultar_titol() << " / " << text.consultar_contingut()[0] << " / " << text.consultar_contingut()[1] << " / " << text.consultar_contingut()[2] << endl;
}

Conjunt_autors Gestor_de_textos::obtenir_conjunt_autors() {
	return autors;
}
Conjunt_cites Gestor_de_textos::obtenir_conjunt_cites() {
	return cites;
}

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
