//
// Created by mezzi on 14/09/2026.
//



#include "PokemonVector.h"
#include <memory>

class PokemonParty : public PokemonVector {
public:
    PokemonParty() = default;
    ~PokemonParty() override = default;

    void ajouterPokemon(const Pokemon& p) override;

    Pokemon* getPokemonByNumero(int numero) override;
    Pokemon* getPokemonByNom(const std::string& nom) override;

    bool retirerPokemon(int numero);
};





