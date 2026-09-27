
#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

// Ecran de sélection : permet de choisir les 6 Pokemon de la PokemonAttack
// parmi la PokemonParty, en cliquant dessus.
class SelectionState : public GameState {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text hintText;

    std::vector<sf::RectangleShape> partySlots;
    std::vector<sf::Text> partyLabels;
    std::deque<sf::Texture> partyTextures; // deque = les adresses restent stables
    std::vector<sf::Sprite> partySprites;

    std::vector<sf::RectangleShape> attackSlots;
    std::vector<sf::Text> attackLabels;
    std::deque<sf::Texture> attackTextures;
    std::vector<sf::Sprite> attackSprites;

    void rebuildUI();

public:
    explicit SelectionState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

