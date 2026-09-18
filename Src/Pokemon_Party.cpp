//
// Created by mezzi on 14/09/2026.
//

#include "../Inc/Pokemon_Party.h"

#include <iostream>

void PokemonParty::ajouterPokemon(const Pokemon& p) {
     getListePokemons().push_back(p);
}

Pokemon* PokemonParty::getPokemonByNumero(int numero) {
    for (auto& p :  getListePokemons()) {
        if (p.getNumero() == numero) {
            return new Pokemon(p);
        }
    }
    return nullptr;
}

Pokemon* PokemonParty::getPokemonByNom(const std::string& nom) {
    for (auto& p :  getListePokemons()) {
        if (p.getNom() == nom) {
            return new Pokemon(p);
        }
    }
    return nullptr;
}

bool PokemonParty::retirerPokemon(int numero) {
    for (auto it = getListePokemons().begin(); it != getListePokemons().end(); ++it) {
        if (it->getNumero() == numero) {
            getListePokemons().erase(it);
            return true;
        }
    }
    return false;
}
