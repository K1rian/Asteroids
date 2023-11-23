/*               ---Contexto de proyecto---

    Astreroids fue un videojuego arcade basado en vectores
    lanzado en 1979 por Atari, desde ahi han salido versiones
    que le ponen vas mecanicas y muchos colores y francamente
    se perdio el estilo, en este proyecto trato de recrear el
    antiguo juego, con un pequeño toque de color porque se
    puede.

*/

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <random>
#include <iostream>

const double SCREEN_WIDTH = 800;
const double SCREEN_HEIGHT = 600;

#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Text.h"

int main() {
    int score = 0;
    std::vector<Asteroid> asteroids;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids");

    Ship playerShip(SCREEN_WIDTH, SCREEN_HEIGHT);

    text coordinatesText;
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(coordinatesText.color);
    coordinatesText.setPosition(10.0, 550.0);

    text scoreText;
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(scoreText.color);
    scoreText.setPosition(10.0, 10.0);

    text collisionText;
    collisionText.setCharacterSize(25);
    collisionText.setFillColor(collisionText.color);
    collisionText.setPosition(SCREEN_WIDTH - 150.0, 10.0);

    text gameText
    gameText.setCharacterSize(40);
    gameText.setFillColor(gameText.color);
    gameText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    sf::Clock asteroidSpawnClock;

    while (window.isOpen()) {
        sf::Event event;
        const int MAX_COLLISIONS = 3;
        bool collisionOccurred = false;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerShip.accelerate();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerShip.rotateLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerShip.rotateRight();
        }
        else {
            playerShip.decelerate();
        }

        playerShip.move();
        playerShip.update(window);
        playerShip.hitbox.update(playerShip.getX(), playerShip.getY());

        for (auto& asteroid : asteroids) {
            asteroid.update();
        }

        if (asteroidSpawnClock.getElapsedTime().asSeconds() > 2.0) {
            double asteroidVelocity = static_cast<double>(rand() % 2 + 1)/10;
            double asteroidX = static_cast<double>(rand() % static_cast<int>(SCREEN_WIDTH - 50));
            double asteroidY = 0;
            double directionX = static_cast<double>(rand() % 200 - 100) / 100.0f;
            double directionY = static_cast<double>(rand() % 200 - 100) / 100.0f;

            double minSize = 10.0;
            double maxSize = 50.0;
            double asteroidSize = minSize + (maxSize - minSize) * (rand() / (RAND_MAX + 1.0));

            asteroids.emplace_back(asteroidX, asteroidY, asteroidVelocity, directionX, directionY, asteroidSize);
            asteroidSpawnClock.restart();
        }

        std::ostringstream oss;
        oss << "X: " << std::fixed << std::setprecision(2) << playerShip.getX()
            << "\nY: " << std::fixed << std::setprecision(2) << playerShip.getY();

        coordinatesText.setString(oss.str());

        playerShip.bullets.erase(std::remove_if(playerShip.bullets.begin(), playerShip.bullets.end(),
            [&](const Bullet& bullet) { return bullet.isOutsideWindow(window); }),
            playerShip.bullets.end());

        // Vector para almacenar los índices de los asteroides que deben eliminarse
        std::vector<size_t> asteroidsToRemove;

        for (size_t i = 0; i < asteroids.size(); ++i) {
            for (const auto& bullet : playerShip.bullets) {
                if (asteroids[i].checkCollision(bullet.position, bullet.shape.getRadius())) {
                    asteroidsToRemove.push_back(i);
                    score += 100;
                    break;  // Sal del bucle interno para evitar colisiones duplicadas
                }
            }
        }

        // Elimina los asteroides marcados para eliminación
        for (auto it = asteroidsToRemove.rbegin(); it != asteroidsToRemove.rend(); ++it) {
            asteroids.erase(asteroids.begin() + *it);
        }

        for (auto it = asteroids.begin(); it != asteroids.end();) {
            if (playerShip.checkCollision(sf::Vector2f(it->getX(), it->getY()), it->getSize())) {
                collisionOccurred = true;
                std::cout << "Collision detected!" << std::endl;

                // Marcamos el asteroide para su eliminación
                it = asteroids.erase(it);
                playerShip.incrementCollisionCount();
            }
            else {
                ++it;  // Solo incrementa si no hay colisión
            }
        }

        if (collisionOccurred) {
            playerShip.incrementCollisionCount();  // Incrementa el contador de colisiones
            if (playerShip.getCollisionCount() >= MAX_COLLISIONS) {
                std::cout << "Game Over!" << std::endl;
                window.close();
            }
        }

        // Muestra la cantidad de colisiones en pantalla
        std::ostringstream collisionString;
        collisionString << "Collisions: " << playerShip.getCollisionCount();
        collisionText.setString(collisionString.str());

        window.clear();
        window.draw(playerShip.shape);
        window.draw(coordinatesText);
        window.draw(collisionText);

        std::ostringstream scoreString;
        scoreString << "Score: " << score;
        scoreText.setString(scoreString.str());
        window.draw(scoreText);

        for (const auto& bullet : playerShip.bullets) {
            window.draw(bullet.shape);
        }

        for (const auto& asteroid : asteroids) {
            window.draw(asteroid.getShape());
        }

        window.display();
    }

    return 0;
}
