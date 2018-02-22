//Author: Lukas Paulmann
//Datum: 27.08.2017		
//Version: 1.0			

//Bibliotheken
#include <vector>
#include <iostream>
#include <fstream>

//Dateien
#include "Objekt.h"
#include "HashTabelle.h"

using namespace std;

//Muss geändert werden////////////////////////////////////////////////////////////////
string TextdateiNameAusgabe = "TestdatenAusgabeD.txt";								//Outputdatei
//////////////////////////////////////////////////////////////////////////////////////

//Globale Variabelen
int GesamteEinfuegeSchritte = 0;


HashTabelle::HashTabelle(int SchluesselanzahlNeu, char KollisionsbehandlungNeu)
{
	Schluesselanzahl = SchluesselanzahlNeu;
	Kollisionsbehandlung = KollisionsbehandlungNeu;
	
	//Initialisiert den Vector mit Objekten mit ObjektID: 0
	for(int i =1; i <= Schluesselanzahl; i++)
	{
		Tabelle.push_back(Objekt(0));
	}
}


void HashTabelle::DropTabelle()
{
	
	ofstream ZielDateiHashTabelle(TextdateiNameAusgabe, ios_base::out | ios_base::app);							//Erzeugt einen Datenstream für die Ausgabedatei
	
	ZielDateiHashTabelle << "Tabelle geloescht!";
	ZielDateiHashTabelle.close();																				//Beendedt den Zugriff auf das Zieldokument
	delete(this);
}


void HashTabelle::Einfuegen(Objekt obj)
{
	//Variabelen
	int ObjektID = obj.getObjektID();
	
	ofstream ZielDateiHashTabelle(TextdateiNameAusgabe, ios_base::out | ios_base::app);
	
	//Wählt die gewünschte EinfügeMetohden
	switch(Kollisionsbehandlung) 
	{
		case 'L' :
			LinearesSondieren(ObjektID);
			ZielDateiHashTabelle << "Objekt mit ID: " << ObjektID << " Eingefuegt  nach " << GesamteEinfuegeSchritte << " Schritten\n";
			GesamteEinfuegeSchritte = 0;
			ZielDateiHashTabelle.close();
			break;
		case 'Q' :
			QuadratischesSondieren(ObjektID);
			ZielDateiHashTabelle << "Objekt mit ID: " << ObjektID << " Eingefuegt  nach " << GesamteEinfuegeSchritte << " Schritten\n";
			GesamteEinfuegeSchritte = 0;
			ZielDateiHashTabelle.close();
			break;
		case 'D' :
			DoppeltesHashing(ObjektID);
			ZielDateiHashTabelle << "Objekt mit ID: " << ObjektID << " Eingefuegt  nach " << GesamteEinfuegeSchritte << " Schritten\n";
			GesamteEinfuegeSchritte = 0;
			ZielDateiHashTabelle.close();
			break;
	}
}
 
 
int HashTabelle::Suchen(int ObjektID) 
{
	//Variabelen
	int Position = 0;
	bool Gefunden = false;
	int Schritzahl = 0;
	
	ofstream ZielDateiHashTabelle(TextdateiNameAusgabe, ios_base::out | ios_base::app);
	
	//Läuft die Schlüsselanzahl mal durch
	for(int i = 1; i <= Schluesselanzahl; i++)
	{
		//Wenn das Objekt gefunden wurde
		if(ObjektID == Tabelle[i].getObjektID())
		{
			Gefunden = true;
			Position = i;
			ZielDateiHashTabelle << "Gefunden nach " << Schritzahl << " Schritten";
			Schritzahl = 0;
			break;
		}
	}
	
	//Gibts das Ergebniss der Suche in der Datei aus
	if(Gefunden)
	{
		ZielDateiHashTabelle << "Such ErgebnisID: " << ObjektID << " Position: " << Position;
	}
	else
	{
		ZielDateiHashTabelle << "Suchergebnis: NULL";
	}
	
	ZielDateiHashTabelle.close();	
	return Position;																				//Gibt die Position des Objektes im Vector an
}


void HashTabelle::Loeschen(int ObjektID)
{
	//Variabelen
	int LoeschzielPosition = Suchen(ObjektID);
	
	//Wenn die ObjektID des Objektes an der Suchposition nicht 0 ist 
	if(LoeschzielPosition != 0)
	{
		Tabelle.erase(Tabelle.begin() + LoeschzielPosition);									//Löscht er das Objekt
	}
}


void HashTabelle::LinearesSondieren(int ObjektID)
{	
	//Variabelen
	int i = ((ObjektID + 1)% Schluesselanzahl);
	bool Eingefuegt = false;
	int Schritzahl = 0;
	
	ofstream ZielDateiHashTabelle(TextdateiNameAusgabe, ios_base::out | ios_base::app);
	
	//Versucht das Objekt mittels liniarer Sondierung einzufügen
	try
	{
		//Solange das Objekt noch nich eingefügt wurde
		while(!Eingefuegt)
		{	
			//Wenn er 10000 mal versucht hat einzufügen aber keinen freien Platz gefunden hat
			if(Schritzahl >= 10000)
			{
				//Läuft den Vector druch
				for( int j = 1; j <= Schluesselanzahl ; j++)
				{
					//Fügt das mommentane Objekt beim ersten Objekt mit ID 0 im Vector ein
					if(Tabelle[j].getObjektID() == 0)
					{
						Tabelle.insert((Tabelle.begin() + j), ObjektID);
						Schritzahl++;
						Eingefuegt = true;
					}
				}
				
				Schritzahl++;
			}
			//Wenn das Feld schon belegt ist gehe eins weiter sonst füge eine
			if(Tabelle[i].getObjektID() !=  0)
			{
				i++;
				i = ((ObjektID + i)% Schluesselanzahl);
				Schritzahl++;
			}
			else
			{
				Tabelle.insert((Tabelle.begin() + i), ObjektID);
				Eingefuegt = true;
				i = ((ObjektID + 1)% Schluesselanzahl);
				Schritzahl++;
			}
		}
		
		//Setzt die ganzen Variabelen zurück
		Eingefuegt = false;
		GesamteEinfuegeSchritte = GesamteEinfuegeSchritte + Schritzahl;
		Schritzahl = 0;
		ZielDateiHashTabelle.close();
	}
	//Wenn fehler auftreten wird gesgt das die Tabelle voll is
	catch(...)
	{
		ZielDateiHashTabelle << "Tabelle ist zu voll";
	}
	
	ZielDateiHashTabelle.close();
}


void HashTabelle::QuadratischesSondieren(int ObjektID)
{
	int i = ((ObjektID + (1*1))% (Schluesselanzahl));
	bool Eingefuegt = false;
	int Schritzahl = 0;
	ofstream ZielDateiHashTabelle(TextdateiNameAusgabe, ios_base::out | ios_base::app);
	
	try
	{
		while(!Eingefuegt)
		{
			//Wenn nach 1000 Schritte kein Platz gefunden wurde probiers mit liniaren Sondieren
			if(Schritzahl >= 1000)
			{
				ZielDateiHashTabelle.close();
				LinearesSondieren(ObjektID);
				Schritzahl++;
				Eingefuegt = true;
			}
			else if(Tabelle[i].getObjektID() != 0)
			{	
				i++;
				i = ((ObjektID + (i*i))% (Schluesselanzahl));
				Schritzahl++;
			}
			else
			{
				Tabelle.insert((Tabelle.begin() + i), ObjektID);
				Eingefuegt = true;
				i = ((ObjektID + (1*1))% (Schluesselanzahl));
				Schritzahl++;
			}
		}
		
		Eingefuegt = false;
		GesamteEinfuegeSchritte = GesamteEinfuegeSchritte + Schritzahl;
		Schritzahl = 0;
	}
	catch(...)
	{
		ZielDateiHashTabelle<< "Tabelle ist zu voll";
	}
	
	ZielDateiHashTabelle.close();
}


void HashTabelle::DoppeltesHashing(int ObjektID)
{
	int i = (Schluesselanzahl% (1 * (1 + (ObjektID% (Schluesselanzahl)))));
	bool Eingefuegt = false;
	int Schritzahl = 0;
	ofstream ZielDateiHashTabelle(TextdateiNameAusgabe, ios_base::out | ios_base::app);
	
	try
	{
		while(!Eingefuegt)
		{
			//Wenn nach 1000 Schritte kein Platz gefunden wurde probiers mit liniaren Sondieren
			if(Schritzahl >= 1000)
			{
				ZielDateiHashTabelle.close();
				LinearesSondieren(ObjektID);
				Schritzahl++;
				Eingefuegt = true;
				
			}
			else if(Tabelle[i].getObjektID() != 0)
			{		
				i++;
				i = (Schluesselanzahl% (i * (1 + (ObjektID% (Schluesselanzahl)))));
				Schritzahl++;
			}
			else
			{
				Tabelle.insert((Tabelle.begin() + i), ObjektID);
				i = (Schluesselanzahl% (1 * (1 + (ObjektID% (Schluesselanzahl)))));
				Eingefuegt = true;
				Schritzahl++;
			}
		}
		Eingefuegt = false;
		GesamteEinfuegeSchritte = GesamteEinfuegeSchritte + Schritzahl;
		Schritzahl = 0;
	}
	catch(...)
	{
		ZielDateiHashTabelle << "Tabelle ist zu voll";
	}
	
	ZielDateiHashTabelle.close();
}