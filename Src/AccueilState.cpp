//
// AccueilState.cpp
// Ecran d'accueil -> Exploration sur appui touche ou clic souris.
//

#include "../Inc/AccueilState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/ExplorationState.h"
#include <iostream>
#include "../Inc/SelectionState.h"
AccueilState::AccueilState(GameStateManager& manager) : GameState(manager) {}

void AccueilState::onEnter() {
    // Adapte le chemin vers une police disponible dans ton projet (dossier data/)
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[AccueilState] Police introuvable, texte non affiché." << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("POKEMON SELECTOR");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(150.f, 200.f);

    hintText.setFont(font);
    hintText.setString("Appuyez sur une touche ou cliquez pour commencer");
    hintText.setCharacterSize(20);
    hintText.setFillColor(sf::Color::White);
    hintText.setPosition(150.f, 320.f);
}

void AccueilState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed ||
        event.type == sf::Event::MouseButtonPressed) {
        manager.changeState(std::make_unique<ExplorationState>(manager));
        }
}
void AccueilState::update(float deltaTime) {
    // Rien à mettre à jour sur l'écran d'accueil
    (void)deltaTime;
}

void AccueilState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 40));
    window.draw(titleText);
    window.draw(hintText);
}
