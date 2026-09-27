//
// SelectionState.cpp
// Ecran de sélection de l'équipe d'attaque (6 Pokemon max) à partir de la Party.
// Clic sur un Pokemon de la Party (gauche)  -> l'ajoute à l'équipe d'attaque.
// Clic sur un Pokemon de l'équipe (droite)  -> le renvoie dans la Party.
// ENTREE -> valide et lance l'exploration.
//

#include "../Inc/SelectionState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/ExplorationState.h"
#include "../Inc/Pokemonassets.h"
#include <iostream>

SelectionState::SelectionState(GameStateManager& manager) : GameState(manager) {}

void SelectionState::onEnter() {
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[SelectionState] Police introuvable." << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("Choisissez votre equipe (6 max)");
    titleText.setCharacterSize(26);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(30.f, 15.f);

    hintText.setFont(font);
    hintText.setString("Clic gauche = ajouter | Clic droite (equipe) = retirer | ENTREE = valider");
    hintText.setCharacterSize(16);
    hintText.setFillColor(sf::Color(180, 180, 180));
    hintText.setPosition(30.f, 550.f);

    rebuildUI();
}

void SelectionState::rebuildUI() {
    partySlots.clear();
    partyLabels.clear();
    partyTextures.clear();
    partySprites.clear();

    attackSlots.clear();
    attackLabels.clear();
    attackTextures.clear();
    attackSprites.clear();

    const auto& party = manager.getParty().getPokemons();
    const auto& attackTeam = manager.getAttackTeam().getPokemons();

    // Colonne de gauche : la Party complète
    float y = 70.f;
    for (const auto& p : party) {
        sf::RectangleShape slot(sf::Vector2f(320.f, 40.f));
        slot.setPosition(30.f, y);
        slot.setFillColor(sf::Color(50, 50, 70));
        slot.setOutlineColor(sf::Color::White);
        slot.setOutlineThickness(1.f);
        partySlots.push_back(slot);

        sf::Texture tex;
        if (!tex.loadFromFile(getPokemonImagePath(p.getNumero()))) {
            tex.loadFromFile(getUnknownPokemonImagePath());
        }
        partyTextures.push_back(tex);

        sf::Sprite sprite;
        sprite.setTexture(partyTextures.back());
        // Réduit le sprite pour qu'il tienne dans le slot de 40px de haut
        sf::FloatRect bounds = sprite.getLocalBounds();
        if (bounds.height > 0.f) {
            float scale = 36.f / bounds.height;
            sprite.setScale(scale, scale);
        }
        sprite.setPosition(35.f, y + 2.f);
        partySprites.push_back(sprite);

        sf::Text label;
        label.setFont(font);
        label.setString("#" + std::to_string(p.getNumero()) + " " + p.getNom());
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);
        label.setPosition(85.f, y + 8.f); // décalé pour laisser la place au sprite
        partyLabels.push_back(label);

        y += 48.f;
    }

    // Colonne de droite : les 6 emplacements de l'équipe d'attaque
    y = 70.f;
    for (size_t i = 0; i < attackTeam.size(); ++i) {
        sf::RectangleShape slot(sf::Vector2f(320.f, 40.f));
        slot.setPosition(430.f, y);
        slot.setFillColor(sf::Color(70, 40, 40));
        slot.setOutlineColor(sf::Color::Yellow);
        slot.setOutlineThickness(1.f);
        attackSlots.push_back(slot);

        sf::Texture tex;
        if (!tex.loadFromFile(getPokemonImagePath(attackTeam[i].getNumero()))) {
            tex.loadFromFile(getUnknownPokemonImagePath());
        }
        attackTextures.push_back(tex);

        sf::Sprite sprite;
        sprite.setTexture(attackTextures.back());
        sf::FloatRect bounds = sprite.getLocalBounds();
        if (bounds.height > 0.f) {
            float scale = 36.f / bounds.height;
            sprite.setScale(scale, scale);
        }
        sprite.setPosition(435.f, y + 2.f);
        attackSprites.push_back(sprite);

        sf::Text label;
        label.setFont(font);
        label.setString("#" + std::to_string(attackTeam[i].getNumero()) + " " + attackTeam[i].getNom());
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);
        label.setPosition(485.f, y + 8.f);
        attackLabels.push_back(label);

        y += 48.f;
    }
}

void SelectionState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        manager.changeState(std::make_unique<ExplorationState>(manager));
        return;
    }

    if (event.type != sf::Event::MouseButtonPressed) {
        return;
    }

    sf::Vector2f mousePos(
        static_cast<float>(event.mouseButton.x),
        static_cast<float>(event.mouseButton.y)
    );

    if (event.mouseButton.button == sf::Mouse::Left) {
        // Clic sur la Party -> ajoute à l'équipe d'attaque (si pas pleine, et pas déjà présent)
        for (size_t i = 0; i < partySlots.size(); ++i) {
            if (partySlots[i].getGlobalBounds().contains(mousePos)) {
                const auto& party = manager.getParty().getPokemons();
                const auto& equipe = manager.getAttackTeam().getPokemons();

                int numero = party[i].getNumero();

                // Lambda : vérifie si ce Pokemon est déjà dans l'équipe d'attaque
                auto dejaDansEquipe = [&equipe, numero]() {
                    for (const auto& p : equipe) {
                        if (p.getNumero() == numero) {
                            return true;
                        }
                    }
                    return false;
                };

                if (dejaDansEquipe()) {
                    std::cout << "Ce Pokemon est deja dans l'equipe d'attaque." << std::endl;
                } else if (!manager.getAttackTeam().estPleine()) {
                    manager.getAttackTeam().ajouterPokemon(party[i]);
                    rebuildUI();
                } else {
                    std::cout << "Equipe d'attaque deja pleine (6/6)." << std::endl;
                }
                break;
            }
        }
    } else if (event.mouseButton.button == sf::Mouse::Right) {
        // Clic droit sur l'équipe -> retire ce Pokemon (retour dans la Party)
        for (size_t i = 0; i < attackSlots.size(); ++i) {
            if (attackSlots[i].getGlobalBounds().contains(mousePos)) {
                const auto& attackTeam = manager.getAttackTeam().getPokemons();
                int numero = attackTeam[i].getNumero();
                manager.getAttackTeam().retirerPokemon(numero); // à ajouter dans PokemonAttack si absent
                rebuildUI();
                break;
            }
        }
    }
}

void SelectionState::update(float deltaTime) {
    (void)deltaTime;
}

void SelectionState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(15, 15, 25));
    window.draw(titleText);
    window.draw(hintText);

    for (auto& s : partySlots) window.draw(s);
    for (auto& sp : partySprites) window.draw(sp);
    for (auto& l : partyLabels) window.draw(l);
    for (auto& s : attackSlots) window.draw(s);
    for (auto& sp : attackSprites) window.draw(sp);
    for (auto& l : attackLabels) window.draw(l);
}
