#include <regex>
#include <set>
#include "../include/Pelicula.h"


unordered_map<string, Pelicula> leerCSV(const string& nombreArchivo) {
    unordered_map<string, Pelicula> peliculas;
    ifstream archivo(nombreArchivo);
    string linea;
    mutex mtx;
    regex imdb_regex("^tt\\d{7,8}$");
    set<string> valid_tags = {
            "absurd", "action", "adult comedy", "allegory", "alternate history",
            "alternate reality", "anti war", "atmospheric", "autobiographical",
            "avant garde", "blaxploitation", "bleak", "boring", "brainwashing",
            "christian film", "claustrophobic", "clever", "comedy", "comic",
            "cruelty", "cult", "cute", "dark", "depressing", "dramatic",
            "entertaining", "fantasy", "feel-good", "flashback", "good versus evil",
            "gothic", "grindhouse film", "haunting", "historical", "historical fiction",
            "home movie", "horror", "humor", "insanity", "inspiring", "intrigue",
            "magical realism", "melodrama", "murder", "mystery", "neo noir",
            "non fiction", "paranormal", "philosophical", "plot twist",
            "pornographic", "prank", "psychedelic", "psychological", "queer",
            "realism", "revenge", "romantic", "sadist", "satire", "sci-fi",
            "sentimental", "storytelling", "stupid", "suicidal", "suspenseful",
            "thought-provoking", "tragedy", "violence", "western", "whimsical"
    };

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
        hilos.emplace_back([&peliculas, &partes, &mtx, &imdb_regex, &valid_tags, i]() {
            for (const string& linea : partes[i]) {
                istringstream stream(linea);
                Pelicula pelicula;

                // Leer imdb_id
                string imdb_id;
                getline(stream, imdb_id, ';');

                if (regex_match(imdb_id, imdb_regex)) {
                    pelicula.imdb_id = imdb_id;}
                else {
                    continue;
                }

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
                    tag.erase(tag.begin(), find_if(tag.begin(), tag.end(), [](unsigned char ch) {
                        return !isspace(ch);
                    }));
                    if (valid_tags.find(tag) != valid_tags.end()) {
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

unordered_map<string, Pelicula> leerCSVconId(const string& nombreArchivo) {
    unordered_map<string , Pelicula> peliculas;
    ifstream archivo(nombreArchivo);
    string linea;
    mutex mtx;
    regex imdb_regex("^tt\\d{7,8}$");
    set<string> valid_tags = {
            "absurd", "action", "adult comedy", "allegory", "alternate history",
            "alternate reality", "anti war", "atmospheric", "autobiographical",
            "avant garde", "blaxploitation", "bleak", "boring", "brainwashing",
            "christian film", "claustrophobic", "clever", "comedy", "comic",
            "cruelty", "cult", "cute", "dark", "depressing", "dramatic",
            "entertaining", "fantasy", "feel-good", "flashback", "good versus evil",
            "gothic", "grindhouse film", "haunting", "historical", "historical fiction",
            "home movie", "horror", "humor", "insanity", "inspiring", "intrigue",
            "magical realism", "melodrama", "murder", "mystery", "neo noir",
            "non fiction", "paranormal", "philosophical", "plot twist",
            "pornographic", "prank", "psychedelic", "psychological", "queer",
            "realism", "revenge", "romantic", "sadist", "satire", "sci-fi",
            "sentimental", "storytelling", "stupid", "suicidal", "suspenseful",
            "thought-provoking", "tragedy", "violence", "western", "whimsical"
    };

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
        hilos.emplace_back([&peliculas, &partes, &mtx, &imdb_regex, &valid_tags, i]() {
            for (const string& linea : partes[i]) {
                istringstream stream(linea);
                Pelicula pelicula;

                // Leer imdb_id
                string imdb_id;
                getline(stream, imdb_id, ';');

                if (regex_match(imdb_id, imdb_regex)) {
                    pelicula.imdb_id = imdb_id;
                }
                else {
                    continue;
                }

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
                    tag.erase(tag.begin(), find_if(tag.begin(), tag.end(), [](unsigned char ch) {
                        return !isspace(ch);
                    }));
                    if (valid_tags.find(tag) != valid_tags.end()) {
                        pelicula.tags.push_back(tag);
                    }
                }

                // Almacenar la película en el unordered_map
                lock_guard<mutex> guard(mtx);
                peliculas[imdb_id] = pelicula;
            }
        });
    }

    // Esperar a que todos los hilos terminen
    for (thread& hilo : hilos) {
        hilo.join();
    }

    return peliculas;
}
