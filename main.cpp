#include "include/Pelicula.h"
#include "include/Cliente.h"
#include "include/Arbol.h"

using namespace std;

void mostrarMenu() {
    cout << "--------------------------" << endl;
    cout << "1. Buscar pelicula" << endl;
    cout << "2. Ver mis likes" << endl;
    cout << "3. Ver mis recomendaciones" << endl;
    cout << "4. Dar like a una pelicula" << endl;
    cout << "5. Salir" << endl;
    cout << "--------------------------" << endl;
    cout << "Opcion: ";
}

ABS crearArbolBinario(const unordered_map<string, Pelicula>& peliculas) {
    ABS arbol;
    for (const auto& par : peliculas) {
        arbol.insertar(par.second);
    }
    return arbol;
}

void buscarPelicula(ABS& arbol) {
    string terminoBusqueda;
    int tipoBusqueda;

    cout << "Ingresa el termino a buscar: ";
    getline(cin, terminoBusqueda);
    cout << "--------------------------" << endl
         << "Para buscar por Titulo (1)" << endl
         << "Para buscar por Sinopsis (2)" << endl
         << "Para buscar por Tag (3)" << endl
         << "Opcion: ";
    cin >> tipoBusqueda;
    cin.ignore(); // Limpiar el buffer de entrada
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
    }
}

void darLikePelicula(Cliente& cliente, const unordered_map<string, Pelicula>& peliculas) {
    string nombrePelicula;
    cout << "Ingresa el nombre de la pelicula a la que quieres dar like: ";
    getline(cin, nombrePelicula);

    auto it = peliculas.find(nombrePelicula);
    if (it != peliculas.end()) {
        cliente.agregarLike(it->second);
        cout << "Le has dado like a: " << nombrePelicula << endl;
    } else {
        cout << "La pelicula no fue encontrada. Intenta de nuevo." << endl;
    }
}


int main() {
    // Ruta del archivo CSV
    string nombreArchivo = "C:\\Users\\LENOVO\\OneDrive\\Escritorio\\UTEC-ciclo-3\\Programacion-III\\ChavezNet\\data\\RawData_fixed.csv";

    // leer
    unordered_map<string, Pelicula> peliculas = leerCSV(nombreArchivo);

    // Arbolito
    ABS arbol = crearArbolBinario(peliculas);
    cout << "Cantidad de nodos: " << arbol.contarNodos() << endl;

    // Cliente
    string nombreCliente;
    cout << "Ingresa tu nombre: ";
    getline(cin, nombreCliente);

    Cliente cliente(nombreCliente);

    int opcion;

    // Bucle principal del menu
    while (true) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                // Buscar pelicula
                buscarPelicula(arbol);
                break;
            case 2:
                // Ver likes
                cliente.imprimirLikes();
                break;
            case 3:
                // Ver recomendaciones
                cliente.generarRecomendaciones(arbol);
                cliente.imprimirRecomenaciones();
                break;
            case 4:
                // Dar like a una pelicula
                darLikePelicula(cliente, peliculas);
                break;
            case 5:
                // Salir
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }

    return 0;
}