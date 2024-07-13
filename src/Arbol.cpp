#include "../include/Cliente.h"
#include "../include/Arbol.h"

using namespace std;


void ABS::insertar(Pelicula dato) {
    raiz = insertarAux(raiz, dato);
}

Nodo *ABS::insertarAux(Nodo *nodo, Pelicula dato) {
    if (nodo == nullptr) {
        return new Nodo(dato);
    }
    if (dato.titulo < nodo->dato.titulo) {
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

void ABS::buscarenTituloAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    // Convertir el cada palabra de la búsqueda a una forma con cada palabra que empieza con mayúscula
    stringstream ss(termino);
    string palabra, terminoTransformado;
    while (ss >> palabra) {
        if (!stopwords.count(palabra)) {
            // Capitalizar la primera letra de la palabra
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

void ABS::buscarenSinopsisAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    string primeraPalabraValida;
    stringstream ss(termino);
    string palabra;

    // Busca priorizando la primera palabra que no sea una stopword
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

void ABS::buscarenTagsAux(Nodo* nodo, const string& termino, priority_queue<PeliculaConCoincidencias>& pq, unordered_set<string>& stopwords) {
    if (!nodo) return;

    // Convertir el término de búsqueda a minúsculas
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

void ABS::buscar_e_Imprimir(const string& termino, const string &tipoBusqueda) {
    priority_queue<PeliculaConCoincidencias> resultados;

    if (tipoBusqueda == "Titulo") {
        resultados = buscarenTitulo(termino);
    } else if (tipoBusqueda == "Sinopsis") {
        resultados = buscarenSinopsis(termino);
    }
    else if (tipoBusqueda == "Tag") {
        resultados = buscarenTags(termino);
    }

    if (resultados.empty()) {
        cout << "No se encontraron coincidencias para '" << termino << "' en " << tipoBusqueda << "." << endl;
        return;
    }

    cout << "Peliculas encontradas para '" << termino << "' en " << tipoBusqueda << ":" << endl;
    while (!resultados.empty()) {
        auto top = resultados.top();
        resultados.pop();
        imprimirPelicula(top.pelicula);
    }
}

double cosineSimilarity(const unordered_set<string>& tags1, const vector<string>& tags2) {
    unordered_map<string, int> freq1, freq2;
    for (const auto& tag : tags1) freq1[tag]++;
    for (const auto& tag : tags2) freq2[tag]++;

    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (const auto& pair : freq1) {
        dotProduct += pair.second * freq2[pair.first];
        norm1 += pair.second * pair.second;
    }
    for (const auto& pair : freq2) {
        norm2 += pair.second * pair.second;
    }
    cout << "Vector 1:" << endl;
    for (const auto& pair : tags1) {
        cout << pair << " ";
    }
    cout << endl;
    cout << "Vector 2:" << endl;
    for (const auto& pair : tags2) {
        cout << pair << " ";
    }
    cout << endl;

    cout << "Tags 1:" << endl;
    for (const auto& pair : freq1) {
        cout << pair.first << " " << pair.second << endl;
    }
    cout << "Tags 2:" << endl;
    for (const auto& pair : freq2) {
        cout << pair.first << " " << pair.second << endl;
    }
    cout << "Dot product: " << dotProduct << endl;

    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

void ABS::recorrerYRecomendar(Cliente &cliente) {
    recorrerYRecomendarAux(raiz, cliente);
}

void ABS::recorrerYRecomendarAux(Nodo *nodo, Cliente &cliente) {
    if (nodo == nullptr) return;

    recorrerYRecomendarAux(nodo->izquierdo, cliente);

    // Calcular la similitud y agregar la recomendación
    double similitud = 0.0;
    similitud += cosineSimilarity(cliente.tags_gustados, nodo->dato.tags);
    similitud /= cliente.likes.size();
    cliente.agregarRecomendacion(nodo->dato, similitud);

    recorrerYRecomendarAux(nodo->derecho, cliente);
}

void ABS::imprimir() {
    imprimirAux(raiz);
}

void ABS::imprimirAux(Nodo *nodo) {
    if (nodo == nullptr) return;

    imprimirAux(nodo->izquierdo);
    imprimirPelicula(nodo->dato);
    imprimirAux(nodo->derecho);
}
