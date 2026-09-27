//
// ExplorationState.cpp
// Exploration -> Rencontre/Capture OU Combat dans l'arène (rencontre aléatoire).
//

#include "../Inc/ExplorationState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RencontreState.h"
#include "../Inc/CombatState.h"
#include "../Inc/SelectionState.h"
#include <random>
#include <iostream>

ExplorationState::ExplorationState(GameStateManager& manager)
    : GameState(manager), timerAvantRencontre(0.f)
{
}

void ExplorationState::onEnter() {
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[ExplorationState] Police introuvable." << std::endl;
    }

    infoText.setFont(font);
    infoText.setString("Exploration en cours...  [ESPACE] avancer   [S] equipe");
    infoText.setCharacterSize(22);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(50.f, 50.f);

    timerAvantRencontre = 0.f;
}

void ExplorationState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return;
    }

    if (event.key.code == sf::Keyboard::Space) {
        // Force une rencontre immédiate pour tester le jeu
        timerAvantRencontre = 999.f;
    } else if (event.key.code == sf::Keyboard::S) {
        // Ouvre l'écran de gestion d'équipe
        manager.changeState(std::make_unique<SelectionState>(manager));
    }
}

void ExplorationState::update(float deltaTime) {
    timerAvantRencontre += deltaTime;

    // Une rencontre survient toutes les ~3 secondes (ou via ESPACE)
    if (timerAvantRencontre < 3.f) {
        return;
    }

    // Lambda : détermine aléatoirement le type de rencontre.
    // Usage de lambda demandé par le sujet du TP.
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    auto tirerTypeRencontre = [&]() -> bool {
        // true = rencontre sauvage (capture), false = combat d'arène
        return dist(rng) == 0;
    };

    if (tirerTypeRencontre()) {
        manager.changeState(std::make_unique<RencontreState>(manager));
    } else {
        manager.changeState(std::make_unique<CombatState>(manager));
    }
}

void ExplorationState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(30, 80, 30));
    window.draw(infoText);
}
