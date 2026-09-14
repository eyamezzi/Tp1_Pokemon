//
// Created by mezzi on 14/09/2026.
//

#include "../Inc/Pokedex.h"
#include<iostream>
#include <fstream>
#include <sstream>
using namespace std;
Pokedex* Pokedex::instance = nullptr;

Pokedex::Pokedex(const string& csvFile) {
    try {
        ifstream file(csvFile);

        if (!file.is_open()) {
            throw runtime_error("Impossible d'ouvrir le fichier : " + csvFile);
        }

        string line;
        getline(file, line); // Ignorer l'en-tête

        while (getline(file, line)) {
            stringstream ss(line);
            string cell;
            vector<string> data;

            while (getline(ss, cell, ',')) {
                data.push_back(cell);
            }

            // Vérification minimale
            if (data.size() < 12) {
                throw runtime_error("Ligne CSV invalide : " + line);
            }

            int numero     = stoi(data[0]);
            string nom     = data[1];
            int pvMax      = stoi(data[5]);
            int attaque    = stoi(data[6]);
            int defense    = stoi(data[7]);
            int evolution  = stoi(data[11]);

            Pokemon p(numero, nom, pvMax, attaque, defense, evolution);
            listePockemons.push_back(p);
        }
    }
    catch (const exception& e) {
        cerr << "[ERREUR POKEDEX]" << e.what() << endl;
    }
}

Pokedex* Pokedex::getInstance(const std::string& csvFile) {
    if (!instance)
        instance = new Pokedex(csvFile);
    return instance;
}
void Pokedex::ajouterPokemon(const Pokemon& p) {
    listePockemons.push_back(p);
}

Pokemon* Pokedex::getPokemonByNumero(int numero) {
    for (auto& p : listePockemons) {
        if (p.getNumero() == numero)
            return new Pokemon(p); // clone de pokemon
    }
    return nullptr;
}

Pokemon* Pokedex::getPokemonByNom(const string& nom) {
    for (auto& p : listePockemons) {
        if (p.getNom() == nom)
            return new Pokemon(p); // clone de pokemon
    }
    return nullptr;
}
