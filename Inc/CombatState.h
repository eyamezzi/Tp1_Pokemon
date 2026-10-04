#pragma once
#include "GameState.h"
#include "Pokemon.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class CombatState : public GameState {
private:
    struct Duel {
        Pokemon* combattant;
        std::unique_ptr<Pokemon> adversaire;
        bool gagne = false;

        sf::Texture combattantTexture;
        sf::Sprite combattantSprite;
        sf::Texture adversaireTexture;
        sf::Sprite adversaireSprite;

        sf::CircleShape glowLeft;
        sf::CircleShape glowRight;

        sf::Text vsLabel;
    };

    std::vector<Duel> duels;

    sf::Font font;
    sf::Text titleText;

    sf::VertexArray background;

    sf::RectangleShape resultButton;
    sf::Text resultButtonText;
    sf::Color buttonColorNormal;
    sf::Color buttonColorHover;

    bool resultatsAffiches = false;
    std::vector<sf::Text> resultTexts;

    void resoudreDuel(Duel& duel);
    void chargerSprites();
    void positionnerDuels();
    bool isMouseOverButton(const sf::Vector2f& mousePos) const;

public:
    explicit CombatState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};