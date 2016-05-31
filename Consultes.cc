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
	else if (paraula == "nombre") nombre_de(consulta.substr(paraula.size()));
	else if (paraula == "cites") cites_consultar(consulta.substr(paraula.size()));
	else if (paraula == "textos") {
		string nom;
		iss >> paraula; //llegeix autor
		iss >> paraula;
		bool llegit = false;
		while (!llegit) {
			if (paraula[paraula.size()-1] == '\"') {
				llegit = true;
			}
			nom += " " + paraula;
			iss >> paraula;
		}
		textos_autor(nom.substr(2, nom.size()-3));
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
	set<Autor, Conjunt_autors::classcomp>::iterator it_autors = autors.tots_autors().begin();
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
	vector<Cita> aux = cites.totes_cites(autors);
	for (int i = 0; i < aux.size(); i++) {
		//Cita cita = aux[i];
		escriure_cita(aux[i]);
		cout << aux[i].consultar_nom_autor() << " ";
		cout << "\"" << aux[i].consultar_titol() << "\"" << endl;
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
			string titol_text_seleccionat = autors.obtenir_text_seleccionat();
			string nom_autor_text_seleccionat = autors.obtenir_autor_text_seleccionat();
			Text text = autors.obtenir_text_autor(nom_autor_text_seleccionat, titol_text_seleccionat);
			//info text
			cout << nom_autor_text_seleccionat << " ";
			cout << "\"" << titol_text_seleccionat << "\" ";
			cout << text.consultar_numero_frases() << " " << text.consultar_numero_paraules() << endl;
			//cites associades
			cout << "Cites Associades:" << endl;
			vector<Cita> aux = cites.cites_text_seleccionat(titol_text_seleccionat, autors);
			for (int c = 0; c < aux.size(); c++) {
				escriure_cita(aux[c]);
			}
		}
		else cout << "error" << endl;
	}
}

void Consultes::info_cita(string referencia) {
	Cita cita = cites.cita_referencia(referencia, autors);
	if (cita.consultar_titol() != "NULL") {
		cout << cita.consultar_nom_autor() << " ";
		cout << "\"" << cita.consultar_titol() << "\"" << endl;
		cout << cita.obtenir_frases().begin()->first << "-" << cita.obtenir_frases().rbegin()->first << endl;
		escriure_cita(cita);
	} else {
		cout << "error" << endl;
	}
}

void Consultes::frases(string consulta) {
	istringstream iss(consulta);
	char lletra;
	iss >> lletra;
	if (lletra >= '0' and lletra <= '9') {
		int x = lletra - 48, y;
		iss >> y;
		frases_text_triat(x,y);
	}
	else if (lletra == '\(') {
    //cout << consulta.substr(1, consulta.size()) << endl;
		frases_expressio(consulta.substr(1, consulta.size()));
	}
	else if (lletra == '\"') {
		string paraula;
		iss >> paraula;
		vector<string> paraules;
		bool llegit = false;
		while(!llegit) {
			if (paraula[paraula.size()-1] == '\"') {
				paraula = paraula.substr(0, paraula.size()-1);
				llegit = true;
			}
			paraules.push_back(paraula);
			iss >> paraula;
		}
		frases_sequencia(paraules);
	}
}

void Consultes::frases_text_triat(int x, int y) {
	if (autors.hi_ha_text_seleccionat()) {
		string titol_text = autors.obtenir_text_seleccionat();
		string nom_autor = autors.existeix_titol(titol_text);
		Text text = autors.obtenir_text_autor(nom_autor, titol_text);
		if (x >= 1 and (y >= x and y <= text.consultar_numero_frases())) {
			map<int, string> frases = text.consultar_frases(x, y);
			map<int, string>::iterator it = frases.begin();
			while (it != frases.end()) {
				cout << it->first << " " << it->second << endl;
				it++;
			}
		}
		else cout << "error" << endl;
	}
	else cout << "error" << endl;
}

void Consultes::frases_expressio(string expressio) {
  if (autors.hi_ha_text_seleccionat()) {
    expressio = expressio.substr(1, expressio.size()-2);
    string titol_text = autors.obtenir_text_seleccionat();
    string nom_autor = autors.existeix_titol(titol_text);

    Text text = autors.obtenir_text_autor(nom_autor, titol_text);
    vector<string> frases = text.consultar_frases();
    vector<string>::iterator it = frases.begin();
    int i = 1;
    while (it != frases.end()) {
      //cout << "intentem trobar" << endl;
      if (frases_expressio_algebraica(expressio, *it)) {
        cout << i << " - " << *it << endl;
      }
      i++;
      it++;
    }
  } else {
    cout << "error" << endl;
  }

  //frases_expressio_algebraica(expressio.substr(1, expressio.size()-2), frase);
}

bool Consultes::frases_expressio_algebraica(string consulta, const string frase) {
  /* La idea es fer crides recursives per cada expresió, es a dir,
  per tots els subconjunts de caracters inclosos entre els parentesis '(' i ')'
  Partint de la idea que:
    - conjunt_de_paraules = '{' + paraula* + '}'.
    - expressió = '(' + (expressió|conjunt_de_paraules) + ')'. */
  /*
  Forma del programa:
    expressio_exquerre = obtenir_expressio;
    operand = obtenir_operand;
    expressio_dreta = obtenir_expressio;
    return expressio_esquerre operand expressio_dreta;
  */
  //cout << consulta << endl;
  string expressio_e, expressio_d, operand;
  bool resultat_e_e, resultat_e_d;
  int posicio_lectura = 0;
  //obtenir_expressio_esquerre
  if (consulta[0] == '(') { //en cas que sigui una expressio composta, la recollim i fem recursivitat.
    //string expressio_e = "(";
    expressio_e = "";
    posicio_lectura = 1;
    while (consulta[posicio_lectura] != ')') {
      expressio_e += consulta[posicio_lectura];
      posicio_lectura++;
    }
    posicio_lectura++;
    //expressio_e += ")";
    //cout << "cridem recursivitat amb:" << expressio_e << endl;
    resultat_e_e = frases_expressio_algebraica(expressio_e, frase);
  } else { //en cas que sigui una expressio simple, la tractem.
    expressio_e = "";
    posicio_lectura = 1;
    while (consulta[posicio_lectura] != '}') {
      expressio_e += consulta[posicio_lectura];
      posicio_lectura++;
    }
    posicio_lectura++;
    vector<string> paraules = split(expressio_e, ' ');
    resultat_e_e = true;
    for(int i = 0 ; i < paraules.size() && resultat_e_e ; i++) {
      if (frase.find(paraules[i]) == string::npos) resultat_e_e = false;
    }
  }
  while (consulta[posicio_lectura] != '(' && consulta[posicio_lectura] != '{') {
    if (consulta[posicio_lectura] == '&' || consulta[posicio_lectura] == '|') {
      operand = consulta[posicio_lectura];
    }
    posicio_lectura++;
  }

  //obtenir_expressio_dreta
  if (consulta[posicio_lectura] == '(') { //en cas que sigui una expressio composta, la recollim i fem recursivitat.
    //expressio_d = "(";
    expressio_d = "";
    posicio_lectura++;
    while (consulta[posicio_lectura] != ')') {
      expressio_d += consulta[posicio_lectura];
      posicio_lectura++;
    }
    posicio_lectura++;
    //expressio_d += ")";
    //cout << "cridem recursivitat ambasdascdscda:" << expressio_d << endl;
    resultat_e_d = frases_expressio_algebraica(expressio_d, frase);
  } else { //en cas que sigui una expressio simple, la tractem.
    expressio_d = "";
    posicio_lectura++;
    while (consulta[posicio_lectura] != '}') {
      expressio_d += consulta[posicio_lectura];
      posicio_lectura++;
    }
    posicio_lectura++;
    vector<string> paraules = split(expressio_d, ' ');
    resultat_e_d = true;
    for(int i = 0 ; i < paraules.size() && resultat_e_d ; i++) {
      if (frase.find(paraules[i]) == string::npos) resultat_e_d = false;
    }
  }
  //cout << "resultat esquerre: " << resultat_e_e << " amb esquerre = '" << expressio_e << "'" << " resultat dret: " << resultat_e_d << " amb dreta = '" << expressio_d << "'" << endl;
  return (operand == "&") ? (resultat_e_e && resultat_e_d) : (resultat_e_e || resultat_e_d);
}

/*bool Consultes::frases_expressio_recursiu(int parentesi, string consulta, vector<string> paraules) {
  if (parentesi == 0) return frases;
  if (consulta[0] == '(') frases_expressio_recursiu(frases, parentesi++, consulta.substr(1, consulta.size()), paraules);
  else if (consulta[0] == '}') {
    int i = 1;
    while (consulta[i] != ')' && consulta[i] != '&' && consulta[i] != '|') { i++; }
    if (consulta[i] == ')') {
      //realitzar busqueda;
      frases_expressio_recursiu(frases, parentesi--, consulta.substr(1, consulta.size()), paraules);
    }
    else frases_expressio_recursiu(frases, , consulta.substr(1, consulta.size()), paraules);
  }
  else if (consulta[0] == '{') {
    string paraula ""; paraules.push_back(paraula);
    frases_expressio_recursiu(frases, parentesi, consulta.substr(1, consulta.size()), paraules);
  }
  else if (consulta[0] == '&')
  else if (consulta[0] == '|')
  else {
    paraules[paraules.size()-1] +=
  }
}*/

void Consultes::frases_sequencia(vector<string> paraules) {
	//for (int x = 0; 0 < paraules.size();x++) cout << paraules[x] <<  " " << endl;
	if(autors.hi_ha_text_seleccionat()) {
		//cout << "hi ha text seleccionat" << endl;
		string titol_text = autors.obtenir_text_seleccionat();
		string nom_autor = autors.existeix_titol(titol_text);
		Text text = autors.obtenir_text_autor(nom_autor, titol_text);
		int n = text.consultar_numero_frases();
		for (int i = 1; i <= n; i++) {
			if(text.conte_paraules(i, paraules)) {
				cout << i << " " << text.consultar_frase(i) << endl;
			}
			//else cout << i << " no es troba " << endl;
		}
	}
	else cout << "error" << endl;
}

void Consultes::nombre_de(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula; //llegeix de
	iss >> paraula;
	if (paraula == "frases") nombre_de_frases();
	else if (paraula == "paraules") nombre_de_paraules();
}

void Consultes::nombre_de_frases() {
	if (autors.hi_ha_text_seleccionat()) {
		string titol_text = autors.obtenir_text_seleccionat();
		string nom_autor = autors.existeix_titol(titol_text);
		Text text = autors.obtenir_text_autor(nom_autor, titol_text);
		cout << text.consultar_numero_frases() << endl;
	}
	else cout << "error" << endl;
}

void Consultes::nombre_de_paraules() {
	if (autors.hi_ha_text_seleccionat()) {
		string titol_text = autors.obtenir_text_seleccionat();
		string nom_autor = autors.existeix_titol(titol_text);
		Text text = autors.obtenir_text_autor(nom_autor, titol_text);
		cout << text.consultar_numero_paraules() << endl;
	}
	else cout << "error" << endl;
}

void Consultes::cites_consultar(string consulta) {
	istringstream iss(consulta);
	string paraula;
	iss >> paraula;
	if (paraula == "autor") {
		string nom;
		iss >> paraula;
		bool llegit = false;
		while (!llegit) {
			if (paraula[paraula.size()-1] == '\"') {
				llegit = true;
			}
			nom += " " + paraula;
			iss >> paraula;
		}
		cites_autor(nom.substr(2, nom.size()-3));
	}
	else {
		vector<Cita> aux = cites.cites_text_seleccionat(autors.obtenir_text_seleccionat(), autors);
		for (int c = 0; c < aux.size(); c++) {
			escriure_cita(aux[c]);
		}
	}
}

void Consultes::cites_autor(string nom) {
	vector<Cita> aux = cites.cites_autor(nom, autors);
	for (int c = 0; c < aux.size(); c++) {
		escriure_cita(aux[c]);
	}
}

void Consultes::textos_autor(string nom) {
	//cout << "nom: " << nom << endl;
	const Autor autor = autors.obtenir_autor(nom);
	vector<string> textos = autor.consultar_titol_textos();
	for (int i = 0; i < textos.size(); i++) {
		cout << "\"" << textos[i] << "\"" << endl;
	}
}

void Consultes::autor() {
	if (autors.hi_ha_text_seleccionat()) {
		string autor = autors.obtenir_autor_text_seleccionat();
		cout << autor << endl;
	}
	else cout << "error" << endl;
}

void Consultes::contingut() {
	if (autors.hi_ha_text_seleccionat()) {
		//cout << "text seleccionat :" << endl;
		string titol_text = autors.obtenir_text_seleccionat();
		string nom_autor = autors.existeix_titol(titol_text);
		//cout << "titol: " << titol_text << " / autor: " << nom_autor << endl;
		Text text = autors.obtenir_text_autor(nom_autor, titol_text);
		vector<string> frases = text.consultar_contingut();
		for (int i = 0; i < frases.size(); i++) {
			cout << i+1 << " " << frases[i] << endl;
		}
	}
	else cout << "error" << endl;
}

void Consultes::taula_de_frequencies() {
	string titol_text = autors.obtenir_text_seleccionat();
	string nom_autor = autors.existeix_titol(titol_text);
	//cout << "titol : " << titol_text << " / autor: " << nom_autor << endl;
	Text text = autors.obtenir_text_autor(nom_autor, titol_text);
	vector<vector<string> > taula = text.consultar_taula_frequencies();
	for (int i = taula.size()-1; i > 0; i--) {
		for (int j = 0; j < taula[i].size(); j++){
			cout << taula[i][j] << " " << i << endl;
		}
	}
}

<<<<<<< HEAD
void Consultes::escriure_cita(Cita& cita) {
	cout << cita.consultar_referencia() << endl;
	map<int, string> frases = cita.obtenir_frases();
	map<int, string>::iterator it = frases.begin();
	while (it != frases.end()) {
		cout << it->first << " " << it->second << endl;
		it++;
	}
=======
vector<string> Consultes::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter)) {
    	internal.push_back(tok);
	}

	return internal;
>>>>>>> origin/master
}
