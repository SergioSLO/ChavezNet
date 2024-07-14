#ifndef CHAVEZNET_CLIENTECONCRETEFACTORY_H
#define CHAVEZNET_CLIENTECONCRETEFACTORY_H
#pragma once

#include "ClienteFactory.h"
#include "Cliente.h"

class ConcreteClienteFactory : public ClienteFactory {
public:
    Cliente* crearCliente(const std::string& nombre) const override {
        return new Cliente(nombre);
    }
};


#endif //CHAVEZNET_CLIENTECONCRETEFACTORY_H
