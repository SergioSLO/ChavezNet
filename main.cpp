#include "include/Pelicula.h"
#include "include/Arbol.h"
#include "include/DatabaseSingleton.h"
#include "include/IStrategyBusqueda.h"
#include "include/Observer.h"
#include "include/DecoradorPelicula.h"
#include "include/Pelicula.h"
#include "include/ABS.h"
using namespace std;

//Comit para milton
//comit para ANGEL
int main() {

    string nombreArchivo = "C:/Users/Hamilton/OneDrive/Escritorio/ChavezNet/data/RawData_fixed.csv";

    auto peliculas = leerCSV(nombreArchivo);

    // Lista de stopwords
    unordered_set<string> stopwords = {"a", "the", "and", "of", "in", "on", "at", "for", "with"};

    // Buscar la información de "A Hard Day's Night" - Ejemplo correcto: "Henry: Portrait of a Serial Killer"
    string tituloBusqueda = "A Hard Day's Night";

    // Creación del Árbol Binario de Búsqueda y la inserción del todas las pelicula al mismo
    ABS arbol;
    for (auto& par : peliculas) {
        arbol.insertar(par.second);
    }

    //Uso solo para prueba
    Pelicula busqueda;
    busqueda.titulo = tituloBusqueda;

    Nodo* resultado = arbol.buscarTitulo(busqueda);
    imprimirPelicula(resultado->dato);
    return 0;
}

/*
// Usar la sintaxis y funciones de unordered_map para buscar y mostrar la película.
auto it = peliculas.find(tituloBusqueda);
if (it != peliculas.end()) {
imprimirPelicula(it->second);
} else {
cout << "Pelicula no encontrada: " << tituloBusqueda << endl;
}

*/