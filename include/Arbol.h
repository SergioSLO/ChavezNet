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
    Nodo* insertarNodoAux(Nodo* nodo, int dato);
    Nodo* buscarNodoAux(Nodo* nodo, int dato);

public:
    void insertarNodo(int dato);
    Nodo* buscarNodo(int dato);
};


#endif //CHAVEZNET_ARBOL_H
