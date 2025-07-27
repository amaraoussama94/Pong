/**
 * @file Ball.cpp
 * @brief Implementation of the Ball class, representing the ball in a Pong game.
 * This class handles the ball's position, movement, and collision logic.
 * @author Oussama Amara
 * @date 2025-07-27
 */

#include "Ball.hpp"
#include "Logger.hpp"

/**
 * @brief Constructs a ball at the specified position.
 */
Ball::Ball(float startX, float startY)
    : m_Position(startX, startY)
{
    m_Shape.setSize(sf::Vector2f(10.f, 10.f));
    m_Shape.setPosition(m_Position);
    Logger().info("Ball created at position (" + std::to_string(startX) + ", " + std::to_string(startY) + ")");
}

/**
 * @brief Retrieves the global bounding rectangle of the ball.
 */
sf::FloatRect Ball::getGlobalBounds() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Retrieves the current position rectangle of the ball.
 */
sf::FloatRect Ball::getPosition() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Provides access to the ball's shape for rendering.
 */
const sf::RectangleShape& Ball::getShape() const {
    return m_Shape;
}

/**
 * @brief Returns the horizontal velocity of the ball.
 */
float Ball::getXVelocity() const {
    return m_DirectionX;
}

/**
 * @brief Reverses horizontal direction to simulate bounce off side walls.
 */
void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
    Logger().info("Ball rebounded off side wall. DirectionX is now " + std::to_string(m_DirectionX));
}

/**
 * @brief Reverses vertical direction when hitting bat or top edge.
 */
void Ball::reboundBatOrTop() {
    m_DirectionY = -m_DirectionY;
    Logger().info("Ball rebounded off bat or top. DirectionY is now " + std::to_string(m_DirectionY));
}

/**
 * @brief Handles ball rebound on bottom hit — resets position.
 */
void Ball::reboundBottom() {
    m_Position = {500.f, 100.f};
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
    Logger().info("Ball hit bottom. Position reset to (500, 100). DirectionY is now " + std::to_string(m_DirectionY));
}

/**
 * @brief Multiplayer-specific rebound logic when hitting top edge or bat.
 */
void Ball::reboundBatOrTopMultiplayer() {
    m_Position = {500.f, 100.f};
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
    Logger().info("Multiplayer: Ball rebounded off bat or top. Reset position to (500, 100). DirectionY is now " + std::to_string(m_DirectionY));
}

/**
 * @brief Updates ball position based on velocity and delta time.
 */
void Ball::update(sf::Time dt) {
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
    Logger().info("Ball updated position to (" + std::to_string(m_Position.x) + ", " + std::to_string(m_Position.y) + ")");
}
