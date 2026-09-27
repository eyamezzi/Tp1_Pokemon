#pragma once

#include "GameState.h"
#include "Pokemon.h"
#include "Pokemon_Attack.h"
#include <SFML/Graphics.hpp>
#include <memory>

class CombatState : public GameState {
private:
    sf::Font font;
    sf::Text infoText;
    std::unique_ptr<Pokemon> adversaire;
    Pokemon* combattant; // non possédé : appartient à GameStateManager (PV persistants)

    sf::Texture texJoueur;
    sf::Texture texAdversaire;
    sf::Texture texGauge;
    sf::Texture texVs;

    sf::Sprite spriteJoueur;
    sf::Sprite spriteAdversaire;
    sf::Sprite spriteGaugeJoueur;
    sf::Sprite spriteGaugeAdversaire;
    sf::Sprite spriteVs;

    sf::RectangleShape barreVieJoueur;
    sf::RectangleShape barreVieAdversaire;

    void chargerSprites();
    void mettreAJourBarresVie();

public:
    explicit CombatState(GameStateManager& manager);

    void onEnter() override;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
