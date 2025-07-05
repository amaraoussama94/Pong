#include "Bat.hpp"

Bat::Bat(float startX, float startY)
    : m_Position(startX, startY)
{
    m_Shape.setSize(sf::Vector2f(50.f, 5.f));
    m_Shape.setPosition(m_Position);
}

sf::FloatRect Bat::getPosition() const {
    return m_Shape.getGlobalBounds();
}

const sf::RectangleShape& Bat::getShape() const {
    return m_Shape;
}

void Bat::moveLeft() {
    m_MovingLeft = true;
}

void Bat::moveRight() {
    m_MovingRight = true;
}

void Bat::stopLeft() {
    m_MovingLeft = false;
}

void Bat::stopRight() {
    m_MovingRight = false;
}

void Bat::update(sf::Time dt) {
    if (m_MovingLeft)
        m_Position.x -= m_Speed * dt.asSeconds();
    if (m_MovingRight)
        m_Position.x += m_Speed * dt.asSeconds();

    m_Shape.setPosition(m_Position);
}
