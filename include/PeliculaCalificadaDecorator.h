//
// Created by Hamilton on 15/07/2024.
//

#ifndef CHAVEZNET_PELICULACALIFICADADECORATOR_H
#define CHAVEZNET_PELICULACALIFICADADECORATOR_H
#include "PeliculaDecorator.h"

class PeliculaCalificadaDecorator : public PeliculaDecorator {
private:
    double calificacion;
public:
    explicit PeliculaCalificadaDecorator(PeliculaComponent* componente, double calificacion = 0)
            : PeliculaDecorator(componente), calificacion(calificacion) {}

    void imprimir(Cliente* cliente) const override {
        PeliculaDecorator::imprimir(cliente);
        cout << "Calificacion: " << calificacion << endl;
    }

    void setCalificacion(double nuevaCalificacion) {
        calificacion = nuevaCalificacion;
    }
};



#endif //CHAVEZNET_PELICULACALIFICADADECORATOR_H
