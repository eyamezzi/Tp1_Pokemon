//
// Created by mezzi on 14/09/2026.
//
#pragma once
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


void PokemonAttack::creerDepuisParty(const PokemonParty& party) {
    getListePokemons().clear();

    for (const auto& pokemon : party.getPokemons()) { 
        if (estPleine()) {
            break;
        }
        getListePokemons().push_back(pokemon);
    }
}

void PokemonAttack::reintegrerDansParty(PokemonParty& party) {

    for (const auto& pokemon : getListePokemons()) {
        party.ajouterPokemon(pokemon);
    }

    getListePokemons().clear();
}