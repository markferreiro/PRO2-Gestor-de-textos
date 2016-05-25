OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x
OPCIONS2 = -D_GLIBCXX_DEBUG

Gestor_de_textos.exe: Gestor_de_textos.o Cita.o Autor.o Text.o Conjunt_autors.o Conjunt_cites.o Consultes.o
	g++ -o Gestor_de_textos Cita.o Autor.o Text.o Conjunt_autors.o Conjunt_cites.o Consultes.o Gestor_de_textos.o -v
	rm *.o

Text.o: Text.cc Text.hh
	g++ -c Text.cc $(OPCIONS2)

Autor.o: Autor.cc Autor.hh Text.hh
	g++ -c Autor.cc $(OPCIONS2)

Cita.o: Cita.cc Cita.hh
	g++ -c Cita.cc $(OPCIONS2)

Consultes.o: Consultes.cc Consultes.hh
	g++ -c Consultes.cc $(OPCIONS2)

Conjunt_autors.o: Conjunt_autors.cc Conjunt_autors.hh Autor.hh
	g++ -c Conjunt_autors.cc $(OPCIONS2)

Conjunt_cites.o: Conjunt_cites.cc Conjunt_cites.hh Cita.hh Text.hh Autor.hh
	g++ -c Conjunt_cites.cc $(OPCIONS2)

Gestor_de_textos.o: Gestor_de_textos.cc Gestor_de_textos.hh Conjunt_cites.hh Conjunt_autors.hh Text.hh Autor.hh Consultes.hh
	g++ -c Gestor_de_textos.cc $(OPCIONS2)

clean:
	rm *.o
	rm *.exe
	rm *.gch
