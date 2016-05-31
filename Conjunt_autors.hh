/** @file Conjunt_autors.hh
	@brief Especificaci� de la classe Conjunt_autors
*/

#ifndef CONJUNT_AUTORS_HH
#define CONJUNT_AUTORS_HH

#include "Autor.hh"
#include <vector>
#include <string>
#include <iostream>
#include <set>

/*
 * Classe Conjunt_autors
 */

/** @class Conjunt_autors
	@brief Representa un conjunt d'autors
*/

class Conjunt_autors
{
public:

	struct classcomp
	{
		bool operator() (const Autor& lhs, const Autor& rhs) const;
	};
	
	//Constructores

	/** @brief Creadora per defecte

		/pre cert
		/post El resultat es un Conjunt_autors sense inicialitzar
	*/
	Conjunt_autors();

	//Modificadores

	/** @brief Afegeix un autor al conjunt d'autors
		@param nom: Nom de l'autor a afegir.
		
		/pre cert
		/post retorna false si ja existeix un autor amb nom = "nom"; sino retorna true
		 i s'ha afegit l'autor al p.i.
	*/
	bool afegir_autor(string nom);

	/** @brief Elimina un autor al conjunt d'autors
		@param nom: Nom de l'autor a eliminar.
		
		/pre existeix un autor amb nom = "nom"
		/post s'ha eliminat l'autor amb nom = "nom" del p.i.
	*/
	void eliminar_autor(string nom);
	
	/**	@brief Ja no hi ha text_triat
	
		/pre cert
		/post si hi havia un text triat, ja no ho esta
	
	*/
	void esborrar_text_triat();

	/** @brief Tria el text que contingui paraules
		@param paraules: Vector d'strings amb les paraules que es vol que contingui el text triat.
		
		/pre cert
		/post Retorna true si ha trobat un unic text que conte "paraules"
		 i el selecciona; retorna false si no ha trobat cap que
		 contingui "paraules" o s'ha trobat m�s d'un.
	*/
	bool triar_text (vector<string> paraules);

	/** @brief Afegeix un text a un autor
		@param text: text que es vol afegir
		@param nom_autor: nom de l'autor al qual es vol afegir el text
		
		/pre El text es valid
		/post Retorna true si s'ha pogut afegir, es a dir, si no existia un text del mateix autor amb el mateix titol; sino retorna false
	*/
	bool afegir_text_a_autor (Text text, string nom_autor);
	
	/** @brief Elimina un text d'un autor
		@param titol: titol del text que es vol eliminar
		@param nom_autor: nom de l'autor del qual es vol eliminar el text
		
		/pre cert
		/post Retorna true si s'ha pogut eliminar el text; retorna false si el text no existia i per tant no s'ha eliminat
	*/
	bool eliminar_text_de_autor(string titol, string nom_autor);
	
	/** @brief Transforma un int en un string
		@param a: int a transformar
		
		/pre cert
		/post Retorna a en format string
	*/
	string IntToString (int a);

	//Consultores

  /** @brief Obté l'autor del text seleccionat.
  
		\pre Ha d'haber un text seleccionat previament i com a conseqüencia un autor seleccionat.
		\post Retorna l'objecte Autor corresponent al text seleccionat per la consulta "triar text"
	*/
	string obtenir_autor_text_seleccionat();

  /** @brief Obté el Text seleccionat.
  
		\pre Ha d'haber un text seleccionat previament.
		\post Retorna l'objecte Text corresponent al text seleccionat per la consulta "triar text"
	*/
	string obtenir_text_seleccionat();

	/** @brief Consulta si existeix un text pel titol
		@param titol: Titol del text que es vol cercar.
		
		/pre cert
		/post retorna el nom de l'autor  del text si existeix un text amb titol = "titol"; sino retorna "NULL"
	*/
	string existeix_titol(string titol);

	/** @brief Consulta un autor pel nom
		@param nom: Nom de l'autor que es vol cercar.
		
		/pre cert
		/post retorna l'autor de nom = "nom", sino existeix retorna 0
	*/
	Autor obtenir_autor(string nom);
	/** @brief Consulta un text d'un autor
		@param nom: nom de l'autor del qual es vol obtenir el text
		@param titol: titol del text que es vol obtenir
	
		\pre existeix un autor i un text amb Nom = nom i Titol = titol
		\post Retorna el text de titol = Titol de l'autor amb nom = Nom
	*/
	Text obtenir_text_autor(string nom, string titol);

	/** @brief Consulta tots els autors del sistema
	
		/pre cert
		/post retorna tots els autors del conjunt ordenats alfabeticament
	
	set<Autor, classcomp> tots_autors();*/
	
	/** @brief Consulta tots els textos del sistema
		
		/pre cert
		/post retorna un vector amb un string per cada text del sistema, 
		i cada string esta format pel nom de l'autor del text, i el titol del text entre cometes.
	*/
	vector<string> tots_textos();
	
	/** @brief Consulta tots els autors del sistema
	
		/pre cert
		/post retorna un vector amb un string per cada autor del sistema, 
		i cada string esta format pel nom de l'autor, el nom de textos d'aquest, el nombre de frases 
		i el nombre de paraules, separats per espais.
	*/
	vector<string> tots_autors();
	
	/** @brief Consulta si hi ha un text triat
		
		/pre cert
		/post Retorna true si hi ha un text triar; sino retorna false;
	*/
	bool hi_ha_text_seleccionat();
	
	
	
private:
	set<Autor, classcomp> autors;
	static bool text_esta_seleccionat;
	string autor_text_seleccionat;
	string text_seleccionat;
};

#endif
