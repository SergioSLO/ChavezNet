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

Nodo* ABS::buscarSinopsis(Pelicula dato) {
    return buscarSinopsisAux(raiz, dato);
}
Nodo* ABS::buscarSinopsisAux(Nodo *nodo, Pelicula dato) {
    if (nodo == nullptr || nodo->dato.sinopsis == dato.sinopsis){
        return nodo;
    }
    if (dato.sinopsis < nodo->dato.sinopsis)
        return buscarTituloAux(nodo->izquierdo, dato);
    else
        return buscarSinopsisAux(nodo->derecho, dato);
}
