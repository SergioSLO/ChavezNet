#pragma once // Para q se ejecute solo 1 vez
#ifndef CHAVEZNET_DATABASE_H
#define CHAVEZNET_DATABASE_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Pelicula.h"

using namespace std;

class Database {
private:
    unordered_map<string , Pelicula> data;
    static string leerCeldaConComas(istringstream& stream);
    static string leerSinopsis(istringstream& stream);
public:
    Database(const string& filename);
    unordered_map<string , Pelicula> getData();
};


#endif //CHAVEZNET_DATABASE_H
