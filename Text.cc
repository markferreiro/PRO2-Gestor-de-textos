#include <iostream>
using namespace std;
#include "Text.hh"

class Text {
	string titol;
	vector<string> frases;
	map <string,int> frequencies;
	
	private void modificar_contingut (string paraula1, string paraula2) {
		
	}
	
	private void construir_taula_de_frequencies() {
		
	}
	
	Text (string titol, vector<string> frases) {
		this->titol = titol;
		this->frases = frases;
	}
	
	public string consultar_titol() {
		return titol;
	}
	
	public string consultar_frase (int posicio) {
		return frases[posicio-1];
	}
	
	public vector<string> consultar_frases () {
		return frases;
	}
	
	public map<int, string> consultar_frases (int x, int y) {
		map<int, string> aux;
		for (int i = x; i <= y; i++) {
			aux[i] = frases[i-1];
		}
		return aux;
	}
	
	public vector<list<string> > consultar_taula_frequencies() {
		
	}
	
	public list<int> obtenir_frases_amb_paraules (string paraules) {
		
	}
	
	public void substitueix_paraula (string paraula1, string paraula2) {
		modificar_contingut(paraula1, paraula2);
	}
	
	public bool existeix_paraula (string paraula) {
		
	}
	
	public int consultar_numero_frases() {
		return frases.size()+1;
	}
};
