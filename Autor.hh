/** @file Autor.hh
	@brief Especificació de la classe Autor.

Classe utilitzada per la caracterització dels autors dels textos.

*/

#ifndef AUTORS_HH
#define AUTORS_HH

#include <set>
#include "Text.hh"
#include <iostream>

using namespace std;

/*
 * Classe Autor
*/

/** @class Autor
	@brief Representa els autors dels textos del sistema.

*/
class Autor
{
	public:
		struct custom_sort {
				bool operator()(const Text& a, const Text& b) const;
		};
		
		//Constructores

		/** @brief Constructor de la classe.
			@param nom: Nom de l'autor.
			@param referencia: Referencia de l'autor.
			
			\pre cert
			\post Retorna un nou objecte de tipus Autor amb el nom i la referencia inicialitzats.
		*/
		Autor(string nom, string referencia);
		

		//Consultores

		/** @brief Retorna el nom del paràmetre implicit.
		
			\pre El paràmetre implícit ha de tenir un nom.
			\post Retorna l'string equivalent al nom de l'autor.
		*/
		
		string consultar_nom() const;
		
		/** @brief Retorna la referencia del paràmetre implicit.
		
			\pre El paràmetre implícit ha de tenir una referencia.
			\post Retorna l'string equivalent a la referencia del paràmetre implícit.
		*/
		
		string consultar_referencia();
		
		/** @brief Retorna el titol de cada text de l'autor.
		
			\pre cert
			\post Retorna un vector amb el titol de cada text del parametre implicit.
			*/
		
		vector<string> consultar_titol_textos() const;
		
		/** @brief Retorna un objecte "set" amb tots els Textos del paràmetre implícit.
		
			\pre cert
			\post Retorna un objecte "set" amb els textos del paràmetre implícit. Si el paràmetre implícit no té textos, el set estarà buit.
		*/
		
		int nombre_de_textos() const;
		
		/** @brief Retorna el nombre de frases de l'autor.
		
			\pre cert
			\post Retorna retorna el nombre de frases de l'autor.
		*/
		
		int nombre_de_frases();
		
		/** @brief Retorna el nombre de paraules de l'autor.
		
			\pre cert
			\post Retorna retorna el nombre de paraules de l'autor.
		*/
		
		int nombre_de_paraules();
		
		/** @brief Comprova si el paràmetre implícit ja té un text amb un titol rebut per paràmetre.
			@param titol: Titol del text a buscar.
			
			\pre cert
			\post Retorna "True" si el paràmetre implícit ja té un text amb el titol rebut. Retorna "False" en cas contrari.
		*/
		
		bool existeix_titol(string titol);
		
		/** @brief Comprova si el paràmetre implícit ja té un text amb un titol rebut per paràmetre.
			@param titol: Titol del text a buscar.
			
			\pre cert
			\post Retorna "True" si el paràmetre implícit ja té un text amb el titol rebut. Retorna "False" en cas contrari.
		*/
		
		set<Text, custom_sort>::iterator existeix_text(string titol) const;
		
		/** @brief Comprova si el paràmetre implícit té un text en el qual aparegui unes paraules no necessariament seguides (tant en el titol com en el contingut).
			@param paraula: Paraules a cercar.
			
			\pre cert
			\post Retorna el Text en el que apareixen les paraules del paràmetre si n'existeix un al paràmetre implícit. Retorna un Text de titol "NULL" si no existeix cap o m�s d'un.
		*/
		
		Text existeix_text_amb_paraules(vector<string> paraules);
		
		/** @brief Obtenir text
			@param titol: titol del text que es vol obtenir
			
			/pre cert
			/post Retorna el text de Titol = titol; retorna un text amb Titol = "NULL"
		*/
		Text obtenir_text(string titol);

		//Modificadores

		/** @brief Afegeix un text al paràmetre implícit, retornant el resultat de l'operació.
			@param text: Objecte del tipus Text a afegir.
			
			\pre L'objecte del paràmetre ha d'estar correctament definit.
			\post El paràmetre implícit tindrà afegit aquest nou Text sempre i quan no existís cap Text amb el mateix titol. El boolea ens diu si s'ha pogut afegir (True) o no (False).
		*/
		
		bool afegir_text(Text text);
		
		/** @brief Consulta tots els textos de l'autor
		
			/pre cert
			/post Retorna un vector amb un string per cada text de l'autor, el string es el titol del text.
		*/
		vector<string> tots_textos();
		
		/** @brief Elimina el text del paràmetre implícit amb un titol en concret, retornant el resultat de l'operació.
			@param titol: Titol del text a eliminar.
			
			\pre cert
			\post El parametre implicit ja no té el Text amb titol = paràmetre. Retorna "True" si s'ha eliminat el Text. Retorna "False" en cas que no s'hagi trobat cap text.
		*/
		
		bool eliminar_text(string titol);

	private:
		string nom, referencia;
		set<Text, custom_sort> textos;
		vector<string> split(string str, char delimiter);
};

#endif
