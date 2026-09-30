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

bool PokemonVector::retirerPokemon(int numero) {
    auto& liste = getListePokemons();
    for (auto it = liste.begin(); it != liste.end(); ++it) {
        if (it->getNumero() == numero) {
            liste.erase(it);
            return true;
        }
    }
    return false;
}

Pokemon* PokemonVector::getPokemonAt(size_t index) {
    auto& liste = getListePokemons();
    if (index >= liste.size()) return nullptr;
    return &liste[index];
}

const Pokemon* PokemonVector::getPokemonAt(size_t index) const {
    const auto& liste = getListePokemons();
    if (index >= liste.size()) return nullptr;
    return &liste[index];
}

void PokemonVector::viderListe() {
    getListePokemons().clear();
}