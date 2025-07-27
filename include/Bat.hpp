/**
 * @file Bat.hpp
 * @brief Header file for the Bat class, representing the player's paddle in a Pong game.
 * This class handles movement, position tracking, and graphical representation of the paddle.
 * @author Oussama Amara
 * @date 2025-07-27
 */

#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Bat
 * @brief Represents a paddle controlled by the player, with logic for motion and rendering.
 */
class Bat {
private:
    /** @brief Current position of the bat in 2D space. */
    sf::Vector2f m_Position;

    /** @brief Graphical shape used to render the bat (a rectangle). */
    sf::RectangleShape m_Shape;

    /** @brief Movement speed of the bat in pixels per second. */
    float m_Speed = 1000.0f;

    /** @brief Indicates whether the bat is currently moving right. */
    bool m_MovingRight = false;

    /** @brief Indicates whether the bat is currently moving left. */
    bool m_MovingLeft = false;

public:
    /**
     * @brief Constructs a bat at the given starting coordinates.
     * @param startX Initial x-coordinate.
     * @param startY Initial y-coordinate.
     */
    Bat(float startX, float startY);

    /**
     * @brief Retrieves the current bounding rectangle of the bat.
     * @return FloatRect representing the bat's position and size.
     */
    sf::FloatRect getPosition() const;

    /**
     * @brief Provides read-only access to the bat's graphical shape.
     * @return Reference to the internal RectangleShape.
     */
    const sf::RectangleShape& getShape() const;

    /**
     * @brief Returns the global bounds of the bat for collision detection.
     * @return FloatRect containing position and dimensions in global coordinates.
     */
    sf::FloatRect getGlobalBounds() const;

    /**
     * @brief Begins leftward movement.
     */
    void moveLeft();

    /**
     * @brief Begins rightward movement.
     */
    void moveRight();

    /**
     * @brief Stops leftward movement.
     */
    void stopLeft();

    /**
     * @brief Stops rightward movement.
     */
    void stopRight();

    /**
     * @brief Updates the bat's position based on movement flags and elapsed time.
     * @param dt Time delta since the last update.
     */
    void update(sf::Time dt);
};
