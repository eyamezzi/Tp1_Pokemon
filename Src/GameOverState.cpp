#include "../Inc/GameOverState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/AccueilState.h"

GameOverState::GameOverState(GameStateManager& manager) : GameState(manager) {
}

void GameOverState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(250.f, 200.f);

    instructionText.setFont(font);
    instructionText.setString("Appuyez sur une touche pour recommencer");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(200.f, 300.f);
}

void GameOverState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        manager.getParty().viderListe();
        manager.getAttack().viderListe();
        manager.changeState(std::make_unique<AccueilState>(manager));
    }
}

void GameOverState::update(float deltaTime) {
}

void GameOverState::render(sf::RenderWindow& window) {
    window.draw(gameOverText);
    window.draw(instructionText);
}