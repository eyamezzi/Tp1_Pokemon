#include "../Inc/SelectionState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/ExplorationState.h"
#include <iostream>

SelectionState::SelectionState(GameStateManager& manager)
    : GameState(manager), party(manager.getParty()), attack(manager.getAttack()) {
}

void SelectionState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    titleText.setFont(font);
    titleText.setString("Selectionnez votre equipe (clic)");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(20.f, 20.f);

    validateButton.setSize({150.f, 50.f});
    validateButton.setFillColor(sf::Color(60, 60, 60));
    validateButton.setPosition(620.f, 20.f);

    validateText.setFont(font);
    validateText.setString("Valider");
    validateText.setCharacterSize(20);
    validateText.setFillColor(sf::Color::White);
    validateText.setPosition(650.f, 35.f);

    rebuildDisplay();
}

void SelectionState::rebuildDisplay() {
    // Reconstruit entièrement les listes de sprites à partir de l'état actuel de Party et Attack
    partyTextures.clear();
    partySprites.clear();
    partyLabels.clear();
    attackTextures.clear();
    attackSprites.clear();
    attackLabels.clear();

    const auto& partyList = party.getPokemons();
    partyTextures.resize(partyList.size());
    for (size_t i = 0; i < partyList.size(); ++i) {
        std::string path = "data/image_pokedex-20260914/pokemon/" +
                            std::to_string(partyList[i].getNumero()) + ".png";
        if (!partyTextures[i].loadFromFile(path)) {
            std::cerr << "[SelectionState] Image manquante : " << path << std::endl;
        }
        sf::Sprite sprite(partyTextures[i]);
        sprite.setPosition(20.f + (i % 6) * 90.f, 100.f + (i / 6) * 100.f);
        sprite.setScale(0.5f, 0.5f);
        partySprites.push_back(sprite);

        sf::Text label(partyList[i].getNom(), font, 14);
        label.setPosition(sprite.getPosition().x, sprite.getPosition().y + 70.f);
        partyLabels.push_back(label);
    }

    const auto& attackList = attack.getPokemons();
    attackTextures.resize(attackList.size());
    for (size_t i = 0; i < attackList.size(); ++i) {
        std::string path = "data/image_pokedex-20260914/pokemon/" +
                            std::to_string(attackList[i].getNumero()) + ".png";
        if (!attackTextures[i].loadFromFile(path)) {
            std::cerr << "[SelectionState] Image manquante : " << path << std::endl;
        }
        sf::Sprite sprite(attackTextures[i]);
        sprite.setPosition(20.f + i * 90.f, 400.f);
        sprite.setScale(0.5f, 0.5f);
        attackSprites.push_back(sprite);

        sf::Text label(attackList[i].getNom(), font, 14);
        label.setPosition(sprite.getPosition().x, sprite.getPosition().y + 70.f);
        attackLabels.push_back(label);
    }
}

void SelectionState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
    if (event.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x),
                           static_cast<float>(event.mouseButton.y));

    // Clic sur un Pokemon de la Party -> l'ajouter à l'Attack
    for (size_t i = 0; i < partySprites.size(); ++i) {
        if (partySprites[i].getGlobalBounds().contains(clickPos)) {
            const auto& partyList = party.getPokemons();
            int numero = partyList[i].getNumero();

            if (!attack.estPleine()) {
                Pokemon copie = partyList[i];
                attack.ajouterPokemon(copie);
                party.retirerPokemon(numero);
                rebuildDisplay();
            } else {
                std::cout << "Equipe d'attaque deja pleine (6/6)." << std::endl;
            }
            return;
        }
    }

    // Clic sur un Pokemon de l'Attack -> le renvoyer vers la Party
    for (size_t i = 0; i < attackSprites.size(); ++i) {
        if (attackSprites[i].getGlobalBounds().contains(clickPos)) {
            const auto& attackList = attack.getPokemons();
            int numero = attackList[i].getNumero();

            Pokemon copie = attackList[i];
            party.ajouterPokemon(copie);
            attack.retirerPokemon(numero);
            rebuildDisplay();
            return;
        }
    }

    // Clic sur le bouton Valider
    if (validateButton.getGlobalBounds().contains(clickPos)) {
        if (attack.getNombrePokemons() == 0) {
            std::cout << "Selectionnez au moins un Pokemon avant de valider." << std::endl;
            return;
        }
        manager.changeState(std::make_unique<ExplorationState>(manager));
    }
}

void SelectionState::update(float deltaTime) {
}

void SelectionState::render(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(validateButton);
    window.draw(validateText);

    for (auto& sprite : partySprites) window.draw(sprite);
    for (auto& label : partyLabels) window.draw(label);

    for (auto& sprite : attackSprites) window.draw(sprite);
    for (auto& label : attackLabels) window.draw(label);
}