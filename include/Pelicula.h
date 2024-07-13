#ifndef CHAVEZNET_PELICULA_H
#define CHAVEZNET_PELICULA_H


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

using namespace std;

struct Pelicula {
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> tags;
};

//string leerSinopsis(ifstream& archivo);
//bool leerLinea(ifstream& archivo, string& linea);
unordered_map<string, Pelicula> leerCSV(const string& nombreArchivo);
void imprimirPelicula(const Pelicula& pelicula);
vector<string> Stopwords(const string& texto, const unordered_set<string>& stopwords);


#endif //CHAVEZNET_PELICULA_H
