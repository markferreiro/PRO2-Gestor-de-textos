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
	}
	public bool afegir_cita(int x, int y) {
		
	}
	public bool eliminar_cita(string referencia) {
		int original_size = cites.size();
		int size = cites.erase(referencia);
		if (size < original_size) {
			return true;
		}
		return false;
	}
	public vector<Cita> totes_cites() {
		int size = cites.size();
		vector<Cita> cites_to_return(size);
		map<string, p_cita>::iterator iterator = cites.begin();
		for (int i = 0 ; i < size ; i++) {
			p_cita = iterator->second;
			Cita c = Cita(p_cita->autor, p_cita->text.consultar_titol(), iterator->first, p_cita->text.consultar_frases(p_cita->frases[0], p_cita->frases[1]));
			cites_to_return[i] = c; 
			iterator++;
		}
		return cites_to_return;
	}
	public vector<Cita> cites_autor(string nom_autor) {
		vector<Cita> cites_to_return();
		map<string, p_cita>::iterator iterator = cites.begin();
		while (iterator != cites.end()) {
			p_cita = iterator->second;
			if (p_cita->autor == nom_autor) {
				Cita c = Cita(p_cita->autor, p_cita->text.consultar_titol(), iterator->first, p_cita->text.consultar_frases(p_cita->frases[0], p_cita->frases[1]));
				cites_to_return.push_back(c); 
			}
			iterator++;
		}
		return cites_to_return;
	}
	public Cita cita_referencia (string referencia) {
		vector<Cita> cites_to_return(size);
		map<string, p_cita>::iterator iterator = cites.begin();
		int i = 0;
		while (iterator != cites.end()) {
			if (iterator->first == referencia) {
				p_cita = iterator->second;
				Cita c = Cita(p_cita->autor, p_cita->text.consultar_titol(), iterator->first, p_cita->text.consultar_frases(p_cita->frases[0], p_cita->frases[1]));
				cites_to_return[i] = c;
				i++;
			}
			iterator++;
		}
		return cites_to_return;
	}
	public vector<Cita> cites_text_seleccionat() {
		Text text_seleccionat = Gestor_de_textos.obtenir_text_seleccionat();
		vector<Cita> cites_to_return();
		map<string, p_cita>::iterator iterator = cites.begin();
		while (iterator != cites.end()) {
			p_cita = iterator->second;
			if (p_cita.text == &text_seleccionat) {
				Cita c = Cita(p_cita->autor, p_cita->text.consultar_titol(), iterator->first, p_cita->text.consultar_frases(p_cita->frases[0], p_cita->frases[1]));
				cites_to_return.push_back(c);
			}
			iterator++;
		}
		return cites_to_return;
	}
	
	private int maxima_referencia(string inicials) {
		map<string,int>::iterator it = max_ref.find(inicials); 
		if (it != max_ref.end()) {
			return (it->second) + 1;
		}
		return 1;
	}
};
