/*Questo programma cripta singolarmente le lettere delle frasi o parole 
tramite il loro codice asci. 
Ogni lettera andrà inserita singolarmente, la richiesta di input carattere 
terminerà all'inserimento di un punto. Il programma sommerà un certo numero a ciascuna lettera,
lo stesso che poi gli sottrarrà per decriptare e tornare alla lettera originale.
Le chiavi modificano il numero sommato (e poi sottratto) al carattere per aumentare la sicurezza.
Vengono considerate solo le prime chiavi necessarie per arrivare alla lunghezza della frase, eventualmente ripetendo il set di chiavi.
*/

#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <conio.h>
using namespace std;

int i; //contatore
int chiavi [6]; //chiavi
int chiavecopia[6]; //output chiavi
char parole [50]; //frase da criptare o decriptare
string frase; //frase intera (aiuto)
string frasechiavi; //tutte le chiavi (aiuto)
char menu; //scelta menu

//colori
void SetColor(short Color) 
{ 
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); // oppure system("COLOR E9"); 
SetConsoleTextAttribute(hCon,Color); 
}

//inizio
int main ()
{
SetColor(11);
cout<<"Benvenuto in CryptoLuca, cripta e decripta qui le tue frasi"<<endl;
while (menu!='s')
{
	//criptare o decriptare?
	cout<<"Crypte or decrypte? (c/d) or stop (s)";
	cin>>menu;
	system ("cls");
	//se la scelta è di criptare                                                                //Criptare
	if (menu=='c')
	{	
		//inserire chiavi+moltiplicarle per più sicurezza                                   
		cout<<"inserisci le chiavi (una alla volta): "<<endl;                                    //Chiavi
		for (i=0;i<6;i++)
		{
			cout<<"chiave "<<i<<": ";
			cin>>chiavi[i];
			chiavecopia[i]=chiavi[i];
			chiavi[i]=(chiavi[i]*1.5)+1;
			chiavi[i]=chiavi[i]*3;
		}
		system ("cls");
		for (i=0;i<6;i++)
		{
			cout<<chiavecopia[i]<<" ";
		}
		cout << " "<<endl;
		
		
		cout<<"digita singolarmente ogni carattere,"<<endl;                                      //Lettere
		cout<<"scriviti prima la frase intera per aiutarti e dai 'invio':"<<endl;
		cin>>frase;
		cout<<"ok, inizia a digitare singolarmente e a ogni lettera dai invio:"<<endl;
		//criptare ogni singolo carattere
		for (i=0; i<50 ; i++)                            //input
		{
			cin >> parole[i];
			if (parole[i]=='.') goto outputc;
			parole[i]=parole[i]+25+chiavi[i];
			
		}
		outputc:
		system("cls");
		cout << "La frase criptata e': "<<endl;
		for (i=0; parole[i]!='.'; i++)                   //output
			{
				cout << parole[i];
			}
		cout << "|Chiavi:";
		for (i=0; parole[i]!='.'; i++)                   
			{
				cout << chiavecopia[i];
			}
			cout << " "<<endl;
			cout << "Copiala per decriptarla in futuro";
			cout << " "<<endl;
			system("PAUSE");
			system("cls");
		
	}
	
	
	
	//se la scelta è di decriptare                                                               //Decriptare
	else
		{
		if (menu=='d')
		{
		//inserire chiavi+moltiplicarle per più sicurezza
		cout<<"scriviti o incolla prima tutte le chiavi per aiutarti e dai 'invio':"<<endl;
		cin>>frasechiavi;
		cout<<"ok, inizia a digitare singolarmente e a ogni chiave dai invio:"<<endl;
		cout<<"inserisci le chiavi (una alla volta): "<<endl;                                    //Chiavi
		for (i=0;i<6;i++)
		{
			cout<<"chiave "<<i<<": ";
			cin>>chiavi[i];
			chiavecopia[i]=chiavi[i];
			chiavi[i]=(chiavi[i]*1.5)+1;
			chiavi[i]=chiavi[i]*3;
		}
		system ("cls");
		i=0;
		for (i=0;i<6;i++)
		{
			cout<<chiavecopia[i]<<" ";
		}
		cout << " "<<endl;
		
		cout<<"digita singolarmente ogni carattere, "<<endl;                                     //Lettere
        cout<<"scriviti prima la frase intera per aiutarti e dai 'invio':"<<endl;
		cin>>frase;
		cout<<"ok, inizia a digitare singolarmente e a ogni lettera dai invio:"<<endl;
		//decriptare ogni singolo carattere
		for (i=0; parole[i-1]!='.'; i++)                     //Input
			{
				cin >> parole[i];
				if (parole[i]=='.') goto outputd;
				parole[i]=parole[i]-25-chiavi[i];
			}
		outputd:
		system("cls");
		cout << "La frase decriptata e': "<<endl;
		for (i=0; parole[i]!='.'; i++)                       //Output
			{
				cout << parole[i];
			}
			cout << " "<<endl;
			cout << "Copiala per decriptarla in futuro";
			cout << " "<<endl;
			system("PAUSE");
			system("cls");
		}
		}
		system ("cls");
}
}


