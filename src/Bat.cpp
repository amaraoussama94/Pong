/**
 * @file Bat.cpp
 * @brief Implementation of the Bat class, representing the player's paddle in a Pong game.
 * This class handles the bat's position, movement, and rendering.
 * @author Oussama Amara
 * @date 2025-07-27
 */

#include "Bat.hpp"
#include "Logger.hpp"

/**
 * @brief Constructs a bat at the given coordinates.
 */
Bat::Bat(float startX, float startY)
    : m_Position(startX, startY)
{
    m_Shape.setSize(sf::Vector2f(50.f, 5.f));
    m_Shape.setPosition(m_Position);
    Logger().info("Bat created at position (" + std::to_string(startX) + ", " + std::to_string(startY) + ")");
}

/**
 * @brief Retrieves the bat's bounding rectangle.
 */
sf::FloatRect Bat::getPosition() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Gets global bounds for collision detection.
 */
sf::FloatRect Bat::getGlobalBounds() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Accesses bat shape for rendering.
 */
const sf::RectangleShape& Bat::getShape() const {
    return m_Shape;
}

/**
 * @brief Begins movement to the left.
 */
void Bat::moveLeft() {
    m_MovingLeft = true;
    Logger().info("Bat movement: left initiated");
}

/**
 * @brief Begins movement to the right.
 */
void Bat::moveRight() {
    m_MovingRight = true;
    Logger().info("Bat movement: right initiated");
}

/**
 * @brief Stops leftward movement.
 */
void Bat::stopLeft() {
    if (m_MovingLeft) {
        Logger().info("Bat movement: left stopped");
    }
    m_MovingLeft = false;
}

/**
 * @brief Stops rightward movement.
 */
void Bat::stopRight() {
    if (m_MovingRight) {
        Logger().info("Bat movement: right stopped");
    }
    m_MovingRight = false;
}

/**
 * @brief Updates bat position based on movement flags.
 */
void Bat::update(sf::Time dt) {
    bool updated = false;

    if (m_MovingLeft) {
        m_Position.x -= m_Speed * dt.asSeconds();
        updated = true;
    }

    if (m_MovingRight) {
        m_Position.x += m_Speed * dt.asSeconds();
        updated = true;
    }

    m_Shape.setPosition(m_Position);

    if (updated) {
        Logger().info("Bat updated position to (" + std::to_string(m_Position.x) + ", " + std::to_string(m_Position.y) + ")");
    }
}
