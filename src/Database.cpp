#include <fstream>
#include <sstream>
#include "../include/Database.h"

//Database::Database(const string& nombreArchivo) {
//    ifstream archivo(nombreArchivo);
//    string linea;
//
//    if (!archivo.is_open()) {
//        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
//        data = unordered_map<string, Pelicula>();
//        return;
//    }
//
//    // Leer y ignorar la cabecera
//    getline(archivo, linea);
//
//    // Leer línea por línea el archivo CSV
//    while (getline(archivo, linea)) {
//        istringstream stream(linea);
//        Pelicula pelicula;
//
//        // Leer imdb_id
//        string id = leerCeldaConComas(stream);// TODO: pasar el id a int
//
//        // Leer el título
//        string titulo = leerCeldaConComas(stream);
//
//        // Leer la sinopsis
//        string sinopsis = leerSinopsis(stream);
//
//        // Leer los tags y separarlos
//        string tags;
//        tags = leerCeldaConComas(stream);
//        istringstream tagsStream(tags);
//        string tag;
//        vector<string> tagsVector;
//        while (getline(tagsStream, tag, '|')) {
//            tagsVector.push_back(tag);
//        }
//
//        // Crear la película
//        pelicula = Pelicula(id, titulo, sinopsis, tagsVector);
//
//        // Ignorar las columnas restantes
//        leerCeldaConComas(stream); // split
//        leerCeldaConComas(stream); // synopsis_source
//
//        // Almacenar la película en el unordered_map
//        this->data[id] = pelicula;
//    }
//    archivo.close();
//}
//
//string Database::leerCeldaConComas(istringstream &stream) {
//    string celda;
//    char ch;
//    bool enComillas = false;
//
//    while (stream.get(ch)) {
//        if (ch == '"' && (celda.empty() || enComillas)) {
//            enComillas = !enComillas;
//        } else if (ch == ',' && !enComillas) {
//            break;
//        } else {
//            celda += ch;
//        }
//    }
//
//    // Eliminar comillas dobles escapadas
//    string result;
//    for (size_t i = 0; i < celda.length(); ++i) {
//        if (celda[i] == '"' && i + 1 < celda.length() && celda[i + 1] == '"') {
//            result += '"';
//            ++i;
//        } else {
//            result += celda[i];
//        }
//    }
//
//    return result;
//}
//
//string Database::leerSinopsis(istringstream &stream) {
//    string sinopsis;
//    char ch;
//    bool enComillas = false;
//
//    while (stream.get(ch)) {
//        sinopsis += ch;
//        if (ch == '"' && (sinopsis.empty() || enComillas)) {
//            enComillas = !enComillas;
//        } else if (ch == '.' && !enComillas) {
//            // Verificar los siguientes caracteres
//            char nextChars[3] = {0};
//            for (int i = 0; i < 3 && stream.peek() != EOF; ++i) {
//                nextChars[i] = stream.get();
//                sinopsis += nextChars[i];
//            }
//            if (isalpha(stream.peek())) {
//                continue;
//            } else if ((nextChars[0] == ' ' || nextChars[0] == '\n') &&
//                       (nextChars[1] == ' ' || nextChars[1] == '\n') &&
//                       (nextChars[2] == ' ' || nextChars[2] == '\n' || isalpha(nextChars[2]))) {
//                for (int i = 2; i >= 0; --i) {
//                    if (nextChars[i] != 0) {
//                        stream.unget();
//                        sinopsis.pop_back();
//                    }
//                }
//                break;
//            }
//        }
//    }
//
//    // Eliminar comillas dobles escapadas
//    string result;
//    for (size_t i = 0; i < sinopsis.length(); ++i) {
//        if (sinopsis[i] == '"' && i + 1 < sinopsis.length() && sinopsis[i + 1] == '"') {
//            result += '"';
//            ++i;
//        } else {
//            result += sinopsis[i];
//        }
//    }
//    return result;
//}
//
//unordered_map<string , Pelicula> Database::getData() {
//    return this->data;
//}
