/** @file Songs.h
    @brief Classe Songs
*/

// Vicenç Verge Mondéjar
// Usuari u1954010
// Pràctica 1

#ifndef SONGS_H
#define SONGS_H
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <memory>       //per fer el shared pointer, tambe anar a settings<compiler<...+11;
#include"Song.h"

using namespace std;

/** @class Songs
    @brief Conjunt de cançons, indexats pel tid i mXm_tid. I un vector de paraules.
    @author Vicenç Verge
    @date 30/11/2018
*/

class Songs     // A set of songs, indexed by both tid and mXm_tid, and a list of words.
{
    public:
        Songs();
        /**<
        @brief Crea una Songs a NULL
        @pre Cert
        @post Constructor buit
        */

        shared_ptr<Song> addSong(const string tid,
                                      const string MSD_artist_name,
                                      const string MSD_title,
                                      const string mXm_tid,
                                      const string mXm_artist_name,
                                      const string mXm_title);
        /**<
        @brief S'afegeix una cançó
        @pre There is no song with this tid and mXm_tid in this set of songs
        @post The song has been added and a shared pointer to it is returned
        */

        bool deleteSong(const string id);
        /**<
        @brief S'elimina la cançó indicada si pot, i diu si la ha esborrat
        @pre Cert
        @post The song with (tid == id) or (mXm_tid == id) in this set has
        been deleted; says if it succeeded
        */

        void addWord(const string s);
        /**<
        @brief S'afegeix una paraula
        @pre Cert
        @post s has been added as the last word in the list of words
        */

        shared_ptr<Song> getSong(const string id) const;
        /**<
        @brief Dona un punter a la cançó indicada, si no hi és el punter és NULL
        @pre Cert
        @post If there is a song (tid == id) or (mXm_tid == id) in this set
        then returns a pointer to this song; otherwise it returns nullptr
        */

        set<pair<string, string>> songsWithWord(string w) const;
        /**<
        @brief Dona els noms dels artistes i de les cançons on apareix la paraula indicada
        @pre Cert
        @post Returns the set of pairs <mXm_artist_name, mXm_title> of songs
        with word w
        */

        list<string> mostFrequentWordsIn(const string id) const;
        /**<
        @brief Si la cançó existeix dona les paraules que més apareixen en la cançó,
        si no existeix dona una llista buida
        @pre Cert
        @post If there is a song (tid == id) or (mXm_tid == id) in this set
        then returns the list of its most frequent words; otherwise it
        returns an empty list
        */

        set<string> mostFrequentN(ushort n) const;
        /**<
        @brief Dona les n paraules més frequents en un conjunt de cançons
        @pre Cert
        @post Returns the n most frequent words in this set of songs
        */

        void entrarParaula(string element, vector<ushort> vWords);
        /**<
        @brief Entra totes les paraules a una cançó
        @pre Cert
        @post Entra totes les paraules a la canço indicada pel tid
        */

    private:

        map<string, shared_ptr<Song> > _tidSong;   //tid, Song
        map<string, shared_ptr<Song> > _mXmSong;   //mXm_tid, Song
        vector<string> _lWords;

        bool esTid(const string id) const;
        /**<
        @brief Comprova si l'string que es passa és un tid o un mXm_tid
        @pre Cert
        @post Retorna cert si id és un tid, fals si es un mXm_tid
        */
};

#endif // SONGS_H
