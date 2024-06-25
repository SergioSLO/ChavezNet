#include "../include/Pelicula.h"

Pelicula::Pelicula() {

}

Pelicula::Pelicula(const string &imdb_id, const string &titulo, const string &sinopsis, const vector<string> &tags)
    : imdb_id(imdb_id), titulo(titulo), sinopsis(sinopsis), tags(tags) {}

void Pelicula::imprimirPelicula() {
    cout << "IMDB ID: " << imdb_id << endl;
    cout << "Titulo: " << titulo << endl;
    cout << "Sinopsis: " << sinopsis << endl;
    cout << "Tags: ";
    for (const auto& tag : tags) {
        cout << tag << " ";
    }
    cout << endl;
}
