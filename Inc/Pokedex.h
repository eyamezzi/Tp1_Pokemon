
#include <string>

#include "PockemonVector.h"
using namespace std;
class Pokedex : public PokemonVector {
private:
    static Pokedex* instance;
    // Constructeur privé
    Pokedex(const std::string& csvFile);
public:
    // Accès au singleton
    static Pokedex* getInstance(const string& csvFile);

    // Implémentation des méthodes abstraites
    void ajouterPokemon(const Pokemon& p) override;
    Pokemon* getPokemonByNumero(int numero) override;
    Pokemon* getPokemonByNom(const string& nom) override;
};
