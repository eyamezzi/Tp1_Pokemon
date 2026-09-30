//
// Created by mezzi on 14/09/2026.
//

#pragma once
#include "Pokemon_Party.h"

class PokemonAttack : public PokemonVector {
public:
    PokemonAttack() = default;
    ~PokemonAttack() override = default;

    // Ajouter un Pokemon à l'équipe d'attaque
    void ajouterPokemon(const Pokemon& p) override;

    // Rechercher un Pokemon
    Pokemon* getPokemonByNumero(int numero) override;
    Pokemon* getPokemonByNom(const std::string& nom) override;

    // Créer l'équipe d'attaque à partir de la Party
    void creerDepuisParty(PokemonParty& party);

    // Réintégrer les Pokemon dans la Party
    void reintegrerDansParty(PokemonParty& party);

    // Vérifier si l'équipe est pleine
    bool estPleine() const;

    static constexpr size_t MAX_POKEMONS = 6;
};

