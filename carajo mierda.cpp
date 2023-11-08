
/*    ---Agarrese porque me dio la esquizofrenia y cañon---
 
    Astreroids fue un videojuego arcade basado en vectores 
    lanzado en 1979 por Atari, desde ahi han salido versiones
    que le ponen vas mecanicas y muchos colores y francamente 
    se perdio el estilo, en este proyecto trato de recrear el 
    antiguo juego, con un pequeño toque de color porque se 
    puede

*/

// el mugre SFML que se batallo para instalar
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
// Archivos .h, personalisados
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"

// Pantalla (modificar despues)
const double SCREEN_WIDTH = 800;
const double SCREEN_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Asteroids");

    Ship playerShip(SCREEN_WIDTH, SCREEN_HEIGHT);

    sf::Font font;
    if (!font.loadFromFile("Roboto_Mono.ttf")) {  // Si la fuente no sirve
        return 1;
    }

    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10.0, 10.0);

    // Mientras juego abierto
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // teclas arriba, left y right (medio raro pero asi me salio XD)
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

        // Actualiza la nave
        playerShip.move();

        // Redondea las coordenadas a 2 decimales
        std::ostringstream oss;
        oss << "X: " << std::fixed << std::setprecision(2) << playerShip.getX()
            << "\nY: " << std::fixed << std::setprecision(2) << playerShip.getY();

        coordinatesText.setString(oss.str());

        window.clear();
        window.draw(playerShip.shape); // Dibuja la nave
        window.draw(coordinatesText); // Dibuja coodinadas
        window.display();
    }

    return 0;
}
