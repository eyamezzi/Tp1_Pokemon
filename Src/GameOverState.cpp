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

    sf::FloatRect gb = gameOverText.getLocalBounds();

    gameOverText.setOrigin(
        gb.left + gb.width / 2.f,
        gb.top + gb.height / 2.f
    );

    gameOverText.setPosition(400.f, 250.f);


    instructionText.setFont(font);
    instructionText.setString("Appuyez sur une touche pour recommencer");
    instructionText.setCharacterSize(12);
    instructionText.setFillColor(sf::Color::White);

    sf::FloatRect ib = instructionText.getLocalBounds();

    instructionText.setOrigin(
        ib.left + ib.width / 2.f,
        ib.top + ib.height / 2.f
    );

    instructionText.setPosition(400.f, 350.f);

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