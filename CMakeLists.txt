cmake_minimum_required(VERSION 3.26)
project(ChavezNet)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChavezNet
        main.cpp
        src/Database.cpp
        include/Database.h
        src/Pelicula.cpp
        include/Pelicula.h
        include/Arbol.h
        src/Arbol.cpp)
