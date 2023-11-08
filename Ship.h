#include <SFML/Graphics.hpp>

const double SHIP_SPEED = 0.08;

class Ship {
public:
    // Obtener coodenadas en main
    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }
    Ship(double screenWidth, double screenHeight)
        : angle(0.0), x(screenWidth / 2.0), y(screenHeight / 2.0), speed(0.0),
        acceleration(0.2), rotationSpeed(0.07), SCREEN_WIDTH(screenWidth), SCREEN_HEIGHT(screenHeight) {

        // Triangulo nave con outline azul *astretic*
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(-10.0, 10.0));
        shape.setPoint(1, sf::Vector2f(0.0, -10.0));
        shape.setPoint(2, sf::Vector2f(10.0, 10.0));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(3);
        shape.setPosition(static_cast<float>(x), static_cast<float>(y));

    };

    // Mover nave
    void move() {
        double angleRad = angle * 3.14159265 / 180.0;
        double moveX = std::sin(angleRad) * speed;
        double moveY = -std::cos(angleRad) * speed;

        x += moveX;
        y += moveY;

        // No salir de pantalla
        if (x < 0.0) {
            x = 0.0;
            speed = 0.0;
        }
        if (x > SCREEN_WIDTH) {
            x = SCREEN_WIDTH;
            speed = 0.0;
        }
        if (y < 0.0) {
            y = 0.0;
            speed = 0.0;
        }
        if (y > SCREEN_HEIGHT) {
            y = SCREEN_HEIGHT;
            speed = 0.0;
        }

        shape.setPosition(static_cast<double>(x), static_cast<double>(y));

        shape.setRotation(static_cast<double>(angle));
    }

    void setAngle(double newAngle) {
        angle = newAngle;
    }

    void accelerate() {
        speed += acceleration;
        if (speed > SHIP_SPEED) {
            speed = SHIP_SPEED;
        }
    }

    void decelerate() {
        speed -= acceleration;
        if (speed < 0.0) {
            speed = 0.0;
        }
    }

    void rotateLeft() {
        angle -= rotationSpeed;
    }

    void rotateRight() {
        angle += rotationSpeed;
    }

    sf::ConvexShape shape;
    double angle;
    double x, y;
    double speed;
    double acceleration;
    double rotationSpeed;
    double SCREEN_WIDTH;
    double SCREEN_HEIGHT;

};
