#include <utility>

#include "../include/Cliente.h"
#include "../include/Arbol.h"

// sobrecarga para poder comparar pair<double, Pelicula> en la priority_queue
bool operator>(const pair<double, Pelicula>& a, const pair<double, Pelicula>& b) {
    return a.first > b.first;
}

Cliente::Cliente(string nombre) {
    this->nombre = std::move(nombre);
}

void Cliente::agregarLike(const Pelicula& pelicula) {
    likes.push_back(pelicula);
    for (const auto& tag : pelicula.tags) {
        tags_gustados.insert(tag);
    }
}

void Cliente::agregarPorVer(const Pelicula& pelicula) {
    peliculasPorVer.push_back(pelicula);
}

void Cliente::imprimirLikes() {
    cout << "Likes de " << nombre << ":" << endl;
    for (const auto& pelicula : likes) {
        cout << pelicula.titulo << endl;
    }
}

void Cliente::imprimirPorVer() {
    cout << "Por ver de " << nombre << ":" << endl;
    for (const auto& pelicula : peliculasPorVer) {
        cout << pelicula.titulo << endl;
    }
}

void Cliente::generarRecomendaciones(ABS &arbol){
    arbol.recorrerYRecomendar(*this);
}

void Cliente::agregarRecomendacion(const Pelicula &pelicula, double intensidad) {
    cout << "Se agrego la pelicula " << pelicula.titulo << " con intensidad " << intensidad << endl;
    if (recomendaciones.size() < 20) {
        recomendaciones.emplace(intensidad, pelicula);
    } else if (intensidad > recomendaciones.top().first) {
        recomendaciones.pop();
        recomendaciones.emplace(intensidad, pelicula);
    }
}

void Cliente::imprimirRecomenaciones() {
    cout << "tags" << endl;
    for ( auto tag : tags_gustados){
        cout << tag << endl;
    }
    cout << "-----------" << endl;
    cout << "Recomendaciones para " << nombre << ":" << endl;
    auto reco = recomendaciones; // Make a copy of the queue
    while (!reco.empty()) {
        cout << reco.top().second.titulo << " con intensidad " << reco.top().first << endl;
        reco.pop();
    }
}
