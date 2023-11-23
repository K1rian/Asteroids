#pragma once

#include <SFML/Graphics.hpp>

class text {
public:
    int tama�o = 25;
    sf::Color color = sf::Color::White;
    sf::Font fontObject;
    std::string font = "Roboto_Mono";

    text() {
        if (!fontObject.loadFromFile(font + ".ttf")) {
            throw std::runtime_error("Error al cargar la fuente");
        }
    }
};