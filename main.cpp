#include "include/Pelicula.h"
#include "include/Arbol.h"
using namespace std;

//Comit para milton
int main() {

    string nombreArchivo = "C://Users//flxam//Downloads//Proyecto - Progra III//ChavezNet//data//RawData_fixed.csv";

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
    string terminoBusqueda = "Zalinsky";
    auto resultados = arbol.buscarenSinopsis(terminoBusqueda);

    cout << "Peliculas con coincidencias para '" << terminoBusqueda << "':" << endl;
    while (!resultados.empty()) {
        auto top = resultados.top();
        resultados.pop();
        imprimirPelicula(top.pelicula);
    }

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