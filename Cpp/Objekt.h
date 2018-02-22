//Author: Lukas Paulmann
//Datum: 27.08.2017	
//Version: 1.0
 
 //Beginn der Definition von Objekt
#ifndef OBJEKT_H
#define OBJEKT_H	

using namespace std;

//Einfaches Objekt das eine ID hat und diese zurückgeben kann
class Objekt
{
	private:
		int ObjektID;
	
	public:
		Objekt(int);					//Konstruktor
		int getObjektID();				//Metohde zur ausgabe der ID
};
#endif