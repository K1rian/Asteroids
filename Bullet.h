#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <tuple>

class Bullet {
public:
    // bala pequeña redonda
    Bullet(float x, float y, float angle) : position(x, y), angle(angle) {
        shape.setRadius(BULLET_RADIUS);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Cyan);
        shape.setOutlineThickness(1);
        shape.setPosition(position);
    }

    void update() {
        float angleRad = angle * 3.14159265 / 180;
        sf::Vector2f movement(std::sin(angleRad) * BULLET_SPEED, -std::cos(angleRad) * BULLET_SPEED);
        position += movement;
        shape.setPosition(position);
    }

    bool isOutsideWindow(const sf::RenderWindow& window) const {
        return position.x < 0 || position.x > window.getSize().x || position.y < 0 || position.y > window.getSize().y;
    }
    bool operator==(const Bullet& other) const {
        return std::tie(position, angle) == std::tie(other.position, other.angle);
    }
    sf::CircleShape shape;
    sf::Vector2f position;
    float angle;

private:
    static constexpr float BULLET_SPEED = 0.08f; 
    static constexpr float BULLET_RADIUS = 4.5f;
};
