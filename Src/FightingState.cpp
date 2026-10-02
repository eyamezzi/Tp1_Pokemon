#include "../Inc/FightingState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/AccueilState.h"
#include "../Inc/CombatState.h"
#include <algorithm>

FightingState::FightingState(GameStateManager& manager)
    : GameState(manager), party(manager.getParty()) {
}

void FightingState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    // Degrade de fond, identique a RencontreState
    background.setPrimitiveType(sf::Quads);
    background.resize(4);
    sf::Color topColor(20, 25, 50);
    sf::Color bottomColor(5, 5, 10);
    background[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), topColor);
    background[1] = sf::Vertex(sf::Vector2f(800.f, 0.f), topColor);
    background[2] = sf::Vertex(sf::Vector2f(800.f, 600.f), bottomColor);
    background[3] = sf::Vertex(sf::Vector2f(0.f, 600.f), bottomColor);

    titleText.setFont(font);
    titleText.setString("Choisissez vos combattants");
    titleText.setCharacterSize(18);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, 0.f);
    titleText.setPosition(400.f, 30.f);

    buttonColorNormal = sf::Color(50, 120, 220);
    buttonColorHover = sf::Color(70, 150, 255);

    fightButton.setSize({180.f, 55.f});
    fightButton.setFillColor(buttonColorNormal);
    fightButton.setOutlineThickness(2.f);
    fightButton.setOutlineColor(sf::Color::White);
    fightButton.setOrigin(90.f, 27.5f);
    fightButton.setPosition(400.f, 530.f);

    fightButtonText.setFont(font);
    fightButtonText.setString("FIGHT");
    fightButtonText.setCharacterSize(20);
    fightButtonText.setFillColor(sf::Color::White);
    sf::FloatRect btnBounds = fightButtonText.getLocalBounds();
    fightButtonText.setOrigin(btnBounds.width / 2.f, btnBounds.height / 2.f + 5.f);
    fightButtonText.setPosition(400.f, 530.f);

    candidateNumeros.clear();
    const auto& partyList = party.getPokemons();
    size_t n = std::min<size_t>(partyList.size(), 6);
    for (size_t i = 0; i < n; ++i) {
        candidateNumeros.push_back(partyList[i].getNumero());
    }

    selectedOrder.clear();
    rebuildDisplay();
}

void FightingState::rebuildDisplay() {
    candidateTextures.clear();
    candidateSprites.clear();
    candidateLabels.clear();
    candidateBackPlates.clear();

    const auto& partyList = party.getPokemons();
    candidateTextures.resize(candidateNumeros.size());

    float startX = 400.f - (candidateNumeros.size() * 110.f) / 2.f + 55.f;

    for (size_t i = 0; i < candidateNumeros.size(); ++i) {
        int numero = candidateNumeros[i];
        std::string path = "data/image_pokedex-20260914/pokemon/" +
                            std::to_string(numero) + ".png";
        candidateTextures[i].loadFromFile(path);

        float cx = startX + i * 110.f;
        float cy = 220.f;

        auto it = std::find(selectedOrder.begin(), selectedOrder.end(), numero);
        bool isSelected = (it != selectedOrder.end());

        // Plateau circulaire derriere le sprite, rouge si selectionne, sombre sinon
        sf::CircleShape plate(50.f);
        plate.setOrigin(50.f, 50.f);
        plate.setPosition(cx, cy);
        plate.setFillColor(isSelected
            ? sf::Color(200, 30, 30, 160)
            : sf::Color(255, 255, 255, 25));
        plate.setOutlineThickness(isSelected ? 3.f : 1.f);
        plate.setOutlineColor(isSelected ? sf::Color(255, 220, 0) : sf::Color(100, 100, 100));
        candidateBackPlates.push_back(plate);

        sf::Sprite sprite(candidateTextures[i]);
        sf::FloatRect sBounds = sprite.getLocalBounds();
        sprite.setOrigin(sBounds.width / 2.f, sBounds.height / 2.f);
        sprite.setPosition(cx, cy);
        sprite.setScale(1.2f, 1.2f);
        candidateSprites.push_back(sprite);

        std::string nom = "?";
        for (const auto& p : partyList) {
            if (p.getNumero() == numero) { nom = p.getNom(); break; }
        }
        std::string suffix = isSelected
            ? " [" + std::to_string(std::distance(selectedOrder.begin(), it) + 1) + "]"
            : "";

        sf::Text label(nom + suffix, font, 12);
        label.setFillColor(isSelected ? sf::Color(255, 220, 0) : sf::Color::White);
        sf::FloatRect lBounds = label.getLocalBounds();
        label.setOrigin(lBounds.width / 2.f, 0.f);
        label.setPosition(cx, cy + 60.f);
        candidateLabels.push_back(label);
    }
}

bool FightingState::isMouseOverButton(const sf::Vector2f& mousePos) const {
    return fightButton.getGlobalBounds().contains(mousePos);
}

void FightingState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x),
                               static_cast<float>(event.mouseMove.y));
        fightButton.setFillColor(isMouseOverButton(mousePos) ? buttonColorHover : buttonColorNormal);
    }

    if (event.type != sf::Event::MouseButtonPressed) return;
    if (event.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x),
                           static_cast<float>(event.mouseButton.y));

    for (size_t i = 0; i < candidateBackPlates.size(); ++i) {
        float dx = clickPos.x - candidateBackPlates[i].getPosition().x;
        float dy = clickPos.y - candidateBackPlates[i].getPosition().y;
        if (dx * dx + dy * dy <= 50.f * 50.f) {
            int numero = candidateNumeros[i];
            auto it = std::find(selectedOrder.begin(), selectedOrder.end(), numero);
            if (it != selectedOrder.end()) {
                selectedOrder.erase(it);
            } else if (selectedOrder.size() < 6) {
                selectedOrder.push_back(numero);
            }
            rebuildDisplay();
            return;
        }
    }

    if (isMouseOverButton(clickPos)) {
        if (selectedOrder.empty()) {
            manager.changeState(std::make_unique<AccueilState>(manager));
            return;
        }

        manager.getAttack().viderListe();
        const auto& partyList = party.getPokemons();
        for (int numero : selectedOrder) {
            for (const auto& p : partyList) {
                if (p.getNumero() == numero) {
                    manager.getAttack().ajouterPokemon(p);
                    break;
                }
            }
        }

        manager.changeState(std::make_unique<CombatState>(manager));
    }
}

void FightingState::update(float deltaTime) {
}

void FightingState::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(titleText);

    for (size_t i = 0; i < candidateSprites.size(); ++i) {
        window.draw(candidateBackPlates[i]);
        window.draw(candidateSprites[i]);
        window.draw(candidateLabels[i]);
    }

    window.draw(fightButton);
    window.draw(fightButtonText);
}