#include "Gestor_de_textos.hh"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Gestor_de_textos::Gestor_de_textos() {
	Gestor_de_textos::autors = Conjunt_autors();
	Gestor_de_textos::cites = Conjunt_cites();
	Gestor_de_textos::consultes = Consultes();
}
void Gestor_de_textos::afegir(string consulta) {
	consulta = "";
}

void Gestor_de_textos::afegir_text(string consulta) {
	consulta = "";
}

void Gestor_de_textos::afegir_cita(string consulta) {
	consulta = "";
}

void Gestor_de_textos::eliminar(string consulta) {
	consulta = "";
}

void Gestor_de_textos::eliminar_text(string consulta) {
	consulta = "";
}

void Gestor_de_textos::eliminar_cita(string consulta) {
	consulta = "";
}
void Gestor_de_textos::triar_text(string consulta) {
	consulta = "";
}
void Gestor_de_textos::substituir_paraules(string consulta) {
	consulta = "";
}

<<<<<<< HEAD
Conjunt_autors Gestor_de_textos::obtenir_conjunt_autors() {
	return Conjunt_autors();
}
Text* Gestor_de_textos::obtenir_text_seleccionat() {
	Text t = Text();
	return &t;
}
Autor* Gestor_de_textos::obtenir_autor_text_seleccionat() {
	Autor a = Autor("Antonio Lopes", "AL2");
	return &a;
}
Conjunt_cites Gestor_de_textos::obtenir_conjunt_cites() {
	return Conjunt_cites();
}

int main() {

}
