//
// Created by Hamilton on 13/07/2024.
//

#ifndef CHAVEZNET_DECORADORPELICULA_H
#define CHAVEZNET_DECORADORPELICULA_H

#include "Pelicula.h"
#include <memory>

class DecoradorPelicula : public Pelicula {
private:
    std::shared_ptr<Pelicula> pelicula;

public:
    DecoradorPelicula(std::shared_ptr<Pelicula> pelicula)
            : Pelicula(*pelicula), pelicula(pelicula) {}

    std::string getDescripcionExtendida() const {
        return "Titulo: " + titulo + ", Sinopsis: " + sinopsis + ", Año: " + std::to_string(sinopsis.length());
    }
};




#endif //CHAVEZNET_DECORADORPELICULA_H
