
#include "../include/Pelicula.h"
#include "Arbol.h"


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



void leerCSVenArbol(const string& nombreArchivo) {
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
        return;
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
        hilos.emplace_back([&partes, &mtx, &imdb_regex, &valid_tags, i]() {
            for (const string& linea : partes[i]) {
                istringstream stream(linea);
                Pelicula pelicula;

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
                ABS::getInstance().insertar(pelicula);
            }
        });
    }

    for (thread& hilo : hilos) {
        hilo.join();
    }
}

void Pelicula::imprimir(Cliente* cliente) const {
    system("cls");
    cout << "\033[2J\033[1;1H"; // Limpiar pantalla
    int opcion;
    int highlight = 0;
    const int numOptions = 4;
    char input;

    while (true) {
        cout << "\033[1;32m";
        cout << "IMDB ID: " << imdb_id << endl << endl;
        cout << "\033[1;34m";
        cout << "Titulo: " << titulo << endl << endl;
        cout << "\033[1;33m";
        cout << "Sinopsis: " << sinopsis << endl << endl;
        cout << "\033[1;35m";
        cout << "Tags: ";
        for (const auto& tag : tags) {
            if(tag != tags.back())
                cout << tag << " - ";
            else
                cout << tag << endl;
        }
        cout << endl << endl;

        cout << "\033[1;36m";

        cout << "Seleccione una opcion:" << endl;
        cout << endl;
        cout << "\033[1;36m"; // azul claro para el submenú
        cout << "--------------------------" << endl;
        for (int i = 0; i < numOptions; ++i) {
            if (i == highlight) {
                cout << "\033[1;31m"; // rojo para la opción seleccionada
                cout << " -> ";
            } else {
                cout << "    ";
            }

            switch (i) {
                case 0: cout << "Dar like" << endl; break;
                case 1: cout << "Ver mas tarde" << endl; break;
                case 2: cout << "Ambos" << endl; break;
                case 3: cout << "Ninguno" << endl; break;
            }

            if (i == highlight) {
                cout << "\033[1;36m"; // Resetear color
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
            opcion = highlight;
            break;
        }
    }
    cout << "\033[0m"; // Resetear color

    switch (opcion) {
        case 0:
            cliente->agregarLike(*this);
            cout << "Like agregado a la pelicula" << endl;
            break;
        case 1:
            cliente->agregarPorVer(*this);
            cout << "Pelicula agregada a tu lista de peliculas por ver" << endl;
            break;
        case 2:
            cliente->agregarLike(*this);
            cliente->agregarPorVer(*this);
            cout << "Pelicula agregada a tu lista de peliculas por ver y like agregado" << endl;
            break;
        case 3:
            cout << "No se ha realizado ninguna accion" << endl;
            break;
    }
}