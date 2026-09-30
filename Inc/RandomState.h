#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class RandomState : public GameState {
private:
    sf::Font font;
    sf::Text explorationText;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape ground;
    sf::CircleShape player;

    float elapsedTime = 0.f;
    float explorationDuration = 2.5f;

    float playerX = 0.f;
    float playerSpeed = 150.f;

    bool destinationChoisie = false;
    bool versRencontre = false;

    void choisirDestination();

public:
    explicit RandomState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};