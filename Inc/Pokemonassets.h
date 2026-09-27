#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// Construit le chemin vers l'image d'un Pokemon à partir de son numéro.
// Format confirmé : 1.png, 2.png, 3.png ... (pas de zéro de remplissage).
inline std::string getPokemonImagePath(int numero) {
    return "data/image_pokedex-20260914/pokemon/" + std::to_string(numero) + ".png";
}

// Chemin de l'image "inconnue" (0.png), utilisée en repli si le sprite
// d'un numéro précis est introuvable.
inline std::string getUnknownPokemonImagePath() {
    return "data/image_pokedex-20260914/pokemon/0.png";
}

