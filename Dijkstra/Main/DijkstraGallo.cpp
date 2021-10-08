//Valerio Gallo 4 DS A
//Algoritmo di Dijkstra
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


#define MAX_ARR 32

struct nodo{                                                                                                                                                                     //Struct per i dati del singolo nodo, adiacenze contiene gli indici dei nodi con i quali
    int adiacenze[MAX_ARR];                                                                                                                                             //il nodo in questione ha una connessione, costoPerNodo contiene appunto il costo delle adiacenze di quel nodo.
    int costoPerNodo[MAX_ARR];
};

struct nodoTotale{                                                                                                                                                          //Contiene tutti gli altri dati del nodo, come il nome, il numero di adiacenze, e altri flag utili per
    string nome;                                                                                                                                                                //il calcolo dell'algoritmo di Dijkstra.
    nodo nodi;
    int nArchi;
    int costoProvvisorio;
    bool terraBruciata;
    int precedente;
    int nodiStessoCosto[MAX_ARR];
};

struct insiemeFinale{                                                                                                                                                       //Contiene la tabella delle adiacenze, un array con tutti quanti i nodi e i loro dati, e il numero di nodi del grafo.
    nodoTotale grafi[MAX_ARR];
    int matriceAdiacenze[MAX_ARR][MAX_ARR];
    int nNodi;
};

insiemeFinale inizializzaGrafo(){                                                                                                                                       //Inizializza tutti i valori(Grafo, adiacenze) a 0, in modo da settare gli array, i valori delle adiacenze
    insiemeFinale tabele;                                                                                                                                                   //dei singoli nodi e dei costi per nodo vengono inizializzati invece a -1, sia per andare ad inizializzare gli array,
    for(int i = 0; i < MAX_ARR; i++){                                                                                                                                 //sia per, quando si va a mandare in input i dati, tutti quelli prima del -1 verranno presi in considerazione.
        tabele.grafi[i].nome = "";
        tabele.grafi[i].nArchi = 0;
        tabele.grafi[i].costoProvvisorio = -1;
        tabele.grafi[i].terraBruciata = false;
        tabele.grafi[i].precedente = -1;
        for(int j = 0; j < MAX_ARR; j++){
            tabele.grafi[i].nodi.adiacenze[j] = -1;
            tabele.grafi[i].nodi.costoPerNodo[j] = -1;
            tabele.grafi[i].nodiStessoCosto[j] =  -1;
        }
    }
    return tabele;
}

insiemeFinale inputMEGAGrafo(insiemeFinale tabele){                                                                                                             //Funzione di input dei dati della tabella delle adiacenze per eseguire l'algoritmo.
    cout<<"Quanti nodi ci sono in totale nel grafo?\n";
    int nNodi;
    cin>>nNodi; 
    tabele.nNodi = nNodi;
    for(int i = 0; i < nNodi; i++){
        int j;
        j = i + 1;
        cout<<"Inserisci il nome del nodo: "<<j<<".\n";                                                                                                             //Inserimento nome del nodo.
        cin>>tabele.grafi[i].nome;
    }
    cout<<"Inserimento della tabella delle adiacenze: \n";                                                                                                      //Inserimento della tabella delle adiacenze.
    for(int i = 0; i < nNodi; i++){
        for(int j = 0; j < nNodi; j++){
            cout<<"Inserisci adiacenza nodo "<<tabele.grafi[i].nome<<" con il nodo "<<tabele.grafi[j].nome<<":\n";
            cin>>tabele.matriceAdiacenze[i][j];
        }
    }
    for(int i = 0; i < nNodi; i++){                                                                                                                                                 //Questo ciclo invece prende i dati  dalla tabella delle adiacenze, quindi
        int cont = 0;                                                                                                                                                                       //per esempio il costo, per per andare a riempire altri array come appunto quello che contiene i vari costi.
        for(int j = 0; j < nNodi; j++){
            if(tabele.matriceAdiacenze[i][j] > 0 && tabele.matriceAdiacenze[i][j] != 999){
                tabele.grafi[i].nodi.adiacenze[cont] = j;
                tabele.grafi[i].nodi.costoPerNodo[cont] = tabele.matriceAdiacenze[i][j];
                tabele.grafi[i].nArchi++;
                cont++;
            }
        }
    }
    return tabele;
}

insiemeFinale settaGrafo(insiemeFinale tabele){                                                                                                                             //Legge i dati dalla tabella delle adiacenze e li estrapola per metterli nella struct del nodo,
    for(int i = 0; i < tabele.nNodi; i++){                                                                                                                                              //prende i valori come il costo e le adiacenze, e calcola il numero di archi di ogni nodo.
        int cont = 0;
        for(int j = 0; j < tabele.nNodi; j++){
            if(tabele.matriceAdiacenze[i][j] > 0 && tabele.matriceAdiacenze[i][j] != 999){
                tabele.grafi[i].nodi.adiacenze[cont] = j;
                tabele.grafi[i].nodi.costoPerNodo[cont] = tabele.matriceAdiacenze[i][j];
                tabele.grafi[i].nArchi++;
                cont++;
            }
        }
    }
    return tabele;
}

int nodoSuccessivo(insiemeFinale tabele){                                                                                                                                                                                       //Questa funzione va a decidere il prossimo nodo da analizzare,
    int costoProvvisorioMinimo = 999;                                                                                                                                                                                               //se non è stato già analizzato e se ha un'etichetta.
    int indiceNodoMin;
    for(int i = 0; i<tabele.nNodi; i++){
        if(tabele.grafi[i].terraBruciata == false && tabele.grafi[i].costoProvvisorio != -1 && tabele.grafi[i].costoProvvisorio <= costoProvvisorioMinimo){
            costoProvvisorioMinimo = tabele.grafi[i].costoProvvisorio;
            indiceNodoMin = i;
        }
    }
    return indiceNodoMin;
}

int ultimaCella(insiemeFinale tabele, int posizione){                                                                                                                       //Serve per emulare il comando .add dei vector in JAVA.
    int contatore = 0;
    while(true){
        if(tabele.grafi[posizione].nodiStessoCosto[contatore] == -1){
            return contatore;
        }else{
            contatore++;
        }
    }
}

void djikstraCalculator(insiemeFinale tabele){                                                                                                                                  //Funzione di calcolo dell'algoritmo di Dijkstra.   
    string nodoPartenza;
    cout<<"Da quale nodo vuoi partire?\n";
    cin>>nodoPartenza;
    string nodoArrivo;
    cout<<"A quale nodo vuoi arrivare?\n";
    cin>>nodoArrivo;
    int a = 0;
    int cont = 0;
    int indicePartenza = -1;
    int indiceArrivo = -1;
    int indiceNodoSuccessivo = -1;
    int posizioneAttuale;
    int contNodiBruciati = 0;
    int nodiPrecedenti[MAX_ARR];

    for(int i=0; i<MAX_ARR; i++){
        nodiPrecedenti[i] = -1;
    }
    
    while(a == 0){                                                                                                                                                                                              //Qui a partire dai nodi inseriti per la partenza e l'arrivo trova i loro indici.
        if(nodoPartenza == tabele.grafi[cont].nome){
            indicePartenza = cont;
        }
        if(nodoArrivo == tabele.grafi[cont].nome){
            indiceArrivo = cont;
        }
        if(indiceArrivo != -1 && indicePartenza != -1){
            a++;
        }
        cont++;
    }

    tabele.grafi[indicePartenza].costoProvvisorio = 0;
    while(contNodiBruciati != tabele.nNodi){
        posizioneAttuale = nodoSuccessivo(tabele);
        for(int i = 0; i < tabele.grafi[posizioneAttuale].nArchi; i++){
            if(tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].costoProvvisorio == -1){
                tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].costoProvvisorio = tabele.grafi[posizioneAttuale].costoProvvisorio + tabele.grafi[posizioneAttuale].nodi.costoPerNodo[i];                                    //Questo è il cuore dell'algoritmo di Dijkstra, per prima cosa cerca il nodo da analizzare attraverso la funzione nodoSuccessivo(),
                tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].precedente = posizioneAttuale;                                                                                                                                                                                   //poi, ci sono 3 possibilità, se al nodo attuale non è ancora stato assegnato un costo provvisorio, allora setta il costo per quell'adiacenza al costo per arrivare
            }else{                                                                                                                                                                                                                                                                                                                                  //al nodo che si sta analizzando più il costo dell'arco. La stessa cosa succede se il nodo è stato analizzato ma è maggiore di un costo calcolato precedentemente.
                if(tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].costoProvvisorio > tabele.grafi[posizioneAttuale].costoProvvisorio + tabele.grafi[posizioneAttuale].nodi.costoPerNodo[i]){                                //Se invece si trova un costo uguale, viene copiato in un array l'indice del nodo, per i costi alternativi. Infine, dopo aver analizzato il nodo viene attivato un flag per dire che quel nodo è stato già analizzato.
                    tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].costoProvvisorio = tabele.grafi[posizioneAttuale].costoProvvisorio + tabele.grafi[posizioneAttuale].nodi.costoPerNodo[i];
                    tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].precedente = posizioneAttuale;
                }else if(tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].costoProvvisorio == tabele.grafi[posizioneAttuale].costoProvvisorio + tabele.grafi[posizioneAttuale].nodi.costoPerNodo[i]){
                    tabele.grafi[tabele.grafi[posizioneAttuale].nodi.adiacenze[i]].nodiStessoCosto[ultimaCella(tabele,tabele.grafi[posizioneAttuale].nodi.adiacenze[i])] = posizioneAttuale;
                }
            }
        }
        tabele.grafi[posizioneAttuale].terraBruciata = true;
        contNodiBruciati++;
    }
    
    
    int contino = 0;
    cont = 0;
    nodiPrecedenti[0] = indiceArrivo;
    cout<<"Costo minimo calcolato per andare dal nodo : "<<nodoPartenza<<" al nodo: "<<nodoArrivo<<": "<<tabele.grafi[indiceArrivo].costoProvvisorio<<".\n";
    cout<<"Percorso effettuato per ottenere il costo minimo: \n";
    while(1){                                                                                                                                                                               //Questa parte vede il percorso effettuato per calcolare il costo minimo, vedendo il precedente del nodo finale,
        contino = cont;                                                                                                                                                                 //per poi vedere il precedente del precedente  trovato, e così via.
        cont++;
        nodiPrecedenti[cont] = tabele.grafi[nodiPrecedenti[contino]].precedente;
        if(nodiPrecedenti[cont] == indicePartenza){
            break;
        }
    }
    for(int i = MAX_ARR-1; i >=1; i--){
        if(nodiPrecedenti[i] != -1){
            cout<<"Nodo "<<tabele.grafi[nodiPrecedenti[i]].nome<<" ---> ";
        }
        
    }
    cout<<"Nodo "<<tabele.grafi[indiceArrivo].nome<<".\n";

    for(int i=0; i<MAX_ARR; i++){
        nodiPrecedenti[i] = -1;
    }
    
    if(tabele.grafi[indiceArrivo].nodiStessoCosto[0] == -1){                                                                                                        //Questa parte calcola i percorsi alternativi, quelli con lo stesso costo minore, per prima cosa
        cout<<"Non ci sono percorsi alternativi oltre quello calcolato.\n";                                                                                 //controlla che ci siano dei nodi inseriti nell'array con i nodi che hanno lo stesso costo di altri, riempito durante il
    }else{                                                                                                                                                                                      //calcolo con l'algoritmo di Dijkstra, poi, se ne trova, calcola il percorso considerando i precedenti dei nodi
        int contatore = 0;                                                                                                                                                              //nell'array con i nodi con lo stesso costo.
        while(1){
            if(tabele.grafi[indiceArrivo].nodiStessoCosto[contatore] != -1){
                cout<<"Percorso alternativo: "<<(contatore+1)<<endl;
                for(int i=0; i<MAX_ARR; i++)
                    nodiPrecedenti[i] = -1;
                    cont = 0;
                    contino = 0;
                    nodiPrecedenti[0] = tabele.grafi[indiceArrivo].nodiStessoCosto[contatore];
                    while(1){
                        contino = cont;
                        cont++;
                        nodiPrecedenti[cont] = tabele.grafi[nodiPrecedenti[contino]].precedente;
                        if(nodiPrecedenti[cont] == indicePartenza){
                            break;
                        }
                    }           
                    for(int i = MAX_ARR-1; i >=0; i--){
                        if(nodiPrecedenti[i] != -1){
                            cout<<"Nodo "<<tabele.grafi[nodiPrecedenti[i]].nome<<" ---> ";
                        }
                    }
                    cout<<"Nodo "<<tabele.grafi[indiceArrivo].nome<<".\n";
                    contatore++;
            }else{
                break;
            }
        }
    }
    system("pause"); 
}


void outputGrafoAdiacenze(insiemeFinale tabele){                                                                                                                            //Funzione per l'output della tabella delle adiacenze.
    cout<<"Tabella delle adiacenze\n";
    cout<<"       ";
    for(int i = 0; i < tabele.nNodi; i++){
        cout<<tabele.grafi[i].nome<<"       ";
    }
    cout<<"\n";
    for(int i = 0; i < tabele.nNodi + 1; i++){
        cout<<tabele.grafi[i].nome<<"      ";
        for(int j = 0; j < tabele.nNodi; j++){
            if(tabele.matriceAdiacenze[i][j] == 999){
                cout<<"INF       ";
            }else{
            cout<<tabele.matriceAdiacenze[i][j]<<"      ";
            }
        }
        cout<<"\n";
    }
}

int main(){
    int caso;
    int a = 0;
    while(a == 0){
        system("cls");
    cout<<"Premere 1 per inserire manualmente una tabella delle adiacenze, e saperne il percorso e costo minimo.\n";
    cout<<"Premere 2 per utilizzare una tabella delle adiacenze 5x5 gia' registrata, e saperne il percorso e costo minimo.\n";
    cout<<"Premere 3 per utilizzare una tabella delle adiacenze 10x10 gia' registrata, e saperne il percorso e costo minimo.\n";
    cout<<"Premere 4 per terminare il programma.\n";
    cin>>caso;
    switch(caso){                                                                                                                                                                                                       //Menu di scelta della tabella sulla quale andare ad utilizzare l'algoritmo di Dijkstra.
        case 1: {                                                                                                                                                                                                           //Inserimento del grafo manuale, con numero scelto dall'utente di nodi.
            insiemeFinale tabele;
            tabele = inizializzaGrafo();
            tabele = inputMEGAGrafo(tabele);
            outputGrafoAdiacenze(tabele);
            djikstraCalculator(tabele);
        break;
        }
        case 2: {                                                                                                                                                                                                              //Inserimento del grafo 5x5 di default.
            insiemeFinale tabeleA5;
            tabeleA5 = inizializzaGrafo();
            tabeleA5.nNodi = 5;
            tabeleA5.grafi[0].nome = "a";
            tabeleA5.grafi[1].nome = "b";
            tabeleA5.grafi[2].nome = "c";
            tabeleA5.grafi[3].nome = "d";
            tabeleA5.grafi[4].nome = "e";
            int tabeleA5prov[5][5] = { { 0, 1, 3, 999, 999 },         //Nodo A
                                                        { 1, 0, 999, 1, 3 },           //Nodo B
                                                        {3, 999, 0, 999, 1},         //Nodo C
                                                        {999, 1, 999, 0, 2},         //Nodo D
                                                        {999, 3, 1, 2, 0} };           //Nodo E
            for(int i = 0; i < tabeleA5.nNodi; i++){
                for(int j = 0; j < tabeleA5.nNodi;j++){
                    tabeleA5.matriceAdiacenze[i][j] = tabeleA5prov[i][j];
            }
            }
            tabeleA5 = settaGrafo(tabeleA5);
            outputGrafoAdiacenze(tabeleA5);
            djikstraCalculator(tabeleA5);
        break;
        }

        case 3: {                                                                                                                                                                                                               //Inserimento del grafo 10x10 di default.
            insiemeFinale tabeleA10;
            tabeleA10 = inizializzaGrafo();
            tabeleA10.nNodi = 10;
            tabeleA10.grafi[0].nome = "a";
            tabeleA10.grafi[1].nome = "b";
            tabeleA10.grafi[2].nome = "c";
            tabeleA10.grafi[3].nome = "d";
            tabeleA10.grafi[4].nome = "e";
            tabeleA10.grafi[5].nome = "f";
            tabeleA10.grafi[6].nome = "g";
            tabeleA10.grafi[7].nome = "h";
            tabeleA10.grafi[8].nome = "i";
            tabeleA10.grafi[9].nome = "j";
            int tabeleA10prov[10][10]= { { 0, 1, 2, 5, 999,999,999,999,999,999 },               //Nodo A
                                                            {999,0,999,999,3,999,999,999,999,999},            //Nodo B
                                                            {999,999,0,999,999,999,999,999,999,999},        //Nodo C
                                                            {999,999,999,0,999,3,7,999,999,999},                //Nodo D
                                                            {999,999,999,1,0,999,999,999,999,999},            //Nodo E
                                                            {999,999,999,999,999,0,999,999,1,999},             //Nodo F
                                                            {999,999,999,999,999,999,0,999,1,2},                //Nodo G
                                                            {999,999,999,999,999,999,999,0,999,999},        //Nodo H
                                                            {999,999,999,999,999,999,999,999,0,999},        //Nodo I
                                                            {999,999,999,999,999,999,0,1,999,0},                //Nodo J
                                                        };
            for(int i = 0; i < tabeleA10.nNodi; i++){
                for(int j = 0; j < tabeleA10.nNodi;j++){
                    tabeleA10.matriceAdiacenze[i][j] = tabeleA10prov[i][j];
            }
            }
            tabeleA10 = settaGrafo(tabeleA10);
            outputGrafoAdiacenze(tabeleA10);
            djikstraCalculator(tabeleA10);
        break;
    }
    case 4: {                                   //Termina il programma.
        a++;
    }
    }
    }
    return 0;
}