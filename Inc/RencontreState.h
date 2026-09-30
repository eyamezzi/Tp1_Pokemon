#pragma once
#include "GameState.h"
#include "Pokemon.h"
#include <SFML/Graphics.hpp>
#include <memory>

class RencontreState : public GameState {
private:
    std::unique_ptr<Pokemon> sauvage;

    sf::Font font;
    sf::Text infoText;
    sf::Text choixText;

    sf::Texture sauvageTexture;
    sf::Sprite sauvageSprite;

    bool resultatAffiche = false;
    std::string resultatMessage;

public:
    explicit RencontreState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};