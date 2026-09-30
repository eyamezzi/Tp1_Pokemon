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
    };

    std::vector<Duel> duels;

    sf::Font font;
    sf::Text titleText;
    sf::RectangleShape resultButton;
    sf::Text resultButtonText;

    bool resultatsAffiches = false;
    std::vector<sf::Text> resultTexts;

    void resoudreDuel(Duel& duel);

public:
    explicit CombatState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};