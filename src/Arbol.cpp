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

vector<Pelicula> ABS::buscar(string termino) {
    vector<Pelicula> resultados_busqueda_titulo;
    buscarAux(raiz,termino,resultados_busqueda_titulo);

    if(resultados_busqueda_titulo.size() < 10){
        vector<Pelicula> resultados_busqueda_sinopsis;
        buscar_en_sinopsis(raiz, termino, resultados_busqueda_sinopsis);

    }
}