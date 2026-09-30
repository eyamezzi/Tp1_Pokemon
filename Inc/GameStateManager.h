#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameState.h"
#include "Pokedex.h"
#include "Pokemon_Party.h"
#include "Pokemon_Attack.h"

class GameStateManager {
private:
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<GameState> nextState;

    Pokedex* pokedex;
    PokemonParty party;
    PokemonAttack attack;

    size_t combattantIndex = 0;

public:
    explicit GameStateManager(Pokedex* pokedex);

    void changeState(std::unique_ptr<GameState> newState);
    void applyPendingChange();

    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    bool hasState() const;

    Pokedex& getPokedex();
    PokemonParty& getParty();
    PokemonAttack& getAttack();

    // Combat
    Pokemon* getCombattantActuel();
    void combattantSuivant();
    bool toutePartieVaincue();
    void resetCombatIndex();
};