#include "Text.hh"

using namespace std;

vector<string> Text::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter)) {
    	internal.push_back(tok);
	}

	return internal;
}

bool Text::classcomp::operator() (const std::string& lhs, const std::string& rhs) const
{
    if (lhs.length() < rhs.length()) {
    	return true;
    } else if (lhs.size() > rhs.size()) {
    	return false;
    } else {
    	return lhs < rhs;
    }
}

void Text::modificar_contingut (const string paraula1, const string paraula2) {
	//vector<string> noves_frases;
	//replace(frases.begin(), frases.end(), paraula1, paraula2);
	for (int f = 0; f < frases.size(); f++) {
	    //string f = frases[frase];
		replaceAll(frases[f], paraula1, paraula2);
	    /*string frase;
		vector<string> par = split(frases[f], ' ');
		for (int p = 0; p < par.size(); p++) {
			string paraula = clean_word(par[p]);
			if (paraula == paraula1) {
				char c = par[p][par[p].size()];
				if ((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or (c >= '0' and c <= '9')) {
					par[p] = paraula2;
				}
				else {
					paraula2 += c;
					par[p] = paraula2;
				}
			}
			frase += par[p];
		}
		noves_frases.push_back(frase);*/
	    
	    //frases[frase] = f;
	}
	//afegir_contingut(noves_frases);
}

void Text::construir_taula_de_frequencies() {
	for(int frase = 0 ; frase < frases.size() ; frase++) {
		vector<string> paraules = split(frases[frase], ' ');
		for (int paraula = 0 ; paraula < paraules.size() ; paraula++) {
			frequencies[ paraules[paraula] ]++;
		}
	}
}

Text::Text() {

}
Text::Text (string titol) {
	this->titol = titol;
}

void Text::afegir_contingut (vector<string> frases) {
	this->frases = frases;
}

void Text::modificar_titol(string titol) {
	this->titol = titol;
}

string Text::consultar_titol() const{
	return titol;
}

string Text::consultar_frase (int posicio) {
	return frases[posicio-1];
}

vector<string> Text::consultar_contingut () {
	return frases;
}

map<int, string > Text::consultar_frases (int x, int y) {
	map<int, string > aux = map<int, string>();
  //cout << "Preparat per llegir de la " << x << " a la " << y << endl;
<<<<<<< HEAD
	for (int i = x; i <= y; i++) {
		//aux[i-x] = frases[i];
    	//cout << "Intentando acceder a la frase: " << i+x << " de " << y-x+1 << endl;
    	aux[i] = frases[i-1];
    	//cout << "Extrayendo frase: " << frases[i-1] << " (" << i << "," << y-x << ")" << endl;
=======
	for (int i = x; i <= y-x+1; i++) {
		//aux[i-x] = frases[i];
    //cout << "Intentando acceder a la frase: " << i+x << " de " << y-x+1 << endl;
    aux[i+1] = frases[i];
    //cout << "Extrayendo frase: " << frases[i] << " (" << i << "," << y-x+1 << ")" << endl;
>>>>>>> origin/master
	}
	return aux;
}

vector<string> Text::consultar_frases() {
  return frases;
}

vector<list<string> > Text::consultar_taula_frequencies() {

	vector<list<string> > aux(consultar_frequencia_maxima());
	for (map<string, int, Text::classcomp>::iterator it = frequencies.begin() ; it != frequencies.end() ; it++) {
		cout << it->first << " " << it->second;
		aux[it->second].insert(aux[it->second].end(), it->first);
	}
	return aux;
}

bool Text::conte_paraules (int i, vector<string> paraules) {
	string frase = consultar_frase(i);
	int paraula = 0;
	vector<string> par = split(frase, ' ');
	for (int p = 0; p < par.size(); p++) {
		if(paraula < paraules.size()) {
			if (par[p] == paraules[paraula]) {
				paraula++;
			} else {
				return true;
			}
		}
	}
	return false;
}

bool Text::conte_expressio(string expressio) {

}

void Text::substitueix_paraula (string paraula1, string paraula2) {
	modificar_contingut(paraula1, paraula2);
}

pair<int,int> Text::existeix_paraula (string paraula) {
	for (int f = 0; f < frases.size(); f++) {
		vector<string> par = split(frases[f], ' ');
		for (int p = 0 ; p < par.size(); p++) {
			string paraula_neta = clean_word(par[p]);
			if (paraula_neta == paraula) {
        		//cout << "Comprobem contingut: " << par[p] << " - " << paraula << endl;
				return (pair<int,int>(f,p));
			}
		}
	}
	vector<string> par = split(consultar_titol(), ' ');
	for (int p = 0 ; p < par.size(); p++) {
		string paraula_neta = clean_word(par[p]);
    	if (paraula_neta == paraula) {
    		return (pair<int,int>(-1,p));
    	}
	}
	return (pair<int,int>(-1,-1));
}

int Text::consultar_numero_frases() {
	return frases.size();
}

int Text::consultar_numero_paraules() {
	int paraules = 0;
	for (int f = 0; f < frases.size(); f++) {
		vector<string> par = split(frases[f], ' ');
		//cout << "frase " << f << ": " << par.size()-1 << endl;
		paraules += par.size() -1;
	}
	return paraules;
}

int Text::consultar_frequencia_maxima() {
	int freq = 0;
	for (map<string, int, Text::classcomp>::iterator it = frequencies.begin() ; it != frequencies.end() ; it++) {
		if (it->second > freq) freq = it->second;
	}
	return freq;
}

void Text::replaceAll( string& source, const string& from, const string& to )
{
    string newString;
    newString.reserve( source.length() );  // avoids a few memory allocations

    string::size_type lastPos = 0;
    string::size_type findPos;

    while( string::npos != ( findPos = source.find( from, lastPos )))
    {
        newString.append( source, lastPos, findPos - lastPos );
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr( lastPos );

    source.swap( newString );
}

<<<<<<< HEAD
string Text::clean_word (string paraula) {
	string p;
	for (int i = 0; i < paraula.length(); i++) {
		if ((paraula[i] >= 'a' and paraula[i] <= 'z') or (paraula[i] >= 'A' and paraula[i] <= 'Z') or (paraula[i] >= '0' and paraula[i] <= '9')) {
			p += paraula[i];
		}
	}
	return p;
=======
bool Text::rang_correcte(int x, int y) {
  //cout << "comprovant rang..." << endl;
  return ( (x < y) && (x >= 1 && y <= frases.size()) );
>>>>>>> origin/master
}
