#include "../include/Cliente.h"
#include "../include/Arbol.h"

using namespace std;


void ABS::insertar(Pelicula dato) {
    raiz = insertarAux(raiz, dato);
}

Nodo<Pelicula> *ABS::insertarAux(Nodo<Pelicula> *nodo, Pelicula dato) {
    if (nodo == nullptr) {
        return new Nodo<Pelicula>(dato);
    }
    if (dato.imdb_id == nodo->dato.imdb_id) {
        cout << "ID repetido: " << dato.imdb_id << endl;
        return nodo;
    }
    if (dato.imdb_id < nodo->dato.imdb_id) {
        nodo->izquierdo = insertarAux(nodo->izquierdo, dato);
    } else {
        nodo->derecho = insertarAux(nodo->derecho, dato);
    }
    return nodo;
}
priority_queue<PeliculaConCoincidencias> ABS::buscarenTitulo(const string& termino) {
    priority_queue<PeliculaConCoincidencias> pq;
    if (raiz) {
        buscarenTituloAux(raiz, termino, pq, stopwords);
    }
    return pq;
}

void ABS::buscarenTituloAux(Nodo<Pelicula>* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    stringstream ss(termino);
    string palabra, terminoTransformado;
    while (ss >> palabra) {
        if (!stopwords.count(palabra)) {
            palabra[0] = toupper(palabra[0]);
            for (size_t i = 1; i < palabra.size(); i++) {
                palabra[i] = tolower(palabra[i]);
            }
            terminoTransformado += palabra + " ";
        }
    }
    terminoTransformado = terminoTransformado.substr(0, terminoTransformado.size() - 1);

    if (!terminoTransformado.empty()) {
        if (nodo->dato.titulo.find(terminoTransformado) != string::npos) {
            PeliculaConCoincidencias item = {nodo->dato, 1}; // Solo contamos la primera aparición
            pq.push(item);
            if (pq.size() > 3) pq.pop(); // Mantener el tamaño máximo de 3, si no encuentra exactamente el título
        }
    }

    buscarenTituloAux(nodo->izquierdo, termino, pq, stopwords);
    buscarenTituloAux(nodo->derecho, termino, pq, stopwords);
}

priority_queue<PeliculaConCoincidencias> ABS::buscarenSinopsis(const string& termino) {
    priority_queue<PeliculaConCoincidencias> pq;
    if (raiz) {
        buscarenSinopsisAux(raiz, termino, pq, stopwords);
    }
    return pq;
}

void ABS::buscarenSinopsisAux(Nodo<Pelicula>* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    string primeraPalabraValida;
    stringstream ss(termino);
    string palabra;

    while (ss >> palabra && primeraPalabraValida.empty()) {
        if (!stopwords.count(palabra)) {
            primeraPalabraValida = palabra;
        }
    }

    if (!primeraPalabraValida.empty()) {
        size_t pos = nodo->dato.sinopsis.find(primeraPalabraValida);
        if (pos != string::npos) {
            PeliculaConCoincidencias item = {nodo->dato, 1};
            pq.push(item);
            if (pq.size() > 10) pq.pop(); // Mantener el tamaño máximo de 10
        }
    }

    buscarenSinopsisAux(nodo->izquierdo, termino, pq, stopwords);
    buscarenSinopsisAux(nodo->derecho, termino, pq, stopwords);
}

priority_queue<PeliculaConCoincidencias> ABS::buscarenTags(const string& termino) {
    priority_queue<PeliculaConCoincidencias> pq;
    if (raiz) {
        buscarenTagsAux(raiz, termino, pq, stopwords);
    }
    return pq;
}

void ABS::buscarenTagsAux(Nodo<Pelicula>* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    stringstream ss(termino);
    string palabra, terminoTransformado;
    while (ss >> palabra) {
        if (!stopwords.count(palabra)) {
            transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
            terminoTransformado += palabra + " ";
        }
    }
    terminoTransformado = terminoTransformado.substr(0, terminoTransformado.size() - 1); // Eliminar el último espacio

    if (!terminoTransformado.empty()) {
        int coincidencias = 0;
        for (const auto& tag : nodo->dato.tags) {
            if (tag.find(terminoTransformado) != string::npos) {
                coincidencias++;
            }
        }
        if (coincidencias > 0) {
            PeliculaConCoincidencias item = {nodo->dato, coincidencias};
            pq.push(item);
            if (pq.size() > 20) pq.pop(); // Mantener el tamaño máximo de 20
        }
    }

    buscarenTagsAux(nodo->izquierdo, termino, pq, stopwords);
    buscarenTagsAux(nodo->derecho, termino, pq, stopwords);
}

void ABS::buscar_e_Imprimir(const string& termino, const string &tipoBusqueda, Cliente* cliente) {
    priority_queue<PeliculaConCoincidencias> resultados;

    if (tipoBusqueda == "Titulo") {
        resultados = buscarenTitulo(termino);
    }
    else if (tipoBusqueda == "Sinopsis") {
        resultados = buscarenSinopsis(termino);
    }
    else if (tipoBusqueda == "Tag") {
        resultados = buscarenTags(termino);
    }
    else if (tipoBusqueda == "Id") {
        Pelicula resultado = buscarPorId(termino);
        if (resultado.imdb_id.empty()) {
            cout << "No se encontraron coincidencias para '" << termino << "' en " << tipoBusqueda << "." << endl;
            return;
        }
        cout << "Pelicula encontrada para '" << termino << "' en " << tipoBusqueda << ":" << endl;
        resultado.imprimir(cliente);
        return;
    }

    if (resultados.empty()) {
        cout << "No se encontraron coincidencias para '" << termino << "' en " << tipoBusqueda << "." << endl;
        return;
    }

    vector<PeliculaConCoincidencias> temp;
    while (!resultados.empty()) {
        temp.push_back(resultados.top());
        resultados.pop();
    }

    int highlight = 0;
    char input;

    while (true) {
        system("cls");
        cout << "\033[2J\033[1;1H"; // Limpiar pantalla

        cout << endl << endl << "Peliculas encontradas para '" << termino << "' en " << tipoBusqueda << ":" << endl;
        for (size_t i = 0; i < temp.size(); ++i) {
            if (i == highlight) {
                cout << "\033[1;31m"; // rojito
                cout << " -> ";
            } else {
                cout << "    ";
            }
            cout << "ID: " << temp[i].pelicula.imdb_id << " - " << temp[i].pelicula.titulo << endl<< "\033[0m";
        }

        input = _getch();

        if (input == 72) { // Flecha arriba
            highlight = (highlight == 0) ? temp.size() - 1 : highlight - 1;
        } else if (input == 80) { // Flecha abajo
            highlight = (highlight == temp.size() - 1) ? 0 : highlight + 1;
        } else if (input == 13) { // Enter
            system("cls");
            cout << "\033[2J\033[1;1H";
            temp[highlight].pelicula.imprimir(cliente);
            break;
        }
    }
}
double cosineSimilarity(const unordered_map<string, int>& freq1, const vector<string>& tags2) {
    unordered_map<string, int> freq2;
    for (const auto& tag : tags2) freq2[tag]++;
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (const auto& pair : freq1) {
        dotProduct += pair.second * freq2[pair.first];
        norm1 += pair.second * pair.second;
    }
    for (const auto& pair : freq2) {
        norm2 += pair.second * pair.second;
    }
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

void ABS::recorrerYRecomendar(Cliente &cliente) {
    recorrerYRecomendarAux(raiz, cliente);
}

void ABS::recorrerYRecomendarAux(Nodo<Pelicula> *nodo, Cliente &cliente) {
    if (nodo == nullptr) return;

    recorrerYRecomendarAux(nodo->izquierdo, cliente);

    double similitud = 0.0;
    similitud += cosineSimilarity(cliente.tags_gustados, nodo->dato.tags);
    similitud /= cliente.likes.size();
    if (similitud > 0.0) cliente.agregarRecomendacion(nodo->dato, similitud);

    recorrerYRecomendarAux(nodo->derecho, cliente);
}


int ABS::contarNodos() {
    return contarNodosAux(raiz);
}

int ABS::contarNodosAux(Nodo<Pelicula>* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contarNodosAux(nodo->izquierdo) + contarNodosAux(nodo->derecho);
}

Pelicula ABS::buscarPorId(const string &id) {
    return buscarPorIdAux(raiz, id);
}

Pelicula ABS::buscarPorIdAux(Nodo<Pelicula> *nodo, const string &id) {
    if (nodo == nullptr) {
        return {};
    }
    if (nodo->dato.imdb_id == id) {
        return nodo->dato;
    }
    if (nodo->dato.imdb_id < id) {
        return buscarPorIdAux(nodo->derecho, id);
    } else {
        return buscarPorIdAux(nodo->izquierdo, id);
    }
}
