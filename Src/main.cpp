#include <SFML/Graphics.hpp>
#include "../Inc/GameStateManager.h"
#include "../Inc/AccueilState.h"
#include "../Inc/Pokedex.h"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Selector");

    Pokedex* dex = Pokedex::getInstance("data/pokedex.csv");

    GameStateManager manager(dex);

    manager.changeState(std::make_unique<AccueilState>(manager));
    manager.applyPendingChange();

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            manager.handleEvent(event);
        }

        float deltaTime = clock.restart().asSeconds();
        manager.update(deltaTime);
        manager.applyPendingChange();

        window.clear(sf::Color::Black);
        manager.render(window);
        window.display();
    }

    return 0;
}