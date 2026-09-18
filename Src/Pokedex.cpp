#include "../Inc/Pokedex.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

Pokedex* Pokedex::instance = nullptr;

Pokedex::Pokedex(const std::string& csvFile) {
    try {
        std::ifstream file(csvFile);

        if (!file.is_open()) {
            throw std::runtime_error(
                "Impossible d'ouvrir le fichier : " + csvFile
            );
        }

        std::string line;

        // Ignorer l'en-tête
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            std::vector<std::string> data;

            while (std::getline(ss, cell, ',')) {
                data.push_back(cell);
            }

            if (data.size() < 12) {
                throw std::runtime_error(
                    "Ligne CSV invalide : " + line
                );
            }

            int numero = std::stoi(data[0]);
            std::string nom = data[1];
            int pvMax = std::stoi(data[5]);
            int attaque = std::stoi(data[6]);
            int defense = std::stoi(data[7]);
            int evolution = std::stoi(data[11]);

            Pokemon p(
                numero,
                nom,
                pvMax,
                attaque,
                defense,
                evolution
            );

            getListePokemons().push_back(p);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[ERREUR POKEDEX] "
                  << e.what()
                  << std::endl;
    }
}


Pokedex* Pokedex::getInstance(const std::string& csvFile) {
    if (instance == nullptr) {
        instance = new Pokedex(csvFile);
    }

    return instance;
}


void Pokedex::ajouterPokemon(const Pokemon& p) {
    getListePokemons().push_back(p);
}


Pokemon* Pokedex::getPokemonByNumero(int numero) {
    for (auto& p : getListePokemons()) {
        if (p.getNumero() == numero) {
            return new Pokemon(p);
        }
    }

    return nullptr;
}


Pokemon* Pokedex::getPokemonByNom(const std::string& nom) {
    for (auto& p : getListePokemons()) {
        if (p.getNom() == nom) {
            return new Pokemon(p);
        }
    }

    return nullptr;
}