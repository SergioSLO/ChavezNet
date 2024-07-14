cmake_minimum_required(VERSION 3.26)
project(ChavezNet)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(ChavezNet
        main.cpp
        src/Pelicula.cpp
        src/Arbol.cpp
        src/Nodo.cpp
        src/PeliculaConCoincidencias.cpp
        src/Cliente.cpp
        src/Menu.cpp
        src/ClienteFactory.cpp
        src/ClienteConcreteFactory.cpp
)
