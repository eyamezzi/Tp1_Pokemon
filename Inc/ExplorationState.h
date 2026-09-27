
#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

class ExplorationState : public GameState {
private:
    sf::Font font;
    sf::Text infoText;
    float timerAvantRencontre;

public:
    explicit ExplorationState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
