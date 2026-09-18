//
// Created by mezzi on 14/09/2026.
//
#include "../Inc/PokemonVector.h"

#include <iostream>

std::vector<Pokemon>& PokemonVector::getListePokemons() {
    return listePokemons;
}

const std::vector<Pokemon>& PokemonVector::getListePokemons() const {
    return listePokemons;
}

void PokemonVector::afficherListePokemon() const {
    std::cout << "===== Liste des Pokemon =====" << std::endl;

    for (const Pokemon& p : listePokemons) {
        p.displayInfo();
        std::cout << "-----------------------------" << std::endl;
    }
}
size_t PokemonVector::getNombrePokemons() const {
    return listePokemons.size();
}