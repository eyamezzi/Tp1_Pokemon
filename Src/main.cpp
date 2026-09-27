#include <SFML/Graphics.hpp>
#include "../Inc/GameStateManager.h"
#include "../Inc/AccueilState.h"


int main() {
    // Le Pokedex est un Singleton : une seule instance pour tout le programme
    Pokedex* pokedex = Pokedex::getInstance("data/pokedex.csv");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Selector");
    window.setFramerateLimit(60);

    GameStateManager gameManager(pokedex);
    gameManager.changeState(std::make_unique<AccueilState>(gameManager));

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            gameManager.handleEvent(event);
        }

        float deltaTime = clock.restart().asSeconds();
        gameManager.update(deltaTime);

        gameManager.render(window);
        window.display();
    }

    return 0;
}

