
#include <vector>

#include "Pokemon.h"


class PokemonVector {



public:
    std::vector<Pokemon> listePockemons;
    PokemonVector() = default;
    virtual ~PokemonVector() = default;
    virtual void ajouterPokemon(const Pokemon& p) = 0;
    virtual Pokemon* getPokemonByNumero(int numero) = 0;
    virtual Pokemon* getPokemonByNom(const std::string& nom) = 0;
    void afficherListePockemon() const;
};


