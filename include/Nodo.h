#ifndef CHAVEZNET_NODO_H
#define CHAVEZNET_NODO_H
#pragma once // para q solo se llame una vez


#include <utility>

#include "Pelicula.h"

template <typename T>
struct Nodo {
    T dato;
    Nodo* izquierdo;
    Nodo* derecho;
    explicit Nodo(T dato) : dato(std::move(dato)), izquierdo(nullptr), derecho(nullptr) {}
    ~Nodo() {
        delete izquierdo;
        delete derecho;
    }

};


#endif //CHAVEZNET_NODO_H
