OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

Gestor_de_textos.exe: Gestor_de_textos.o Cita.o Autor.o Text.o Conjunt_autors.o Conjunt_cites.o Consultes.o
	g++ -o Gestor_de_textos Gestor_de_textos.o Cita.o Autor.o Text.o Conjunt_autors.o Conjunt_cites.o Consultes.o
	rm *.o

Text.o: Text.cc Text.hh
	clang++ -c Text.cc $(OPCIONS)

Autor.o: Autor.cc Autor.hh Text.hh
	clang++ -c Autor.cc $(OPCIONS)

Cita.o: Cita.cc Cita.hh
	clang++ -c Cita.cc $(OPCIONS)

Consultes.o: Consultes.cc Consultes.hh
	clang++ -c Consultes.cc $(OPCIONS)

Conjunt_autors.o: Conjunt_autors.cc Conjunt_autors.hh Autor.hh
	clang++ -c Conjunt_autors.cc $(OPCIONS)

Conjunt_cites.o: Conjunt_cites.cc Conjunt_cites.hh Cita.hh Text.hh Autor.hh
	clang++ -c Conjunt_cites.cc $(OPCIONS)

Gestor_de_textos.o: Gestor_de_textos.cc Gestor_de_textos.hh Conjunt_cites.hh Conjunt_autors.hh Text.hh Autor.hh Consultes.hh
	clang++ -c Gestor_de_textos.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
