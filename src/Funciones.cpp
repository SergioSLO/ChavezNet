#include "Funciones.h"
#include "Database.h"
#include "Pelicula.h"
#include "DatabaseSingleton"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


void leerCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::string field;
        std::vector<std::string> fields;
        while (std::getline(s, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() >= 4) {
            std::vector<std::string> tags; // Ajusta esto según tu formato CSV
            auto pelicula = PeliculaFactory::crearPelicula(fields[0], fields[1], fields[2], tags);
            DatabaseSingleton::getInstance().agregarPelicula(pelicula);
        }
    }
}

void imprimirPelicula(const Pelicula& pelicula) {
    std::cout << "Titulo: " << pelicula.titulo << std::endl;
    std::cout << "Director: " << pelicula.sinopsis << std::endl;
    std::cout << "Genero: " << pelicula.sinopsis << std::endl;
    std::cout << "Año: " << pelicula.sinopsis.length() << std::endl;
    std::cout << "Actores: ";
    for (const auto& actor : pelicula.tags) {
        std::cout << actor << " ";
    }
    std::cout << std::endl;
}
