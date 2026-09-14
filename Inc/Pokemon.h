
#include <string>
class Pokemon {
private:
    int numero;
    std::string nom;
    int evolution;
    int pvMax;
    int pvActuel;
    int attaque;
    int defense;

public:
    // Constructeur
    Pokemon(int numero,
            const std::string& nom,
            int pvMax,
            int attaque,
            int defense,
            int evolution = 0);

    // Destructeur
    ~Pokemon();

    // Méthode d'attaque
    void attaquer(Pokemon& cible);

    // Affichage
    void displayInfo() const;




    //Getters
    int getNumero() const;

    const std::string &getNom() const;

    double getEvolution() const;

    double getAttack() const;

    double getDefense() const;

    int getPvMax() const;
    int getPvActual() const;


};

