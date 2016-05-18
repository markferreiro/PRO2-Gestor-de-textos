#include <iostream>
using namespace std;
#include "Text.hh"

class Text {
	string titol;
	vector<vector<string> > frases;
	map <string, int, custom_sort> frequencies;
	struct custom_sort {
	    bool operator()(string a, string b) {
	        return cntBits(a) < cntBits(b);
	        if (a.length() < b.length()) {
	        	return true;
			} else if (a.size() > b.size()) {
				return false;
			} else {
				return a < b;
			}
	    }
	};
	
	private void modificar_contingut (string paraula1, string paraula2) {
		for (int f = 0; f < frases.size(); f++) {
			for (int p = 0; p < frases[f].size(); p++) {
				if (frases[f][p] == paraula1) frases[f][p] = paraula2;
			}
		}
	}
	
	private void construir_taula_de_frequencies() {
		for(int frase = 0 ; frase < frases.size() ; frase++) {
			for (int paraula = 0 ; paraula < frases[frase].size() ; paraula++) {
				string p = frases[frase][paraula];
				frequencies[p]++;
			}
		}
	}
	
	Text (string titol) {
		this->titol = titol;
	}
	
	public void afegir_contingut (vector<vector<string> > frases) {
		this->frases = frases;
	}
	
	public void modificar_titol(string titol) {
		this->titol = titol;
	}
	
	public string consultar_titol() {
		return titol;
	}
	
	public string consultar_frase (int posicio) {
		return frases[posicio-1];
	}
	
	public vector<vector<string> > consultar_contingut () {
		return frases;
	}
	
	public map<int, vector<string> > consultar_frases (int x, int y) {
		map<int, vector<string> > aux;
		for (int i = x; i <= y; i++) {
			aux[i] = frases[i-1];
		}
		return aux;
	}
	
	public vector<list<string> > consultar_taula_frequencies() {
		
	}
	
	public list<int> obtenir_frases_amb_paraules (vector<string> paraules) {
		
	}
	
	public void substitueix_paraula (string paraula1, string paraula2) {
		modificar_contingut(paraula1, paraula2);
	}
	
	public bool existeix_paraula (string paraula) {
		for (int f = 0; f < frases.size(); f++) {
			for (int p = 0; p < frases[f].size(); p++) {
				if (frases[f][p] == paraula) return true;
			}
		}
		return false;
	}
	
	public int consultar_numero_frases() {
		return frases.size()+1;
	}
};
