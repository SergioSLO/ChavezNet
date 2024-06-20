#pragma once // Para q se ejecute solo 1 vez
#ifndef CHAVEZNET_PELICULA_H
#define CHAVEZNET_PELICULA_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Pelicula {
private:
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> tags;
public:
    Pelicula();
    Pelicula(const string& imdb_id, const string& titulo, const string& sinopsis, const vector<string>& tags);
    void imprimirPelicula();
};


#endif //CHAVEZNET_PELICULA_H
