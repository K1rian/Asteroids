#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Bullet {
public:
    Bullet(float x, float y, float angle) : x(x), y(y), angle(angle) {
        shape.setRadius(3);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Cyan);
        shape.setOutlineThickness(1);
        shape.setPosition(x, y);
    }

    void update() {
        float angleRad = angle * 3.14159265 / 180;
        float moveX = std::sin(angleRad) * 10.0f;
        float moveY = -std::cos(angleRad) * 10.0f;
        x += moveX;
        y += moveY;
        shape.setPosition(x, y);
    }

    sf::CircleShape shape;
    float x, y;
    float angle;
};