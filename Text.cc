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

Text::void construir_taula_de_frequencies() {
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

Text::void afegir_contingut (vector<vector<string> > frases) {
	this->frases = frases;
}

Text::void modificar_titol(string titol) {
	this->titol = titol;
}

Text::string consultar_titol() {
	return titol;
}

Text::string consultar_frase (int posicio) {
	return frases[posicio-1];
}

Text::vector<vector<string> > consultar_contingut () {
	return frases;
}

Text::map<int, vector<string> > consultar_frases (int x, int y) {
	map<int, vector<string> > aux;
	for (int i = x; i <= y; i++) {
		aux[i] = frases[i-1];
	}
	return aux;
}

Text::vector<list<string> > consultar_taula_frequencies() {
	
	vector<list<string> > aux[consultar_frequencia_maxima()];
	for (auto it = frequencies.begin() ; it != frequencies.end() ; it++) {
		aux[it->second].insert(aux[it->second].end(), it->first);
	}
	return aux;
}

Text::list<int> obtenir_frases_amb_paraules (vector<string> paraules) {
	
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

Text::void substitueix_paraula (string paraula1, string paraula2) {
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

Text::pair<int,int> existeix_paraula (string paraula) {
	for (int f = 0; f < frases.size(); f++) {
		while (int p = 0; p < frases[f].size(); p++) {
			if (frases[f][p] == paraula) {
				return (pair<int,int>(f,p));
			}
		}
	}
	return (pair<int,int>(-1,-1));
}

Text::int consultar_numero_frases() {
	return frases.size();
}
Text::int consultar_frequencia_maxima() {
	int freq = 0;
	for (auto it = frequencies.begin() ; it != frequencies.end() ; it++) {
		if (it->second > freq) freq = it->second;
	}
	return freq;
}
