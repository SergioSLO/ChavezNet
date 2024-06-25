#include "include/Pelicula.h"
using namespace std;



int main() {
    string nombreArchivo = "C://Users//flxam//Downloads//Proyecto - Progra III//ChavezNet//data//RawData_fixed.csv";

    auto peliculas = leerCSV(nombreArchivo);

    // Buscar la información de "A Hard Day's Night" - Ejemplo correcto: "Henry: Portrait of a Serial Killer"
    string tituloBusqueda = "A Hard Day's Night";

    // Usar la sintaxis y funciones de unordered_map para buscar y mostrar la película
    auto it = peliculas.find(tituloBusqueda);
    if (it != peliculas.end()) {
        imprimirPelicula(it->second);
    } else {
        cout << "Película no encontrada: " << tituloBusqueda << endl;
    }

    return 0;
}
