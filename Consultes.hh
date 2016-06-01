/** @file Consultes.hh
	@brief Especificaci� de la classe Consultes
*/

#ifndef CONSULTES_HH
#define CONSULTES_HH

#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include "Conjunt_autors.hh"
#include "Conjunt_cites.hh"
#include "Cita.hh"

using namespace std;
/*
 * Classe Consultes
 */

/** @class Consultes
	@brief Representa un processador de consultes sobre autors, textos i cites en el gestor de textos

*/

class Consultes
{
public:

	Conjunt_autors autors;
	Conjunt_cites cites;
	
	/** @brief Processador de consultes
		@param consulta: String corresponent a la consulta a processar.
		
		/pre cert
		/post haura fet la consulta que ens indica "consulta"

	*/
	void processar_consulta (string consulta, Conjunt_autors autors, Conjunt_cites cites);
	
private:

	struct classcomp
	{
		bool operator() (const Autor& lhs, const Autor& rhs) const;
		bool operator() (const Text& lhs, const Text& rhs) const;
	};
	
	/** @brief Processador consultes que comencen per "tots"
		@param consulta: String corresponent a la consulta a processar.
		
		/pre s'ha llegit la primera paraula de la consulta i es "tots"
		/post s'haura fet la consulta "tots textos ?" o "tots autors ?"
		
	*/
	void tots (string consulta);

	/** @brief Processador consulta "tots textos ?"

		/pre la consulta processada anteriorment es "tots textos ?"
		/post mostra tots els textos emmagatzemats en el sistema (nom�s el t�tol
		 i l'autor de cada text) ordenats per autor i despr�s per t�tol

	*/
	void tots_textos();

	/** @brief Processador consulta "tots autors ?"

		/pre la consulta processada anteriorment es "tots autors ?"
		/post mostra tots els autors amb textos al sistema (ordenats alfabeticament) indicant el nombre de
		 textos que hi consten, el nombre total de frases i de paraules del contingut dels seus textos

	*/
	void tots_autors();

	/** @brief Processador consulta "totes cites ?"

		/pre s'ha comprovat que la consulta es "totes cites ?"
		/post mostra totes les cites emmagatzemades al sistema, indicant per a cada cita la seva referencia,
		 el contingut de les frases i l'autor i titol del text d'on provenen, ordenades per referencia

	*/
	void totes_cites();

	/** @brief Processador de consultes que comencen per "info"
		@param consulta: String corresponent a la consulta a processar.
		/pre s'ha llegit la primera paraula de la consulta i es "info"
		/post s'haura fet la consulta "info ?", que mostra informacio de l'ultim text triat indicant
		 l'autor, titol, nombre de frases, nombre de paraules i cites associades; o "info cita "<referencia> ?";
		 emet un error si no hi ha cap text triat

	*/
	void  info (string consulta);

	/** @brief Processador consulta "info cita <referencia> ?"
		@param referencia: String corresponent a la referenica a consultar.
		
		/pre s'ha comprovat que la consulta es "info cita <referencia> ?"
		/post mostra informacio d'una cita, indicant l'autor i titol d'on provenen,
		 numero de la frase inicial i final, i el contingut de la frase o frases que la componen

	*/
	void info_cita(string referencia);

	/** @brief Processador de les consultes que comencen per "frases"
		@param consulta: String corresponent a la consulta a processar.
		
		/pre s'ha llegit la primera paraula de la consulta i es "frases"
		/post s'haura fet la consulta "frases x y ?", "frases (expressio) ?" o "frases "sequencia" ?"

	*/
	void frases (string consulta);

	/** @brief Processador de la consulta "frases x y ?"
		@param x: Part petita (posici� m�s petita) del rang de frases que es vol agafar del text.
		@param y: Part gran (posici� m�s gran) del rang de frases que es vol agafar del text.
		
		/pre s'ha comprovat que la consulta es "frases x y ?"
		/post mostra les frases entre la x-esima i la y-esima del contingut de l'ultim text triat, extrems
		 inclosos; emetra un error si l'interval de frases no es valid, es valid si 1 <= x <= y <= n,
		 on n es el nombre total de frases, o si no hi ha cap text triat

	*/
	void frases_text_triat (int x, int y);

	/** @brief Processador de la comanda "frases <expressio> ?"
		@param expressio: String corresponent a la expressi� corresponent a la consulta "frases <expresi�>".
		
		/pre s'ha comprovat que la comanada es "frases <expressio> ?"
		/post mostra les frases del contingut de l'ultim text triat que copleixen l'expressio,
		 indicant per a cada frase el seu numero i el contingut, ordenades creixentment pel
		 numero; emetra un error si no hi ha cap text triat

	*/
	void frases_expressio (string expressio);
	
	/** @brief Funcio recursiva auxiliar de frases_expressio
		@param consulta: expressio per trobar a la frase
		@param frase: frase del text on es vol trobar l'expressio de consulta
		
		/pre cert
		/post retorna true si a frase es troben les paraules com indica l'expressio, retorna false si no
	*/
	bool frases_expressio_algebraica(string consulta, Text text, int i);

	/** @brief Processador de la consulta "frases "sequencia" ?"
		@param sequencia: String corresponent a la seq�encia de paraules a utilitzar en la consulta.
		
		/pre s'ha comprovat que la consulta es "frases "sequencia"?"
		/post mostra les frases on hi apareix (consecutivament, sense signes de puntuacio) la "sequencia"
		 en el contingut de l'ultim text triat; emetra un error si no hi ha cap text triat

	*/
	void frases_sequencia (vector<string> paraules);

	/** @brief Processador de consultes que comencen per "nombre de"
		@param consulta: String corresponent a la consulta a processar.
		
		/pre s'ha llegit les primeres paraules de la consulta i es "nombre de"
		/post s'haura fet la consulta "nombre de frases ?" o "nombre de paraules ?"

	*/
	void nombre_de (string consulta);

	/** @brief Processador de la consulta "nombre de frases ?"

		/pre s'ha comprovat que la consulta es "nombre de frases ?"
		/post mostra el nombre de frases del contingut de l'ultim text triat, emetra un error si no hi ha cap text triat

	*/
	void nombre_de_frases ();

	/** @brief Processador de la consulta "nombre de paraules ?"

		/pre s'ha comprovat que la consulta es "nombre de paraules ?"
		/post mostra el nombre de paraules de l'ultim text triat; emetra un error si no hi ha cap text triat

	*/
	void nombre_de_paraules();
	
	/** @brief Processador de consultes que comencen per "cites"
		@param consulta: String corresponent a la consulta a processar.
		
		/pre s'ha llegit la primera paraula de la consulta i es "cites"
		/post s'haura fet la consulta "cites ?", que mostra les cites de l'ultim text triat indicant
		 la referencia i les frases de cada cita; o "cites autor "<autor> ?";
		 emet un error si no hi ha cap text triat

	*/
	void cites_consultar (string consulta);
	
	/** @brief Processador de consulta "cites autor "<autor>"?"
	
		\pre s'ha comprovat que la consulta es "cites autor "<autor>"?"
		\post s'haura realitzat la consulta, mostrant totes les cites de l'autor de Nom = nom, mostrant la referencia
		i frases de cada cita
		
	*/
	void cites_autor (string nom, Conjunt_autors autors);
	
	/** @brief Processador de la consulta "textos autor "<autor>" ?"
		@param nom: Nom de l'autor del que es volen obtenir els textos.
		
		/pre s'ha comprovat que la consulta es "textos autor "<autor>" ?"
		/post mostra tots els textos d'un determindat autor (nomes el titol de cada text) ordenats
		 alfabeticament per titol; emetra un error si no hi ha cap text triat

	*/
	void textos_autor (string nom);

	/** @brief Processador de la consulta "autor ?"

		/pre s'ha comprovat que la consulta es "autor ?"
		/post mostra l'autor de l'ultim text triat; emetra un error si no hi ha cap text triat

	*/
	void autor ();

	/** @brief Processador de la consulta "contingut ?"

		/pre s'ha comprovat que la consulta es "contingut ?"
		/post mostra el contingut de l'ultim text triat amb les frases numerades a partir
		 de l'1; emetra un error si no hi ha cap text seleccionat

	*/
	void contingut ();

	/** @brief Processador de la consulta "taula de frequencies ?"

		/pre s'ha comprovat que la consulta es "taula de frequencies ?"
		/post mostra totes les paraules del contingut de l'ultim text triat ordenades
		 decreixentment per frequencia (per a cada paraula el string que la representa
		 i la seva frequencia), en cas d'empat de frequencia, les paraules s'ordenen
		 creixentment, primer de llargada i despres alfabeticament; emetra un error
		 si no hi ha cap text triat

	*/
	void taula_de_frequencies();
	
	/** @brief Escriu una cita
	
		\pre la cita es valida
		\post escriu la referencia de la cita seguida de les frases de la cita
		
	*/
	void escriure_cita(Cita& cita);
	
	bool conte_paraula(string paraula, string frase);

	vector<string> split(string str, char delimiter);
};

#endif
