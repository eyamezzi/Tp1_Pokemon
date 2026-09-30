#include "../Inc/GameStateManager.h"

GameStateManager::GameStateManager(Pokedex* pokedex) : pokedex(pokedex) {
}

void GameStateManager::changeState(std::unique_ptr<GameState> newState) {
    nextState = std::move(newState);
}

void GameStateManager::applyPendingChange() {
    if (nextState) {
        if (currentState) currentState->onExit();
        currentState = std::move(nextState);
        currentState->onEnter();
    }
}

void GameStateManager::handleEvent(const sf::Event& event) {
    if (currentState) currentState->handleEvent(event);
}

void GameStateManager::update(float deltaTime) {
    if (currentState) currentState->update(deltaTime);
}

void GameStateManager::render(sf::RenderWindow& window) {
    if (currentState) currentState->render(window);
}

bool GameStateManager::hasState() const {
    return currentState != nullptr;
}

Pokedex& GameStateManager::getPokedex() { return *pokedex; }
PokemonParty& GameStateManager::getParty() { return party; }
PokemonAttack& GameStateManager::getAttack() { return attack; }

Pokemon* GameStateManager::getCombattantActuel() {
    for (size_t i = combattantIndex; i < attack.getNombrePokemons(); ++i) {
        Pokemon* p = attack.getPokemonAt(i);
        if (p && p->getPvActual() > 0) {
            combattantIndex = i;
            return p;
        }
    }
    return nullptr;
}

void GameStateManager::combattantSuivant() {
    combattantIndex++;
}

bool GameStateManager::toutePartieVaincue() {
    for (size_t i = 0; i < attack.getNombrePokemons(); ++i) {
        const Pokemon* p = attack.getPokemonAt(i);
        if (p && p->getPvActual() > 0) return false;
    }
    return true;
}

void GameStateManager::resetCombatIndex() {
    combattantIndex = 0;
}