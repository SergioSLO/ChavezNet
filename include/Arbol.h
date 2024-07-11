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
#include <queue>


using namespace std;

struct Nodo {
    Pelicula dato;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor
    Nodo(Pelicula dato) : dato(dato), izquierdo(nullptr), derecho(nullptr) {}
};


struct PeliculaConCoincidencias {
    Pelicula pelicula;
    int coincidencias;
    bool operator<(const PeliculaConCoincidencias& otro) const {
        return coincidencias < otro.coincidencias; // Orden ascendente, la cola prioriza el mayor
    }
};

class ABS {
private:
    Nodo* raiz = nullptr;
    unordered_set<string> stopwords;

    Nodo* insertarAux(Nodo* nodo, Pelicula dato);
    Nodo* buscarTituloAux(Nodo* nodo, Pelicula dato);
    Nodo* buscarSinopsisAux(Nodo* nodo, Pelicula dato);
    void buscar_en_titulo(Nodo* nodo, string busqueda, vector<Pelicula>& resultados);
    void buscar_en_sinopsis(Nodo* nodo, string busqueda, vector<Pelicula>& resultados);

    void buscarenSinopsisAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords);


public:

    void insertar(Pelicula dato);
    Nodo* buscarTitulo(Pelicula dato);
    Nodo* buscarSinopsis(Pelicula dato);
    vector<Pelicula> buscar(string termino);

    priority_queue<PeliculaConCoincidencias> buscarenSinopsis(const string& termino);
};

#endif //CHAVEZNET_ARBOL_H
