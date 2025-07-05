#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::Vector2f m_Position;
    sf::RectangleShape m_Shape;
    float m_Speed = 1000.0f;
    float m_DirectionX = 0.2f;
    float m_DirectionY = 0.2f;

public:
    Ball(float startX, float startY);
    sf::FloatRect getPosition() const;
    const sf::RectangleShape& getShape() const;
    sf::FloatRect getGlobalBounds() const;
    float getXVelocity() const;
    void reboundSides();
    void reboundBatOrTop();
    void reboundBatOrTopMultiplayer();
    void reboundBottom();
    void update(sf::Time dt);
};
