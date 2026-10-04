#include "../Inc/CombatState.h"
#include "../Inc/GameStateManager.h"
#include "../Inc/RandomState.h"
#include "../Inc/GameOverState.h"
#include <cstdlib>
#include <iostream>

CombatState::CombatState(GameStateManager& manager) : GameState(manager) {
}

void CombatState::chargerSprites() {
    for (auto& duel : duels) {
        std::string pathCombattant = "data/image_pokedex-20260914/pokemon/" +
                                      std::to_string(duel.combattant->getNumero()) + ".png";
        if (duel.combattantTexture.loadFromFile(pathCombattant)) {
            duel.combattantSprite.setTexture(duel.combattantTexture);
            sf::FloatRect b = duel.combattantSprite.getLocalBounds();
            duel.combattantSprite.setOrigin(b.width / 2.f, b.height / 2.f);
            duel.combattantSprite.setScale(1.f, 1.f);
        }

        std::string pathAdversaire = "data/image_pokedex-20260914/pokemon/" +
                                      std::to_string(duel.adversaire->getNumero()) + ".png";
        if (duel.adversaireTexture.loadFromFile(pathAdversaire)) {
            duel.adversaireSprite.setTexture(duel.adversaireTexture);
            sf::FloatRect b = duel.adversaireSprite.getLocalBounds();
            duel.adversaireSprite.setOrigin(b.width / 2.f, b.height / 2.f);
            duel.adversaireSprite.setScale(1.f, 1.f);
        }

        duel.glowLeft.setRadius(55.f);
        duel.glowLeft.setOrigin(55.f, 55.f);
        duel.glowLeft.setFillColor(sf::Color(50, 120, 220, 110));

        duel.glowRight.setRadius(55.f);
        duel.glowRight.setOrigin(55.f, 55.f);
        duel.glowRight.setFillColor(sf::Color(220, 40, 40, 110));

        duel.vsLabel.setFont(font);
        duel.vsLabel.setString(duel.combattant->getNom() + " VS " + duel.adversaire->getNom());
        duel.vsLabel.setCharacterSize(11);
        duel.vsLabel.setFillColor(sf::Color::White);
        sf::FloatRect vb = duel.vsLabel.getLocalBounds();
        duel.vsLabel.setOrigin(vb.width / 2.f, 0.f);
    }
}

void CombatState::positionnerDuels() {
    size_t n = duels.size();
    if (n == 0) return;

    float columnWidth = 800.f / static_cast<float>(n);

    for (size_t i = 0; i < n; ++i) {
        float cx = columnWidth * i + columnWidth / 2.f;

        duels[i].glowLeft.setPosition(cx - 35.f, 250.f);
        duels[i].glowRight.setPosition(cx + 35.f, 250.f);

        duels[i].combattantSprite.setPosition(cx - 35.f, 250.f);
        duels[i].adversaireSprite.setPosition(cx + 35.f, 250.f);

        duels[i].vsLabel.setPosition(cx, 340.f);
    }
}

void CombatState::onEnter() {
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    background.setPrimitiveType(sf::Quads);
    background.resize(4);
    sf::Color topColor(20, 25, 50);
    sf::Color bottomColor(5, 5, 10);
    background[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), topColor);
    background[1] = sf::Vertex(sf::Vector2f(800.f, 0.f), topColor);
    background[2] = sf::Vertex(sf::Vector2f(800.f, 600.f), bottomColor);
    background[3] = sf::Vertex(sf::Vector2f(0.f, 600.f), bottomColor);

    duels.clear();
    auto& attack = manager.getAttack();
    int maxNumero = static_cast<int>(manager.getPokedex().getNombrePokemons());

    if (maxNumero == 0 || attack.getNombrePokemons() == 0) {
        std::cerr << "[CombatState] Pokedex ou Attack vide, retour a l'accueil." << std::endl;
        manager.changeState(std::make_unique<RandomState>(manager));
        return;
    }

    for (size_t i = 0; i < attack.getNombrePokemons(); ++i) {
        Duel duel;
        duel.combattant = attack.getPokemonAt(i);
        int numero = (std::rand() % maxNumero) + 1;
        duel.adversaire.reset(manager.getPokedex().getPokemonByNumero(numero));

        if (!duel.adversaire) continue;

        duels.push_back(std::move(duel));
    }

    if (duels.empty()) {
        manager.changeState(std::make_unique<RandomState>(manager));
        return;
    }

    chargerSprites();
    positionnerDuels();

    titleText.setFont(font);
    titleText.setString("Combats en cours");
    titleText.setCharacterSize(20);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect tb = titleText.getLocalBounds();
    titleText.setOrigin(tb.width / 2.f, 0.f);
    titleText.setPosition(400.f, 30.f);

    buttonColorNormal = sf::Color(50, 120, 220);
    buttonColorHover = sf::Color(70, 150, 255);

    resultButton.setSize({220.f, 55.f});
    resultButton.setFillColor(buttonColorNormal);
    resultButton.setOutlineThickness(2.f);
    resultButton.setOutlineColor(sf::Color::White);
    resultButton.setOrigin(110.f, 27.5f);
    resultButton.setPosition(400.f, 530.f);

    resultButtonText.setFont(font);
    resultButtonText.setString("Voir le resultat");
    resultButtonText.setCharacterSize(10);
    resultButtonText.setFillColor(sf::Color::White);

    sf::FloatRect bb = resultButtonText.getLocalBounds();

    resultButtonText.setOrigin(
        bb.left + bb.width / 2.f,
        bb.top + bb.height / 2.f
    );

    resultButtonText.setPosition(400.f, 530.f);


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

bool CombatState::isMouseOverButton(const sf::Vector2f& mousePos) const {
    return resultButton.getGlobalBounds().contains(mousePos);
}

void CombatState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x),
                               static_cast<float>(event.mouseMove.y));
        resultButton.setFillColor(isMouseOverButton(mousePos) ? buttonColorHover : buttonColorNormal);
    }

    if (event.type != sf::Event::MouseButtonPressed) return;
    if (event.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x),
                           static_cast<float>(event.mouseButton.y));

    if (!resultatsAffiches) {
        if (isMouseOverButton(clickPos)) {
            resultTexts.clear();
            float y = 420.f;

            for (auto& duel : duels) {
                resoudreDuel(duel);
                std::string msg = duel.combattant->getNom() + " vs " +
                                   duel.adversaire->getNom() + " : " +
                                   (duel.gagne ? "GAGNE" : "PERDU");
                sf::Text t(msg, font, 14);
                t.setFillColor(duel.gagne ? sf::Color(100, 220, 100) : sf::Color(220, 80, 80));
                sf::FloatRect b = t.getLocalBounds();
                t.setOrigin(b.width / 2.f, 0.f);
                t.setPosition(400.f, y);
                y += 28.f;
                resultTexts.push_back(t);

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
    window.draw(background);
    window.draw(titleText);

    if (!resultatsAffiches) {
        for (auto& duel : duels) {
            window.draw(duel.glowLeft);
            window.draw(duel.glowRight);
            window.draw(duel.combattantSprite);
            window.draw(duel.adversaireSprite);
            window.draw(duel.vsLabel);
        }
        window.draw(resultButton);
        window.draw(resultButtonText);
    } else {
        for (auto& t : resultTexts) window.draw(t);

        sf::Text continueText("Cliquez pour continuer", font, 12);
        continueText.setFillColor(sf::Color(150, 150, 150));
        sf::FloatRect b = continueText.getLocalBounds();
        continueText.setOrigin(b.width / 2.f, 0.f);
        continueText.setPosition(400.f, 560.f);
        window.draw(continueText);
    }
}