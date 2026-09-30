#include "../Inc/CombatState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RandomState.h"
#include "../Inc/GameOverState.h"
#include <cstdlib>

CombatState::CombatState(GameStateManager& manager) : GameState(manager) {
}

void CombatState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    duels.clear();
    auto& attack = manager.getAttack();
    int maxNumero = static_cast<int>(manager.getPokedex().getNombrePokemons());

    for (size_t i = 0; i < attack.getNombrePokemons(); ++i) {
        Duel duel;
        duel.combattant = attack.getPokemonAt(i);
        int numero = (std::rand() % maxNumero) + 1;
        duel.adversaire.reset(manager.getPokedex().getPokemonByNumero(numero));
        duels.push_back(std::move(duel));
    }

    titleText.setFont(font);
    titleText.setString("Combats en cours - cliquez pour voir le resultat");
    titleText.setCharacterSize(20);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(20.f, 20.f);

    resultButton.setSize({200.f, 50.f});
    resultButton.setFillColor(sf::Color(60, 60, 60));
    resultButton.setPosition(300.f, 520.f);

    resultButtonText.setFont(font);
    resultButtonText.setString("Voir le resultat");
    resultButtonText.setCharacterSize(18);
    resultButtonText.setFillColor(sf::Color::White);
    resultButtonText.setPosition(320.f, 535.f);

    resultatsAffiches = false;
}

void CombatState::resoudreDuel(Duel& duel) {
    int rounds = 0;
    while (duel.combattant->getPvActual() > 0 &&
           duel.adversaire->getPvActual() > 0 &&
           rounds < 100) {
        duel.combattant->attaquer(*duel.adversaire);
        if (duel.adversaire->getPvActual() <= 0) break;
        duel.adversaire->attaquer(*duel.combattant);
        rounds++;
    }
    duel.gagne = duel.combattant->getPvActual() > 0;
}

void CombatState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
    if (event.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x),
                           static_cast<float>(event.mouseButton.y));

    if (!resultatsAffiches) {
        if (resultButton.getGlobalBounds().contains(clickPos)) {
            resultTexts.clear();
            for (auto& duel : duels) {
                resoudreDuel(duel);
                std::string msg = duel.combattant->getNom() + " vs " +
                                   duel.adversaire->getNom() + " : " +
                                   (duel.gagne ? "GAGNE" : "PERDU");
                sf::Text t(msg, font, 18);
                t.setFillColor(duel.gagne ? sf::Color::Green : sf::Color::Red);
                resultTexts.push_back(t);
            }

            for (auto& duel : duels) {
                if (!duel.gagne) {
                    manager.getParty().retirerPokemon(duel.combattant->getNumero());
                }
            }
            manager.getAttack().viderListe();

            resultatsAffiches = true;
        }
    } else {
        if (manager.getParty().getNombrePokemons() == 0) {
            manager.changeState(std::make_unique<GameOverState>(manager));
        } else {
            manager.changeState(std::make_unique<RandomState>(manager));
        }
    }
}

void CombatState::update(float deltaTime) {
}

void CombatState::render(sf::RenderWindow& window) {
    window.draw(titleText);

    if (!resultatsAffiches) {
        window.draw(resultButton);
        window.draw(resultButtonText);
    } else {
        float y = 100.f;
        for (auto& t : resultTexts) {
            sf::Text copy = t;
            copy.setPosition(20.f, y);
            window.draw(copy);
            y += 30.f;
        }
        sf::Text continueText("Cliquez pour continuer", font, 16);
        continueText.setFillColor(sf::Color(180, 180, 180));
        continueText.setPosition(20.f, 550.f);
        window.draw(continueText);
    }
}