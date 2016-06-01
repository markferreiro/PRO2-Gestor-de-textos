/** @file Text.hh
	@brief Especificació de la classe Text.

Classe utilitzada per la caracterització dels textos que el sistema emmagatzemarà.

*/

#ifndef TEXTOS_HH
#define TEXTOS_HH

#include <vector>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

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
	
		Text();
		
		/** @brief Constructor de la classe.
			@param titol: Titol del text.
			@param frases: Vector de les frases del text.
			
			\pre cert
			\post Retorna un nou objecte de tipus Text amb el titol i les frases inicialitzats.
		*/
		Text(string titol, vector<vector<string> > frases);
		
		/** @brief Constructor alternatiu de la classe.
			@param titol: Titol del text.
			
			\pre cert
			\post Retorna un nou objecte de tipus Text amb el titol i les frases sense inicialitzar.
		*/
		Text(string titol);


		//Modificadores

		/** @brief Afegeix el contingut al Text
			@param frases: contingut que s'ha d'afegir al p.i.
			
			\pre cert
			\post El parametre implicit queda amb el seu contingut
		*/
		void afegir_contingut (vector<string> frases);

		/** @brief Modifica el titol del Text
			@param titol: el nou titol que es vol posar al p.i.
			
			\pre cert
			\post el titol del Text queda modificat i ara es "titol"
		*/
		void modificar_titol(string titol);
		
		/** @brief Substitueix les aparicions de la "paraula1" per la "paraula2".
			@param paraula1: Paraula que es vol substituir.
			@param paraula2: Paraula per la que es substituirà la "paraula1".
			
			\pre cert
			\post El paràmetre implícit queda modificat, habent-se substituit les aparicions de "paraula1" per "paraula2".
		*/
		void substitueix_paraula(string paraula1, string paraula2);

		//Consultores

		/** @brief Retorna el titol del text del paràmetre implicit.
		
			\pre El paràmetre implícit ha de tenir un titol.
			\post Retorna l'string equivalent al titol del text.
		*/
		string consultar_titol() const;
		
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
		vector<string> consultar_contingut();
		
		/** @brief Retorna totes les frases entre les posicions X i Y (ambdues incloses).
			@param x Index més petit del conjunt de frases a consultar.
			@param y Index més gran del conjunt de frases a consultar.
			
			\pre El paràmetre implícit ha de cumplir que 1 <= X <= Y <= nº frases.
			\post Retorna un vector amb totes les frases del paràmetre implícit (buit si no en té).
		*/
		map<int, string > consultar_frases (int x, int y);

		/** @brief Retorna un vector amb la taula de frequencia del contingut del paràmetre implicit.
		
			\pre cert
			\post Retorna un vector amb la taula de frequencia del contingut del paràmetre implícit.
		*/
		vector<vector<string> > consultar_taula_frequencies();
		
		/** @brief Retorna si la frase i conte les paraules del par?metre.
			@param i: index de la frase que es vol consultar
			@param paraules: paraules que es volen trobar a la frase
		
			\pre cert
			\post Retorna true si la frase i conte les paraules del par?metre, false si no.
		*/
		bool conte_paraules(int i, vector<string> paraules);
		
		/** @brief Comprova si la frase i conte la paraula
			@param i: index de la frase que es vol consultar
			@param paraula: paraula que es volen trobar a la frase
			
			\pre cert
			\post Retorna true si la frase i conte la paraula del parametre, false si no;
		*/
		bool conte_paraula(string paraula, int i);
		
		/** @brief Retorna true si la frase i conte les paraules que indica l'expressio del parametre.
		
			\pre cert
			\post Retorna true si la frase i conte les paraules del par?metre d'acord amb l'expressio, false si no.
		*/
		bool conte_expressio(string expressio);
		
		/** @brief Comprova la existència de l'string "paraula" tant en el titol com en el contingut del paràmetre implícit.
			@param paraula: Paraula que es vol cercar en el text.
			
			\pre cert
			\post Es retornarà un True si s'ha trobat la paraula al titol o al contingut del paràmetre implícit. Es retornarà False en cas contrari.
		*/
		pair<int,int> existeix_paraula (string paraula);

		/**@brief Consulta el nombre de frases del text
		
			\pre cert
			\post Retorna el numero de frases del text
		*/
		int consultar_numero_frases();

		/**@brief Consulta el nombre de paraules del text
		
			\pre cert
			\post Retorna el numero de paraules del text
		*/
		int consultar_numero_paraules();

		bool rang_correcte(int x, int y);

	private:
		string titol;
		vector< string > frases;
		struct classcomp
		{
		    bool operator() (const std::string& lhs, const std::string& rhs) const;
		};
		map <string, int, classcomp> frequencies;

		//Modificadores

		void modificar_contingut(string paraula1, string paraula2);
		void construir_taula_de_frequencies();
		int consultar_frequencia_maxima();
		vector<string> split(string str, char delimiter);
		void replaceAll( string& source, const string& from, const string& to );
		string clean_word (string paraula);

};

#endif
