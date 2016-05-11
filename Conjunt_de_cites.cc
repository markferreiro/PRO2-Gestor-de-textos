#include "Cita.hh"
#include <vector>
#include <string>
#include <map>

class Conjunt_cites{
	struct p_cita {
  		string* autor;
  		Text* text;
  		vector<int> (2) frases; 
	};
	private map<string, p_cita> cites;
	private map<string, int> max_ref;
	
	Conjunt_cites() {
		cites = map<string, p_cita>();
		max_ref = map<string, int>();
		hola cacarruta
	}
	public bool afegir_cita(int x, int y) {
		
	}
	public bool eliminar_cita(string referencia) {
		
	}
	public vector<Cita> totes_cites() {
		
	}
	public vector<Cita> cites_autor(string nom_autor) {
		
	}
	public Cita cita_referencia (string referencia) {
		
	}
	public vector<Cita> cites_text_seleccionat() {
		
	}
	
	private int maxima_referencia(string inicials) {
		
	}
};
