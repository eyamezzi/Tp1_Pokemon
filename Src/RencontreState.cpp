#include "../Inc/RencontreState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RandomState.h"
#include <cstdlib>
#include <iostream>

RencontreState::RencontreState(GameStateManager& manager) : GameState(manager) {
}

void RencontreState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    int maxNumero = static_cast<int>(manager.getPokedex().getNombrePokemons());
    int numeroSauvage = (std::rand() % (maxNumero > 0 ? maxNumero : 1)) + 1;
    sauvage.reset(manager.getPokedex().getPokemonByNumero(numeroSauvage));

    if (!sauvage) {
        std::cerr << "[RencontreState] Impossible de tirer un Pokemon sauvage." << std::endl;
        manager.changeState(std::make_unique<RandomState>(manager));
        return;
    }

    std::string path = "data/image_pokedex-20260914/pokemon/" +
                        std::to_string(sauvage->getNumero()) + ".png";
    if (sauvageTexture.loadFromFile(path)) {
        sauvageSprite.setTexture(sauvageTexture);
        sauvageSprite.setPosition(350.f, 150.f);
        sauvageSprite.setScale(1.5f, 1.5f);
    }

    infoText.setFont(font);
    infoText.setString("Un " + sauvage->getNom() + " sauvage apparait !");
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(20.f, 20.f);

    choixText.setFont(font);
    choixText.setCharacterSize(20);
    choixText.setFillColor(sf::Color::Yellow);
    choixText.setString("C : Capturer   |   F : Fuir");
    choixText.setPosition(20.f, 500.f);

    resultatAffiche = false;
}

void RencontreState::handleEvent(const sf::Event& event) {
    if (resultatAffiche) {
        if (event.type == sf::Event::KeyPressed) {
            manager.changeState(std::make_unique<RandomState>(manager));
        }
        return;
    }

    if (event.type != sf::Event::KeyPressed) return;

    if (event.key.code == sf::Keyboard::F) {
        resultatMessage = "Vous avez fui.";
        resultatAffiche = true;
        return;
    }

    if (event.key.code == sf::Keyboard::C) {
        int chance = std::rand() % 100;
        if (chance < 50) {
            manager.getParty().ajouterPokemon(*sauvage);
            resultatMessage = "Capture reussie ! #" + std::to_string(sauvage->getNumero()) +
                               " " + sauvage->getNom() +
                               " (PV:" + std::to_string(sauvage->getPvMax()) +
                               " ATK:" + std::to_string(static_cast<int>(sauvage->getAttack())) +
                               " DEF:" + std::to_string(static_cast<int>(sauvage->getDefense())) + ")";
        } else {
            resultatMessage = sauvage->getNom() + " s'est echappe.";
        }
        resultatAffiche = true;
    }
}

void RencontreState::update(float deltaTime) {
}

void RencontreState::render(sf::RenderWindow& window) {
    window.draw(sauvageSprite);
    window.draw(infoText);

    if (resultatAffiche) {
        sf::Text result(resultatMessage, font, 22);
        result.setFillColor(sf::Color::Green);
        result.setPosition(20.f, 400.f);
        window.draw(result);

        sf::Text continueText("Appuyez sur une touche pour continuer", font, 16);
        continueText.setFillColor(sf::Color(180, 180, 180));
        continueText.setPosition(20.f, 550.f);
        window.draw(continueText);
    } else {
        window.draw(choixText);
    }
}