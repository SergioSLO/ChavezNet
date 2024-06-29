#include "../include/Pelicula.h"


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

void imprimirPelicula(const Pelicula& pelicula) {

    cout << "IMDB ID: " << pelicula.imdb_id << endl;
    cout << "Titulo: " << pelicula.titulo << endl;
    cout << "Sinopsis: " << pelicula.sinopsis << endl;
    cout << "Tags: ";
    for (const auto& tag : pelicula.tags) {
        cout << tag << " ";
    }
    cout << endl;
}

vector<string> Stopwords(const string& texto, const unordered_set<string>& stopwords) {
    istringstream stream(texto);
    string palabra;
    vector<string> filteredWords;
    while (stream >> palabra) {
        // Convertir a minúsculas y eliminar puntuaciones
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        palabra.erase(remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());

        if (!stopwords.count(palabra)) {
            filteredWords.push_back(palabra);
        }
    }
    return filteredWords;
}






//string leerSinopsis(ifstream& archivo) {
//    string sinopsis;
//    string linea;
//    bool enComillas = false;
//
//    while (getline(archivo, linea)) {
//        for (char ch : linea) {
//            if (ch == '"' && (sinopsis.empty() || enComillas)) {
//                enComillas = !enComillas;
//            } else if (ch == ';' && !enComillas) {
//                return sinopsis;
//            } else {
//                sinopsis += ch;
//            }
//        }
//        sinopsis += '\n'; // Mantener el salto de línea en la sinopsis
//    }
//
//    return sinopsis;
//}
//
//bool leerLinea(ifstream& archivo, string& linea) {
//    bool enComillas = false;
//    linea.clear();
//    char ch;
//    while (archivo.get(ch)) {
//        if (ch == '"' && (linea.empty() || enComillas)) {
//            enComillas = !enComillas;
//        }
//        linea += ch;
//        if (ch == '\n' && !enComillas) {
//            break;
//        }
//    }
//    return !linea.empty();
//}

