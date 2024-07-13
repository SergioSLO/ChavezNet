#ifndef CHAVEZNET_NODO_H
#define CHAVEZNET_NODO_H
#pragma once // para q solo se llame una vez


#include <utility>

#include "Pelicula.h"

struct Nodo {
    Pelicula dato;
    Nodo* izquierdo;
    Nodo* derecho;
    explicit Nodo(Pelicula dato) : dato(std::move(dato)), izquierdo(nullptr), derecho(nullptr) {}
    ~Nodo() {
        delete izquierdo;
        delete derecho;
    }

};


#endif //CHAVEZNET_NODO_H
