# Author: Lukas Paulmann
# Datum: 27.08.2017		
# Version: 1.0

Hashtabelletest: main.o Hashtabelle.o Objekt.o
	g++ -Wall -o Hashtabelletest main.o Hashtabelle.o Objekt.o

main.o: main.cpp Hashtabelle.h Objekt.h
	g++ -Wall -c main.cpp

Hashtabelle.o: Hashtabelle.cpp Objekt.h Hashtabelle.h 
	g++ -Wall -c Hashtabelle.cpp
	
Objekt.o: Objekt.cpp Objekt.h
	g++ -Wall -c Objekt.cpp
