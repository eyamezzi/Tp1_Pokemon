//
// Created by mezzi on 14/09/2026.
//
#include "../Inc/PockemonVector.h"

#include <iostream>

void PokemonVector::afficherListePockemon() const {
    std::cout << "===== Liste des Pokemon =====" << std::endl;

    for (const Pokemon& p : listePockemons) {
       p.displayInfo();
        std::cout << "-----------------------------" << std::endl;
    }
}