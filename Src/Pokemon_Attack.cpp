//
// Created by mezzi on 14/09/2026.
//

#include "../Inc/Pokemon_Attack.h"

#include <iostream>

void PokemonAttack::ajouterPokemon(const Pokemon& p) {

    if (estPleine()) {
        std::cout << "PokemonAttack est deja pleine !" << std::endl;
        return;
    }

    getListePokemons().push_back(p);
}

Pokemon* PokemonAttack::getPokemonByNumero(int numero) {

    for (auto& p : getListePokemons()) {

        if (p.getNumero() == numero) {
            return new Pokemon(p);
        }
    }

    return nullptr;
}


Pokemon* PokemonAttack::getPokemonByNom(const std::string& nom) {

    for (auto& p : getListePokemons()) {

        if (p.getNom() == nom) {
            return new Pokemon(p);
        }
    }

    return nullptr;
}


bool PokemonAttack::estPleine() const {
    return getListePokemons().size() >= MAX_POKEMONS;
}


void PokemonAttack::creerDepuisParty(PokemonParty& party) {
    getListePokemons().clear();
    auto pokemonsCopy = party.getPokemons(); // copie des numéros à traiter
    for (const auto& pokemon : pokemonsCopy) {
        if (estPleine()) break;
        ajouterPokemon(pokemon);
        party.retirerPokemon(pokemon.getNumero());
    }
}

void PokemonAttack::reintegrerDansParty(PokemonParty& party) {

    for (const auto& pokemon : getListePokemons()) {
        party.ajouterPokemon(pokemon);
    }

    getListePokemons().clear();
}