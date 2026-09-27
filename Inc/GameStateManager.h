//
// GameStateManager.h
// C'est le "contexte" du design pattern STATE : il détient l'état courant
// et fournit un accès centralisé aux données partagées du jeu
// (Pokedex, PokemonParty, PokemonAttack).
//

#pragma once

#include <memory>
#include <vector>
#include "GameState.h"
#include "Pokedex.h"
#include "Pokemon_Party.h"
#include "Pokemon_Attack.h"

class GameStateManager {
private:
    std::unique_ptr<GameState> currentState;

    // Données de jeu partagées entre les états
    Pokedex* pokedex;              // Singleton, pas de propriété ici
    PokemonParty party;
    PokemonAttack attackTeam;

    // Etat "vivant" de l'équipe pendant l'aventure : contrairement à
    // attackTeam (la sélection faite par le joueur), ces clones gardent
    // leurs PV endommagés d'un combat à l'autre, jusqu'à ce qu'ils soient K.O.
    std::vector<std::unique_ptr<Pokemon>> equipeVivante;
    size_t indexCombattantActuel;

public:
    explicit GameStateManager(Pokedex* pokedex);

    // Changement d'état : détruit l'ancien, construit le nouveau
    void changeState(std::unique_ptr<GameState> newState);

    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    // Accès aux données de jeu depuis n'importe quel état
    Pokedex& getPokedex();
    PokemonParty& getParty();
    PokemonAttack& getAttackTeam();

    // Gestion du combattant actif, avec PV persistants entre les combats.
    // Initialise equipeVivante au premier appel (à partir de attackTeam).
    Pokemon* getCombattantActuel();

    // true si tous les membres de l'équipe vivante sont K.O.
    bool toutePartieVaincue() const;
};
