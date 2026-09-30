#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class AccueilState : public GameState {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;

    sf::RectangleShape startButton;
    sf::Text startButtonText;
    sf::Color buttonColorNormal;
    sf::Color buttonColorHover;

    sf::CircleShape decorCircleTop;
    sf::CircleShape decorCircleBottom;

    bool isMouseOverButton(const sf::Vector2f& mousePos) const;

public:
    explicit AccueilState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};