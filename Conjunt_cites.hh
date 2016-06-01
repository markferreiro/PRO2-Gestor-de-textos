/** @file Conjunt_cites.hh
	@brief Especificaci� de la classe Conjunt_cites
*/

#ifndef CONJUNT_CITES_HH
#define CONJUNT_CITES_HH

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "Cita.hh"
#include "Autor.hh"
#include "Conjunt_autors.hh"


using namespace std;

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
			@param x: Part petita (posici� m�s petita) del rang de frases que es vol afegir a la cita.
			@param y: Part gran (posici� m�s gran) del rang de frases que es vol afegir a la cita.
			
			/pre es compleix 1 <= x <= y <= n, on n es el nombre total de frases
			/post retorna false si ja existia una cita amb les mateixes frases del
			 mateix text i autor, sino retorna true i s'ha afegit una cita al Conjunt_cites
		*/
		bool afegir_cita (int x, int y, string titol_text, string nom_autor, string referencia, map<int, string> frases);

		/** @brief Eliminar una cita del Conjunt_cites
			@param referencia: Referencia de la cita que es vol eliminar.
			
			/pre cert
			/post retorna false si "referencia" es una referencia inexistent, sino retorna
			 true i s'haura eliminat la cita del Conjunt_cites
		*/
		bool eliminar_cita(string referencia);
		
		/** @brief Transforma un int en un string
			@param a: int a transformar
		
			/pre cert
			/post Retorna a en format string
		*/
		string IntToString (int a);

		//Consultores

		/** @brief Consultar totes les cites del sistema

			/pre cert
			/post retorna un vector amb totes les cites que conte p.i. ordenades per referencia
		*/
		vector<Cita> totes_cites(Conjunt_autors autors);

		/** @brief Consulta les cites d'un autor
			@param nom_autor: Nom de l'autor del que es volen obtenir les cites.
			
			/pre  el p.i. no es buit i existeix un autor al sistema de nom == "nom_autor"
			/post retorna un vector amb totes les cites de l'autor amb nom == "nom_autor",
			 ordenades per referencia
		*/
		vector<Cita> cites_autor(string nom_autor, Conjunt_autors autors);

		/** @brief Consulta una Cita per la seva referencia
			@param referencia: Referencia de la cita que es vol obtenir.
			
			/pre el p.i. no es buit
			/post retorna la Cita amb referencia = "referencia", retorna NULL
			 si no hi ha cap Cita amb la referencia = "referencia"
		*/
		Cita cita_referencia (string referencia, Conjunt_autors autors);

		/** @brief Consulta les cites de l'ultim Text_seleccionat
			@param titol_text_seleccionat: titol del text triat

			/pre cert
			/post retorna un vector amb totes les cites de l'ultim Text_seleccionat,
			 retorna NULL si no hi ha cap text triat
		*/
		vector<Cita> cites_text_seleccionat(string titol_text_seleccionat, Conjunt_autors& autors);


	private:
		
		map<string, Cita> cites;
		map<string, int> max_ref;
		int maxima_referencia(string inicials);
		bool existeix_cita(string titol_text, int x, int y);
};
#endif
