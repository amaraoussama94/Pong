/**
 * @file Ball.hpp
 * @brief Header file for the Ball class, representing the ball in a Pong game.
 * This class handles the ball's position, movement, and collision logic.
 * @author Oussama Amara
 - @date 2025-07-27
 */
#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Ball
 * @brief Represents the ball in a Pong game, handling position, movement, and collision logic.
 */
class Ball {
private:
    /** @brief Current position of the ball in 2D space. */
    sf::Vector2f m_Position;

    /** @brief Graphical shape used to render the ball (a rectangle). */
    sf::RectangleShape m_Shape;

    /** @brief Movement speed of the ball in pixels per second. */
    float m_Speed = 1000.0f;

    /** @brief Horizontal direction multiplier (-1.0 to 1.0). */
    float m_DirectionX = 0.2f;

    /** @brief Vertical direction multiplier (-1.0 to 1.0). */
    float m_DirectionY = 0.2f;

public:
    /**
     * @brief Constructor that initializes the ball at a given starting position.
     * @param startX Initial x-coordinate.
     * @param startY Initial y-coordinate.
     */
    Ball(float startX, float startY);

    /**
     * @brief Retrieves the current bounding rectangle of the ball.
     * @return FloatRect representing the ball's position and size.
     */
    sf::FloatRect getPosition() const;

    /**
     * @brief Provides read-only access to the ball's graphical shape.
     * @return Reference to the internal RectangleShape.
     */
    const sf::RectangleShape& getShape() const;

    /**
     * @brief Returns the global bounds of the ball for collision detection.
     * @return FloatRect containing position and dimensions in global coordinates.
     */
    sf::FloatRect getGlobalBounds() const;

    /**
     * @brief Returns the current horizontal velocity of the ball.
     * @return Velocity along the X-axis.
     */
    float getXVelocity() const;

    /**
     * @brief Reverses the horizontal direction when hitting left or right walls.
     */
    void reboundSides();

    /**
     * @brief Reverses the vertical direction when hitting the bat or top of the screen in single-player mode.
     */
    void reboundBatOrTop();

    /**
     * @brief Reverses vertical direction when hitting bat or top edge in multiplayer mode.
     */
    void reboundBatOrTopMultiplayer();

    /**
     * @brief Handles logic when the ball hits the bottom of the screen.
     */
    void reboundBottom();

    /**
     * @brief Updates the ball's position based on its velocity and elapsed time.
     * @param dt Time delta since last update.
     */
    void update(sf::Time dt);
};
