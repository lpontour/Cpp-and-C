#include <stdio.h>
#include <stdlib.h>
#include <time.h>    



void Sortieren(int n, char* Dateiname);
int randnum();

void main() 
{
	int Werte[7] = {1000,2000,5000,10000,20000,50000,100000};	//Array Werte hält die Testwerte
	char str[15];
	srand((unsigned)time(NULL));
	for(int n = 0; n < sizeof(Werte)/sizeof(Werte[0]); n++)		//Schleife die über die Werte von *values* fährt
	{
		sprintf(str, "%d", Werte[n]);							//str hält den Testwert in Werte* form
		
		for(int i = 1; i <= 100; i++)							//Schleife für die geforderten 100 Testdaten
		{		
			Sortieren(Werte[n],str);								
		}
	}
}

void Sortieren(int n, char* Dateiname)
{
    int ZufallszahlenArray[n];									//ZufallszahlenArray wird die Zufallszahlen halten
	int i, j, Hilf;												//Hilfsvariablen für den Insert Sort Algorithmus
	int Wechsel = 0,Vergleich = 0;	

    for (i = 0; i < n; i++)										//Schleife die ZufallszahlenArray in vollständiger größe mit Zufallszahlen füllt
	{
		ZufallszahlenArray[i] = randnum();									
	}	
	
    for (i = 1; i < n; i++) 									//Insertsort Algorithmus mit Wechsel und Vergleich* zum zählen der Vertauschungen und Zuweisungen
	{
		j = i;
		Vergleich += 1;
		while ((j > 0) && (ZufallszahlenArray[j - 1] > ZufallszahlenArray[j])) 
		{
			if(ZufallszahlenArray[j-1]>ZufallszahlenArray[j])
			{
				Vergleich += 1;
			}
			Hilf = ZufallszahlenArray[j - 1];
			ZufallszahlenArray[j - 1] = ZufallszahlenArray[j];
			ZufallszahlenArray[j] = Hilf;
			j--;
			Wechsel += 1;
		}
	}
	
	FILE *file = fopen(Dateiname, "a");							//Erstellen/öffnen der Datei die die Testdaten hält
	fprintf(file,"%d, %d \n",Wechsel,Vergleich);				//Schreiben in diese Datei
	fclose(file);												//Schließen der Datei
	
	printf("%d ,%d\n",Wechsel,Vergleich);						//Anzeigen der Testdaten auf der Console (war nicht gefordert, hilft beim überblicken/vortschritt überprüfen)
}
int randnum()													//Funktion zum Zufallszahlen erstellen
{ 
		int x,y;

		x = rand();												//Zufallszahl 1
		y = rand();												//Zufallszahl 2
		int xy = x * y;											//xy wird benötigt um Zahlen größer als 32767 zu erzeugen
		if(xy <= 1000000)
		{
			return xy;											//Zahlen von 1-1Million sind möglich(möglicherweise mit ausnahmen)
		}														//kleinere Zahlen sind unwahrscheinlicher da diese x oder Y = 1 benötigen
		else
		{
			return x;
		}					
}

