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

    titleText.setFont(font);
    titleText.setString("Choisissez vos combattants (clic, dans l'ordre)");
    titleText.setCharacterSize(20);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(20.f, 20.f);

    fightButton.setSize({150.f, 50.f});
    fightButton.setFillColor(sf::Color(60, 60, 60));
    fightButton.setPosition(620.f, 500.f);

    fightButtonText.setFont(font);
    fightButtonText.setString("Fight");
    fightButtonText.setCharacterSize(20);
    fightButtonText.setFillColor(sf::Color::White);
    fightButtonText.setPosition(660.f, 515.f);

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

    const auto& partyList = party.getPokemons();
    candidateTextures.resize(candidateNumeros.size());

    for (size_t i = 0; i < candidateNumeros.size(); ++i) {
        int numero = candidateNumeros[i];
        std::string path = "data/image_pokedex-20260914/pokemon/" +
                            std::to_string(numero) + ".png";
        candidateTextures[i].loadFromFile(path);

        sf::Sprite sprite(candidateTextures[i]);
        sprite.setPosition(20.f + i * 110.f, 100.f);
        sprite.setScale(0.5f, 0.5f);
        candidateSprites.push_back(sprite);

        std::string nom = "?";
        for (const auto& p : partyList) {
            if (p.getNumero() == numero) { nom = p.getNom(); break; }
        }

        auto it = std::find(selectedOrder.begin(), selectedOrder.end(), numero);
        std::string suffix = (it != selectedOrder.end())
            ? " [" + std::to_string(std::distance(selectedOrder.begin(), it) + 1) + "]"
            : "";

        sf::Text label(nom + suffix, font, 14);
        label.setPosition(sprite.getPosition().x, sprite.getPosition().y + 70.f);
        candidateLabels.push_back(label);
    }
}

void FightingState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
    if (event.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x),
                           static_cast<float>(event.mouseButton.y));

    for (size_t i = 0; i < candidateSprites.size(); ++i) {
        if (candidateSprites[i].getGlobalBounds().contains(clickPos)) {
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

    if (fightButton.getGlobalBounds().contains(clickPos)) {
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
    window.draw(titleText);
    for (auto& s : candidateSprites) window.draw(s);
    for (auto& l : candidateLabels) window.draw(l);
    window.draw(fightButton);
    window.draw(fightButtonText);
}