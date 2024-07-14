#ifndef CHAVEZNET_PELICULA_H
#define CHAVEZNET_PELICULA_H
#pragma once // para q solo se llame una vez


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

using namespace std;

struct Pelicula {
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> tags;
};


unordered_map<string, Pelicula> leerCSV(const string& nombreArchivo);
unordered_map<string, Pelicula> leerCSVconId(const string& nombreArchivo);
void imprimirPelicula(const Pelicula& pelicula);
vector<string> Stopwords(const string& texto, const unordered_set<string>& stopwords);


#endif //CHAVEZNET_PELICULA_H
