/**
 * @file Ball.cpp
 * @brief Implementation of the Ball class, representing the ball in a Pong game.
 * This class handles the ball's position, movement, and collision logic.
 * @author Oussama Amara
 * @date 2025-07-27
 */
#include "Ball.hpp"

/**
 * @brief Constructs a ball at the specified position.
 * @param startX X-coordinate for the ball's initial position.
 * @param startY Y-coordinate for the ball's initial position.
 */
Ball::Ball(float startX, float startY)
    : m_Position(startX, startY)
{
    m_Shape.setSize(sf::Vector2f(10.f, 10.f));
    m_Shape.setPosition(m_Position);
}

/**
 * @brief Retrieves the global bounding rectangle of the ball.
 * @return A FloatRect representing the ball's bounds in global coordinates.
 */
sf::FloatRect Ball::getGlobalBounds() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Retrieves the current position rectangle of the ball.
 * @return A FloatRect representing the ball's position and dimensions.
 */
sf::FloatRect Ball::getPosition() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Provides access to the ball's shape for rendering.
 * @return A const reference to the RectangleShape.
 */
const sf::RectangleShape& Ball::getShape() const {
    return m_Shape;
}

/**
 * @brief Returns the horizontal velocity of the ball.
 * @return The direction multiplier for movement along the X-axis.
 */
float Ball::getXVelocity() const {
    return m_DirectionX;
}

/**
 * @brief Reverses the horizontal direction to simulate bouncing off side walls.
 */
void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
}

/**
 * @brief Reverses the vertical direction to simulate bounce off top or paddle in single-player mode.
 */
void Ball::reboundBatOrTop() {
    m_DirectionY = -m_DirectionY;
}

/**
 * @brief Resets position and reverses vertical direction when the ball hits the bottom wall.
 */
void Ball::reboundBottom() {
    m_Position = {500.f, 100.f};
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
}

/**
 * @brief Resets position and reverses direction for multiplayer-specific collision logic.
 */
void Ball::reboundBatOrTopMultiplayer() {
    m_Position = {500.f, 100.f};
    m_DirectionY = -m_DirectionY;
    m_Shape.setPosition(m_Position);
}

/**
 * @brief Updates ball position based on velocity and elapsed time.
 * @param dt Time elapsed since last frame.
 */
void Ball::update(sf::Time dt) {
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}
