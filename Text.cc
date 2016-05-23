#include <iostream>
#include <utility>
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

bool Text::custom_sort::operator()(string a, string b) {
    if (a.length() < b.length()) {
    	return true;
	} else if (a.size() > b.size()) {
		return false;
	} else {
		return a < b;
	}
}

void Text::modificar_contingut (string paraula1, string paraula2) {
	for (int frase = 0; frase < frases.size(); frase++) {
		//string frase = frases[frase];
		frases[frase] = frases[frase].replace(frases[frase].begin(), frases[frase].end(), paraula1, paraula2);
	}
}

void Text::construir_taula_de_frequencies() {
	for(int frase = 0 ; frase < frases.size() ; frase++) {
		vector<string> paraules = split(frases[frase], ' ');
		for (int paraula = 0 ; paraula < paraules.size() ; paraula++) {
			frequencies[ paraules[paraula] ]++;
		}
	}
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

string Text::consultar_titol() {
	return titol;
}

string Text::consultar_frase (int posicio) {
	return frases[posicio-1];
}

vector<string> Text::consultar_contingut () {
	return frases;
}

map<int, string > Text::consultar_frases (int x, int y) {
	map<int, string > aux;
	for (int i = x; i <= y; i++) {
		aux[i] = frases[i-1];
	}
	return aux;
}

vector<list<string> > Text::consultar_taula_frequencies() {
	
	vector<list<string> > aux(consultar_frequencia_maxima());
	for (map<string, int>::iterator it = frequencies.begin() ; it != frequencies.end() ; it++) {
		aux[it->second].insert(aux[it->second].end(), it->first);
	}
	return aux;
}

list<int> Text::obtenir_frases_amb_paraules (vector<string> paraules) {
	
	list<int> aux;
	for (int f = 0; f < frases.size(); f++) {
		int paraula = 0;
		vector<string> par = split(frases[f], ' ');
		for (int p = 0; p < par.size(); p++) {
			if (paraula < paraules.size()) {
				if (par[p] == paraules[paraula]) {
					paraula++;
				} else {
					paraula = 0;
				}
			} else {
				aux.insert(aux.end(), f);
				p = par.size();
			}
		}
	}
}

void Text::substitueix_paraula (string paraula1, string paraula2) {
	modificar_contingut(paraula1, paraula2);
}
/*
public bool existeix_paraula (string paraula) {
	for (int f = 0; f < frases.size(); f++) {
		for (int p = 0; p < frases[f].size(); p++) {
			if (frases[f][p] == paraula) return true;
		}
	}
	return false;
}*/

pair<int,int> Text::existeix_paraula (string paraula) {
	for (int f = 0; f < frases.size(); f++) {
		vector<string> par = split(frases[f], ' ');
		for (int p = 0 ; p < par.size(); p++) {
			if (par[p] == paraula) {
				return (pair<int,int>(f,p));
			}
		}
	}
	return (pair<int,int>(-1,-1));
}

int Text::consultar_numero_frases() {
	return frases.size();
}
int Text::consultar_frequencia_maxima() {
	int freq = 0;
	for (map<string, int>::iterator it = frequencies.begin() ; it != frequencies.end() ; it++) {
		if (it->second > freq) freq = it->second;
	}
	return freq;
}
