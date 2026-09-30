#include "../Inc/RencontreState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RandomState.h"
#include <cstdlib>
#include <iostream>

RencontreState::RencontreState(GameStateManager& manager) : GameState(manager) {
}

void RencontreState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    // Degrade de fond : bleu nuit en haut -> noir en bas
    background.setPrimitiveType(sf::Quads);
    background.resize(4);
    sf::Color topColor(20, 25, 50);
    sf::Color bottomColor(5, 5, 10);
    background[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), topColor);
    background[1] = sf::Vertex(sf::Vector2f(800.f, 0.f), topColor);
    background[2] = sf::Vertex(sf::Vector2f(800.f, 600.f), bottomColor);
    background[3] = sf::Vertex(sf::Vector2f(0.f, 600.f), bottomColor);

    // Halo doux derriere le pokemon, couleur rouge attenuee
    glow.setRadius(160.f);
    glow.setOrigin(160.f, 160.f);
    glow.setPosition(400.f, 280.f);
    glow.setFillColor(sf::Color(220, 40, 40, 200)); // rouge plus marque
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
        sf::FloatRect bounds = sauvageSprite.getLocalBounds();
        sauvageSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        sauvageSprite.setPosition(400.f, 280.f);
        sauvageSprite.setScale(2.5f, 2.5f);
    }

    infoText.setFont(font);
    infoText.setString("Un " + sauvage->getNom() + " sauvage apparait !");
    infoText.setCharacterSize(22);
    infoText.setFillColor(sf::Color::White);
    sf::FloatRect infoBounds = infoText.getLocalBounds();
    infoText.setOrigin(infoBounds.width / 2.f, 0.f);
    infoText.setPosition(400.f, 40.f);

    choixText.setFont(font);
    choixText.setCharacterSize(18);
    choixText.setFillColor(sf::Color(50, 150, 255));
    choixText.setString("C : Capturer   |   F : Fuir");
    sf::FloatRect choixBounds = choixText.getLocalBounds();
    choixText.setOrigin(choixBounds.width / 2.f, 0.f);
    choixText.setPosition(400.f, 530.f);

    resultText.setFont(font);
    resultText.setCharacterSize(12);
    resultText.setFillColor(sf::Color(100, 220, 100));

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
        resultText.setString(resultatMessage);
        sf::FloatRect b = resultText.getLocalBounds();
        resultText.setOrigin(b.width / 2.f, 0.f);
        resultText.setPosition(400.f, 500.f);
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
        resultText.setString(resultatMessage);
        sf::FloatRect b = resultText.getLocalBounds();
        resultText.setOrigin(b.width / 2.f, 0.f);
        resultText.setPosition(400.f, 500.f);
    }
}

void RencontreState::update(float deltaTime) {
}

void RencontreState::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(glow);
    window.draw(sauvageSprite);
    window.draw(infoText);

    if (resultatAffiche) {
        window.draw(resultText);
        sf::Text continueText("Appuyez sur une touche pour continuer", font, 12);
        continueText.setFillColor(sf::Color(150, 150, 150));
        sf::FloatRect b = continueText.getLocalBounds();
        continueText.setOrigin(b.width / 2.f, 0.f);
        continueText.setPosition(400.f, 550.f);
        window.draw(continueText);
    } else {
        window.draw(choixText);
    }
}