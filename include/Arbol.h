#ifndef CHAVEZNET_ARBOL_H
#define CHAVEZNET_ARBOL_H
#pragma once // para q solo se llame una vez

#include "Nodo.h"
#include "PeliculaConCoincidencias.h"
#include "Cliente.h"

using namespace std;

class Cliente;

class ABS {
private:
    Nodo* raiz = nullptr;
    unordered_set<string> stopwords;

    Nodo* insertarAux(Nodo* nodo, Pelicula dato);
    void buscarenTituloAux(Nodo *nodo, const string &termino, priority_queue<PeliculaConCoincidencias> &pq,unordered_set<string> &stopwords);
    void buscarenSinopsisAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords);
    void buscarenTagsAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords);
    void recorrerYRecomendarAux(Nodo* nodo, Cliente& cliente);

public:
    void insertar(Pelicula dato);
    priority_queue<PeliculaConCoincidencias> buscarenTitulo(const string &termino);
    priority_queue<PeliculaConCoincidencias> buscarenSinopsis(const string& termino);
    priority_queue<PeliculaConCoincidencias> buscarenTags(const string& termino);
    void buscar_e_Imprimir(const string &termino, const string& tipoBusqueda);
    void recorrerYRecomendar(Cliente& cliente);
    void imprimir();
    void imprimirAux(Nodo* nodo);
};

#endif //CHAVEZNET_ARBOL_H
