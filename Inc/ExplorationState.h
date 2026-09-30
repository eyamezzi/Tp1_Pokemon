// ExplorationState.h
#pragma once
#include "GameState.h"
#include "Pokemon_Party.h"
#include "Pokemon_Attack.h"
#include <SFML/Graphics.hpp>

class ExplorationState : public GameState {
private:
    PokemonParty& party;
    PokemonAttack& attack;

    sf::RectangleShape player;
    float playerSpeed = 200.f;

    sf::Font font;
    sf::Text hintText;

    float encounterTimer = 0.f;
    float encounterInterval = 3.f; // secondes entre chaque tentative de rencontre aléatoire

public:
    explicit ExplorationState(GameStateManager& manager);
    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};