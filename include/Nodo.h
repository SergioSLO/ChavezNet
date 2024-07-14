#ifndef CHAVEZNET_NODO_H
#define CHAVEZNET_NODO_H
#pragma once // para q solo se llame una vez


#include <utility>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <thread>
#include <mutex>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

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
