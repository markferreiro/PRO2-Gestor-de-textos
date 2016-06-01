OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o Cita.o Autor.o Text.o Conjunt_autors.o Conjunt_cites.o Consultes.o
	g++ program.o Cita.o Autor.o Text.o Conjunt_autors.o Conjunt_cites.o Consultes.o -o program.exe
	tar -cvf practica.tar program.cc program.hh Conjunt_autors.cc Conjunt_autors.hh Conjunt_cites.cc Conjunt_cites.hh Autor.cc Autor.hh Text.cc Text.hh Cita.cc Cita.hh Consultes.cc Consultes.hh
	#rm *.o

program.o: program.cc Conjunt_cites.hh Conjunt_autors.hh Consultes.hh
	g++ -c program.cc $(OPCIONS)

Conjunt_autors.o: Conjunt_autors.cc Autor.hh
	g++ -c Conjunt_autors.cc $(OPCIONS)

Conjunt_cites.o: Conjunt_cites.cc Cita.hh Text.hh Autor.hh
	g++ -c Conjunt_cites.cc $(OPCIONS)

Autor.o: Autor.cc Text.hh
	g++ -c Autor.cc $(OPCIONS)

Text.o: Text.cc Text.hh
	g++ -c Text.cc $(OPCIONS)

Cita.o: Cita.cc Cita.hh
	g++ -c Cita.cc $(OPCIONS)

Consultes.o: Consultes.cc Consultes.hh
	g++ -c Consultes.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
