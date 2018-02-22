//Author: Lukas Paulmann
//Datum: 27.08.2017		
//Version: 1.0

//Beginn der Definition von HashTabelle
#ifndef HashTabelle_H
#define HashTabelle_H	

//Bibliotheken
#include <vector>

//Bindedt die Objekte ein
#include "Objekt.h"

using namespace std;

//Hashtabelle die Objekte Speichert und die Bearbetung erlaubt
class HashTabelle
{
	private:
		char Kollisionsbehandlung;
		int Schluesselanzahl;
		vector<Objekt> Tabelle;								//Ein Vector der Objekte der Objektklasse hält
	
	public:
		HashTabelle(int, char);								//Konstruktor
		void Einfuegen(Objekt);								//Fügt ein Objekt über eine im Konstruktor gewählte Kollisionsbehandlung ein
		int Suchen(int);									//Sucht ein Objekt anhand seiner ID
		void Loeschen(int);									//Löscht ein Objekt anhand siner ID
		void DropTabelle();									//Löscht die Hashtabelle
		void LinearesSondieren(int);						//Eine der Kollisionsbehandlungsmöglichkeiten für das Einfügen
		void QuadratischesSondieren(int);					//Eine der Kollisionsbehandlungsmöglichkeiten für das Einfügen
		void DoppeltesHashing(int);							//Eine der Kollisionsbehandlungsmöglichkeiten für das Einfügen
};
#endif