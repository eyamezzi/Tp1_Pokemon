#  Tp1_Pokemon

Projet réalisé dans le cadre du TP n°1 — *Introduction à la programmation orientée objet en C++*.

Ce projet implémente un **sélecteur de Pokémon** en C++17 avec le framework **SFML**, ainsi qu'un moteur de jeu basé sur le **design pattern State**.

## Sommaire

- [Aperçu](#aperçu)
- [Fonctionnalités](#fonctionnalités)
- [Architecture](#architecture)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Structure du projet](#structure-du-projet)
- [Auteurs](#auteurs)

## Aperçu

<!-- TODO: ajoutez ici 1-2 phrases décrivant le jeu (mode texte ou graphique) et éventuellement une capture d'écran -->

Le projet permet de :
- Charger un Pokédex de référence à partir d'un fichier CSV.
- Constituer une équipe de Pokémon (`Pokemon_Party`) sans limite de taille.
- Sélectionner jusqu'à 6 Pokémon pour combattre (`Pokemon_Attack`).
- Faire évoluer le joueur à travers différents états de jeu (accueil, exploration, capture, combat, game over).

## Fonctionnalités

- **Classe `Pokemon`** : numéro, nom, évolution, PV max/actuels, attaque, défense, et une méthode d'attaque avec une règle de jeu personnalisée.
- **Classe abstraite `Pokemon_Vector`** : base commune pour toute collection de Pokémon.
- **Classe `Pokedex`** (Singleton) : référence complète de tous les Pokémon disponibles, lue depuis un fichier CSV ; expose uniquement des clones, les données internes restent inaccessibles.
- **Classe `Pokemon_Party`** : équipe du joueur, ajout/retrait libre, taille illimitée.
- **Classe `Pokemon_Attack`** : sous-ensemble de 6 Pokémon extrait de la `Pokemon_Party` pour le combat, avec réintégration possible.
- **Interface graphique SFML** : sélection des 6 Pokémon de combat et positionnement libre dans l'équipe.
- **Moteur de jeu** basé sur le design pattern **State**, avec au minimum 5 états.

## Architecture

<!-- TODO: décrivez brièvement vos choix de conception (hiérarchie de classes, pattern State, etc.) -->

Le projet suit une architecture orientée objet avec :
- Héritage : `Pokedex`, `Pokemon_Party` et `Pokemon_Attack` héritent de `Pokemon_Vector`.
- Pattern **Singleton** pour `Pokedex`.
- Pattern **State** pour le moteur de jeu (chaque état du jeu est une classe implémentant une interface commune).

## 🧰 Prérequis

- Un compilateur C++ supportant le standard **C++17** (MinGW / MSVC via Visual Studio)
- **CMake** ≥ 3.21
- **SFML** (graphics, window, system, audio)
- **CLion** ou **Visual Studio** (recommandés sous Windows)

## 📥 Installation

### 1. Installer SFML sous Windows

### 2. Cloner le dépôt

```bash
git clone https://github.com/eyamezzi/Tp1_Pokemon.git
cd Tp1_Pokemon
```


## 📁 Structure du projet

```
Tp1_Pokemon/
│
├── 📄 CMakeLists.txt
├── 📄 README.md
├── 🗜️ image_pokedex-20260914.zip
│
├── 📂 Inc/
│   ├── 📝 Pokemon.hpp
│   ├── 📝 Pokemon_Vector.hpp
│   ├── 📝 Pokedex.hpp
│   ├── 📝 Pokemon_Party.hpp
│   └── 📝 Pokemon_Attack.hpp
│
├── 📂 Src/
│   ├── 🧩 main.cpp
│   ├── 🧩 Pokemon.cpp
│   ├── 🧩 Pokedex.cpp
│   ├── 🧩 Pokemon_Party.cpp
│   └── 🧩 Pokemon_Attack.cpp
│
└── 📂 image_pokedex-20260914/
    └── 📂 pokemon/
        ├── 🖼️ (images des Pokémon)
        └── 📊 Pokedex.csv
```

## 👤 Auteurs

- **Eya Mezzi**

---

