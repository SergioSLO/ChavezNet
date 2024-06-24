#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Estructura para almacenar la información de una película
struct Pelicula {
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> tags;
};

// Función para leer la sinopsis hasta encontrar un punto y coma
string leerSinopsis(ifstream& archivo) {
    string sinopsis;
    string linea;
    bool enComillas = false;

    while (getline(archivo, linea)) {
        for (char ch : linea) {
            if (ch == '"' && (sinopsis.empty() || enComillas)) {
                enComillas = !enComillas;
            } else if (ch == ';' && !enComillas) {
                return sinopsis;
            } else {
                sinopsis += ch;
            }
        }
        sinopsis += '\n'; // Mantener el salto de línea en la sinopsis
    }

    return sinopsis;
}

// Función para leer una línea completa del archivo
bool leerLinea(ifstream& archivo, string& linea) {
    bool enComillas = false;
    linea.clear();
    char ch;
    while (archivo.get(ch)) {
        if (ch == '"' && (linea.empty() || enComillas)) {
            enComillas = !enComillas;
        }
        linea += ch;
        if (ch == '\n' && !enComillas) {
            break;
        }
    }
    return !linea.empty();
}

// Función para leer el CSV y cargarlo en un unordered_map
unordered_map<string, Pelicula> leerCSV(const string& nombreArchivo) {
    unordered_map<string, Pelicula> peliculas;
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return peliculas;
    }

    // Leer y ignorar la cabecera
    getline(archivo, linea);

    // Leer línea por línea el archivo CSV
    while (getline(archivo, linea)) {
        istringstream stream(linea);
        Pelicula pelicula;

        // Leer imdb_id
        getline(stream, pelicula.imdb_id, ';');

        // Leer el título
        getline(stream, pelicula.titulo, ';');

        // Leer la sinopsis
        getline(stream, pelicula.sinopsis, ';');

        // Leer los tags y separarlos
        string tags;
        getline(stream, tags, ';');
        istringstream tagsStream(tags);
        string tag;
        while (getline(tagsStream, tag, ',')) {
            if (tag!= "train" && tag!= "wikipedia") {
                pelicula.tags.push_back(tag);
            }
        }

        // Almacenar la película en el unordered_map
        peliculas[pelicula.titulo] = pelicula;
    }

    archivo.close();
    return peliculas;
}

// Función para imprimir una película
void imprimirPelicula(const Pelicula& pelicula) {
    cout << "IMDB ID: " << pelicula.imdb_id << endl;
    cout << "Título: " << pelicula.titulo << endl;
    cout << "Sinopsis: " << pelicula.sinopsis << endl;
    cout << "Tags: ";
    for (const auto& tag : pelicula.tags) {
        cout << tag << " ";
    }
    cout << endl;
}

int main() {
    string nombreArchivo = "C:/Users/tokio/OneDrive/Escritorio/ChavezNet/data/RawData_fixed.csv";

    auto peliculas = leerCSV(nombreArchivo);

    // Buscar la información de "A Hard Day's Night" - Ejemplo correcto: "Henry: Portrait of a Serial Killer"
    string tituloBusqueda = "In Time";

    // Usar la sintaxis y funciones de unordered_map para buscar y mostrar la película
    auto it = peliculas.find(tituloBusqueda);
    if (it != peliculas.end()) {
        imprimirPelicula(it->second);
    } else {
        cout << "Película no encontrada: " << tituloBusqueda << endl;
    }

    return 0;
}
