#include "../Inc/AccueilState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RandomState.h"
#include <iostream>

AccueilState::AccueilState(GameStateManager& manager) : GameState(manager) {
}

void AccueilState::onEnter() {
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[AccueilState] Impossible de charger la police." << std::endl;
    }

    // Titre principal
    titleText.setFont(font);
    titleText.setString("POKEMON");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titleText.setPosition(400.f, 160.f);

    // Sous-titre
    subtitleText.setFont(font);
    subtitleText.setString("Selector");
    subtitleText.setCharacterSize(28);
    subtitleText.setFillColor(sf::Color(200, 200, 200));
    sf::FloatRect subBounds = subtitleText.getLocalBounds();
    subtitleText.setOrigin(subBounds.width / 2.f, subBounds.height / 2.f);
    subtitleText.setPosition(400.f, 220.f);


    decorCircleTop.setRadius(180.f);
    decorCircleTop.setFillColor(sf::Color(200, 30, 30));
    decorCircleTop.setOrigin(180.f, 180.f);
    decorCircleTop.setPosition(400.f, 300.f);

    decorCircleBottom.setRadius(60.f);
    decorCircleBottom.setFillColor(sf::Color(30, 30, 30));
    decorCircleBottom.setOrigin(60.f, 60.f);
    decorCircleBottom.setPosition(400.f, 300.f);

    // Bouton START
    buttonColorNormal = sf::Color(50, 120, 220);
    buttonColorHover = sf::Color(70, 150, 255);

    startButton.setSize({200.f, 60.f});
    startButton.setFillColor(buttonColorNormal);
    startButton.setOutlineThickness(3.f);
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOrigin(100.f, 30.f);
    startButton.setPosition(400.f, 450.f);

    startButtonText.setFont(font);
    startButtonText.setString("START");
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setStyle(sf::Text::Bold);
    sf::FloatRect btnTextBounds = startButtonText.getLocalBounds();
    startButtonText.setOrigin(btnTextBounds.width / 2.f, btnTextBounds.height / 2.f + 5.f);
    startButtonText.setPosition(400.f, 450.f);
}

bool AccueilState::isMouseOverButton(const sf::Vector2f& mousePos) const {
    return startButton.getGlobalBounds().contains(mousePos);
}

void AccueilState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x),
                               static_cast<float>(event.mouseMove.y));
        startButton.setFillColor(isMouseOverButton(mousePos) ? buttonColorHover : buttonColorNormal);
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                               static_cast<float>(event.mouseButton.y));
        if (isMouseOverButton(mousePos)) {
            manager.changeState(std::make_unique<RandomState>(manager));
        }
    }

    // Touche Entrée ou Espace = raccourci clavier pour démarrer aussi
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)) {
        manager.changeState(std::make_unique<RandomState>(manager));
    }
}

void AccueilState::update(float deltaTime) {
}

void AccueilState::render(sf::RenderWindow& window) {
    window.draw(decorCircleTop);
    window.draw(decorCircleBottom);
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(startButton);
    window.draw(startButtonText);
}