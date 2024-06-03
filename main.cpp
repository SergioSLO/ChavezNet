#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Estructura para almacenar la información de una película
struct Pelicula {
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> tags;
};

// Función para leer una celda con posibles comas y comillas
string leerCeldaConComas(istringstream& stream) {
    string celda;
    char ch;
    bool enComillas = false;

    while (stream.get(ch)) {
        if (ch == '"' && (celda.empty() || enComillas)) {
            enComillas = !enComillas;
        } else if (ch == ',' && !enComillas) {
            break;
        } else {
            celda += ch;
        }
    }

    // Eliminar comillas dobles escapadas
    string result;
    for (size_t i = 0; i < celda.length(); ++i) {
        if (celda[i] == '"' && i + 1 < celda.length() && celda[i + 1] == '"') {
            result += '"';
            ++i;
        } else {
            result += celda[i];
        }
    }

    return result;
}

// Función para leer la sinopsis manejando puntos y saltos de línea correctamente
string leerSinopsis(istringstream& stream) {
    string sinopsis;
    char ch;
    bool enComillas = false;

    while (stream.get(ch)) {
        sinopsis += ch;
        if (ch == '"' && (sinopsis.empty() || enComillas)) {
            enComillas = !enComillas;
        } else if (ch == '.' && !enComillas) {
            // Verificar los siguientes caracteres
            char nextChars[3] = {0};
            for (int i = 0; i < 3 && stream.peek() != EOF; ++i) {
                nextChars[i] = stream.get();
                sinopsis += nextChars[i];
            }
            if (isalpha(stream.peek())) {
                continue;
            } else if ((nextChars[0] == ' ' || nextChars[0] == '\n') &&
                       (nextChars[1] == ' ' || nextChars[1] == '\n') &&
                       (nextChars[2] == ' ' || nextChars[2] == '\n' || isalpha(nextChars[2]))) {
                for (int i = 2; i >= 0; --i) {
                    if (nextChars[i] != 0) {
                        stream.unget();
                        sinopsis.pop_back();
                    }
                }
                break;
            }
        }
    }

    // Eliminar comillas dobles escapadas
    string result;
    for (size_t i = 0; i < sinopsis.length(); ++i) {
        if (sinopsis[i] == '"' && i + 1 < sinopsis.length() && sinopsis[i + 1] == '"') {
            result += '"';
            ++i;
        } else {
            result += sinopsis[i];
        }
    }

    return result;
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
        pelicula.imdb_id = leerCeldaConComas(stream);

        // Leer el título
        pelicula.titulo = leerCeldaConComas(stream);

        // Leer la sinopsis
        pelicula.sinopsis = leerSinopsis(stream);

        // Leer los tags y separarlos
        string tags;
        tags = leerCeldaConComas(stream);
        istringstream tagsStream(tags);
        string tag;
        while (getline(tagsStream, tag, '|')) {
            pelicula.tags.push_back(tag);
        }

        // Ignorar las columnas restantes
        leerCeldaConComas(stream); // split
        leerCeldaConComas(stream); // synopsis_source

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
    string nombreArchivo = "C:/Users/tokio/OneDrive/Escritorio/ChavezNet/data/RawData.csv";
    auto peliculas = leerCSV(nombreArchivo);

    // Buscar la información de "A Hard Day's Night"
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
