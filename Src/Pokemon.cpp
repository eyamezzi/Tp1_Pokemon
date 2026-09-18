//
// Created by mezzi on 14/09/2026.
//

#include "../Inc/Pokemon.h"
#include <iostream>
Pokemon::Pokemon(int numero,
                 const std::string& nom,
                 int pvMax,
                 int attaque,
                 int defense,
                 int evolution)
    : numero(numero),
      nom(nom),
      pvMax(pvMax),
      pvActuel(pvMax),
      attaque(attaque),
      defense(defense),
      evolution(evolution)
{
}

Pokemon::~Pokemon() {
}

void Pokemon::attaquer(Pokemon& target) {
    int diff = attaque - target.defense;

    if (diff < 0)
        diff = 0;

    target.pvActuel -= diff;

    if (target.pvActuel < 0)
        target.pvActuel = 0;


    if (target.pvActuel == 0)
        std::cout << target.nom << " est Knock Out" << std::endl;
}

void Pokemon::displayInfo() const {
    std::cout << "Pokemon #" << numero << " - " << nom << std::endl;
    std::cout << "PV : " << pvActuel << "/" << pvMax << std::endl;
    std::cout << "Attaque : " << attaque << " | Défense : " << defense << std::endl;
    std::cout << "Evolution : " << evolution << std::endl;
}
int Pokemon::getNumero() const { return numero; }
const std::string& Pokemon::getNom() const { return nom; }
double Pokemon::getEvolution() const { return evolution; }
double Pokemon::getAttack() const { return attaque; }
double Pokemon::getDefense() const { return defense; }
int Pokemon::getPvActual() const { return pvActuel; }
int Pokemon::getPvMax() const { return pvMax; }
