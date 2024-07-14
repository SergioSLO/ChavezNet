#include "Pelicula.h"
#include "Cliente.h"
#include "Arbol.h"
#include "ClienteConcreteFactory.h"

using namespace std;

void limpiarTerminal() {
    system("cls");
    cout << "\033[2J\033[1;1H";
}

int mostrarMenu() {
    int highlight = 0;
    const int numOptions = 6;
    char input;

    while (true) {
        limpiarTerminal();
        cout << "\033[1;32m"; // verde para el título
        cout << "--------------------------" << endl;
        for (int i = 0; i < numOptions; ++i) {
            if (i == highlight) {
                cout << "\033[1;31m"; // rojito
                cout << " -> ";
            } else {
                cout << "    ";
            }

            switch (i) {
                case 0: cout << "1. Buscar pelicula" << endl; break;
                case 1: cout << "2. Ver mis likes" << endl; break;
                case 2: cout << "3. Ver mis recomendaciones" << endl; break;
                case 3: cout << "4. Ver mis guardados" << endl; break;
                case 4: cout << "5. Dar like a una pelicula" << endl; break;
                case 5: cout << "6. Salir" << endl; break;
            }

            if (i == highlight) {
                cout << "\033[1;32m";
            }
        }
        cout << "--------------------------" << endl;
        cout << "\033[0m"; // Resetear color

        input = _getch();

        if (input == 72) { // Flecha arriba
            highlight = (highlight == 0) ? numOptions - 1 : highlight - 1;
        } else if (input == 80) { // Flecha abajo
            highlight = (highlight == numOptions - 1) ? 0 : highlight + 1;
        } else if (input == 13) { // Enter
            break;
        }
    }

    limpiarTerminal();
    return highlight + 1; // Retornar la opción seleccionada (1-based index)
}

int seleccionarTipoBusqueda() {
    int highlight = 0;
    const int numOptions = 4;
    char input;

    while (true) {
        limpiarTerminal();
        cout << "\033[1;34m"; // azul para el submenú
        cout << "--------------------------" << endl;
        for (int i = 0; i < numOptions; ++i) {
            if (i == highlight) {
                cout << "\033[1;31m"; // rojo para la opción seleccionada
                cout << "> ";
            } else {
                cout << "  ";
            }

            switch (i) {
                case 0: cout << "Para buscar por Titulo" << endl; break;
                case 1: cout << "Para buscar por Sinopsis" << endl; break;
                case 2: cout << "Para buscar por Tag" << endl; break;
                case 3: cout << "Para buscar por Id" << endl; break;
            }

            if (i == highlight) {
                cout << "\033[1;34m";
            }
        }
        cout << "--------------------------" << endl;
        cout << "\033[0m";

        input = _getch();

        if (input == 72) { // Flecha arriba
            highlight = (highlight == 0) ? numOptions - 1 : highlight - 1;
        } else if (input == 80) { // Flecha abajo
            highlight = (highlight == numOptions - 1) ? 0 : highlight + 1;
        } else if (input == 13) { // Enter
            break;
        }
    }

    limpiarTerminal();
    return highlight + 1; // se usa mas 1
}

void buscarPelicula(ABS& arbol, Cliente* cliente) {
    string terminoBusqueda;



    int tipoBusqueda = seleccionarTipoBusqueda();

    cout << "Ingresa el termino a buscar: ";
    getline(cin, terminoBusqueda);

    cout << "--------------------------" << endl;

    switch (tipoBusqueda) {
        case 1:
            arbol.buscar_e_Imprimir(terminoBusqueda, "Titulo", cliente);
            break;
        case 2:
            arbol.buscar_e_Imprimir(terminoBusqueda, "Sinopsis", cliente);
            break;
        case 3:
            arbol.buscar_e_Imprimir(terminoBusqueda, "Tag", cliente);
            break;
        case 4:
            arbol.buscar_e_Imprimir(terminoBusqueda, "Id", cliente);
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
    }

    cout << "Presione enter para seguir";
    cin.get();
}

void darLikePelicula(Cliente* cliente) {
    string nombrePelicula;
    cout << "Ingresa el id de la pelicula a la que quieres dar like: ";
    getline(cin, nombrePelicula);

    auto it = ABS::getInstance().buscarPorId(nombrePelicula);
    if(it.imdb_id.empty()){
        cout << "No se encontro la pelicula con el id: " << nombrePelicula << endl << endl;
        cout << "Presione enter para seguir";
        cin.get();
        return;
    } else {
        cliente->agregarLike(it);
        cout << "Like agregado a la pelicula: " << it.titulo << endl;
    }
    cout << "Presione enter para seguir";
    cin.get();

}

int main() {
    // Ruta del archivo CSV
    string nombreArchivo = "C:/Users/Angel/Desktop/ChavezNet/data/RawData_fixed.csv";


    // Arbolito (singleton)
    ABS& arbol = ABS::getInstance();
    leerCSVenArbol(nombreArchivo);

    // Cliente (Factory)
    string nombreCliente;
    cout << "Ingresa tu nombre: ";
    getline(cin, nombreCliente);

    ConcreteClienteFactory clienteFactory;

    Cliente* cliente = clienteFactory.crearCliente("usuario");
    int opcion;

    while (true) {//while principal
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                buscarPelicula(arbol, cliente);
                break;
            case 2:
                cliente->imprimirLikes();
                break;
            case 3:
                cliente->generarRecomendaciones(arbol);
                cliente->imprimirRecomenaciones();
                break;
            case 4:
                cliente->imprimirPorVer();
                break;
            case 5:
                darLikePelicula(cliente);
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }

    return 0;
}
