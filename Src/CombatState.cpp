
//
// CombatState.cpp
// Combat dans l'arène. Les PV du combattant actif persistent entre les
// combats (via GameStateManager::getCombattantActuel), et l'équipe tourne
// automatiquement vers le Pokemon suivant quand l'actuel est K.O.
// Game Over seulement quand toute l'équipe est K.O.
//

#include "../Inc/CombatState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/ExplorationState.h"
#include "../Inc/GameOverState.h"
#include "../Inc/Pokemonassets.h"
#include <random>
#include <iostream>

CombatState::CombatState(GameStateManager& manager)
    : GameState(manager), combattant(nullptr)
{
}

void CombatState::chargerSprites() {
    combattant = manager.getCombattantActuel();

    if (combattant) {
        if (texJoueur.loadFromFile(getPokemonImagePath(combattant->getNumero()))) {
            spriteJoueur.setTexture(texJoueur);
            spriteJoueur.setPosition(150.f, 320.f);
        } else {
            std::cerr << "[CombatState] Sprite joueur introuvable." << std::endl;
        }
    }

    if (adversaire) {
        if (texAdversaire.loadFromFile(getPokemonImagePath(adversaire->getNumero()))) {
            spriteAdversaire.setTexture(texAdversaire);
            spriteAdversaire.setPosition(500.f, 120.f);
        } else {
            std::cerr << "[CombatState] Sprite adversaire introuvable." << std::endl;
        }
    }

    if (texVs.loadFromFile("data/versusSmall.png")) {
        spriteVs.setTexture(texVs);
        spriteVs.setPosition(370.f, 220.f);
    }

    if (texGauge.loadFromFile("data/healthGauge.png")) {
        spriteGaugeJoueur.setTexture(texGauge);
        spriteGaugeJoueur.setPosition(140.f, 290.f);

        spriteGaugeAdversaire.setTexture(texGauge);
        spriteGaugeAdversaire.setPosition(490.f, 90.f);
    }

    barreVieJoueur.setFillColor(sf::Color::Green);
    barreVieJoueur.setPosition(160.f, 300.f);
    barreVieJoueur.setSize(sf::Vector2f(100.f, 10.f));

    barreVieAdversaire.setFillColor(sf::Color::Green);
    barreVieAdversaire.setPosition(510.f, 100.f);
    barreVieAdversaire.setSize(sf::Vector2f(100.f, 10.f));
}

void CombatState::mettreAJourBarresVie() {
    if (combattant) {
        float ratio = static_cast<float>(combattant->getPvActual()) /
                      static_cast<float>(combattant->getPvMax());
        barreVieJoueur.setSize(sf::Vector2f(100.f * ratio, 10.f));
        barreVieJoueur.setFillColor(ratio > 0.3f ? sf::Color::Green : sf::Color::Red);
    }

    if (adversaire) {
        float ratio = static_cast<float>(adversaire->getPvActual()) /
                      static_cast<float>(adversaire->getPvMax());
        barreVieAdversaire.setSize(sf::Vector2f(100.f * ratio, 10.f));
        barreVieAdversaire.setFillColor(ratio > 0.3f ? sf::Color::Green : sf::Color::Red);
    }
}

void CombatState::onEnter() {
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")) {
        std::cerr << "[CombatState] Police introuvable." << std::endl;
    }

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 151);
    adversaire.reset(manager.getPokedex().getPokemonByNumero(dist(rng)));

    chargerSprites();
    mettreAJourBarresVie();

    std::string nomJoueur = combattant ? combattant->getNom() : "???";
    std::string nomAdv = adversaire ? adversaire->getNom() : "???";

    infoText.setFont(font);
    infoText.setString(nomJoueur + " VS " + nomAdv + "   [A = attaquer]");
    infoText.setCharacterSize(22);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(50.f, 20.f);
}

void CombatState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed || event.key.code != sf::Keyboard::A) {
        return;
    }

    if (!combattant || !adversaire) {
        std::cout << "Pas de Pokemon disponible pour combattre !" << std::endl;
        manager.changeState(std::make_unique<ExplorationState>(manager));
        return;
    }

    combattant->attaquer(*adversaire);

    if (adversaire->getPvActual() <= 0) {
        std::cout << "Victoire ! " << adversaire->getNom() << " rejoint votre equipe." << std::endl;
        manager.getParty().ajouterPokemon(*adversaire);
        manager.changeState(std::make_unique<ExplorationState>(manager));
        return;
    }

    adversaire->attaquer(*combattant);
    mettreAJourBarresVie();

    if (combattant->getPvActual() <= 0) {
        std::cout << combattant->getNom() << " est K.O." << std::endl;

        // GameStateManager passe automatiquement au prochain Pokemon vivant
        Pokemon* suivant = manager.getCombattantActuel();

        if (manager.toutePartieVaincue() || !suivant) {
            std::cout << "Toute l'equipe est K.O. ! Defaite..." << std::endl;
            manager.changeState(std::make_unique<GameOverState>(manager));
        } else {
            std::cout << suivant->getNom() << " entre au combat !" << std::endl;
            chargerSprites(); // recharge le sprite/texte pour le nouveau combattant
            infoText.setString(suivant->getNom() + " VS " + adversaire->getNom() + "   [A = attaquer]");
        }
    }
}

void CombatState::update(float deltaTime) {
    (void)deltaTime;
}

void CombatState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(90, 30, 30));
    window.draw(infoText);

    window.draw(spriteGaugeJoueur);
    window.draw(spriteGaugeAdversaire);
    window.draw(barreVieJoueur);
    window.draw(barreVieAdversaire);
    window.draw(spriteJoueur);
    window.draw(spriteAdversaire);
    window.draw(spriteVs);
}
