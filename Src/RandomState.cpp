#include "../Inc/RandomState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RencontreState.h"
#include "../Inc/FightingState.h"
#include <cstdlib>
#include <iostream>

RandomState::RandomState(GameStateManager& manager) : GameState(manager) {
}

void RandomState::choisirDestination() {
    if (manager.getParty().getNombrePokemons() == 0) {
        versRencontre = true;
    } else {
        int chance = std::rand() % 100;
        versRencontre = (chance < 50);
    }
    destinationChoisie = true;
}

void RandomState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    if (backgroundTexture.loadFromFile("data/EXPLORATION.png")) {
        backgroundSprite.setTexture(backgroundTexture);

        // Redimensionne l'image pour qu'elle remplisse exactement la fenêtre 800x600
        sf::Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            800.f / static_cast<float>(textureSize.x),
            600.f / static_cast<float>(textureSize.y)
        );
    } else {
        std::cerr << "[RandomState] Impossible de charger l'image de fond." << std::endl;
    }

    ground.setSize({800.f, 150.f});
    ground.setFillColor(sf::Color(200, 30, 30));
    ground.setPosition(0.f, 400.f);

    player.setRadius(20.f);
    player.setFillColor(sf::Color(50, 120, 220));
    player.setOutlineThickness(2.f);
    player.setOutlineColor(sf::Color::White);
    player.setOrigin(20.f, 20.f);

    explorationText.setFont(font);
    explorationText.setString("Exploration en cours...");
    explorationText.setCharacterSize(28);
    explorationText.setFillColor(sf::Color::White);
    sf::FloatRect bounds = explorationText.getLocalBounds();
    explorationText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    explorationText.setPosition(400.f, 100.f);

    elapsedTime = 0.f;
    playerX = -30.f;
    destinationChoisie = false;
    versRencontre = false;

    choisirDestination();
}

void RandomState::handleEvent(const sf::Event& event) {
}

void RandomState::update(float deltaTime) {
    elapsedTime += deltaTime;

    playerX += playerSpeed * deltaTime;
    if (playerX > 830.f) playerX = -30.f;

    player.setPosition(playerX, 460.f);

    if (elapsedTime >= explorationDuration) {
        if (versRencontre) {
            manager.changeState(std::make_unique<RencontreState>(manager));
        } else {
            manager.changeState(std::make_unique<FightingState>(manager));
        }
    }
}

void RandomState::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(explorationText);
    window.draw(player);
}