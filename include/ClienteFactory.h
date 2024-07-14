#ifndef CHAVEZNET_CLIENTEFACTORY_H
#define CHAVEZNET_CLIENTEFACTORY_H
#pragma once
#include "Cliente.h"

class ClienteFactory {
public:
    virtual ~ClienteFactory() = default;
    virtual Cliente* crearCliente(const std::string& nombre) const = 0;
};


#endif //CHAVEZNET_CLIENTEFACTORY_H
