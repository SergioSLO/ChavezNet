#include "../include/Arbol.h"

using namespace std;


void ABS::insertar(Pelicula dato) {
    insertarAux(raiz, dato);
}

Nodo *ABS::insertarAux(Nodo *nodo, Pelicula dato) {
    if (nodo == nullptr) {
        new Nodo(dato);
    }
    if (dato.titulo < nodo->dato.titulo) {
        nodo->izquierdo = insertarAux(nodo->izquierdo, dato);
    } else {
        nodo->derecho = insertarAux(nodo->derecho, dato);
    }
    return nodo;
}

Nodo* ABS::buscarTitulo(Pelicula dato) {
    return buscarSinopsisAux(raiz, dato);
}
Nodo* ABS::buscarTituloAux(Nodo* nodo, Pelicula dato) {
    if (nodo == nullptr || nodo->dato.titulo == dato.titulo){
        return nodo;
    }
    if (dato.titulo < nodo->dato.titulo)
        return buscarTituloAux(nodo->izquierdo, dato);
    else
        return buscarSinopsisAux(nodo->derecho, dato);
}

Nodo* ABS::buscarSinopsis(Pelicula dato) {
    return buscarSinopsisAux(raiz, dato);
}
Nodo* ABS::buscarSinopsisAux(Nodo *nodo, Pelicula dato) {
    if (nodo == nullptr || nodo->dato.sinopsis == dato.titulo){
        return nodo;
    }
    if (dato.sinopsis < nodo->dato.titulo)
        return buscarTituloAux(nodo->izquierdo, dato);
    else
        return buscarSinopsisAux(nodo->derecho, dato);
}


vector<Pelicula> ABS::resultados(string termino) {
    vector<Pelicula> resultados_busqueda_titulo;
    buscarAux(raiz,termino,resultados_busqueda_titulo);

    if(resultados_busqueda_titulo.size() < 10){
        vector<Pelicula> resultados_busqueda_sinopsis;
        buscar_en_sinopsis(raiz, termino, resultados_busqueda_sinopsis);
    }
}