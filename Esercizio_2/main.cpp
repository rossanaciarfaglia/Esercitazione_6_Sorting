#include<iostream>
#include<iomanip>
#include<vector>
#include<chrono>
#include<random>
#include"SortingAlgorithm.hpp"
using namespace std;
using namespace SortLibrary;
using namespace std::chrono;


//stampa i vettori
void Stampa(vector<double> vettore, unsigned int taglia){
    cout<<"vettore random: " <<endl;
    for (unsigned int i= 0; i<taglia; i++){
        cout<<vettore[i]<<" ";
    }
    cout<<endl;
}

//generazione di vettori Random
vector<double> RandomVector(unsigned int taglia){
    vector<double> vettore;
    double element;
    for (unsigned int i=0; i<taglia; ++i){
        srand(i+taglia);
        element = rand() % 100; //genera elementi tra 0 e 100
        vettore.push_back(element);
    }
    return vettore;
}

//esecuzione del test di prestazione per BubbleSort
duration<double, milli> BubbleDurata(vector<double> vec, unsigned int size){
    // Misura il tempo di esecuzione per MergeSort
    auto inizio_bubble = high_resolution_clock::now();
    BubbleSort(vec);
    auto fine_bubble = high_resolution_clock::now();
    duration<double, milli> bubble_durata = fine_bubble - inizio_bubble;
    return bubble_durata;
}

//esecuzione del test di prestazione per MergeSort
duration<double, milli> MergeDurata(vector<double> vec, unsigned int size){
    // Misura il tempo di esecuzione per MergeSort
    auto inizio_merge = high_resolution_clock::now();
    MergeSort(vec, 0, size -1);
    auto fine_merge = high_resolution_clock::now();
    duration<double, milli> merge_durata = fine_merge - inizio_merge;
    return merge_durata;
}



int main(int argc, char *argv[]){
    unsigned int taglia;
    //creo vettori che conterranno i tempi di esecuzione dei due sort
    vector<double> bubble_tempi ={};
    vector<double> merge_tempi ={};
    for (unsigned int i=1 ; i < taglia+argc; ++i){   //prendo i dati dalla linea di comando
        if (argc < 2) {
            cerr << "Devi fornire almeno un argomento per la dimensione." << endl;
            return 1;
        }
        // Converti il primo argomento in un numero intero
        unsigned int taglia = atoi(argv[i]);
        cout << "Size: " << taglia << endl;
        vector<double> vettore;
        vettore = RandomVector(taglia);
        Stampa(vettore, taglia);

        //creo una copia per controllo equo dei tempi
        vector<double> copia_vec = vettore;

        //misurazione del tempo di esecuzione
        //--> misuro i tempi di esecuzione di BubbleSort
        duration<double, milli> bubble_durata = BubbleDurata(copia_vec, taglia);
        //cout <<fixed<<setprecision(8)<< "BubbleSort Time: " << bubble_durata_comando.count() << " milliseconds" << endl;

        //--> misuro i tempi di esecuzione di MergeSort
        duration<double, milli> merge_durata = MergeDurata(vettore, taglia);

        //li inserisco nel vettore creato
        bubble_tempi.push_back(double(bubble_durata.count()));
        merge_tempi.push_back(double(merge_durata.count())) ;

    }

    //effettuo la differenza dei tempi
    vector<double> differenza;
    //analisi dei risultati --> confronto dei tempi di esecuzione dei due algoritmi per determinare quale sia il migliore
    for (size_t k = 0; k < bubble_tempi.size(); ++k) {
        differenza.push_back(bubble_tempi[k] - merge_tempi[k]);
    }
    cout<<endl<<endl;

    cout<<"-->la differenza tra i tempi è stata effettuata nel seguente modo:"<<endl<<"con bubble_time - merge_time"<<endl;
    cout<<"l'eventuale valore negativo della differenza e' quindi dovuto al fatto che merge e' piu' lento di bubble"<<endl;
    cout<<"i valori ottenuti sono:"<<endl<<endl;
    //stampo le differenze
    cout<<"size    "<<"differenza di tempi ottenuta"<<endl;
    for (int i = 0; i < differenza.size(); ++i){
        cout<< i+1<<"   -->   " <<differenza[i]<<endl;
    }
    cout<<"dunque e' possibile notare che se BubbleSort e' piu' veloce per vettori di taglia piccola, MergeSort e' piu' efficiente per taglie di vettori maggiori"<<endl;

}
