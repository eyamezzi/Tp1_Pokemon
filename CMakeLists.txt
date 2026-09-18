cmake_minimum_required(VERSION 3.21)
project(Tp1)

set(CMAKE_CXX_STANDARD 20)

# Chemin vers SFML
set(SFML_DIR "C:/Users/mezzi/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

add_executable(Tp1
        src/main.cpp
        Src/Pokemon.cpp
        Inc/Pokemon.h
        Src/PokemonVector.cpp
        Inc/PokemonVector.h
        Src/Pokedex.cpp
        Inc/Pokedex.h
        Src/Pokemon_Party.cpp
        Inc/Pokemon_Party.h
        Src/Pokemon_Attack.cpp
        Inc/Pokemon_Attack.h
)
target_link_libraries(Tp1
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
)
