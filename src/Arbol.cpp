#include "../include/Arbol.h"

using namespace std;


void ABS::insertar(Pelicula dato) {
    raiz = insertarAux(raiz, dato);
}

Nodo *ABS::insertarAux(Nodo *nodo, Pelicula dato) {
    if (nodo == nullptr) {
        return new Nodo(dato);
    }
    if (dato.titulo < nodo->dato.titulo) {
        nodo->izquierdo = insertarAux(nodo->izquierdo, dato);
    } else {
        nodo->derecho = insertarAux(nodo->derecho, dato);
    }
    return nodo;
}

Nodo* ABS::buscarTitulo(Pelicula dato) {
    return buscarTituloAux(raiz, dato);
}
Nodo* ABS::buscarTituloAux(Nodo* nodo, Pelicula dato) {
    if (nodo == nullptr || nodo->dato.titulo == dato.titulo){
        return nodo;
    }
    if (dato.titulo < nodo->dato.titulo)
        return buscarTituloAux(nodo->izquierdo, dato);
    else
        return buscarTituloAux(nodo->derecho, dato);
}

priority_queue<PeliculaConCoincidencias> ABS::buscarenSinopsis(const string& termino) {
    priority_queue<PeliculaConCoincidencias> pq;
    if (raiz) {
        buscarenSinopsisAux(raiz, termino, pq, stopwords);
    }
    return pq;
}

void ABS::buscarenSinopsisAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    string primeraPalabraValida;
    stringstream ss(termino);
    string palabra;

    // Busca priorizando la primera palabra que no sea una stopword
    while (ss >> palabra && primeraPalabraValida.empty()) {
        if (!stopwords.count(palabra)) {
            primeraPalabraValida = palabra;
        }
    }

    if (!primeraPalabraValida.empty()) {
        size_t pos = nodo->dato.sinopsis.find(primeraPalabraValida);
        if (pos != string::npos) {
            PeliculaConCoincidencias item = {nodo->dato, 1};
            pq.push(item);
            if (pq.size() > 20) pq.pop();
        }
    }

    buscarenSinopsisAux(nodo->izquierdo, termino, pq, stopwords);
    buscarenSinopsisAux(nodo->derecho, termino, pq, stopwords);
}