
//
// GameStateManager.cpp
//

#include "../Inc/GameStateManager.h"

GameStateManager::GameStateManager(Pokedex* pokedex)
    : currentState(nullptr), pokedex(pokedex), indexCombattantActuel(0)
{
}

void GameStateManager::changeState(std::unique_ptr<GameState> newState) {
    if (currentState) {
        currentState->onExit();
    }

    currentState = std::move(newState);

    if (currentState) {
        currentState->onEnter();
    }
}

void GameStateManager::handleEvent(const sf::Event& event) {
    if (currentState) {
        currentState->handleEvent(event);
    }
}

void GameStateManager::update(float deltaTime) {
    if (currentState) {
        currentState->update(deltaTime);
    }
}

void GameStateManager::render(sf::RenderWindow& window) {
    if (currentState) {
        currentState->render(window);
    }
}

Pokedex& GameStateManager::getPokedex() {
    return *pokedex;
}

PokemonParty& GameStateManager::getParty() {
    return party;
}

PokemonAttack& GameStateManager::getAttackTeam() {
    return attackTeam;
}

Pokemon* GameStateManager::getCombattantActuel() {
    // Initialisation paresseuse : la première fois qu'on a besoin d'un
    // combattant, on clone l'équipe d'attaque choisie par le joueur.
    if (equipeVivante.empty() && attackTeam.getNombrePokemons() > 0) {
        for (const auto& p : attackTeam.getPokemons()) {
            equipeVivante.push_back(std::make_unique<Pokemon>(p));
        }
        indexCombattantActuel = 0;
    }

    // Saute les Pokemon déjà K.O. pour trouver le prochain combattant valide
    while (indexCombattantActuel < equipeVivante.size() &&
           equipeVivante[indexCombattantActuel]->getPvActual() <= 0) {
        ++indexCombattantActuel;
    }

    if (indexCombattantActuel >= equipeVivante.size()) {
        return nullptr; // toute l'équipe est K.O.
    }

    return equipeVivante[indexCombattantActuel].get();
}

bool GameStateManager::toutePartieVaincue() const {
    if (equipeVivante.empty()) {
        return false; // équipe pas encore engagée, pas de défaite à déclarer
    }
    for (const auto& p : equipeVivante) {
        if (p->getPvActual() > 0) {
            return false;
        }
    }
    return true;
}
