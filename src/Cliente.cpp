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
        tags_gustados[tag]++;
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
    if(intensidad > mejor){
        mejor = intensidad;
    }
    if (recomendaciones.size() < 20) {
        recomendaciones.emplace(intensidad, pelicula);
    } else if (intensidad > recomendaciones.top().first) {
        recomendaciones.pop();
        recomendaciones.emplace(intensidad, pelicula);
    }
}

void Cliente::imprimirRecomenaciones() {
    cout << "tags" << endl;
    for (const auto& tag : tags_gustados){
        cout << tag.first << " " << tag.second << endl;
    }
    cout << "-----------" << endl;
    cout << "Mejor: " << mejor << endl;
    cout << "Recomendaciones para " << nombre << ":" << endl;

    // Transferir elementos a un vector temporal
    vector<pair<double, Pelicula>> temp;
    auto reco = recomendaciones; // Hacer una copia de la cola
    while (!reco.empty()) {
        temp.push_back(reco.top());
        reco.pop();
    }

    // Imprimir elementos en orden inverso
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        cout << it->second.titulo << " con intensidad " << it->first << endl;
    }
}