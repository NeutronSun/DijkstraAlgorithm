///////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define MAX 100

struct nodo{
	int etichetta = -1;
	int nArchi;
	char nome = 'A';
};

struct processo{
    int costo[MAX][MAX];
    int nNodi;
    nodo nodi[MAX];
    char partenza='A';
	char arrivo='A';
};

void djikstra (processo grafo){							//funzione principale, calcolo
	int rep=0, min = 0, costo_sup = 0;
	grafo.nodi[0].etichetta = 0;
	int suppP, suppA;
	int unverso;
	
	cout<<"il frocio ha un erso? 1 = si && 0 = no.\n";
	cin>>unverso;
	
	while(true){
	cout<<"Dimmi lo ieido idi paedtenxa.\n";
	cin>>grafo.partenza;
	cout<<"Dimmi lo ieido idi arivvo.\n";
	cin>>grafo.arrivo;
	for(int i=0; i<grafo.nNodi; i++){
			if(grafo.nodi[i].nome==grafo.partenza){
				suppP=i;
			}
			if(grafo.nodi[i].nome==grafo.arrivo){
				suppA=i;
			}
		}
	if(unverso == 1 && grafo.costo[suppP][suppA] == 999 && grafo.costo[0][suppA] != 999 )
		cout<<"Bro cazzo fai dio pr ioco ti sogzzo\n";
	else
		break;
	
}
	if(grafo.partenza=='A' && grafo.arrivo=='A'){
		for(int i=0; i<grafo.nNodi;i++){
			for(int j=0; j<grafo.nNodi; j++){
				if(grafo.costo[i][j]!= 999 && grafo.costo[i][j]!= 0){
						//     DOVE SIAMO				+  COSTO PER ANDARE DA I A J
					costo_sup = grafo.nodi[i].etichetta + grafo.costo[i][j];
					if(grafo.nodi[j].etichetta == -1)
						// IL NODO NON HA UN COSTO E LO SEGNO   A-->B   B(NON HA UN COSTO)  ARCO A--B = 2,  ETICHETTA DI B = 2
						grafo.nodi[j].etichetta = costo_sup;
					else if(grafo.nodi[j].etichetta > costo_sup)	
						// IL NODO HA UN COSTO MA É MAGGIORE  A-->B   B(COSTA 5)  ARCO A--B = 2,   ETICHETTA DI B = 5 MAGGIORE DI SUP = 2 NEW ETICHETTA = 2
						grafo.nodi[j].etichetta = costo_sup;
				}
			}
		}
	}

	else{
		
		
		grafo.nodi[suppP].etichetta = 0;
		for(int i = 0; i < grafo.nNodi; i++){
			if(grafo.costo[suppP][i]!= 999 && grafo.costo[suppP][i]!= 0)
				grafo.nodi[i].etichetta = grafo.nodi[suppP].etichetta + grafo.costo[suppP][i];
			}
			
		for(int i=0; i<grafo.nNodi; i++){
			if(i != suppP){
			
			for(int j=0; j<grafo.nNodi; j++){
				if(grafo.costo[i][j]!= 999 && grafo.costo[i][j]!= 0){
						//			DOVE SIAMO			+  COSTO PER ANDARE DA I A J
					costo_sup = grafo.nodi[i].etichetta + grafo.costo[i][j];
					if(grafo.nodi[j].etichetta == -1)
						// IL NODO NON HA UN COSTO E LO SEGNO   A-->B   B(NON HA UN COSTO)  ARCO A--B = 2,  ETICHETTA DI B = 2
						grafo.nodi[j].etichetta = costo_sup;
					else if(grafo.nodi[j].etichetta > costo_sup)	
						// IL NODO HA UN COSTO MA É MAGGIORE  A-->B   B(COSTA 5)  ARCO A--B = 2,   ETICHETTA DI B = 5 MAGGIORE DI SUP = 2 NEW ETICHETTA = 2
						grafo.nodi[j].etichetta = costo_sup;
				}
			}
		}
	}
	cout<<"Costo per arrivare al nodo "<<grafo.nodi[suppA].nome<<" "<<grafo.nodi[suppA].etichetta<<endl;
	for(int i = 0; i < 50; i++)
	cout<<"DAMMI CENTO EURO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	return;
	}
	
	
	cout<<"Nodo "<<grafo.nodi[0].nome<<" "<<grafo.nodi[grafo.nNodi].etichetta<<endl;
	cout<<"DAMMI CENTO EURO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
};


void visualizza(processo grafo){						//visualizzazione grafo
	int scelta=0, rep=0;
	
	while(rep==0){	
		cout<<endl<<"Menu"<<endl;
		cout<<"(1) visualizza il grafico inserito"<<endl;
		cout<<"(2) calcola il percorso piu breve"<<endl;
		cout<<"(3) calcola il percorso piu breve tra nodi a piacere"<<endl;
		cout<<"(0) Termina sessione"<<endl;
		cin>>scelta;
		
		switch(scelta){
			case 0:
				rep=1;
			break;
			case 1:
			{
				cout<<"Grafico con "<<grafo.nNodi<<" nodi"<<endl;
				
				for(int i=0; i<grafo.nNodi; i++){
					cout<<"\t"<<grafo.nodi[i].nome;
				}
				cout<<endl;
				
				for(int i=0; i<grafo.nNodi;i++){
					cout<<grafo.nodi[i].nome;
					for(int j=0; j<grafo.nNodi; j++){
						cout<<"\t|"<<grafo.costo[i][j];
					}
					cout<<endl;
				}
				cout<<endl;
				
			}
			break;
			case 2:
				{
					djikstra (grafo);
				}
			break;
			case 3:
				{
					for(int i=0; i<grafo.nNodi; i++){
						cout<<"\t"<<grafo.nodi[i].nome;
					}
					cout<<endl;
				
					for(int i=0; i<grafo.nNodi;i++){
						cout<<grafo.nodi[i].nome;
						for(int j=0; j<grafo.nNodi; j++){
							cout<<"\t|"<<grafo.costo[i][j];
						}
						cout<<endl;
					}
					cout<<endl;			
					djikstra (grafo);
				}
			break;
		}
	}
};

void inizializzazione(int nn){								//funzione di inizializzazione
	processo grafo;
	
	if(nn==0){
		
		cout<<"da quanti nodi e formato il tuo grafo?"<<endl;
		cin>>grafo.nNodi;
		
		for(int i=0; i<grafo.nNodi;i++){
			grafo.nodi[i].nome=grafo.nodi[i].nome+i;
			for(int j=0; j<grafo.nNodi; j++){
				cout<<"inserisci il costo tra il nodo "<<char(grafo.nodi[i].nome+i)<<" e il nodo "<<char(grafo.nodi[j].nome+j)<<endl;
				cin>>grafo.costo[i][j];
			}
		}
		visualizza(grafo);
	}
	/////////////////
	else if(nn==5){
		cout<<"hai scelto il grafo predefinito da 5 nodi"<<endl;
		grafo.nNodi=5;
		int costoc[5][5]={ { 0, 1, 3, 999, 999 }, 
                           { 999, 0, 999, 1, 3 }, 
                           {999, 999, 0, 999, 1}, 
                           {999, 999, 999, 0, 2}, 
                           {999, 999, 999, 999, 0} };
						
		for(int i=0; i<grafo.nNodi;i++){
			grafo.nodi[i].nome=grafo.nodi[i].nome+i;
			for(int j=0; j<grafo.nNodi; j++){
				grafo.costo[i][j]=costoc[i][j];
			}
		}
		
		visualizza(grafo);
	}
	/////////////////
	else if(nn==10){
		cout<<"hai scelto il grafo predefinito da 10 nodi"<<endl;
		grafo.nNodi=10;
		
		int costod[10][10]={ 
                            { 0, 1, 999, 1, 1, 999, 999, 999, 999, 999},
                            { 999, 0, 2, 999, 2, 999, 999, 999, 999, 999},
                            { 999, 999, 0, 999, 2, 3, 999, 999, 999, 999},
                            { 999, 999, 999, 0, 3, 999, 5, 999, 999, 999},
                            { 999, 999, 999, 999, 0, 2, 2, 3, 1, 999},
                            { 999, 999, 999, 999, 999, 0, 2, 999, 999, 999},
                            { 999, 999, 999, 999, 999, 999, 0, 999, 999, 5 },
                            { 999, 999, 999, 999, 999, 999, 999, 0, 999, 3 },
                            { 999, 999, 999, 999, 999, 999, 999, 999, 0, 3 },
                            { 999, 999, 999, 999, 999, 999, 999, 999, 999, 0 },
                            };
						 
		for(int i=0; i<grafo.nNodi;i++){
			grafo.nodi[i].nome=grafo.nodi[i].nome+i;
			for(int j=0; j<grafo.nNodi; j++){				
				grafo.costo[i][j]=costod[i][j];
			}
		}				 
						 
		visualizza(grafo);
	}
};

int main(){
	int scelta=0, rep=0, nn=0;
	
	while(rep==0){
		cout<<endl<<"Menu"<<endl;
		cout<<"(1) Inserisci il grafico che si desidera"<<endl;
		cout<<"(2) Visualizza il grafico predefinito a 5 nodi"<<endl;
		cout<<"(3) Visualizza il grafico perdefinito a 10 nodi"<<endl;
		cout<<"(0) Termina programma"<<endl;
		cin>>scelta;
		
		switch(scelta){
			case 0:
				rep=1;
			break;
			case 1:
				nn=0;
				inizializzazione(nn);
			break;
			case 2:
				nn=5;
				inizializzazione(nn);
			break;
			case 3:
				nn=10;
				inizializzazione(nn);
			break;
		}
	}
};


