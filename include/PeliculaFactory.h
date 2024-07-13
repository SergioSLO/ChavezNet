//
// Created by Hamilton on 13/07/2024.
//

#ifndef CHAVEZNET_PELICULAFACTORY_H
#define CHAVEZNET_PELICULAFACTORY_H

#include "Pelicula.h"
#include <memory>

class PeliculaFactory {
public:
    static std::shared_ptr<Pelicula> crearPelicula(const std::string& imdb_id, const std::string& titulo, const std::string& sinopsis, const std::vector<std::string>& tags) {
        return std::make_shared<Pelicula>(Pelicula{imdb_id, titulo, sinopsis, tags});
    }
};



#endif //CHAVEZNET_PELICULAFACTORY_H
