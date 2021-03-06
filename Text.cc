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
	for (int f = 0; f < frases.size(); f++) {
		replaceAll(frases[f], paraula1, paraula2);
	}
}

void Text::construir_taula_de_frequencies() {
	for(int frase = 0 ; frase < frases.size() ; frase++) {
		vector<string> paraules = split(frases[frase], ' ');
		for (int paraula = 0 ; paraula < paraules.size() ; paraula++) {
			string paraula_neta = clean_word(paraules[paraula]);
			frequencies[paraula_neta]++;
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
	construir_taula_de_frequencies();
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
	for (int i = x; i <= y; i++) {
    	aux[i] = frases[i-1];
	}
	return aux;
}

vector<vector<string> > Text::consultar_taula_frequencies() {
	vector<vector<string> > aux(consultar_frequencia_maxima()+1);
	for (map<string, int, Text::classcomp>::iterator it = frequencies.begin() ; it != frequencies.end() ; it++) {
		aux[it->second].push_back(it->first);
	}
	return aux;
}

bool Text::conte_paraules (int i, vector<string> paraules) {
	string frase = consultar_frase(i);
	int paraula = 0;
	vector<string> par = split(frase, ' ');
	for (int p = 0; p < par.size(); p++) {
		if(paraula < paraules.size()) {
			string paraula_neta = clean_word(par[p]);
			if (paraula_neta == paraules[paraula]) {
				paraula++;
			}
			else {
				paraula = 0;
			}
		}
		else if (paraula == paraules.size()) return true;
	}
	return false;
}

bool Text::conte_paraula(string paraula, int i) {
	string frase = consultar_frase(i);
	vector<string> f = split(frase, ' ');
	for (int i = 0; i < f.size(); ++i) {
		string neta = clean_word(f[i]);
		if (neta == paraula) return true;
	}
	return false;
}

void Text::substitueix_paraula (string paraula1, string paraula2) {
	modificar_contingut(paraula1, paraula2);
	construir_taula_de_frequencies();
}

pair<int,int> Text::existeix_paraula (string paraula) {
	for (int f = 0; f < frases.size(); f++) {
		vector<string> par = split(frases[f], ' ');
		for (int p = 0 ; p < par.size(); p++) {
			string paraula_neta = clean_word(par[p]);
			if (paraula_neta == paraula) {
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
		paraules += par.size();
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

string Text::clean_word (string paraula) {
	string p = "";
	for (int i = 0; i < paraula.length(); i++) {
		if ((paraula[i] >= 'a' and paraula[i] <= 'z') or (paraula[i] >= 'A' and paraula[i] <= 'Z') or (paraula[i] >= '0' and paraula[i] <= '9')) {
			p += paraula[i];
		}
	}
	return p;
}

bool Text::rang_correcte(int x, int y) {
  return ( (x <= y) && (x >= 1 && y <= frases.size()) );
}
