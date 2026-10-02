#pragma once
#include "GameState.h"
#include "Pokemon_Party.h"
#include <SFML/Graphics.hpp>
#include <vector>

class FightingState : public GameState {
private:
    PokemonParty& party;

    std::vector<int> candidateNumeros;
    std::vector<int> selectedOrder;

    sf::Font font;
    sf::Text titleText;

    sf::VertexArray background;

    sf::RectangleShape fightButton;
    sf::Text fightButtonText;
    sf::Color buttonColorNormal;
    sf::Color buttonColorHover;

    std::vector<sf::Texture> candidateTextures;
    std::vector<sf::Sprite> candidateSprites;
    std::vector<sf::Text> candidateLabels;
    std::vector<sf::CircleShape> candidateBackPlates;

    void rebuildDisplay();
    bool isMouseOverButton(const sf::Vector2f& mousePos) const;

public:
    explicit FightingState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};