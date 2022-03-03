// Vicenç Verge Mondéjar
// Usuari u1954010
// Pràctica 1

#include "Song.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

Song::Song()
{
    _tid = _MSD_artist_name = _MSD_title = _mXm_tid = _mXm_artist_name = _mXm_title = "NULL";
}

Song::Song(const string tid, const string MSD_artist_name, const string MSD_title, const string mXm_tid, const string mXm_artist_name, const string mXm_title){

    _tid = tid;
    _MSD_artist_name = MSD_artist_name;
    _MSD_title = MSD_title;
    _mXm_tid = mXm_tid;
    _mXm_artist_name = mXm_artist_name;
    _mXm_title = mXm_title;
}

void Song::addWord(ushort idx, ushort cnt){

    _mWords[idx] = cnt;     //es pot fer així perquè no existeix l'índex al map
}

ushort Song::count(ushort idx) const{

    map<ushort, ushort>::const_iterator itM;
    itM = _mWords.find(idx);

    if(itM == _mWords.end()) return 0;
    else return itM->second;
}

list<ushort> Song::mostFrequentWordIdxs() const{

    ushort maxim = 0;
    list<ushort> mesFrequents;
    map<ushort, ushort>::const_iterator itM = _mWords.begin();

    while(itM != _mWords.end()){
        if(itM->second > maxim) maxim = itM->second;
        itM++;
    }
    itM = _mWords.begin();

    while(itM != _mWords.end()){
        if(itM->second == maxim) mesFrequents.push_back(itM->first);
        itM++;
    }
    return mesFrequents;
}

void Song::giveWords(vector<int> &vWords){

    map<ushort, ushort>::const_iterator itM = _mWords.begin();
    while(itM != _mWords.end()){
        vWords.at(itM->first) = vWords.at(itM->first) + itM->second;
        itM++;
    }
}

void Song::actualitzar(string name, string title, string mXm_name, string mXm_title){

    _MSD_artist_name = name;
    _MSD_title = title;
    _mXm_artist_name = mXm_name;
    _mXm_title = mXm_title;
}

string Song::getTid() const{

    return _tid;
}

string Song::getMXMtid() const{

    return _mXm_tid;
}

string Song::getMSDTitle() const{

    return _MSD_title;
}

string Song::getMXMTitle() const{

    return _mXm_title;
}

string Song::getMSDAuthor() const{

    return _MSD_artist_name;
}

string Song::getMXMAuthor() const{

    return _mXm_artist_name;
}
