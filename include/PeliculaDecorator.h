//
// Created by Hamilton on 15/07/2024.
//

#ifndef CHAVEZNET_PELICULADECORATOR_H
#define CHAVEZNET_PELICULADECORATOR_H
#include "PeliculaComponent.h"

class PeliculaDecorator : public PeliculaComponent {
protected:
    PeliculaComponent* componente;
public:
    explicit PeliculaDecorator(PeliculaComponent* componente) : componente(componente) {}
    void imprimir(Cliente* cliente) const override {
        componente->imprimir(cliente);
    }
    ~PeliculaDecorator() override {
        delete componente;
    }
};



#endif //CHAVEZNET_PELICULADECORATOR_H
