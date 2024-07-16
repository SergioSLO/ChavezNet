//
// Created by Hamilton on 15/07/2024.
//

#ifndef CHAVEZNET_PELICULACOMPONENT_H
#define CHAVEZNET_PELICULACOMPONENT_H

#include "Pelicula.h"
#include "Cliente.h"


class Cliente;

class PeliculaComponent {
public:
    virtual void imprimir(Cliente* cliente) const = 0;
    virtual ~PeliculaComponent() = default;
};




#endif //CHAVEZNET_PELICULACOMPONENT_H
