//
// Created by Hamilton on 13/07/2024.
//

#ifndef CHAVEZNET_DATABASESINGLETON_H
#define CHAVEZNET_DATABASESINGLETON_H

#include "Database.h"
#include <memory>

class DatabaseSingleton {
private:
    static std::unique_ptr<Database> instancia;
    DatabaseSingleton() = default;

public:
    static Database& getInstance() {
        if (!instancia) {
            instancia.reset(new Database("C:/Users/Hamilton/OneDrive/Escritorio/ChavezNet/data/RawData_fixed.csv"));
        }
        return *instancia;
    }
};

std::unique_ptr<Database> DatabaseSingleton::instancia = nullptr;


#endif //CHAVEZNET_DATABASESINGLETON_H
