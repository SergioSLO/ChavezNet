#include "include/Pelicula.h"
#include "include/Arbol.h"
using namespace std;

//Comit para Felix
int main() {

    string nombreArchivo = "C:/Users/flxam/OneDrive/Desktop/ChavezNet/data/RawData_fixed.csv";

    auto peliculas = leerCSV(nombreArchivo);

    // Lista de stopwords
    unordered_set<string> stopwords = {"a", "the", "and", "of", "in", "on", "at", "for", "with"};

    // Creación del Árbol Binario de Búsqueda y la inserción del todas las pelicula al mismo
    ABS arbol;
    for (auto& par : peliculas) {
        arbol.insertar(par.second);
    }

    //Uso solo para prueba
    string terminoBusqueda;
    int tipoBusqueda;

    cout << "Ingresa el termino a buscar: ";
    getline(cin, terminoBusqueda);

    while (true) {
        cout << "--------------------------" << endl
             << "Para buscar por Titulo (1)" << endl
             << "Para buscar por Sinopsis (2)" << endl
             << "Para buscar por Tag (3)" << endl
             << "Opcion: ";
        cin >> tipoBusqueda;
        cout << "--------------------------" << endl;

        switch (tipoBusqueda) {
            case 1:
                arbol.buscar_e_Imprimir(terminoBusqueda, "Titulo");
                break;
            case 2:
                arbol.buscar_e_Imprimir(terminoBusqueda, "Sinopsis");
                break;
            case 3:
                arbol.buscar_e_Imprimir(terminoBusqueda, "Tag");
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                continue;
        }
        break;
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