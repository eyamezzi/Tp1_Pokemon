#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameStateManager; // forward declaration, évite l'inclusion circulaire

class GameState {
protected:
    GameStateManager& manager; // référence vers le gestionnaire, pour demander un changement d'état

public:
    explicit GameState(GameStateManager& manager);
    virtual ~GameState() = default;

    // Appelée une fois à l'entrée dans l'état (ex: charger textures, réinitialiser sélection)
    virtual void onEnter() {}

    // Appelée une fois à la sortie de l'état (ex: libérer ressources spécifiques)
    virtual void onExit() {}

    // Gestion des événements SFML (clic, touche...)
    virtual void handleEvent(const sf::Event& event) = 0;

    // Mise à jour logique (déplacements, timers, IA...)
    virtual void update(float deltaTime) = 0;

    // Dessin à l'écran
    virtual void render(sf::RenderWindow& window) = 0;
};