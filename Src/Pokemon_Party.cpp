//
// Created by mezzi on 14/09/2026.
//

#include "../Inc/Pokemon_Party.h"

#include <iostream>

void PokemonParty::ajouterPokemon(const Pokemon& p) {
    liste.push_back(p);
}

Pokemon* PokemonParty::getPokemonByNumero(int numero) {
    for (auto& p : liste) {
        if (p.getNumero() == numero) {
            return new Pokemon(p);
        }
    }
    return nullptr;
}

Pokemon* PokemonParty::getPokemonByNom(const std::string& nom) {
    for (auto& p : liste) {
        if (p.getNom() == nom) {
            return new Pokemon(p);
        }
    }
    return nullptr;
}

bool PokemonParty::retirerPokemon(int numero) {
    for (auto it = listePockemons.begin(); it != listePockemons.end(); ++it) {
        if (it->getNumero() == numero) {
            liste.erase(it);
            return true;
        }
    }
    return false;
}
