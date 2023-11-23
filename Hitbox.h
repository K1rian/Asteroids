#pragma once

#include <SFML/Graphics.hpp>

class Hitbox {
public:
    Hitbox(double x, double y, double width, double height);

    void update(double x, double y);

    bool checkCollision(const sf::Vector2f& asteroidPosition, float asteroidRadius) const;

private:
    sf::FloatRect hitbox;
};

Hitbox::Hitbox(double x, double y, double width, double height)
    : hitbox(x, y, width, height) {}

void Hitbox::update(double x, double y) {
    hitbox.left = static_cast<float>(x);
    hitbox.top = static_cast<float>(y);
}

bool Hitbox::checkCollision(const sf::Vector2f& asteroidPosition, float asteroidRadius) const {
    sf::Vector2f hitboxCenter(hitbox.left + hitbox.width / 2.0f, hitbox.top + hitbox.height / 2.0f);
    float distanceSquared = std::pow(hitboxCenter.x - asteroidPosition.x, 2) +
        std::pow(hitboxCenter.y - asteroidPosition.y, 2);
    float collisionThresholdSquared = std::pow(std::max(hitbox.width, hitbox.height) / 2.0f + asteroidRadius, 2);
    return distanceSquared < collisionThresholdSquared;
}
