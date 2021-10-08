#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 16

struct dati_nodo
{
    string nome;
    int posizione[MAX];
    int costo_nodo[MAX];
    int numero_archi;
    bool disponible;
    int costo_parziale;
    int nodo_precedente;
};

struct nm
{
    dati_nodo nodi[MAX];
    int matrice[MAX][MAX];
    int numero_nodi;
    int numero_versi;
};


void menu()
{
    system("cls");
    cout<<"1--->Utilizzare grafo a 5 nodi.\n";
    cout<<"2--->Utilizzare grafo a 10 nodi.\n";
    cout<<"3--->Utilizzare grafo a nodi inseriti dall'utente.\n";
}

void menu_secondario()
{
    system("cls");
    cout<<"1--->Utilizzare soluzione defualt\n";
    cout<<"2--->utilizzare dati inseriti dall'utente.\n";
    cout<<"3--->Torna al menu principale.\n";
}

int inserimento_corretto(int min, int max){

	int numero;
	while(1){
		cin>>numero;
		if(numero>max || numero<min || cin.fail()){
			cout<<"Inserire solo valori compresi tra "<<min<<" e "<<max<<".\n";
            cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}
		else{
			break;
		}

	}
	return numero;
}

nm analizza_dati(nm vettore)
{
    for(int i = 0; i<vettore.numero_nodi; i++)
	{
		int cont = 0;
		for(int j = 0; j<vettore.numero_nodi;j++)
		{
			if(vettore.matrice[i][j] != 0 && vettore.matrice[i][j] != 999)
			{
                vettore.nodi[i].posizione[cont] = j;
                vettore.nodi[i].costo_nodo[cont] = vettore.matrice[i][j];
				cont++;
			}
		}
		vettore.nodi[i].numero_archi = cont;
	}
    return vettore;
}

nm input_default(nm vettore)
{
    int numero_nodi;
    cout<<"Inserire il numero di nodi.\n";
    numero_nodi = inserimento_corretto(2, MAX);
    vettore.numero_nodi = numero_nodi;
    vettore.numero_versi = 2;
    for(int i=0; i < vettore.numero_nodi; i++)
    {
        cout<<"Inserire il nome del nodo: "<<(i+1)<<endl;
        cin>>vettore.nodi[i].nome;
    }
    vettore.numero_nodi = numero_nodi;

    for(int i = 0; i<numero_nodi; i++)
	{
		for(int j=0;j<numero_nodi;j++)
		{
			if(vettore.matrice[i][j] != 0)
			{
				cout<<"Nodo "<<vettore.nodi[i].nome<<" ---> "<<vettore.nodi[j].nome<<":\n";
				vettore.matrice[i][j] = inserimento_corretto(0, 999);
			}
		}
	}
    vettore = analizza_dati(vettore);
    return vettore;
}

nm input_specifico(nm vettore, int numero_nodi)
{
    for(int i = 0; i < numero_nodi; i++)
    {
        cout<<"Inserire il nome del nodo: "<<(i+1)<<endl;
        cin>>vettore.nodi[i].nome;
    }

    vettore.numero_nodi = numero_nodi;
    vettore.numero_versi = 1;

    cout<<"Il grafo sara' automaticamente impostato per essere ad un verso.\n";
    for(int i = 0; i<vettore.numero_nodi; i++)
	{
		for(int j=0;j<vettore.numero_nodi;j++)
		{
			if(vettore.matrice[i][j] == -1 )
			{
				cout<<"Nodo "<<vettore.nodi[i].nome<<" ---> "<<vettore.nodi[j].nome<<":\n";
				vettore.matrice[i][j] = inserimento_corretto(0,999);
                vettore.matrice[j][i] = vettore.matrice[i][j];
			}
		}
	}

    vettore = analizza_dati(vettore);
    return vettore;
}

nm svuota_nodi()
{
    nm supporto_dati;
    for(int i = 0; i < MAX; i++)
    {
        supporto_dati.nodi[i].numero_archi = -1;
        supporto_dati.nodi[i].disponible = true;
        supporto_dati.nodi[i].costo_parziale = -1;

        for(int j = 0; j < MAX; j++)
        {
            supporto_dati.nodi[i].posizione[j] = -1;
            supporto_dati.nodi[i].costo_nodo[j] = -1;
            supporto_dati.matrice[i][j] = -1;
        }
    }
    
    return supporto_dati;
}

int percorso_breve(nm vettore)
{
    int min = 999;
    int pos;

    for(int i = 0; i<vettore.numero_nodi; i++)
    {
        if(vettore.nodi[i].disponible == true && vettore.nodi[i].costo_parziale != -1 && vettore.nodi[i].costo_parziale <= min)    
        {
            min = vettore.nodi[i].costo_parziale;
            pos = i;
        }
    }
    return pos;
}

void dijkstra(nm vettore)
{
    string a, b;
    int inizio, arrivo;
    int posizione;
    if(vettore.numero_versi == 1)
    {
        cout<<"un verso nodo "<<vettore.nodi[0].nome<<endl;
        inizio = 0;
    }
    else
    {
        while(true)
        {
            cout<<"Inserire nodo di partenza.\n";
            cin>>a;
            for(int i = 0; i < vettore.numero_nodi; i++)
            {
                if(a == vettore.nodi[i].nome)
                {
                    inizio = i;
                    break;
                }
            }
            if(inizio != -1)
            break;
        }
    }
    while(true)
    {
        cout<<"Inserire nodo di arrivo.\n";
        cin>>b;
        for(int i = 0; i < vettore.numero_nodi; i++)
        {
            if(b == vettore.nodi[i].nome)
            {
                arrivo = i;
            }
        }
        if(arrivo != -1)
        break;
    }

    vettore.nodi[inizio].costo_parziale = 0; 
    int passo_successivo;  
    int iterazioni = 0;
    while(iterazioni != vettore.numero_nodi)
    {   
        
        posizione = percorso_breve(vettore);
        for(int i = 0; i < vettore.nodi[posizione].numero_archi; i++)
        {
            passo_successivo = vettore.nodi[posizione].posizione[i];
            if(vettore.nodi[passo_successivo].costo_parziale != -1)
            {
                int costo_confronto = vettore.nodi[posizione].costo_parziale + vettore.nodi[posizione].costo_nodo[i];
                if(costo_confronto < vettore.nodi[passo_successivo].costo_parziale)
                {
                    vettore.nodi[passo_successivo].costo_parziale = costo_confronto;
                    vettore.nodi[passo_successivo].nodo_precedente = posizione;
                }
            }
            else
            {
                vettore.nodi[passo_successivo].costo_parziale = vettore.nodi[posizione].costo_parziale + vettore.nodi[posizione].costo_nodo[i];
                vettore.nodi[passo_successivo].nodo_precedente = posizione;
            }
        }
        vettore.nodi[posizione].disponible = false;
        iterazioni++;
    } 
    
    cout<<"nodo: "<<vettore.nodi[arrivo].nome<<" costo: "<<vettore.nodi[arrivo].costo_parziale<<endl;
    cout<<"Percoso: Nodo "<<vettore.nodi[arrivo].nome<<"<---";
    int supporto;
    int indice_precedente = vettore.nodi[arrivo].nodo_precedente;
    while(1)//percorso
    {
        supporto = vettore.nodi[indice_precedente].nodo_precedente;
        cout<<"Nodo "<<vettore.nodi[indice_precedente].nome<<" <--- ";
        indice_precedente = supporto;
        if(supporto == inizio)
        {
            cout<<"Nodo "<<vettore.nodi[supporto].nome<<"\n";
            break;
        }
    }
    system("pause");
    
}


int main()
{
    bool continuare = true;
    while(true)
    {
        continuare = true;
        menu();
        switch(inserimento_corretto(1,3))
        {
            case 1:
            while(continuare)
            {
               menu_secondario();
               switch(inserimento_corretto(1,3)) 
               {
                    case 1:
                    {
                        nm dati_totali = svuota_nodi();
                        dati_totali.nodi[0].nome = "A";
                        dati_totali.nodi[1].nome = "B";
                        dati_totali.nodi[2].nome = "C";
                        dati_totali.nodi[3].nome = "D";
                        dati_totali.nodi[4].nome = "E";
                        dati_totali.numero_versi = 1;
                        dati_totali.numero_nodi = 5;
                        int matrice[5][5]= { { 0, 6, 2, 999, 999 }, 
                           { 999, 0, 999, 1, 999 }, 
                           {999, 999, 0, 4, 5}, 
                           {999, 999, 999, 0, 1}, 
                           {999, 999, 999, 999, 999} };
                        for(int i=0; i<5; i++)
                        {
                            for(int j=0; j<5; j++)
                            {
                                dati_totali.matrice[i][j]=matrice[i][j];
                            }
                        }
                        dati_totali = analizza_dati(dati_totali);
                        dijkstra(dati_totali);
                        break;
                    }
                    case 2:
                    {
                        nm dati_totali = svuota_nodi();
                        dati_totali = input_specifico(dati_totali, 5);
                        dijkstra(dati_totali);
                        break;
                    }

                    case 3:
                    {
                        continuare = false;
                        break;
                    }
               }
            }
            break;

            case 2:
            while(continuare)
            {
               menu_secondario();
               switch(inserimento_corretto(1,3)) 
               {
                    case 1:
                    {
                        nm dati_totali = svuota_nodi();
                        dati_totali.nodi[0].nome = "A";
                        dati_totali.nodi[1].nome = "B";
                        dati_totali.nodi[2].nome = "C";
                        dati_totali.nodi[3].nome = "D";
                        dati_totali.nodi[4].nome = "E";
                        dati_totali.nodi[5].nome = "F";
                        dati_totali.nodi[6].nome = "G";
                        dati_totali.nodi[7].nome = "H";
                        dati_totali.nodi[8].nome = "I";
                        dati_totali.nodi[9].nome = "J";
                        dati_totali.numero_versi = 1;
                        dati_totali.numero_nodi = 10;
                        int matrice[10][10]= { { 0, 1, 2, 5, 999,999,999,999,999,999 },//a
                            {999,0,999,999,3,999,999,999,999,999},//b
                            {999,999,0,999,999,999,999,999,999,999},//c
                            {999,999,999,0,999,3,7,999,999,999},//d
                            {999,999,999,1,0,999,999,999,999,999},//e
                            {999,999,999,999,999,0,999,999,1,999},//f
                            {999,999,999,999,999,999,0,999,1,2},//g
                            {999,999,999,999,999,999,999,0,999,999},//h
                            {999,999,999,999,999,999,999,999,0,999},//i
                            {999,999,999,999,999,999,0,1,999,0},//j
                            };
                        for(int i=0; i<10; i++)
                        {
                            for(int j=0; j<10; j++)
                            {
                                dati_totali.matrice[i][j]=matrice[i][j];
                            }
                        }
                        dati_totali = analizza_dati(dati_totali);
                        dijkstra(dati_totali);
                        break;
                    }
                    case 2:
                    {
                        nm dati_totali = svuota_nodi();
                        dati_totali = input_specifico(dati_totali, 10);
                        dijkstra(dati_totali);
                        break;
                    }

                    case 3:
                    {
                        continuare = false;
                        break;
                    }
               }
            }
            break;

            case 3:
            nm dati_totali = svuota_nodi();
            dati_totali = input_default(dati_totali);
            dijkstra(dati_totali);
            break;

        }
    }
    
}

