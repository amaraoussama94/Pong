/**
 * @file DisplayManager.hpp
 * @brief 
 * Manages the rendering of game elements and HUD.
 * Handles different game states like menu, single-player, and multiplayer.
 * Provides methods to render the game screen and update HUD elements.
 * @author Oussama Amara
 * @date 2025-08-2
 * @version 1.0
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Bat.hpp"
#include "Ball.hpp"

/**
 * @class DisplayManager
 * @brief Manages the rendering of game elements and HUD.   
 * Handles different game states like menu, single-player, and multiplayer.
 * Provides methods to render the game screen and update HUD elements.
 */
class DisplayManager {
public:
    DisplayManager(sf::Font& font, const sf::Vector2f& resolution);
    void renderMenu(sf::RenderWindow& window);
    void renderSingleplayer(sf::RenderWindow& window, const Bat& bat, const Ball& ball, int score, int lives, int highScore1);
    void renderMultiplayer(sf::RenderWindow& window, const Bat& bat1, const Bat& bat2, const Ball& ball, int score1, int lives1, int score2, int lives2);

private:
    sf::Text hud_1, hud_2, GameMode;
};
