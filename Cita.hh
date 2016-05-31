/** @file Cita.hh
	@brief Especificació de la classe Cita.

Classe utilitzada per la caracterització de les cites que el sistema farà sobre els textos.

*/

#ifndef CITA_HH
#define CITA_HH

#include <map>
#include <string>
#include <vector>

using namespace std;

/*
 * Classe Cita
*/

/** @class Cita
	@brief Representa les cites fetes sobre els textos emmagatzemades al sistema.

*/
class Cita
{
	public:
		//Constructores

		Cita();

		/** @brief Constructor de la classe.
			@param nom_autor: Nom de l'autor del text al que fa referéncia la cita.
			@param titol_text: Titol del text sobre el que es crea la cita.
			@param referencia: Referencia de la cita.
			@param frases: Mapa de les frases a afegir a la cita.
			
			\pre cert
			\post Retorna un nou objecte de tipus Cita amb tots els seus parametres inicialitzats.
		*/
		Cita(string nom_autor, string titol_text, string referencia, int x, int y, map<int, string> frases);
		
		//Consultores

		/** @brief Retorna el titol del text al que fà referencia el paràmetre implicit.
		
			\pre El paràmetre implícit ha d'haber sigut inicialitzat.
			\post Retorna l'string equivalent al titol del text al que fà referencia la.
		*/
		string consultar_titol();
		
		/** @brief Retorna la referencia del paràmetre implícit.
		
			\pre El paràmetre implícit ha d'haber sigut inicialitzat.
			\post Retorna l'string equivalent a la referencia del paràmetre implícit.
		*/
		
		string consultar_referencia();
		/** @brief Retorna el nom de l'autor del text al que fà referencia el paràmetre implícit.
		
			\pre El paràmetre implícit ha d'haber sigut inicialitzat.
			\post Retorna l'string equivalent al nom de l'autor del text al que fà referencia el paràmetre implícit.
		*/
		string consultar_nom_autor();
		
		/** @brief Retorna totes les frases del paràmetre implícit.
		
			\pre cert
			\post Retorna un vector amb totes les frases del paràmetre implícit (buit si no en té).
		*/
		pair<int, int> consultar_x_y();
		
		/** @brief Obtenir frases de la cita
		
			/pre El p.i. conte frases
			/post Retorna un map<int, string> on l'int es l'indez de la frase, i l'string la frase, amb les frases
			que componen el p.i.
		*/
		map<int, string> obtenir_frases();

	private:
		string referencia, nom_autor, titol_text;
		int x, y;
		map<int, string> frases;
};

#endif
