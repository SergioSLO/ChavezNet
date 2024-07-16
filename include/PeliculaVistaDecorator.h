//
// Created by Hamilton on 15/07/2024.
//

#ifndef CHAVEZNET_PELICULAVISTADECORATOR_H
#define CHAVEZNET_PELICULAVISTADECORATOR_H

#include "PeliculaDecorator.h"

class PeliculaVistaDecorator : public PeliculaDecorator {
private:
    int vecesVista;
public:
    explicit PeliculaVistaDecorator(PeliculaComponent* componente, int vecesVista = 0)
            : PeliculaDecorator(componente), vecesVista(vecesVista) {}

    void imprimir(Cliente* cliente) const override {
        PeliculaDecorator::imprimir(cliente);
        cout << "Veces vista: " << vecesVista << endl;
    }

    void incrementarVista() {
        vecesVista++;
    }
};



#endif //CHAVEZNET_PELICULAVISTADECORATOR_H
