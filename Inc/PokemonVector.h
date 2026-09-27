#pragma once

#include <vector>

#include "Pokemon.h"


class PokemonVector {
private:
    std::vector<Pokemon> listePokemons;

protected:
    std::vector<Pokemon>& getListePokemons();
    const std::vector<Pokemon>& getListePokemons() const;

public:
    const std::vector<Pokemon>& getPokemons() const { return getListePokemons(); }
    PokemonVector() = default;
    virtual ~PokemonVector() = default;

    virtual void ajouterPokemon(const Pokemon& p) = 0;
    virtual Pokemon* getPokemonByNumero(int numero) = 0;
    virtual Pokemon* getPokemonByNom(const std::string& nom) = 0;
    bool retirerPokemon(int numero);
    void afficherListePokemon() const;
    size_t getNombrePokemons() const;
};

