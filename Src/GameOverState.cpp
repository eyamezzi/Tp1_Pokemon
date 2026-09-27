//
// Created by eya on 9/27/26.
//

//
// GameOverState.cpp
// Ecran final. R -> retour à l'écran d'accueil.
//

#include "../Inc/GameOverState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/AccueilState.h"
#include <iostream>

GameOverState::GameOverState(GameStateManager& manager) : GameState(manager) {}

void GameOverState::onEnter() {
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[GameOverState] Police introuvable." << std::endl;
    }

    text.setFont(font);
    text.setString("GAME OVER\n\nAppuyez sur R pour recommencer");
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::Red);
    text.setPosition(150.f, 220.f);
}

void GameOverState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        manager.changeState(std::make_unique<AccueilState>(manager));
    }
}

void GameOverState::update(float deltaTime) {
    (void)deltaTime;
}

void GameOverState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(text);
}
