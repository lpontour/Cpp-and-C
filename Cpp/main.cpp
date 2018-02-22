//Author: Lukas Paulmann
//Datum: 27.08.2017		
//Version: 1.0

//Bibliotheken
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

//Dateien
#include "HashTabelle.h"
#include "Objekt.h"

using namespace std;

//Muss geändert werden////////////////////////////////////////////////
string TextdateiNameAusgabeMain = "TestdatenAusgabeD.txt";			//Outputdatei
string QuelldateiMain = "TestdatenKorrigiert.txt";					//Inputdatei
char Kollisionsbehandlung = 'D'; 									//D, Q oder L
//////////////////////////////////////////////////////////////////////

//Globale Variabelen
int SchluesselAnzahl = 1;
vector<Objekt> Objekte;					//Ein Vector der die Objekte aus Dokument hält
int ObjektAnzahl = 1;
int ZahlI = 0;							//Enthählt später die aus den Dokument gewonenen einzelnen ObjektIDs0

//Erzeugt die Objekt aus dem Dokument und gibt sie in einem Vector zurueck
void ObjekteErzeugen()
{
	//Stream vorbereitungen
	ofstream ZielDatei(TextdateiNameAusgabeMain, ios_base::out | ios_base::app);		//Erzeugt einen Datenstream für die Ausgabedatei
	ifstream Quelldatei;																//Erzeugt einen Datenstream der Eingabedatei
	Quelldatei.open(QuelldateiMain, ios_base::in);										//Öffnet die Quelldatei
	
	//Variabelen
	int ArrayZaehler = 1; 
	int ZahlLeange = 1;
	char Zeichen;																		//Einzelne Zeichen aus dem Stream
	string ZahlS = "";																	//Die eingelesene Zahl als String
	
	//Läuft solange noch neue Zeichen im Quelldokument sind
	while (Quelldatei.get(Zeichen))
	{ 		
		ArrayZaehler++; 
		ZahlLeange++;
		
		//Sobald eine Leerstelle im Dokument kommt werden die einzelnen Zeichen als ganze Zahl interpretiert
		if(Zeichen != ' ' && Zeichen != '	' )
		{			
			ZahlS = ZahlS + Zeichen;
		}
		else
		{	
			ZahlI = atoi(ZahlS.c_str());												//Konvertiert den string ZahlS in einen int(ZahlI)
			Objekte.push_back(Objekt(ZahlI));											//Fügt dem Objekt vector ein Objekt für jede Zahl im Dokument hinzu
			ZahlS = "";
			SchluesselAnzahl++;			
		}
		
	}
	ZielDatei.close();																	//Beendedt den Zugriff auf das Zieldokument
	return;
}

//Steuert die Allgemeine Funktion, Rückgabe ohne Zweck
int main()
{		
	//Variabelen
	ObjekteErzeugen();
	HashTabelle Tabelle_1 = HashTabelle(SchluesselAnzahl, Kollisionsbehandlung);		//Erzeugt die HashTabelle mit den oben festgelegten Parrametern
	ObjektAnzahl = Objekte.size();
	SchluesselAnzahl = 0;
	
	//Solange Objekte da sind füge diese in die HashTabelle ein 
	for(int i = 0; i <= ObjektAnzahl; i++ )
	{	
		Tabelle_1.Einfuegen(Objekte[i]);
	}
	
	return 0;
}