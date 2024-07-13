//
// Created by Hamilton on 13/07/2024.
//

#ifndef CHAVEZNET_ISTRATEGYBUSQUEDA_H
#define CHAVEZNET_ISTRATEGYBUSQUEDA_H


#include "Pelicula.h"
#include "vector"
#include <memory>

class IStrategyBusqueda {
public:
    virtual std::vector<std::shared_ptr<Pelicula>> buscar(const std::vector<std::shared_ptr<Pelicula>>& peliculas, const std::string& criterio) = 0;
};

class BusquedaPorTitulo : public IStrategyBusqueda {
public:
    std::vector<std::shared_ptr<Pelicula>> buscar(const std::vector<std::shared_ptr<Pelicula>>& peliculas, const std::string& criterio) override {
        std::vector<std::shared_ptr<Pelicula>> resultado;
        for (const auto& pelicula : peliculas) {
            if (pelicula->titulo.find(criterio) != std::string::npos) {
                resultado.push_back(pelicula);
            }
        }
        return resultado;
    }
};

class BusquedaPorDirector : public IStrategyBusqueda {
public:
    std::vector<std::shared_ptr<Pelicula>> buscar(const std::vector<std::shared_ptr<Pelicula>>& peliculas, const std::string& criterio) override {
        std::vector<std::shared_ptr<Pelicula>> resultado;
        for (const auto& pelicula : peliculas) {
            if (pelicula->sinopsis.find(criterio) != std::string::npos) {
                resultado.push_back(pelicula);
            }
        }
        return resultado;
    }
};
#endif //CHAVEZNET_ISTRATEGYBUSQUEDA_H
