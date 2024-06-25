#include "include/Database.h"
using namespace std;

int main() {
    string nombreArchivo = "C:\\Users\\LENOVO\\OneDrive\\Escritorio\\UTEC-ciclo-3\\Programacion-III\\ChavezNet\\data\\RawData.csv";
    Database db(nombreArchivo);

    string IdBusqueda = "tt0057603";

    // Usar la sintaxis y funciones de unordered_map para buscar y mostrar la película
    auto it = db.getData().find(IdBusqueda);
    if (it != db.getData().end()) {
        it->second.imprimirPelicula();
    } else {
        cout << "Película no encontrada: " << IdBusqueda << endl;
    }

    return 0;
}
