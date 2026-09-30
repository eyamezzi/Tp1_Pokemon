#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class GameOverState : public GameState {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text instructionText;

public:
    explicit GameOverState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};