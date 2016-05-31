/** @file Gestor_de_textos.hh
	@brief Especificació de la classe principal Gestor_de_textos.

Classe encarregada de gestionar el main principal del programa.

*/

#ifndef GESTOR_DE_TEXTOS_HH
#define GESTOR_DE_TEXTOS_HH

#include <vector>
#include <iostream>
#include <string>
#include "Conjunt_cites.hh"
#include "Conjunt_autors.hh"
#include "Text.hh"
#include "Autor.hh"
#include "Consultes.hh"

using namespace std;

/*
 * Classe Gestor_de_textos
*/

/** @class Gestor_de_textos
	@brief Representa un gestor de de textos, autors i cites.

*/
class Gestor_de_textos
{
public:
	//Consultores

	/** @brief Obtenir el conjunt d'autors de la classe.
		\pre cert
		\post Retorna l'objecte Conjunt_autors de la classe.
	*/
	static Conjunt_autors obtenir_conjunt_autors();
	
	/** @brief Obtenir el conjunt de cites de la classe.
		\pre cert
		\post Retorna l'objecte Conjunt_cites de la classe.
	*/
	static Conjunt_cites obtenir_conjunt_cites();
	
private:
	static Conjunt_autors autors;
	static Conjunt_cites cites;
	Consultes consultes;

	//Constructores

	Gestor_de_textos();

	//Modificadores

	/** @brief Primer nivell d'accés a una consulta de l'estil "afegir".
		@param consulta: String corresponent a la consulta a tractar.
		\pre La consulta enviada havia de tenir (l'string enviat per paràmetre 
		ja no té aquesta paraula) la paraula "afegir" en la posició inicial.
		\post S'haurà afegit el text o la cita (depenent del tipus de consulta) o s'haurà emés un error.
	*/
	void afegir(vector<string> consulta);
	/** @brief Afegeix el text especificat a la consulta a l'autor de la classe Conjunt_autors (si no existia l'autor, el crea).
		@param consulta: String corresponent a la consulta a tractar.
		\pre El primer que trobem al paràmetre es el títol del text entre cometes ("). La consulta ha d'estar ben formada.
		\post S'haurà afegit el text a l'autor, que també s'haurà afegit si encara no existia.
	*/
	void afegir_text(vector<string> consulta);
	/** @brief Afegeix la cita especificada a la consulta a l'objecte Conjunt_cites.
		@param consulta: String corresponent a la consulta a tractar.
		\pre El primer que trobem al paràmetre es el títol del text entre cometes ("). Ha d'haber un text triat previament a l'execució de la comanda. La consulta ha d'estar ben formada.
		\post S'haurà afegit la cita a l'objecte Conjunt_cites.
	*/
	void afegir_cita(vector<string> consulta);
	/** @brief Primer nivell d'accés a una consulta de l'estil "eliminar".
		@param consulta: String corresponent a la consulta a tractar.
		\pre La consulta enviada habia de tenir (l'string enviat per paràmetre 
		ja no té aquesta paraula) la paraula "eliminar" en la posició inicial.
		\post S'haurà eliminat el text seleccionat o la cita especificada.
	*/
	void eliminar(vector<string> consulta);
	/** @brief Elimina el text seleccionat amb anterioritat.
		@param consulta: String corresponent a la consulta a tractar.
		\pre Hi ha d'haber un text seleccionat i existent.
		\post S'haurà eliminat el text seleccionat i ja no hi haurà cap text seleccionat.
	*/
	void eliminar_text(vector<string> consulta);
	/** @brief Elimina la cita especificada pel paràmetre.
		@param consulta: String corresponent a la consulta a tractar.
		\pre La cita especificada a la consulta ha d'existir.
		\post S'haurà eliminat la cita especificada o emés un error en cas que aquesta no existeixi.
	*/
	void eliminar_cita(vector<string> consulta);
	/** @brief Tria un text emmagatzemat al sistema per duur a terme accions posteriors.
		@param consulta: String corresponent a la consulta a tractar.
		\pre La consulta ha d'estar ben formada i ser del tipus "triar text".
		\post S'haurà seleccionat el text que contingui totes les paraules especificades a la consulta. En el cas que no existeixi o hi hagi més d'un, s'emetrà un error.
	*/
	void triar_text(vector<string> consulta);
	/** @brief Substitueix l'aparició d'una paraula per una altre al text triat anteriorment.
		@param consulta: String corresponent a la consulta a tractar.
		\pre Ha d'haber un text triat amb anterioritat. La consulta ha d'estar ben formada i ser del tipus "substituir".
		\post S'hauran substituit totes les aparicions de la paraula a substituir per la paraula de substitució.
	*/
	void substituir_paraules(vector<string> consulta);

};

#endif
