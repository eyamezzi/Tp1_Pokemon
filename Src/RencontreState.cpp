//
// RencontreState.cpp
// Rencontre / Capture de Pokemon -> retour Exploration (succès ou échec).
//

#include "../Inc/RencontreState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/ExplorationState.h"
#include "../Inc/Pokemonassets.h"
#include <random>
#include <iostream>
#include <memory>

RencontreState::RencontreState(GameStateManager& manager)
    : GameState(manager), numeroSauvage(0)
{
}

void RencontreState::onEnter() {
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[RencontreState] Police introuvable." << std::endl;
    }

    // Tire un numéro de Pokemon au hasard dans le Pokedex (adapte le max réel)
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 151);
    numeroSauvage = dist(rng);

    infoText.setFont(font);
    infoText.setString(
        "Un Pokemon sauvage (#" + std::to_string(numeroSauvage) +
        ") apparait !\nC = capturer   E = fuir"
    );
    infoText.setCharacterSize(22);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(50.f, 50.f);

    if (texSauvage.loadFromFile(getPokemonImagePath(numeroSauvage))) {
        spriteSauvage.setTexture(texSauvage);
    } else if (texSauvage.loadFromFile(getUnknownPokemonImagePath())) {
        spriteSauvage.setTexture(texSauvage);
    }
    spriteSauvage.setPosition(350.f, 200.f);
}

void RencontreState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return;
    }

    if (event.key.code == sf::Keyboard::E) {
        manager.changeState(std::make_unique<ExplorationState>(manager));
        return;
    }

    if (event.key.code == sf::Keyboard::C) {
        // Récupère un clone du Pokemon depuis le Pokedex.
        // std::unique_ptr prend possession du pointeur brut renvoyé par
        // Pokedex::getPokemonByNumero afin d'éviter toute fuite mémoire.
        std::unique_ptr<Pokemon> capture(
            manager.getPokedex().getPokemonByNumero(numeroSauvage)
        );

        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 100);
        bool succes = dist(rng) > 40; // 60% de chance de réussite

        if (capture && succes) {
            manager.getParty().ajouterPokemon(*capture);
            std::cout << "Capture reussie : " << capture->getNom() << std::endl;
        } else {
            std::cout << "Capture echouee." << std::endl;
        }

        manager.changeState(std::make_unique<ExplorationState>(manager));
    }
}

void RencontreState::update(float deltaTime) {
    (void)deltaTime;
}

void RencontreState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(60, 40, 90));
    window.draw(infoText);
    window.draw(spriteSauvage);
}
