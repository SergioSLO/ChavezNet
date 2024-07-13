//
// Created by Hamilton on 13/07/2024.
//
#ifndef CHAVEZNET_OBSERVER_H
#define CHAVEZNET_OBSERVER_H


#include <vector>
#include <memory>
#include "iostream"

class IObserver {
public:
    virtual void actualizar() = 0;
};

class BaseDeDatosObservable {
private:
    std::vector<std::shared_ptr<IObserver>> observers;

public:
    void agregarObserver(std::shared_ptr<IObserver> observer) {
        observers.push_back(observer);
    }

    void notificar() {
        for (auto& observer : observers) {
            observer->actualizar();
        }
    }
};

class InterfazUsuario : public IObserver {
public:
    void actualizar() override {
        std::cout<< "La interfaz de usuario ha sido actualizada." << std::endl;
    }
};

#endif //CHAVEZNET_OBSERVER_H
