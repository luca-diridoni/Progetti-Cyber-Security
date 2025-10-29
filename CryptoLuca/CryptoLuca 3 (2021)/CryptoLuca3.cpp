/*Questo programma cripta singolarmente le lettere delle frasi o parole 
tramite il loro codice ascii. Il programma sommerà un certo numero a ciascuna lettera,
lo stesso che poi gli sottrarrà per decriptare e tornare alla lettera originale.
Le chiavi modificano il numero sommato (e poi sottratto) al carattere per aumentare la sicurezza.
*/

#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <conio.h>
using namespace std;

int dimensioneparole = 50;
int i; //contatore
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
char parole [dimensioneparole]; //frase da criptare o decriptare
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
		cout<<"ok, inizia a digitare:"<<endl;                                                   //lettere
		//criptare ogni singolo carattere
		for (i=0; i<51 ; i++)                               //input
		{
			parole[i]=' ';	
		}
		cin >>parole;
		for (i=0; i<50 ; i++)                            
		{
			if (parole[i]!=' ')
			{
			parole[i]=parole[i]+25;
	    	}
	    	else 
	    	{
	    		goto outputc;
			}
			
		}
		outputc:
		system("cls");
		cout << "La frase criptata e': "<<endl;             //output
			cout << parole;   
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
		cout<<"ok, inizia a digitare:"<<endl;                                                     //parole
		//decriptare ogni singolo carattere
		for (i=0; i<50 ; i++)                            //input
		{
			parole[i]=' ';
			
		}
		cin >>parole;
		for (i=0; i<50 ; i++)                            
		{
			if (parole[i]!=' ')
			{
			parole[i]=parole[i]-25/*-chiavi[i]*/;
	    	}
	    	else
	    	{
	    		goto outputd;
			}
			
		}
		outputd:                                                       //output
		system("cls");
		cout << "La frase decriptata e': "<<endl;
		cout << parole;
		cout << " "<<endl;
		system ("PAUSE");
		}
		}
		system ("cls");
}
}


