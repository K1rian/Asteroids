#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Asteroid {
public:
    Asteroid(float x, float y) : x(x), y(y) {
        shape.setPointCount(8);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2);
        shape.setRadius(20);
        shape.setPosition(x, y);
    }

    sf::CircleShape shape;
    float x, y;
};