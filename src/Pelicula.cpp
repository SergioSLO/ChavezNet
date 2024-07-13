#include "../include/Pelicula.h"


unordered_map<string, Pelicula> leerCSV(const string& nombreArchivo) {
    unordered_map<string, Pelicula> peliculas;
    ifstream archivo(nombreArchivo);
    string linea;
    mutex mtx;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return peliculas;
    }

    // Leer y ignorar la cabecera
    getline(archivo, linea);

    // Leer todas las líneas del archivo
    vector<string> lineas;
    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }

    archivo.close();

    // Dividir las líneas en partes para los hilos
    const int numHilos = thread::hardware_concurrency();
    vector<vector<string>> partes(numHilos);
    for (size_t i = 0; i < lineas.size(); ++i) {
        partes[i % numHilos].push_back(lineas[i]);
    }

    // Crear y lanzar los hilos
    vector<thread> hilos;
    for (int i = 0; i < numHilos; ++i) {
        hilos.emplace_back([&peliculas, &partes, &mtx, i]() {
            for (const string& linea : partes[i]) {
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
                    if (tag != "train" && tag != "wikipedia") {
                        pelicula.tags.push_back(tag);
                    }
                }

                // Almacenar la película en el unordered_map
                lock_guard<mutex> guard(mtx);
                peliculas[pelicula.titulo] = pelicula;
            }
        });
    }

    // Esperar a que todos los hilos terminen
    for (thread& hilo : hilos) {
        hilo.join();
    }

    return peliculas;
}

void imprimirPelicula(const Pelicula& pelicula) {

    cout << "-----------------------------------"<<  endl;
    cout << "IMDB ID: " << pelicula.imdb_id << endl;
    cout << "Titulo: " << pelicula.titulo << endl;
    //cout << "Sinopsis: " << pelicula.sinopsis << endl;
    cout << "Tags: ";
    for (const auto& tag : pelicula.tags) {
        cout << tag << " ";
    }
    cout << endl;
    cout << "-----------------------------------"<<  endl;
    cout <<  endl;
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

