#ifndef CHAVEZNET_CLIENTE_H
#define CHAVEZNET_CLIENTE_H
#pragma once // para q solo se llame una vez

#include "Arbol.h"
#include "Pelicula.h"

class ABS;



class Cliente {
private:
    string nombre;
    set<Pelicula> likes;
    vector<Pelicula> peliculasPorVer;
    unordered_map<string, int> tags_gustados;
    double mejor = 0;
    priority_queue<pair<double, Pelicula>, vector<pair<double, Pelicula>>, greater<>> recomendaciones;

public:
    explicit Cliente(string nombre);
    void agregarLike(const Pelicula& pelicula);
    void agregarPorVer(const Pelicula& pelicula);
    void imprimirLikes();
    void imprimirPorVer();
    void imprimirRecomenaciones();
    void generarRecomendaciones(ABS& arbol);
    void agregarRecomendacion(const Pelicula& pelicula, double intensidad);
    friend class ABS;
};


#endif //CHAVEZNET_CLIENTE_H
