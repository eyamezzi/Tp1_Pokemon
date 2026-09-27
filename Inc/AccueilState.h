//
// Created by eya on 9/27/26.
//


#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>

class AccueilState : public GameState {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text hintText;

public:
    explicit AccueilState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

