#pragma once

#include <SFML/Graphics.hpp>
#include <random>

extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;

class Asteroid {
public:
    // octagono transparente con outline amarillo
    Asteroid(float x, float y, float velocity, float directionX, float directionY, float size)
        : x(x), y(y), velocity(velocity), directionX(directionX), directionY(directionY), size(size) {
        shape.setRadius(size);
        shape.setPointCount(8);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Yellow);
        shape.setOutlineThickness(2);
        shape.setPosition(x, y);
    }

    bool checkCollision(const sf::Vector2f& bulletPosition, float bulletRadius);

    bool operator==(const Asteroid& other) const;

    void update();

    const sf::CircleShape& getShape() const {
        return shape;
    }
    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getSize() const {
        return size;
    }

private:
    float x, y, velocity;
    float directionX, directionY;
    sf::CircleShape shape;
    float size;
};

bool Asteroid::checkCollision(const sf::Vector2f& bulletPosition, float bulletRadius) {
    float distance = std::sqrt(std::pow(x - bulletPosition.x, 2) + std::pow(y - bulletPosition.y, 2));
    return distance < (size + bulletRadius);
}

bool Asteroid::operator==(const Asteroid& other) const {
    return std::tie(x, y, velocity, directionX, directionY) == std::tie(other.x, other.y, other.velocity, other.directionX, other.directionY);
} 

void Asteroid::update() {
    static std::mt19937 mt(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-0.05, 0.05);

    // Actualiza la dirección solo cada cierto tiempo
    static sf::Clock directionUpdateClock;
    if (directionUpdateClock.getElapsedTime().asSeconds() > 1.0) {
        directionX = dist(mt);
        directionY = dist(mt);
        directionUpdateClock.restart();
    }

    x += velocity * directionX;
    y += velocity * directionY;

    if (x < 0) {
        x = 0;
        directionX = std::abs(directionX);  // Invierte la dirección en X
    }
    else if (x > SCREEN_WIDTH - 2 * shape.getRadius()) {
        x = SCREEN_WIDTH - 2 * shape.getRadius();
        directionX = -std::abs(directionX);  // Invierte la dirección en X
    }

    if (y < 0) {
        y = 0;
        directionY = std::abs(directionY);  // Invierte la dirección en Y
    }
    else if (y > SCREEN_HEIGHT - 2 * shape.getRadius()) {
        y = SCREEN_HEIGHT - 2 * shape.getRadius();
        directionY = -std::abs(directionY);  // Invierte la dirección en Y
    }

    shape.setPosition(x, y);
}
