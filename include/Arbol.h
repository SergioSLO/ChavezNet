#ifndef CHAVEZNET_ARBOL_H
#define CHAVEZNET_ARBOL_H

#include "Pelicula.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

struct Nodo {
    unordered_map<char,Nodo*> hijo;
    unordered_set<Pelicula*> peliculaTitulo;
    unordered_set<Pelicula*> peliculaSinopsis;
};

class ABS {
private:
    Nodo* raiz=nullptr;
    unordered_set<string> stopwords;

    void insertarPalabraAux(Nodo* nodo, const string& palabra, Pelicula* pelicula, bool esTitulo);
    unordered_set<Pelicula*> buscarPalabraAux(Nodo* nodo, const string& prefijos, bool esTitulo);


public:
    ABS(const unordered_set<string>& stopwords);

    void insertarPalabra(const string& palabra, Pelicula* pelicula, bool esTitulo);
    vector<Pelicula*> buscarPelicula(const string& query);
};


#endif //CHAVEZNET_ARBOL_H
