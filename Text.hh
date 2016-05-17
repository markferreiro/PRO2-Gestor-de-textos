/** @file Text.hh
	@brief Especificació de la classe Text.

Classe utilitzada per la caracterització dels textos que el sistema emmagatzemarà.

*/

#ifndef TEXTOS_HH
#define TEXTOS_HH

#include <vector>
#include <map>
#include <list>

/*
 * Classe Text
*/

/** @class Text
	@brief Representa els textos que el sistema emmagatzema.

*/
class Text
{
	public:
		//Constructores

		/** @brief Constructor de la classe.
			@param titol: Titol del text.
			@param frases: Vector de les frases del text.
			\pre cert
			\post Retorna un nou objecte de tipus Text amb el titol i les frases inicialitzats.
		*/
		Text(string titol);
		
		//Modificadores
		
		/** @brief Afegeix el contingut al Text
			\pre cert
			\post El parametre implicit queda amb el seu contingut
		*/
		void afegir_contingut (vector<vector<string> > frases);
		
		/** @brief Modifica el titol del Text
			\pre cert
			\post el titol del Text queda modificat i ara es "titol"	
		*/
		void modificar_titol(string titol);

		//Consultores

		/** @brief Retorna el titol del text del paràmetre implicit.
			\pre El paràmetre implícit ha de tenir un titol.
			\post Retorna l'string equivalent al titol del text.
		*/
		string consultar_titol();
		/** @brief Retorna la frase del paràmetre implícit d'una posició X determinada (1 <= X <= nº frases).
			@param posicio: Posició de la frase que es vol consultar.
			\pre Sent X la posició demanada, el paràmetre implícit ha de cumplir que 1 <= X <= nº frases.
			\post Retorna l'string equivalent a la frase de la posició demanada.
		*/
		string consultar_frase(int posicio);
		/** @brief Retorna el contingut del paràmetre implícit.
			\pre cert
			\post Retorna un vector amb totes les frases del paràmetre implícit (buit si no en té).
		*/
		vector<vector<string> > consultar_contingut();
		/** @brief Retorna totes les frases entre les posicions X i Y (ambdues incloses).
			@param x Index més petit del conjunt de frases a consultar.
			@param y Index més gran del conjunt de frases a consultar.
			\pre El paràmetre implícit ha de cumplir que 1 <= X <= Y <= nº frases.
			\post Retorna un vector amb totes les frases del paràmetre implícit (buit si no en té).
		*/
		map<int, vector<string> > consultar_frases (int x, int y);
		/** @brief Retorna un vector amb la taula de frequencia del contingut del paràmetre implicit.
			\pre cert
			\post Retorna un vector amb la taula de frequencia del contingut del paràmetre implícit. 
		*/
		vector<list<string> > consultar_taula_frequencies();
		/** @brief Retorna les frases que contenen l'string del paràmetre.
			\pre cert
			\post Retorna una llista amb les posicions de les frases del paràmetre implícit que contenen les paraules del paràmetre.
		*/
		list<int> obtenir_frases_amb_paraules(vector<string> paraules);
		/** @brief Substitueix les aparicions de la "paraula1" per la "paraula2".
			@param paraula1: Paraula que es vol substituir.
			@param paraula2: Paraula per la que es substituirà la "paraula1".
			\pre cert
			\post El paràmetre implícit queda modificat, habent-se substituit les aparicions de "paraula1" per "paraula2".
		*/
		void substitueix_paraula(string paraula1, string paraula2);
		/** @brief Comprova la existència de l'string "paraula" tant en el titol com en el contingut del paràmetre implícit.
			@param paraula: Paraula que es vol cercar en el text.
			\pre cert
			\post Es retornarà un True si s'ha trobat la paraula al titol o al contingut del paràmetre implícit. Es retornarà False en cas contrari.
		*/
		bool existeix_paraula(string paraula);
		/**@brief Consulta el nombre de frases del text
			\pre cert
			\post Retorna el numero de frases del text
		*/
		int consultar_numero_frases();

	private:
		string Titol;
		vector<vector<string> > frases;
		map<string, int> frequencies;

		//Modificadores
		
		/**@brief Modifica el contingut del p.i.
			\pre paraula1 es troba al p.i.
			\post el p.i. queda modificat amb la paraula2 en comptes de la paraula1
		*/
		void modificar_contingut(string paraula1, string paraula2);
		void construir_taula_de_frequencies();

}

#endif
