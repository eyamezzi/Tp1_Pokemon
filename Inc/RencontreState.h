#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

class RencontreState : public GameState {
private:
    sf::Font font;
    sf::Text infoText;
    int numeroSauvage;

    sf::Texture texSauvage;
    sf::Sprite spriteSauvage;

public:
    explicit RencontreState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};


