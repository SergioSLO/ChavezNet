#include <utility>

#include "../include/Cliente.h"
#include "../include/Arbol.h"
#include <conio.h>
// sobrecarga para poder comparar pair<double, Pelicula> en la priority_queue
bool operator>(const pair<double, Pelicula>& a, const pair<double, Pelicula>& b) {
    return a.first > b.first;
}

Cliente::Cliente(string nombre) {
    this->nombre = std::move(nombre);
}

void Cliente::agregarLike(const Pelicula& pelicula) {
    likes.insert(pelicula);
    for (const auto& tag : pelicula.tags) {
        tags_gustados[tag]++;
    }
}

void Cliente::agregarPorVer(const Pelicula& pelicula) {
    peliculasPorVer.push_back(pelicula);
}

void Cliente::imprimirLikes() {
    if (likes.empty()) {
        cout << "\033[1;33m"; // amariilo
        cout << "No hay likes de " << nombre << endl;
        cout << "presione enter para seguir";
        cout << "\033[0m";
        cin.get();
        return;
    }
    cout << "Likes de " << nombre << ":" << endl;
    cout << "\033[1;32m"; // verde
    for (const auto& pelicula : likes) {
        cout << pelicula.titulo << endl;
    }
    cout << "\033[0m";
    cout << "presione enter para seguir";
    cin.get();

}

void Cliente::imprimirPorVer() {
    if(peliculasPorVer.empty()){
        cout << "\033[1;33m"; // amariilo
        cout << "No hay peliculas por ver de " << nombre << endl;
        cout << "presione enter para seguir";
        cout << "\033[0m";
        cin.get();
        return;
    }
    cout << "Por ver de " << nombre << ":" << endl;
    cout << "\033[1;33m";
    for (const auto& pelicula : peliculasPorVer) {
        cout << pelicula.titulo << endl;
    }
    cout << "\033[0m";
    cout << "presione enter para seguir";
    cin.get();
}

void Cliente::generarRecomendaciones(ABS &arbol){
    if (likes.empty()) {
        return;
    }
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
    cout << "-----------" << endl;
    if (tags_gustados.empty()) {
        cout << "\033[1;33m"; // amariillo
        cout << "No hay tags gustados" << endl;
        cout << "presione enter para seguir";
        cin.get();
        cout << "\033[0m";
        return;
    }
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

    int highlight = 0;
    char input;

    while (true) {
        system("cls");
        cout << "\033[2J\033[1;1H"; // Limpiar pantalla

        cout <<endl << endl << "Recomendaciones para " << nombre << ":" << endl;

        for (size_t i = 0; i < temp.size(); ++i) {
            if (i == highlight) {
                cout << "\033[1;31m"; // rojito
                cout << " -> ";
            } else {
                cout << "    ";
            }
            cout << "ID: " << temp[i].second.imdb_id << " - " << temp[i].second.titulo << endl;
            cout << "\033[0m";
        }

        input = _getch();

        if (input == 72) { // Flecha arriba
            highlight = (highlight == 0) ? temp.size() - 1 : highlight - 1;
        } else if (input == 80) { // Flecha abajo
            highlight = (highlight == temp.size() - 1) ? 0 : highlight + 1;
        } else if (input == 13) { // Enter
            cout << "\033[2J\033[1;1H";
            temp[highlight].second.imprimir(this);
            break;
        }
    }
}