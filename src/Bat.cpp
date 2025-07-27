/**
 * @file Bat.cpp
 * @brief Implementation of the Bat class, representing the player's paddle in a Pong game.
 * This class handles the bat's position, movement, and rendering.
 * @author Oussama Amara
 *  @date 2025-07-27
 */
#include "Bat.hpp"

/**
 * @brief Constructs a bat at the specified starting coordinates.
 * @param startX X-coordinate of the bat's initial position.
 * @param startY Y-coordinate of the bat's initial position.
 */
Bat::Bat(float startX, float startY)
    : m_Position(startX, startY)
{
    m_Shape.setSize(sf::Vector2f(50.f, 5.f));
    m_Shape.setPosition(m_Position);
}

/**
 * @brief Retrieves the current bounding rectangle of the bat.
 * @return FloatRect representing the bat's position and dimensions.
 */
sf::FloatRect Bat::getPosition() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Retrieves the global bounding box of the bat for collision detection.
 * @return FloatRect containing global position and size.
 */
sf::FloatRect Bat::getGlobalBounds() const {
    return m_Shape.getGlobalBounds();
}

/**
 * @brief Provides access to the graphical shape of the bat for rendering.
 * @return Const reference to the RectangleShape.
 */
const sf::RectangleShape& Bat::getShape() const {
    return m_Shape;
}

/**
 * @brief Initiates movement to the left by setting the flag.
 */
void Bat::moveLeft() {
    m_MovingLeft = true;
}

/**
 * @brief Initiates movement to the right by setting the flag.
 */
void Bat::moveRight() {
    m_MovingRight = true;
}

/**
 * @brief Stops leftward movement by resetting the flag.
 */
void Bat::stopLeft() {
    m_MovingLeft = false;
}

/**
 * @brief Stops rightward movement by resetting the flag.
 */
void Bat::stopRight() {
    m_MovingRight = false;
}

/**
 * @brief Updates the bat's position based on movement flags and elapsed time.
 * @param dt Time elapsed since last frame.
 */
void Bat::update(sf::Time dt) {
    if (m_MovingLeft)
        m_Position.x -= m_Speed * dt.asSeconds();
    if (m_MovingRight)
        m_Position.x += m_Speed * dt.asSeconds();

    m_Shape.setPosition(m_Position);
}
