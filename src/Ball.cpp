#include "Ball.hpp"

Ball::Ball(float startX, float startY)
    : m_Position(startX, startY)
{
    m_Shape.setSize(sf::Vector2f(10.f, 10.f));
    m_Shape.setPosition(m_Position);
}

sf::FloatRect Ball::getGlobalBounds() const {
    return m_Shape.getGlobalBounds();
}

sf::FloatRect Ball::getPosition() const {
    return m_Shape.getGlobalBounds();
}

const sf::RectangleShape& Ball::getShape() const {
    return m_Shape;
}

float Ball::getXVelocity() const {
    return m_DirectionX;
}

void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop() {
    m_DirectionY = -m_DirectionY;
}

void Ball::reboundBottom() {
    m_Position = {500.f, 100.f};
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
}

void Ball::reboundBatOrTopMultiplayer() {
    m_Position = {500.f, 100.f};
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
}

void Ball::update(sf::Time dt) {
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}
