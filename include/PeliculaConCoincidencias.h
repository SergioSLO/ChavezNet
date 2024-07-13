#ifndef CHAVEZNET_PELICULACONCOINCIDENCIAS_H
#define CHAVEZNET_PELICULACONCOINCIDENCIAS_H
#pragma once // para q solo se llame una vez


#include "Pelicula.h"

struct PeliculaConCoincidencias {
    Pelicula pelicula;
    int coincidencias;
    bool operator<(const PeliculaConCoincidencias& otro) const {
        return coincidencias < otro.coincidencias; // Orden ascendente, la cola prioriza el mayor
    }
};


#endif //CHAVEZNET_PELICULACONCOINCIDENCIAS_H
