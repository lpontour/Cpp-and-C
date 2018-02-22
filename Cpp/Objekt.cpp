//Author: Lukas Paulmann
//Datum: 27.08.2017	
//Version: 1.0

#include "Objekt.h"

using namespace std;

Objekt::Objekt(int ObjektIDNeu)
{
	ObjektID = ObjektIDNeu;				//Setzt die ObjektID
}

int Objekt::getObjektID()
{
	return ObjektID;					//Gibt die ID zurück
}
