#include <iostream>
#include <utility>
#include "Text.hh"

using namespace std;

bool Text::operator()(string a, string b) {
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
		for (int paraula = 0; paraula < frases[frase].size(); paraula++) {
			if (frases[frase][paraula] == paraula1) frases[frase][paraula] = paraula2;
		}
	}
}

void Text::construir_taula_de_frequencies() {
	for(int frase = 0 ; frase < frases.size() ; frase++) {
		for (int paraula = 0 ; paraula < frases[frase].size() ; paraula++) {
			string p = frases[frase][paraula];
			frequencies[p]++;
		}
	}
}

Text::Text (string titol) {
	this->titol = titol;
}

void Text::afegir_contingut (vector<vector<string> > frases) {
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

vector<vector<string> > Text::consultar_contingut () {
	return frases;
}

map<int, vector<string> > Text::consultar_frases (int x, int y) {
	map<int, vector<string> > aux;
	for (int i = x; i <= y; i++) {
		aux[i] = frases[i-1];
	}
	return aux;
}

vector<list<string> > Text::consultar_taula_frequencies() {
	
	vector<list<string> > aux[consultar_frequencia_maxima()];
	for (auto it = frequencies.begin() ; it != frequencies.end() ; it++) {
		aux[it->second].insert(aux[it->second].end(), it->first);
	}
	return aux;
}

list<int> Text::obtenir_frases_amb_paraules (vector<string> paraules) {
	
	list<int> aux;
	for (int f = 0; f < frases.size(); f++) {
		int paraula = 0;
		for (int p = 0; p < frases[f].size(); p++) {
			if (paraula < paraules.size()) {
				if (frases[f][p] == paraules[paraula]) {
					paraula++;
				} else {
					paraula = 0;
				}
			} else {
				aux.insert(aux.end(), f);
				p = frases[f].size();
			}
		}
	}
}

void Text::substitueix_paraula (string paraula1, string paraula2) {
	modificar_contingut(paraula1, paraula2);
}

pair<int,int> Text::existeix_paraula (string paraula) {
	for (int f = 0; f < frases.size(); f++) {
		while (int p = 0; p < frases[f].size(); p++) {
			if (frases[f][p] == paraula) {
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
	for (auto it = frequencies.begin() ; it != frequencies.end() ; it++) {
		if (it->second > freq) freq = it->second;
	}
	return freq;
}
