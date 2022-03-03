// Vicenç Verge Mondéjar
// Usuari u1954010
// Pràctica 1

#include "Songs.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <memory>

using namespace std;

Songs::Songs()
{
    //buit
}

shared_ptr<Song> Songs::addSong(const string tid, const string MSD_artist_name, const string MSD_title, const string mXm_tid, const string mXm_artist_name, const string mXm_title){

         shared_ptr<Song> ptrSong(new Song(tid, MSD_artist_name, MSD_title, mXm_tid, mXm_artist_name, mXm_title));

         _mXmSong.insert(pair<string, shared_ptr<Song> >(mXm_tid, ptrSong));
         _tidSong.insert(pair<string, shared_ptr<Song> >(tid, ptrSong));

         return ptrSong;
}

bool Songs::deleteSong(const string id){

    shared_ptr<Song> ptrAux = getSong(id);
    if(ptrAux == nullptr) return false;

    else{
        string tid, mXm_tid;
        tid = ptrAux->getTid();
        mXm_tid = ptrAux->getMXMtid();

        _tidSong.erase(tid);
        _mXmSong.erase(mXm_tid);

        return true;
    }
}

void Songs::addWord(const string s){

    _lWords.push_back(s);
}

shared_ptr<Song> Songs::getSong(const string id) const{

    bool tid = esTid(id);

    if(tid){
        map<string, shared_ptr<Song> >::const_iterator itT = _tidSong.find(id);
        if(itT != _tidSong.end()) return itT->second;
        else return nullptr;
    }
    else{
        map<string, shared_ptr<Song> >::const_iterator itMxM = _mXmSong.find(id);
        if(itMxM != _mXmSong.end()) return itMxM->second;
        else return nullptr;
    }
}

set<pair<string, string>> Songs::songsWithWord(string w) const{

    set<pair<string, string>> solucio;
    pair<string, string> recollidor;
    int idWord, i = 0;
    bool acabat = false;
    ushort suma;

    while(i < static_cast<int>(_lWords.size()) and !acabat){  //aconsegueixo la id de la paraula que busco en les cançons
        if(_lWords[i] == w){
            idWord = i;
            acabat = true;
        }
        i++;
    }

    map<string, shared_ptr<Song>>::const_iterator itM = _mXmSong.begin();
    while(itM != _mXmSong.end()){
        suma = itM->second->count(static_cast<ushort>(idWord));
        if(suma != 0) solucio.insert(pair<string, string> (itM->second->getMXMAuthor(), itM->second->getMXMTitle()));
        itM++;
    }
    return solucio;
}

list<string> Songs::mostFrequentWordsIn(const string id) const{

    list<string> fWords;
    string paraula;

    shared_ptr<Song> itT = getSong(id);
    if(itT != nullptr){
        list<ushort> lUS = itT->mostFrequentWordIdxs();
        list<ushort>::iterator itLU = lUS.begin();
        while(itLU != lUS.end()){
            paraula = _lWords.at(*itLU);
            fWords.push_back(paraula);
            itLU++;
        }
    }
    return fWords;
}

set<string> Songs::mostFrequentN(ushort n) const{

    vector<int> vMostFreq(5001); //aqui van els cnt de les paraules
    set<pair<int, int> > sWOrdered;    //paraules ordenades per cnt
    set<string> sortida;
    string paraula;
    int comptador = 0;
    map<string, shared_ptr<Song> >::const_iterator itT = _tidSong.begin();
    while(itT != _tidSong.end()){   //empleno el vMostFreq
        itT->second->giveWords(vMostFreq);
        itT++;
    }
    for(int i = 0; i < static_cast<int>(vMostFreq.size()); i++){
            if(vMostFreq[i] != 0) sWOrdered.insert(pair<int, int>(vMostFreq[i], i));
    }

    set<pair<int, int> >::reverse_iterator itsWO = sWOrdered.rbegin();  //per llegir del final al principi
    set<pair<int, int> >::reverse_iterator itsWO2 = --sWOrdered.rend(); //comprova si hi ha repetits

    while(itsWO != sWOrdered.rend() and comptador < n){
        paraula = _lWords.at(itsWO->second);
        sortida.insert(paraula);
        if(itsWO->first != itsWO2->first) comptador++;
        itsWO2 = itsWO;
        itsWO++;
    }
    return sortida;
}

void Songs::entrarParaula(string element, vector<ushort> vWords){

    map<string, shared_ptr<Song>>::const_iterator itM = _tidSong.find(element);

    for(unsigned i = 0; i < vWords.size(); i++) if(vWords[i] != 0) itM->second->addWord(i, vWords[i]);
}

bool Songs::esTid(const string id) const{   //mXm_tid sempre són numeros

    bool esLletra = false;
    unsigned i = 0;

    while(i < id.size() and !esLletra){
        if(id[i] > '9' or id[i] < '0') esLletra = true;
        else i++;
    }
    return esLletra;
}
