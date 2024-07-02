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
    Pelicula dato;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor
    Nodo(Pelicula dato) : dato(dato), izquierdo(nullptr), derecho(nullptr) {}
};

class ABS {
private:
    Nodo* raiz = nullptr;
    unordered_set<string> stopwords;

    Nodo *insertarAux(Nodo* nodo, Pelicula dato);
    void buscarAux(Nodo* nodo, string busqueda, vector<Pelicula>& resultados);
    void buscar_en_sinopsis(Nodo* nodo, string busqueda, vector<Pelicula>& resultados);

public:

    void insertar(Pelicula dato);
    vector<Pelicula> buscar(string termino);

};


#endif //CHAVEZNET_ARBOL_H
