/** @file Conjunt_autors.hh
	@brief Especificació de la classe Conjunt_autors
*/

#ifndef CONJUNT_AUTORS_HH
#define CONJUNT_AUTORS_HH

#include "Autor.hh"
#include <vector>
#include <string>
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
	
	//Consultores
	
	/** @brief Consulta si existeix un text pel titol
		@param titol: Titol del text que es vol cercar.
		/pre cert
		/post retorna true si existeix un text amb titol = "titol"; sino retorna false
	*/
	bool existeix_titol(string titol);
	
	/** @brief Consulta un autor pel nom
		@param nom: Nom de l'autor que es vol cercar.
		/pre cert
		/post retorna l'autor de nom = "nom", sino existeix retorna NULL
	*/
	Autor obtenir_autor(string nom);
	
	/** @brief Consulta tots els autors del sistema
		/pre cert
		/post retorna tots els autors del conjunt ordenats alfabeticament
	*/
	set<Autor> tots_autors();
	
	/** @brief Tria el text que contingui paraules
		@param paraules: Vector d'strings amb les paraules que es vol que contingui el text triat.
		/pre cert
		/post Retorna true si ha trobat un unic text que conte "paraules" 
		 i el selecciona; retorna false si no ha trobat cap que 
		 contingui "paraules" o s'ha trobat més d'un. 
	*/
	bool triar_text (vector<string> paraules);
	
private:
	set<Autor> Autors;
}

#endif
