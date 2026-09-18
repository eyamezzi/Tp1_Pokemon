
#include <string>

#include "PokemonVector.h"
class Pokedex : public PokemonVector {
private:
    static Pokedex* instance;

    // Constructeur privé
    Pokedex(const std::string& csvFile);

public:
    // Empêcher la copie du Singleton
    Pokedex(const Pokedex&) = delete;
    Pokedex& operator=(const Pokedex&) = delete;

    // Accès au Singleton
    static Pokedex* getInstance(const std::string& csvFile);

    void ajouterPokemon(const Pokemon& p) override;
    Pokemon* getPokemonByNumero(int numero) override;
    Pokemon* getPokemonByNom(const std::string& nom) override;
};
