/** @file Song.h
    @brief Classe Song
*/

// Vicen� Verge Mond�jar
// Usuari u1954010
// Pr�ctica 1

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
    @brief Can�� que guarda les dades rellevants i les paraules m�s usades d'aquesta
    que estan en una llista.
    @author Vicen� Verge
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
        @brief Crea una Song amb els par�metres enviats
        @pre Cert
        @post Constructor que copia les entrades
        */

        void addWord(ushort idx, ushort cnt);
        /**<
        @brief Afegeix una paraula a la llista de la can��
        @pre There is no word with index idx in this song
        @post The pair <idx,cnt> has been added to the set of words of this song
        */

        ushort count(ushort idx) const;
        /**<
        @brief Diu quantes vegades apareix la paraula que es demana en la can��
        @pre Cert
        @post Says which is the count for index idx
        */

        list<ushort> mostFrequentWordIdxs() const;
        /**<
        @brief Diu les paraules que m�s apareixen en la can��
        @pre Cert
        @post Returns the indices of the most frequent words in this song
        */

        void giveWords(vector<int> &vWords);
        /**<
        @brief Suma els cnt de les paraules de la can�� en un vector passat per refer�ncia
        @pre Cert
        @post Suma cnt de _mWords a la posicio id del vector per totes les paraules de _mWords
        */

        void actualitzar(string name, string title, string mXm_name, string mXm_title);
        /**<
        @brief Actualitza una can�� afegint els atributs: _MSD_artist_name, _MSD_title, _mXm_artist_name, _mXm_title
        @pre Cert
        @post Actualitza una can�o afegint-hi aquestes variables
        */

        string getTid() const;
        /**<
        @brief Retorna el _tid
        @pre Cert
        @post Retorna el _tid de la can�o
        */

        string getMXMtid() const;
        /**<
        @brief Retorna el _mXm_tid
        @pre Cert
        @post Retorna el _mXm_tid de la can�o
        */

        string getMSDTitle() const;
        /**<
        @brief Retorna el _MSD_title
        @pre Cert
        @post Retorna el _MSD_title de la can�o
        */

        string getMXMTitle() const;
        /**<
        @brief Retorna el _mXm_title
        @pre Cert
        @post Retorna el _mXm_title de la can�o
        */

        string getMSDAuthor() const;
        /**<
        @brief Retorna el _MSD_artist_name
        @pre Cert
        @post Retorna el _MSD_artist_name de la can�o
        */

        string getMXMAuthor() const;
        /**<
        @brief Retorna el _mXm_artist_name
        @pre Cert
        @post Retorna el _mXm_artist_name de la can�o
        */

    private:

        string _tid, _MSD_artist_name, _MSD_title, _mXm_tid, _mXm_artist_name, _mXm_title;
        map<ushort, ushort> _mWords;
};

#endif // SONG_H
