/** @file Song.h
    @brief Classe Song
*/

// Vicenç Verge Mondéjar
// Usuari u1954010
// Pràctica 1

#ifndef SONG_H
#define SONG_H
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

typedef unsigned short ushort;

/** @class Song
    @brief Cançó que guarda les dades rellevants i les paraules més usades d'aquesta
    que estan en una llista.
    @author Vicenç Verge
    @date 30/11/2018
*/

class Song
{
    public:
        Song();
        /**<
        @brief Crea una Song a NULL
        @pre Cert
        @post Constructor buit;
        */

        Song(const string tid, const string MSD_artist_name, const string MSD_title, const string mXm_tid, const string mXm_artist_name, const string mXm_title);
        /**<
        @brief Crea una Song amb els paràmetres enviats
        @pre Cert
        @post Constructor que copia les entrades
        */

        void addWord(ushort idx, ushort cnt);
        /**<
        @brief Afegeix una paraula a la llista de la cançó
        @pre There is no word with index idx in this song
        @post The pair <idx,cnt> has been added to the set of words of this song
        */

        ushort count(ushort idx) const;
        /**<
        @brief Diu quantes vegades apareix la paraula que es demana en la cançó
        @pre Cert
        @post Says which is the count for index idx
        */

        list<ushort> mostFrequentWordIdxs() const;
        /**<
        @brief Diu les paraules que més apareixen en la cançó
        @pre Cert
        @post Returns the indices of the most frequent words in this song
        */

        void giveWords(vector<int> &vWords);
        /**<
        @brief Suma els cnt de les paraules de la cançó en un vector passat per referència
        @pre Cert
        @post Suma cnt de _mWords a la posicio id del vector per totes les paraules de _mWords
        */

        void actualitzar(string name, string title, string mXm_name, string mXm_title);
        /**<
        @brief Actualitza una cançó afegint els atributs: _MSD_artist_name, _MSD_title, _mXm_artist_name, _mXm_title
        @pre Cert
        @post Actualitza una canço afegint-hi aquestes variables
        */

        string getTid() const;
        /**<
        @brief Retorna el _tid
        @pre Cert
        @post Retorna el _tid de la canço
        */

        string getMXMtid() const;
        /**<
        @brief Retorna el _mXm_tid
        @pre Cert
        @post Retorna el _mXm_tid de la canço
        */

        string getMSDTitle() const;
        /**<
        @brief Retorna el _MSD_title
        @pre Cert
        @post Retorna el _MSD_title de la canço
        */

        string getMXMTitle() const;
        /**<
        @brief Retorna el _mXm_title
        @pre Cert
        @post Retorna el _mXm_title de la canço
        */

        string getMSDAuthor() const;
        /**<
        @brief Retorna el _MSD_artist_name
        @pre Cert
        @post Retorna el _MSD_artist_name de la canço
        */

        string getMXMAuthor() const;
        /**<
        @brief Retorna el _mXm_artist_name
        @pre Cert
        @post Retorna el _mXm_artist_name de la canço
        */

    private:

        string _tid, _MSD_artist_name, _MSD_title, _mXm_tid, _mXm_artist_name, _mXm_title;
        map<ushort, ushort> _mWords;
};

#endif // SONG_H
