//
// GameState.h
// Interface abstraite du design pattern STATE.
// Chaque écran du jeu (Accueil, Exploration, Rencontre, Combat, GameOver)
// est une classe concrète qui hérite de GameState.
//

#pragma once

#include <SFML/Graphics.hpp>

class GameStateManager; // déclaration anticipée pour éviter l'inclusion circulaire

class GameState {
protected:
    GameStateManager& manager;

public:
    explicit GameState(GameStateManager& manager) : manager(manager) {}
    virtual ~GameState() = default;

    // Appelé une seule fois quand on entre dans l'état
    virtual void onEnter() {}

    // Appelé une seule fois quand on quitte l'état
    virtual void onExit() {}

    // Gestion des évènements (clavier, souris, fermeture fenêtre)
    virtual void handleEvent(const sf::Event& event) = 0;

    // Logique du jeu (appelée à chaque frame)
    virtual void update(float deltaTime) = 0;

    // Affichage (appelé à chaque frame)
    virtual void render(sf::RenderWindow& window) = 0;
};

