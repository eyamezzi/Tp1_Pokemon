// ExplorationState.cpp
#include "../Inc/ExplorationState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RencontreState.h"
#include "../Inc/CombatState.h"
#include <cstdlib>
#include <iostream>

ExplorationState::ExplorationState(GameStateManager& manager)
    : GameState(manager), party(manager.getParty()), attack(manager.getAttack()) {
}
void ExplorationState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    player.setSize({30.f, 30.f});
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.f, 300.f);

    hintText.setFont(font);
    hintText.setString("Deplacez-vous avec les fleches. Rencontres aleatoires en explorant.");
    hintText.setCharacterSize(18);
    hintText.setFillColor(sf::Color::White);
    hintText.setPosition(20.f, 20.f);

    encounterTimer = 0.f;
}

void ExplorationState::handleEvent(const sf::Event& event) {
    // Le déplacement continu est géré dans update() via sf::Keyboard::isKeyPressed
}

void ExplorationState::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movement.x += 1.f;

    bool isMoving = (movement.x != 0.f || movement.y != 0.f);
    if (isMoving) {
        player.move(movement * playerSpeed * deltaTime);

        encounterTimer += deltaTime;
        if (encounterTimer >= encounterInterval) {
            encounterTimer = 0.f;
            if (attack.getNombrePokemons() == 0) {
                std::cout << "Aucun Pokemon dans l'equipe d'attaque, rencontre ignoree." << std::endl;
                return;
            }
            int chance = std::rand() % 100;
            if (chance < 30) { // 30% de chance par intervalle qu'une rencontre se déclenche
                int typeRencontre = std::rand() % 100;
                if (typeRencontre < 50) {
                    // 50% : rencontre sauvage (capture ou fuite)
                    manager.changeState(std::make_unique<RencontreState>(manager));
                } else {
                    // 50% : combat direct contre un dresseur/Pokemon
                    manager.changeState(std::make_unique<CombatState>(manager));
                }
            }
        }
    }
}

void ExplorationState::render(sf::RenderWindow& window) {
    window.draw(hintText);
    window.draw(player);
}