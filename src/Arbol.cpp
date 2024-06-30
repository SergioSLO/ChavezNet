#include "../include/Arbol.h"

using namespace std;


ABS::ABS(const unordered_set<string> &stopwords): raiz(new Nodo()), stopwords(stopwords) {}


void ABS::insertarNodo(int dato) {
    raiz = insertarNodoAux(raiz, dato);
}

// Función auxiliar para insertar un nodo en el árbol
Nodo* ABS::insertarNodoAux(Nodo* nodo, int dato) {
    if (nodo == nullptr)
        return new Nodo(dato);

    if (dato < nodo->dato)
        nodo->left = insertarNodoAux(nodo->left, dato);
    else
        nodo->right = insertarNodoAux(nodo->right, dato);
    return nodo;
}
