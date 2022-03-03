/** @file main.cpp
    @brief Main
*/

// Vicenç Verge Mondéjar
// Usuari u1954010
// Pràctica 1


#include "Songs.h"
#include "Song.h"
#include "myexception.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <memory>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

typedef unsigned short ushort;

/** @class Main
    @brief Main del programa.
    @author Vicenç Verge
    @date 30/11/2018
*/

/**
    @brief Llegeix i processa tota la informació del primer fitxer
    @pre Fitxer vàlid
    @post Totes les línies del fitxer processades
*/
void processarLiniesFitxer1(ifstream &fitxerEntrada, Songs &conjuntSong){

    string tid, mXm_tid;
    char aux;
    unsigned comptador = 1;
    ushort id, cnt;

    fitxerEntrada.get(aux);
    while(!fitxerEntrada.eof()){
        vector<ushort> vWords(5001, 0);
        if(aux != '#'){
            if(aux == '%'){
                conjuntSong.addWord("");
                while(comptador < 5000){
                    getline(fitxerEntrada, tid, ',');
                    conjuntSong.addWord(tid);
                    comptador++;
                }
                getline(fitxerEntrada, tid, '\n');
                conjuntSong.addWord(tid);
            }
            else{
                fitxerEntrada.unget();
                getline(fitxerEntrada, tid, ',');
                getline(fitxerEntrada, mXm_tid, ',');
                conjuntSong.addSong(tid, "", "", mXm_tid, "", "");

                do{
                    fitxerEntrada>>id;
                    fitxerEntrada.ignore(1);
                    fitxerEntrada>>cnt;
                    vWords[id] = cnt;
                    fitxerEntrada.get(aux);
                }while(aux != '\n');
                 conjuntSong.entrarParaula(tid, vWords);
            }
        }
        else fitxerEntrada.ignore(1000, '\n');
        if(aux != fitxerEntrada.eof()) fitxerEntrada.get(aux);
    }
}

/**
    @brief Mira si hi ha un <SEP>
    @pre Cert
    @post Llegeix una part i mira si és un separador <SEP>, sinó llegeix i ho inclueix a la dada passada
*/
void esSep(ifstream &fEntrat, string &dada){

    string sep = "", SecondDada;
    char aux;
    int i = 1;
    bool acabat = false;
    while(i < 4 and !acabat){
        fEntrat.get(aux);
        if(i == 1 and aux != 'S') acabat = true;
        if(i == 2 and aux != 'E') acabat = true;
        if(i == 3 and aux != 'P') acabat = true;
        i++;
    }
    if(acabat and !fEntrat.eof()){
        while(i != 1){
             fEntrat.unget();
             i--;
        }
        getline(fEntrat, SecondDada, '<');
        esSep(fEntrat, SecondDada);         //per si hi ha més '<' que no precedeixin un SEP
        dada += "<";
        dada += SecondDada;
    }
    else fEntrat.get(aux);
}

/**
    @brief Llegeix i processa els elements d'una línia del segon fitxer
    @pre Cert
    @post Els diferents elements del fitxer llegit
*/
void llegirSong(ifstream &fEntrat, string &tid, string &name, string &title, string &mXm_tid, string &mXm_name, string &mXm_title, string &aux){

    getline(fEntrat, tid, '<');
    esSep(fEntrat, tid);
    getline(fEntrat, name, '<');
    esSep(fEntrat, name);
    getline(fEntrat, title, '<');
    esSep(fEntrat, title);
    getline(fEntrat, mXm_tid, '<');
    esSep(fEntrat, mXm_tid);
    getline(fEntrat, mXm_name, '<');
    esSep(fEntrat, mXm_name);
    getline(fEntrat, mXm_title, '\n');
}

/**
    @brief Llegeix i processa tota la informació del segon fitxer
    @pre Fitxer vàlid
    @post Totes les línies del fitxer processades
*/
void processarLiniesFitxer2(ifstream &fEntrat,Songs &conjuntSong){

    string tid, name, title, mXm_tid, mXm_name, mXm_title, aux;
    char charAux;

    fEntrat.get(charAux);
    while(!fEntrat.eof()){
        fEntrat.unget();
        if(charAux != '#'){
            llegirSong(fEntrat, tid, name, title, mXm_tid, mXm_name, mXm_title, aux);
            shared_ptr<Song> ptrAux = conjuntSong.getSong(tid);

            if(ptrAux != nullptr) ptrAux->actualitzar(name, title, mXm_name, mXm_title);
        }
        else fEntrat.ignore(1000, '\n');
        if(charAux != fEntrat.eof()) fEntrat.get(charAux);
    }
}

/**
    @brief Llegeix els dos fitxers
    @pre Cert
    @post Ha llegit els dos fitxers adequadament, altrament throw
*/
void processarEntrades(string fitxer1, string fitxer2, Songs &conjuntSong){

    ifstream fEntrat1(fitxer1.c_str());
    ifstream fEntrat2(fitxer2.c_str());

    if (fEntrat1.fail()) throw myexception("Fitxer 1 no trobat.");
    else{
        cout<<"Reading file "<<fitxer1<<"... ";
        processarLiniesFitxer1(fEntrat1, conjuntSong);
        cout<<"DONE"<<endl;
    }
    if (fEntrat2.fail()) throw myexception("Fitxer 2 no trobat.");
    else{
        cout<<"Reading file "<<fitxer2<<"... ";
        processarLiniesFitxer2(fEntrat2, conjuntSong);
        cout<<"DONE"<<endl;
    }
}

/**
    @brief Dona el titol i l'autor de la canço relacionada amb la id
    @pre Cert
    @post Dona titol i autor d'una canço (que aparegui al 1r fitxer) a partir de qualsevol dels seus dos codis identificadors
*/
void comandaGET(Songs &conjuntSong, string dada){

    string titol, autor;

    shared_ptr<Song> ptrAux = conjuntSong.getSong(dada);
    if(ptrAux != nullptr){
        titol = ptrAux->getMSDTitle();
        autor = ptrAux->getMSDAuthor();
        cout<<"tid: "<<ptrAux->getTid()<<endl
            <<"MSD_artist_name: "<<ptrAux->getMSDAuthor()<<endl
            <<"MSD_title: "<<ptrAux->getMSDTitle()<<endl
            <<"mXm_tid: "<<ptrAux->getMXMtid()<<endl
            <<"mXm_artist_name: "<<ptrAux->getMXMAuthor()<<endl
            <<"mXm_title: "<<ptrAux->getMXMTitle()<<endl;
    }
    else cout<<"["<<dada<<"] NOT FOUND"<<endl;
    cout<<endl;
}

/**
    @brief Esborra una canço
    @pre Cert
    @post Esborra una canço a partir de qualsevol dels seus dos codis
*/
void comandaDELETE(Songs &conjuntSong, string dada){

    bool esborrat = conjuntSong.deleteSong(dada);

    if(esborrat) cout<<"["<<dada<<"] DELETED"<<endl;
    else cout<<"["<<dada<<"] NOT FOUND"<<endl;
    cout<<endl;
}

/**
    @brief Diu en quines cançons apareix una paraula determinada
    @pre Cert
    @post Diu en quines cançons apareix una paraula determinada (de la llista del 1r fitxer). Donar llista amb artistes i canço, ordenada per ordre alfabetic
*/
void comandaWHERE(Songs &conjuntSong, string dada){

    set<pair<string, string>> aux = conjuntSong.songsWithWord(dada);

    if(!aux.empty()){
        cout<<"Word ["<<dada<<"] occurs in "<<aux.size()<<" songs:"<<endl;
        set<pair<string, string>>::const_iterator itS = aux.begin();
        while(itS != aux.end()){
            cout<<itS->first<<" - "<<itS->second<<endl;
            itS++;
        }
    }
    else cout<<"Word ["<<dada<<"] not found in any song!"<<endl;
    cout<<endl;
}

/**
    @brief Diu quina es la paraula que apareix mes vegades en una canço
    @pre Cert
    @post Diu quina es la paraula que apareix mes vegades en una canço determinada (a partir de qualsevol dels seus codis). En cas d'empat les dona totes, en qualsevol ordre
*/
void comandaFREQIN(Songs &conjuntSong, string dada){

    list<string> lAux = conjuntSong.mostFrequentWordsIn(dada);
    if(!lAux.empty()){
        cout<<"The most frequent word in song ["<<dada<<"] are:"<<endl;
        list<string>::iterator itL = lAux.begin();
        while(itL != lAux.end()){
            cout<<*itL<<endl;
            itL++;
        }
    }
    else cout<<"The song ["<<dada<<"] does not exist"<<endl;
    cout<<endl;
}

/**
    @brief Llista les n paraules mes frequents en el conjunt de cançons
    @pre Cert
    @post Llista les n paraules mes frequents en el conjunt de cançons, en ordre alfabetic. Si hi ha empat les llista totes
*/
void comandaLFREQ(Songs &conjuntSong, ushort n){

    cout<<"The "<<n<<" most frequent words are:"<<endl;
    set<string> sAux = conjuntSong.mostFrequentN(n);

    set<string>::iterator itS = sAux.begin();
    while(itS != sAux.end()){
        cout<<*itS<<endl;
        itS++;
    }
    cout<<endl;
}

/**
    @brief Gestio de les comandes
    @pre Cert
    @post Gestiona les comandes
*/
void tractarComandes(Songs &conjuntSong){

    string adjunt, comanda;
    char fi = ' ';
    cin.ignore(100, '\n');
    getline(cin, comanda, ' ');
    while(fi != '*'){
        if(comanda == "GET"){
            getline(cin, adjunt, '\n');
            comandaGET(conjuntSong, adjunt);
        }
        else if(comanda == "DELETE"){
            getline(cin, adjunt, '\n');
            comandaDELETE(conjuntSong, adjunt);
        }
        else if(comanda == "WHERE"){ //WHERE IS
            cin.ignore(3);
            getline(cin, adjunt, '\n');
            comandaWHERE(conjuntSong, adjunt);
        }
        else if(comanda == "MOST"){ //MOST FREQUENT
            cin.ignore(17);
            getline(cin, adjunt, '\n');
            comandaFREQIN(conjuntSong, adjunt);
        }
        else if(comanda == "LIST"){ //LIST MOST FREQUENT
            cin.ignore(14);
            ushort n;
            cin>>n;
            comandaLFREQ(conjuntSong, n);
            getline(cin, comanda, '\n');
        }

        else cout<<"La comanda '"<<comanda<<"' no esta prevista, introdueix una altra"<<endl;
        cin.get(fi);
        if(fi != '*'){
            cin.unget();
            getline(cin, comanda, ' ');
        }
    }
}

using namespace std;

/**
    @brief Int main()
    @pre Cert
    @post Part principal del programa
*/
int main()
{
#ifdef _WIN32
SetConsoleOutputCP( CP_UTF8 );
SetConsoleCP( CP_UTF8 );
#endif

    string fitxer1, fitxer2, comanda;
    Songs conjuntSong;

    cout<<"Inserta el nom dels dos fitxers: "<<endl;
    cin>>fitxer1>>fitxer2;

    try{
        processarEntrades(fitxer1, fitxer2, conjuntSong);
        cout<<"Ara entre les comandes, per acabar '*': "<<endl;
        tractarComandes(conjuntSong);
    }

    catch (myexception e){
      cerr<<e.what()<<endl;
    }

    return 0;
}
