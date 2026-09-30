#pragma once
#include "GameState.h"
#include "Pokemon_Party.h"
#include "Pokemon_Attack.h"
#include <SFML/Graphics.hpp>
#include <vector>

class SelectionState : public GameState {
private:
    PokemonParty& party;
    PokemonAttack& attack;

    sf::Font font;
    sf::Text titleText;
    sf::Text validateText;
    sf::RectangleShape validateButton;

    std::vector<sf::Texture> partyTextures;
    std::vector<sf::Sprite> partySprites;
    std::vector<sf::Text> partyLabels;

    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Sprite> attackSprites;
    std::vector<sf::Text> attackLabels;

    void rebuildDisplay(); // recharge les sprites après chaque changement Party/Attack

public:
    explicit SelectionState(GameStateManager& manager);
    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};