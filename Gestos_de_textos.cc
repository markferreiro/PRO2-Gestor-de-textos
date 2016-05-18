#include "utils.PRO2"
#include "Conjunt_autors.hh"
#include "Conjunt_cites.hh"
#include "Text.hh"
#include "Autor.hh"
#include "Consultes.hh"
#include <vector>
#include <iostream>
#include <string>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class Gestor_de_textos {
	private static Conjunt_autors autors;
	private static Text* text_seleccionat;
	private static Autor* autor_text_seleccionat;
	private static Conjunt_cites cites;
	private Consultes consultes;
	
	Gestor_de_textos() {
		Gestor_de_textos.autors = Conjunt_autors();
		Gestor_de_textos.cites = Conjunt_cites();
		Gestor_de_textos.consultes = Consultes();
	}
	private void afegir(string consulta) {
		
	}
	private void afegir_text(string consulta) {
		
	}
	private void afegir_cita(string consulta) {
		
	}
	private void eliminar(string consulta) {
		
	}
	private void eliminar_text(string consulta) {
		
	}
	private void eliminar_cita(string consulta) {
		
	}
	private void triar_text(string consulta) {
		
	}
	private void substituir_paraules(string consulta) {
		
	}
	
	static Conjunt_autors obtenir_conjunt_autors() {
		
	}
	static Text obtenir_text_seleccionat() {
		
	}
	static Autor obtenir_autor_text_seleccionat() {
		
	}
	static Conjunt_cites obtenir_conjunt_cites() {
		
	}
};

int main() {
	
}
