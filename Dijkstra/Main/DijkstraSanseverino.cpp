/*
@author Lorenzo Sanseverino 4DSA
Modifiche rispetto l'ultima consegna:
1)migliorata la ricerca dei vari percorsi alternativi, anche interni.
2)migliorata la stampa a video
3)cambiata la struttura della funzione dijkstra(), come l'input dei nodi ecc.
4)automatizzata l'input del nome dei vari nodi
5)aggiunti controlli sui grafi orientati in un verso(ora si potra' selezionare come Source anche il nodo C[esempio] ed il programma controllera' i vari percorsi possibili)
6)
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

//costante che indica il numero massimo di nodi possibili e la grandezza massima dei vari array
#define MAX 32

/*
struct contenente due array che conterrano il costo dell'arco e con chi sara' collegato
*/
struct dataClass
{
    //array contente la posizione dell'arco di arrivo(sincronizzato con costo[])
    int pos[MAX];
    //array contente il costo dell'arco di arrivo(sincronizzato con pos[])
    int costo[MAX];
};

/*
struct che contenente tutti i dati del singolo nodo
*/
struct singleNodes
{
    //nome del nodo
    string name;

    //attributto contenente i due array costo[] e pos[]
    dataClass dataNode;
    //array contente i vari passi per arrivare al nodo richiesto
    int step[MAX];
    //array contenente tutti gli indici dei vari percorsi alternativi
    int sameStep[MAX];
    //attributo che indica se il nodo e' stato analizzato(0) o no(-1)
    int flag;
    //attributo che indica il costo parziale dal nodo iniziale a questo in analisi
    int etichetta;
    //attributo che indica il numero degli archi di questo nodo
    int nArchi;
};

/*
struct contenente l'insieme di tutti i nodi, la matrice delle adiacenze
e specifica il verso
*/
struct routingClass
{
    //array contenente tutti i nodi del grafo
    singleNodes allNodes[MAX];
    //attributo boolean che indica se il grafo e' orientato ad un verso(true) o no
    bool isOneVerse;
    //matrice delle adiacenze
    int matrix[MAX][MAX];
};


routingClass nulling();
routingClass defaultGraph(routingClass myObj, int n);
routingClass inputByUser(routingClass myObj, int n);
routingClass getDataByGraph(routingClass myObj);


int getSize(routingClass myObj);
int menu();
int sottoMenu(int n);
int inserimento(int max, int min);
int FindingShortest(routingClass myObj);

bool dijkstra(routingClass myObj);


void stampa(routingClass myObj);
void positionController(routingClass myObj, int start, int i);


//main del programmma
int main()
{
    
    while(1)
    {
        //oggetto principale unico per tutto il programma
        routingClass myObj = nulling();
        switch(menu())
        {
            //caso con 5 nodi
            case 1:
            switch(sottoMenu(5))
            {
                //grafo default
                case 1:
                myObj = defaultGraph(myObj, 5);
                while(dijkstra(myObj))
                    cout<<"";
                break;

                //grafo scelto dall'utente
                case 2:
                myObj = inputByUser(myObj, 5);
                stampa(myObj);
                while(dijkstra(myObj))
                    cout<<"";
                system("pause");
                break;
            }
            break;
            //caso con 10 nodi
            case 2:
            switch(sottoMenu(10))
            {
                //grafo deafult
                case 1:
                myObj = defaultGraph(myObj, 10);
                while(dijkstra(myObj))
                    cout<<"";
                break;
                
                //grafo scelto dall'utente
                case 2:
                myObj = inputByUser(myObj, 10);
                stampa(myObj);
                while(dijkstra(myObj))
                    cout<<"";
                system("pause");
                break;
            }
            break;
            
            //caso con numero illimitato di nodi
            case 3: 
            switch(sottoMenu(0))
            {
                //grafo deafult
                case 1:
                myObj = defaultGraph(myObj, 0);
                while(dijkstra(myObj))
                    cout<<"";
                break;
                
                //grafo scelto dall'utente
                case 2:
                //per la soluzione default ho scelto comunque 5 nodi in qualsiasi verso
                myObj = inputByUser(myObj, 0);
                stampa(myObj);
                while(dijkstra(myObj))
                    cout<<"";
                system("pause");
                break;
            }
            case 4: 
            return 0;
        }
    }
    
    
 
}


int menu()
{   
    //scelta dell'utente
    int x;
    system("cls");
    while(1)
    {
        system("cls");
	    cout<<"Applicazione ricerca del ShortestPath\nSanseverino Lorenzo ---> 4DSA Sistemi & Reti.\n";
	    cout<<"\n--------->Menu Del Programma<---------\n";
        cout<<"-->Grafi orientati ad un verso<--\n\n";
	    cout<<"1) Grafo a 5 Nodi.\n";
	    cout<<"2) Grafo a 10 Nodi.\n";
        cout<<"\n-->Grafo a libera scelta dell'utente<--\n\n";
	    cout<<"3) Grafo a Nodi illimitati\n";
        cout<<"4) Termina programma.\n";

        x = inserimento(4,1);
        return x;
    }
    
}

/*
sottomenu in cui l'utente puo' scegliere se inserire manualmente la tabella delle adiacenze o usare quella di defualt
@param n
numero di nodi che verranno visualizzati a schermo
@return int: la scelta dell'utente
*/
int sottoMenu(int n)
{
    system("cls");
    //scelta dell'utente
    int x;
    while(1)
    {
        cout<<"--------->Sottomenu Del Programma<---------\n";
        if(n == 0)
        cout<<"--->Selezionato grafo con dati personalizzati e non orientato ad un verso.\n\n";
        else
        cout<<"-->Selezionato grafo a "<<n<<" nodi.\n\n";
        cout<<"1) Grafo di prova predefinito.\n2) Inserisci dati.\n";
        x = inserimento(2,1);
        return x;
    }
}

/*
funzione che setta il grafo con dei valori predefiniti
tramite la variabiel "n" viene settato il numero dei nodi
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@param n
parametro contenente il numero di nodi
@return routingClass: l'oggetto myObj con dentro la matrice ed i dati
*/
routingClass defaultGraph(routingClass myObj, int n)
{
    if(n == 5 )
    {
        myObj.allNodes[0].name = "a";
        myObj.allNodes[1].name = "b";
        myObj.allNodes[2].name = "c";
        myObj.allNodes[3].name = "d";
        myObj.allNodes[4].name = "e";
        myObj.isOneVerse = true;
        //ad alcuni complilatori mi sa che da problemi dichiarare una matrice utilizzando n invece di matrix[5][5]
        int matrix[n][n]= { { 0, 1, 3, 999, 999 }, 
                           { 999, 0, 999, 1, 3 }, 
                           {999, 999, 0, 999, 1}, 
                           {999, 999, 999, 0, 2}, 
                           {999, 999, 999, 999, 0} };
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n;j++)
            {
                myObj.matrix[i][j] = matrix[i][j];
            }
        }
        
    }
    else if(n == 10)
    {
        myObj.isOneVerse = true;
        myObj.allNodes[0].name = "a";
        myObj.allNodes[1].name = "b";
        myObj.allNodes[2].name = "c";
        myObj.allNodes[3].name = "d";
        myObj.allNodes[4].name = "e";
        myObj.allNodes[5].name = "f";
        myObj.allNodes[6].name = "g";
        myObj.allNodes[7].name = "h";
        myObj.allNodes[8].name = "i";
        myObj.allNodes[9].name = "j";  
        int matrix[n][n]= { { 0, 2, 1, 999, 999,999,999,999,999,999 },//a
                            {999,0,999,3,999,999,999,999,999,999},//b
                            {999,999,0,4,999,999,999,999,999,999},//c
                            {999,999,999,0,7,999,999,999,999,999},//d
                            {999,999,999,999,0,1,2,999,999,999},//e
                            {999,999,999,999,999,0,999,2,999,999},//f
                            {999,999,999,999,999,999,0,1,999,999},//g
                            {999,999,999,999,999,999,999,0,3,5},//h
                            {999,999,999,999,999,999,999,999,0,2},//i
                            {999,999,999,999,999,999,999,999,999,0},//j
                            };
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n;j++)
                myObj.matrix[i][j] = matrix[i][j];
        }
    }
    else
    {
        n = 6;
        myObj.isOneVerse = false;
        myObj.allNodes[0].name = "a";
        myObj.allNodes[1].name = "b";
        myObj.allNodes[2].name = "c";
        myObj.allNodes[3].name = "d";
        myObj.allNodes[4].name = "e";
        myObj.allNodes[5].name = "f";
        int matrix[n][n]= { { 0, 2, 1, 999, 999,999 }, 
                           { 2, 0, 999, 3, 5,999 }, 
                           {1, 999, 0, 4, 999,999}, 
                           {999, 3, 4, 0, 2,999}, 
                           {999, 5, 999, 2, 0,2},
                           {999, 999, 999, 999, 2,0 },};
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n;j++)
            {
                myObj.matrix[i][j] = matrix[i][j];
            }
        }
    }

    myObj = getDataByGraph(myObj);
    return myObj;

}

/*
setta inizialmente tutti i valori a 0 o -1.
cosi che tramite funzioni o controll ausiliari riesca a capire quando ho raggiunto la fine di un vettore il numero degli elementi presenti.
una sorta di simulazione dei vector/arraylist in java(purtroppo a meta' programma ho capito che era meglio farlo in java per come programmo io).
@return routingClass: l'oggetto con tutti valori di default svuotati
*/
routingClass nulling()
{
    //oggetto di di supporto che sara' svuotato
    routingClass myObj;
    myObj.isOneVerse = false;
    for(int i = 0; i <MAX; i++)
    {
        myObj.allNodes[i].name = "null";
        myObj.allNodes[i].etichetta = -1;
        myObj.allNodes[i].flag = -1;
        for(int j = 0; j <MAX; j++)
        {
            myObj.allNodes[i].dataNode.pos[j] = -1;
            myObj.allNodes[i].dataNode.costo[j] = 999;
            myObj.allNodes[i].step[j] = -1;
            myObj.allNodes[i].sameStep[j] = -1;
        }
    }

    for(int i = 0; i <MAX; i++)
    {
        for(int j = 0; j <MAX; j++)
        {
            myObj.matrix[i][j] = - 1;
        }
    }
    return myObj;
}

/*
funzione che impedisca all'utente di inserire valori non consentiti in quel determinato contensto in cui la funzione e' richiamata.
@param max
paramentro contente il valore max
@param min
parametro contente il valore minimo
@return int: la scelta dell'utente
*/
int inserimento(int max, int min)
{
    //variabile inserita dall'utente
	int x;
	while(1)
    {
        cout<<"\n-->";
		cin>>x;
		if(x>max || x<min || cin.fail()){
			cout<<"Inserire solo valori compresi tra "<<min<<" e "<<max<<".\n";
            cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}
		else
			break;
	}
	return x;
}

/*
funzione che analizza tutti i nomi dell'array finche' non trova "null", ossia la prima cella disponibile.
quindi mi restituisce il numero di elementi del array.
equivale a fare vector.size() in java.
ho preferito non inserire nella struct una variabile nNodi in quanto avrei usato troppi attributi e rischiato(com'e' successo) di andare incontro allo stack overflow.
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@return int: numero dei nodi dell'oggetto myObj
*/
int getSize(routingClass myObj)
{
    //contatore
    int cont = 0;
    for(int i = 0; i <MAX; i++)
    {
        if(myObj.allNodes[i].name == "null")
            return cont;
        else
            cont++;
    }
    return 0;
}

/*
la funzione riceve per parametro il nodo di cui voglio sapere la posizioni.
partendo dal precedente del' ultimo nodo in maniera recorsiva analizza il precedente dell'ultimo precedente, finche' non trova il nodo iniziale.
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@param start
parametro contenente l'indice del nodo iniziale
@param i
parametro contenente l'indice del nodo preso in analisi(quello di arrivo)
@return void
*/
void getPosition(routingClass myObj, int start, int i, int * index, int* pointer)
{
    //variabile di supporto
    int sup = 0;
    //seconda variabile di supporto che avra' sempre un valore in piu' di sup
    int cont = 0;
    //contatore di supporto che salva l'ultimo indice libero di *index[32]
    int countDx = 0;
    if(i != start)
    {
        while(1)
        {
            if(start != myObj.allNodes[i].step[sup])
            {
                sup = cont;
                cont ++;
                myObj.allNodes[i].step[cont] = myObj.allNodes[myObj.allNodes[i].step[sup]].step[0];
                if( myObj.allNodes[myObj.allNodes[i].step[sup]].sameStep[0] != -1)
                {
                    *(index + countDx) = myObj.allNodes[i].step[sup];
                    countDx++;
                }
            }
            else
            {   
                for(int j = sup; j >= 0; j--)
                {
                    cout<<myObj.allNodes[myObj.allNodes[i].step[j]].name<<"("<<myObj.allNodes[myObj.allNodes[i].step[j]].etichetta<<")-->";
                }
                cout<<myObj.allNodes[i].name<<"("<<myObj.allNodes[i].etichetta<<").\n";
                *pointer = countDx;
                break;
            }
        }
    }
    
}

/*
funzione che mi restituisce il primo indice libero dell'attributo sameStep[](dove andranno i percorsi alternativi)
Anche qui in mancanza del metodo .size() ho dovuto usare una funzione ausiliaria.
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@param pos
parametro contenente l'indice del nodo preso in analisi
@return int: il primo indece libero dell'attributo sameStep[]
*/
int lastIndexOf(routingClass myObj, int pos)
{
    //indice da returnare
    int i = 0;
    while(true)
    {
        if(myObj.allNodes[pos].sameStep[i] == -1)
        return i;
        else
        i++;
    }
}   

/*
Funzione che stampa la tabella delle adiacenze
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@return void
*/
void stampa(routingClass myObj)
{
    
    cout<<"\nTabella delle adiacenze:\n\n";
    cout<<setw(17)<<myObj.allNodes[0].name;
    for(int i = 1; i <getSize(myObj); i++)
    cout<<setw(8)<<myObj.allNodes[i].name;
    cout<<"\n";
    for(int i = 0; i < getSize(myObj); i++)
    {
        cout<<"\t"<<myObj.allNodes[i].name<<" ";
        for(int j = 0; j <getSize(myObj); j++)
        {
            if(myObj.matrix[i][j] == 999)
                cout<<"\tINF";
                else
                cout<<"\t"<<myObj.matrix[i][j];
        }   
        cout<<"\n";
    }
}

/*
funzione che legge la tabella delle adiacenze e setta tutti i valori nei vari attributi nella struct dataClass, dove sono
presenti due array pos(ci andra' l'indice del nodo a cui e' collegato) e costo(ci andra il costo dell'arco).
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@return routingClass: l'oggetto myObj con tutti i dati analizzati dalla matrice ed inseriti nei vari attributi
*/
routingClass getDataByGraph(routingClass myObj)
{
    for(int i = 0; i<getSize(myObj); i++)
	{
        //contatore
		int cont = 0;
		for(int j = 0; j<getSize(myObj);j++)
		{
			if(myObj.matrix[i][j] != 0 && myObj.matrix[i][j] != 999)
			{
                myObj.allNodes[i].dataNode.pos[cont] = j;
                myObj.allNodes[i].dataNode.costo[cont] = myObj.matrix[i][j];
				cont++;
			}
		}
		myObj.allNodes[i].nArchi = cont;
	}
    return myObj;
}

/*
Funzione che consente all'utente di inserire manualemte la tabella.
Essendo presenti due opzioni in cui il numero dei nodi deve essere fisso, se n e' diverso da zero 
verra' forzato l'input di una tabella 5*5 o 10*10 orientata ad un verso.
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@param n
parametro che indica il numero di nodi, se e' zero significa che sara' l'utente ad inserire il valore
@return routingClass: l'oggetto con tutti i dati inseriti dall'utente
*/
routingClass inputByUser(routingClass myObj, int n)
{  
    system("cls");
    if(n == 0)
    {
        cout<<"Inserire numero nodi: (MAX "<<MAX<<").\n";
        n = inserimento(MAX, 3);
        cout<<"Vuoi l'autoconfiguarazione per i grafi orientati ad un verso? y or n?\n";
        string a;
        cin >> a;
        if(a == "y")
        myObj.isOneVerse = true;
        else
        myObj.isOneVerse = false;

    }
    else
     myObj.isOneVerse = true;

    //stringhe di supporto per l'inizializzazione dei nomi
    string a = "a", b = "";   
    for(int i=0, j = 0; i<n; i++)
    {
        if(i > 25)
        {
            a = "a";
            b = ('a' + j);
            a+=b;
            myObj.allNodes[i].name = a;
            j++;
        }
        else
        myObj.allNodes[i].name = 'a' + i;
    }


    system("cls");
    cout<<"Input tabella:";
    if(myObj.isOneVerse)
    cout<<" orientata in un verso.\n";
    else
    cout<<" non orientata in un verso.\n";
    cout<<"Inserire il costo dei vari archi, INF = 9999.\n\n";


    for(int i = 0; i < getSize(myObj); i++)
		myObj.matrix[i][i] = 0;
    
    for(int i = 0; i<getSize(myObj); i++)
	{
		for(int j=0;j<getSize(myObj);j++)
		{
			if(myObj.matrix[i][j] == -1)
			{
				cout<<"Arco "<<myObj.allNodes[i].name<<" ---> "<<myObj.allNodes[j].name<<":\n";
				myObj.matrix[i][j] = inserimento(999,0);
                if(myObj.isOneVerse && myObj.matrix[i][j] != 999)
                myObj.matrix[j][i] = 999;
			}

		}
	}

    myObj = getDataByGraph(myObj);
    return myObj;

}

/*
funzione che returna l'indice del nodo non visitato 
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@return int: l'indice dei vari nodi da analizzare per la funzione dijkstra()
*/
int FindingShortest(routingClass myObj)
{
    //variabile di supporto contenente il costo minore
    int min = 999;
    //salva l'indice del nodo con costo minore
    int pos;

    for(int i = 0; i<getSize(myObj); i++)
    {
        if(myObj.allNodes[i].flag == -1 && myObj.allNodes[i].etichetta != -1 && myObj.allNodes[i].etichetta <= min)    
        {
            min = myObj.allNodes[i].etichetta;
            pos = i;
        }
    }
    return pos;
}

/*
funzione che returna true se sono stati analizzati tutti i nodi
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@return true se tutti i nodi sono stati analizzati
*/
bool AllChecked(routingClass myObj)
{
    //contatore
    int cont = 0;
    for(int i = 0; i< getSize(myObj); i++)
    {
        if(myObj.allNodes[i].flag == 0)
        cont++;
    }
    if(getSize(myObj) == cont)
    return true;
    else
    return false;
}

/*
funzione che stampa a video tutti i percorsi alternativi presenti del nodo di arrivo.
esegue lo stesso procedimento della funzione getPosition() con la differenza che il primo precedente non sara'
il precedente del nodo di arrivo ma il precedente del nodo presente in sameStep[].
In sameStep[] ci andrarnno tutti gli indici che consentono l'arrivo in un nodo con un costo uguale al percorso minore.
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@param start 
parametro contenente l'indice del nodo iniziale
@param i 
parametro contenente l'indice del nodo preso in analisi
@param *index
puntatore che salva nelle celle di memoria del'array index[32](funzione positionController) i vari indici dei nodi interni con percorsi alternativi
@param *pointer
puntatore che salva l'ultimo indice del vettore index[32]
@return void
*/
void sameRoad(routingClass myObj, int start, int i, int* index, int* pointer)
{
    //variabile di supporto
    int sup = 0;
    //seconda variabile di supporto che avra' sempre un valore in piu' di sup
    int cont = 0;
    //vettore contenente tutti gli indici dei nodi per stampare il percorso
    int vet[MAX];
    //iteratore
    int iterator = 0;
    //contatore di supporto che salva l'ultimo indice libero di *index[32]
    int countDx = *pointer;
    while(1)
    {
        if(myObj.allNodes[i].sameStep[iterator] != -1)
        {
            cont = 0;
            sup = 0;
            vet[sup] = myObj.allNodes[i].sameStep[iterator];
            cout<<"Percorso alternativo "<<(iterator+1)<<":\n";
            while(1)
            {   
                if(start != vet[sup])
                {
                    sup = cont;
                    cont ++;
                    vet[cont] = myObj.allNodes[vet[sup]].step[0];
                    if( myObj.allNodes[vet[sup]].sameStep[0] != -1)
                    {
                        bool alreadyPut = false;
                        for(int i = 0; i < countDx; i++)
                        {
                            if(vet[sup] == *(index + i))
                            alreadyPut = true;
                        }
                        if(!alreadyPut)
                        {
                            *(index + countDx) = vet[sup];
                            countDx++;
                        }
                        
                    }
                }
                else
                {   
                    for(int j = sup; j >= 0; j--)
                        cout<<myObj.allNodes[vet[j]].name<<"("<<myObj.allNodes[vet[j]].etichetta<<")-->";
                    cout<<myObj.allNodes[i].name<<"("<<myObj.allNodes[i].etichetta<<").\n";
                    iterator++;
                    break;
                }
            }
        }
        else
        {
            *pointer = countDx;
            return;
        }
            
    }

}

void positionController(routingClass myObj, int start, int i)
{
    //array contenente tutti gli indici dei vari nodi interni con percorsi alternativi
    int index[MAX];
    //contatore che salva l'ultimo indice libeo di index[32]
    int contIdx = 0;
    
    for (int i = 0; i < MAX; i++)
        index[i] = -1;
    
    cout<<"---------------------------------------------------------";
    cout<<"\n\n--------->Stampa dei vari percorsi<---------\n";
    cout<<"--->Stampa del percorso originale: \n\n";
    getPosition(myObj, start, i, index, &contIdx);
    if(myObj.allNodes[i].sameStep[0] != -1)
    {
        cout<<"\n--->Stampa dei percorsi alternativi esterni: \n\n";
        sameRoad(myObj, start,i,index,&contIdx);
    }
    else
        cout<<"\n--->Non sono presenti dei percorsi alternativi esterni.";
    if(contIdx != 0)
    {
        int j = 0;
        int compare[MAX];
        
        cout<<"\n--->Stampa dei percorsi alternativi interni: \n\n";
        do
        {
            cout<<"Percorso alternativo interno "<<myObj.allNodes[start].name<<"("<<myObj.allNodes[index[j]].name<<")\n\n";
            sameRoad(myObj, start, index[j], index, &contIdx);
            cout<<endl;
            j++;
        } 
        while (j != contIdx);
    }
    else
        cout<<"\n--->Non sono presenti dei percorsi alternativi interni: \n";

}

/*
parte principale del programma:
l'utente selezione il nodo di partenza e quello di arrivo e tamite l'algoritmo di dijkstra stampa il percorso minore.
La prima iterazione analizza il nodo di partenza e setta l'etichetta di tutti i nodi adiacenti.
Dalla seconda iterazione in poi si analizzera' il nodo con etichetta minore e non esplorato, e si continua con l'analisi di tutti i nodi adiacenti.
Il programmma non si ferma appena trova il percorso minore ma li analizza tutti cosi' da trovare tutti i percorsi minimi possibili.
@param myObj
oggetto contenente tutti i dati della tabella di routingClass
@return true in caso l'utente decida di continuare ad analizzare lo stesso grafo, false nel caso voglia tornare al menu
*/
bool dijkstra(routingClass myObj)
{
    //nome del nodo di inizio e fine
    char a = '!', b = '!';
    //indice del nodo di inizio
    int start = -1;
    //indice del nodo di arrivo
    int arrive = -1;

    //lambda di stampa
    auto print = [](routingClass myObj, char a, char b)
    {
        //prima stampa iniziale
        system("cls");
        cout<<"--------->Algoritmo di Dijkstra<---------\n";
        cout<<"--->Selezionato grafo a "<<getSize(myObj)<<" nodi ";
        if(myObj.isOneVerse)
        cout<<"orientato in un verso.\n\n";
        else
        cout<<"non orientato in un verso.\n\n";
        if(a != '!')
        cout<<"|Selezionato Nodo di partenza: "<<a<<"|\n";
        if(b != '!')
        cout<<"|Selezionato Nodo di arrivo: "<<b<<"|\n";
        stampa(myObj);//prima stampa iniziale
    };


    //selezione del nodo Source e del nodo di arrivo
    cout<<"\n--->Selezionare i nodi: \n\n";
    while(true)
    {
        print(myObj,a,b);
        cout<<"Inserire nodo di partenza:\n";
        cin>>a;
        if((a - 97) > getSize(myObj)-1 || (a-97)<0)
        {
            cout<<"Nodo inesistente.\n";
            a = '!';
            continue;
        }
        start = (a - 97);
        print(myObj,a,b);
        cout<<"Selezionato Nodo di partenza: "<<a<<endl;
        cout<<"Inserire nodo di arrivo:\n";
        cin>>b;
        arrive = (b - 97);
        if((b - 97) > getSize(myObj)-1 || (b-97)<0 )
        {
            cout<<"Nodo inesistente.\n";
            b = '!';
            continue;
        }
        else if(myObj.isOneVerse && myObj.matrix[start][arrive] == 999 && ((myObj.matrix[0][arrive] != 999) || (myObj.matrix[0][arrive] == 999 && start > arrive)))
        {
            cout<<"Nodo irraggiungibile.\n";
            a = '!';
            b = '!';
            system("pause");
            continue;
        }
        else
        break;
    }

    //indice del nodo che si sta analizzando(ogni iterazione cambia)
    int position = start;
   

    if(myObj.isOneVerse && start != 0)
    {
        for(int i = 0; i < getSize(myObj); i++)
        myObj.allNodes[i].flag = 0;
    }

    myObj.allNodes[start].etichetta = 0;
    myObj.allNodes[start].flag = -1;



    //calcolo del percorso piu' breve
    do
    {
        position = FindingShortest(myObj);
        cout<<"position: "<<myObj.allNodes[position].name<<endl;
        for(int i = 0; i < myObj.allNodes[position].nArchi; i++)
        {
            if(myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].etichetta != -1)
            {
                int supp = myObj.allNodes[position].etichetta + myObj.allNodes[position].dataNode.costo[i];
                if(supp < myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].etichetta)
                {
                    myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].etichetta = supp;
                    myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].step[0] = position;
                    myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].flag = -1;
                }   
                else if(supp == myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].etichetta)
                    myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].sameStep[lastIndexOf(myObj,myObj.allNodes[position].dataNode.pos[i])] = position;
                
            }
            else
            {
                myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].etichetta = myObj.allNodes[position].etichetta + myObj.allNodes[position].dataNode.costo[i];
                myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].step[0] = position;
                myObj.allNodes[myObj.allNodes[position].dataNode.pos[i]].flag = -1;
            }
        }
        myObj.allNodes[position].flag = 0;
        for(int i = 0; i < getSize(myObj); i++)
        {
            if(myObj.allNodes[i].flag == 0)
            cout<<"1\n";
            else
            cout<<"0\n";
        }
    }
    while(!AllChecked(myObj));

    
    //stampa dei percorsi
    print(myObj,a,b);
    cout<<"\nIl costo minimo del percorso "<<myObj.allNodes[start].name<<"("<<myObj.allNodes[arrive].name<<") ha un costo di "<<myObj.allNodes[arrive].etichetta<<endl;
    positionController( myObj, start, arrive );
    cout<<"\nContinuare o tornare al menu principale? y or n\n";
    cout<<"N.B. Ritordando al menu si perdera' il seguente grafo.\n";
    //risposta dell'utente
    string choice;
    cin>>choice;
    if(choice == "y")
    return true;
    else
    return false;
}
