#include <vector>
#include <string>
#include <map>
#include "Cita.hh"

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
		Text *text_seleccionat = Gestor_de_textos.obtenir_text_seleccionat();
		Autor *autor_text_seleccionat = Gestor_de_textos.obtenir_autor_text_seleccionat();
		//Comprovar si el rang de frases es correcte ( 1 <= x <= y <= nº frases )
			//Comprovant aixó primer, en certs casos ens estalviarem la comprovació següent.
		if ( (x >= 1 && y >= x) && text_seleccionat->consultar_numero_frases() >= y) {
			if (!existeix_cita(text_seleccionat, x, y)) {
				String referencia = autor_text_seleccionat->consultar_referencia();
				p_cita p = p_cita();
				p.autor = autor_text_seleccionat;
				p.text = text_seleccionat;
				p.frases[0] = x;
				p.frases[1] = y;
				cites.insert(pair<string, p_cita>(referencia + IntToString(maxima_referencia(referencia)), p));
				return true;
			}
		}
		return false;
		//Comprovar si ja existeix una cita del text seleccionat amb les mateixes frases.
		//Afegir cita.
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
	
	private bool existeix_cita(Text text, int x, int y) {
		bool resultat = false;
		map<string, p_cita>::iterator iterator = cites.begin();
		while (iterator != cites.end() && !resultat) {
			p_cita = iterator->second;
			if (p_cita->text.consultar_titol() == text.consultar_titol() && p_cita.frases[0] == x && p_cita.frases[1] == y) {
				resultat = true;
			}
			iterator++;
		}
		return resultat;
	}

};
