#ifndef CHAVEZNET_ARBOL_H
#define CHAVEZNET_ARBOL_H


struct Nodo {
    int dato;
    Nodo* left;
    Nodo* right;

    // Constructor
    Nodo(int dato) {
        this->dato = dato;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Nodo* raiz=nullptr;
    Nodo* insertarNodoAux(Nodo* nodo, int dato);
    Nodo* buscarNodoAux(Nodo* nodo, int dato);

public:
    void insertarNodo(int dato);
    Nodo* buscarNodo(int dato);
};


#endif //CHAVEZNET_ARBOL_H
