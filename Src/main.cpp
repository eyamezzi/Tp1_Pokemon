#include <SFML/Graphics.hpp>

#include "../Inc/Pokedex.h"
#include <iostream>

using namespace std;

int main() {
    Pokedex* dex = Pokedex::getInstance("pokedex.csv");

    // Test : afficher le nombre de Pokémon lus
    cout << "Nombre de Pokemon lus : " << dex->listePockemons.size() << endl;

    // Test : afficher le premier Pokémon
    Pokemon* p = dex->getPokemonByNumero(1);
    if (p != nullptr) {
        cout << "Premier Pokemon : " << p->getNom() << endl;
    } else {
        cout << "Aucun Pokemon trouvé" << endl;
    }
dex->afficherListePockemon();
    return 0;
}
