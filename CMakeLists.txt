cmake_minimum_required(VERSION 3.26)
project(ChavezNet)

# Cambia el estándar de C++ a C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
