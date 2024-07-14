#ifndef CHAVEZNET_ARBOL_H
#define CHAVEZNET_ARBOL_H
#pragma once // para que solo se llame una vez

#include "Nodo.h"
#include "PeliculaConCoincidencias.h"
#include "Cliente.h"
#include <unordered_set>
#include <queue>
#include <string>

using namespace std;

class Cliente;

class ABS {
private:
    Nodo<Pelicula>* raiz = nullptr;
    unordered_set<string> stopwords;

    ABS() {} //Singleton
    ~ABS() {} //Singleton

    ABS(const ABS&) = delete; //Singleton
    ABS& operator=(const ABS&) = delete; //Singleton

    Nodo<Pelicula>* insertarAux(Nodo<Pelicula>* nodo, Pelicula dato);
    void buscarenTituloAux(Nodo<Pelicula> *nodo, const string &termino, priority_queue<PeliculaConCoincidencias> &pq, unordered_set<string> &stopwords);
    void buscarenSinopsisAux(Nodo<Pelicula>* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords);
    void buscarenTagsAux(Nodo<Pelicula>* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords);
    void recorrerYRecomendarAux(Nodo<Pelicula>* nodo, Cliente& cliente);
    Pelicula buscarPorIdAux(Nodo<Pelicula>* nodo, const string& id);
    void imprimirAux(Nodo<Pelicula>* nodo);
    int contarNodosAux(Nodo<Pelicula>* nodo);

public:
    static ABS& getInstance() {
        static ABS instance;
        return instance;
    }//Singleton

    void insertar(Pelicula dato);
    priority_queue<PeliculaConCoincidencias> buscarenTitulo(const string &termino);
    priority_queue<PeliculaConCoincidencias> buscarenSinopsis(const string& termino);
    priority_queue<PeliculaConCoincidencias> buscarenTags(const string& termino);
    Pelicula buscarPorId(const string& id);
    void buscar_e_Imprimir(const string &termino, const string& tipoBusqueda);
    void recorrerYRecomendar(Cliente& cliente);
    void imprimir();
    int contarNodos();
};

#endif //CHAVEZNET_ARBOL_H
