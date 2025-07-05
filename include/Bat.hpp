#pragma once
#include <SFML/Graphics.hpp>

class Bat {
private:
    sf::Vector2f m_Position;
    sf::RectangleShape m_Shape;
    float m_Speed = 1000.0f;
    bool m_MovingRight = false;
    bool m_MovingLeft = false;

public:
    Bat(float startX, float startY);
    sf::FloatRect getPosition() const;
    const sf::RectangleShape& getShape() const;
    sf::FloatRect getGlobalBounds() const;
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void update(sf::Time dt);
};
