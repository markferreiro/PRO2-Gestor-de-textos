/** @file Conjunt_cites.hh
	@brief Especificació de la classe Conjunt_cites
*/

#ifndef CONJUNT_CITES_HH
#define CONJUNT_CITES_HH

#include "Cita.hh"
#include <vector>
#include <string>
#include <map>

#endif

/*
 * Classe Conjunt_cites
 */
 
/** @class Conjunt_cites
	@brief Representa un conjunt de cites
*/

class Conjunt_cites
{
	public:
		//Constructores
		
		/** @brief Creadora per defecte
			
			/pre cert
			/post El resultat es un Conjunt_cites sense inicialitzar
		*/
		Conjunt_cites();
		
		//Modificadores
		
		/** @brief Afegeix una cita al Conjunt_cites
			@param x: Part petita (posició més petita) del rang de frases que es vol afegir a la cita.
			@param y: Part gran (posició més gran) del rang de frases que es vol afegir a la cita.
			/pre es compleix 1 <= x <= y <= n, on n es el nombre total de frases
			/post retorna false si ja existia una cita amb les mateixes frases del 
			 mateix text i autor, sino retorna true i s'ha afegit una cita al Conjunt_cites
		*/
		bool afegir_cita (int x, int y);
		
		/** @brief Eliminar una cita del Conjunt_cites
			@param referencia: Referencia de la cita que es vol eliminar.
			/pre cert
			/post retorna false si "referencia" es una referencia inexistent, sino retorna
			 true i s'haura eliminat la cita del Conjunt_cites
		*/
		bool eliminar_cita(string referencia);
		
		//Consultores
		
		/** @brief Consultar totes les cites del sistema
			
			/pre el p.i. no es buit
			/post retorna un vector amb totes les cites que conte p.i. ordenades per referencia
		*/
		vector<Cita> totes_cites();
		
		/** @brief Consulta les cites d'un autor
			@param nom_autor: Nom de l'autor del que es volen obtenir les cites.
			/pre  el p.i. no es buit i existeix un autor al sistema de nom == "nom_autor"
			/post retorna un vector amb totes les cites de l'autor amb nom == "nom_autor", 
			 ordenades per referencia
		*/
		vector<Cita> cites_autor(string nom_autor);
		
		/** @brief Consulta una Cita per la seva referencia
			@param referencia: Referencia de la cita que es vol obtenir.
			/pre el p.i. no es buit
			/post retorna la Cita amb referencia = "referencia", retorna NULL 
			 si no hi ha cap Cita amb la referencia = "referencia"
		*/
		Cita cita_referencia (string referencia);
		
		/** @brief Consulta les cites de l'ultim Text_seleccionat
			
			/pre cert
			/post retorna un vector amb totes les cites de l'ultim Text_seleccionat, 
			 retorna NULL si no hi ha cap text triat
		*/
		vector<Cita> cites_text_seleccionat();
		
	private:
		struct p_cita {
	  		string* autor;
	  		Text* text;
	  		vector<int> (2) frases; 
		};
		map<string, p_cita> cites;
		map<string, int> max_ref;
		int maxima_referencia(string inicials);
}
#endif
