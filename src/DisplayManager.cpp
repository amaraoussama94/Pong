/**
 * @file DisplayManager.cpp
 * @brief Implementation of DisplayManager class for rendering game elements and HUD.   
 * Handles different game states like menu, single-player, and multiplayer.
 * Provides methods to render the game screen and update HUD elements.
 *  @author Oussama Amara
 * @date 2025-08-2
 * @version 1.0
 */
#include "DisplayManager.hpp"
#include <sstream>


/**
 * @brief Constructor for DisplayManager.
 * Initializes HUD texts and their properties.
 *  @param font Reference to the font used for HUD texts.
 * @param resolution The resolution of the game window.
 * Initializes the HUD texts with their positions, sizes, and colors.
 * Sets the game mode text to display available game modes.
 */
DisplayManager::DisplayManager(sf::Font& font, const sf::Vector2f& resolution) : hud_1(font, "", 25),
      hud_2(font, "", 25),
      GameMode(font, "1- Single player mode\n2- Multiplayer mode", 80){
    
    hud_1.setFont(font);
    hud_2.setFont(font);
    hud_1.setCharacterSize(25);
    hud_2.setCharacterSize(25);
    hud_1.setFillColor(sf::Color::White);
    hud_2.setFillColor(sf::Color::White);
    hud_1.setPosition(sf::Vector2f(20.f, resolution.y / 2.f));
    hud_2.setPosition(sf::Vector2f(resolution.x - 200.f, resolution.y / 2.f));

    GameMode.setFont(font);
    GameMode.setCharacterSize(80);
    GameMode.setFillColor(sf::Color::White);
    GameMode.setPosition(sf::Vector2f(resolution.x / 2 - 400, resolution.y / 2 - 100));
    GameMode.setString("1- Single player mode\n2- Multiplayer mode");
}
/**
 * @brief Renders the menu screen.
 * Clears the window and draws the game mode text.
 * @param window Reference to the render window.
 * Displays the menu options for the player.
 */
void DisplayManager::renderMenu(sf::RenderWindow& window) {
    window.clear();
    window.draw(GameMode);
    window.display();
}
/**
 * @brief Renders the single-player game screen.
 * Clears the window and draws the bat, ball, and HUD.
 * @param window Reference to the render window.
 * @param bat Reference to the player's bat.
 * @param ball Reference to the ball object.
 * @param score Current score of the player.
 * @param lives Remaining lives of the player.
 * @param highScore1 High score for player 1.
 * Displays the player's score, lives, and high score on the HUD.
 */
void DisplayManager::renderSingleplayer(sf::RenderWindow& window, const Bat& bat, const Ball& ball, int score, int lives, int highScore1) {
    std::stringstream ss;
    ss << "Score:" << score << " Lives:" << lives << " High:" << highScore1;
    hud_1.setString(ss.str());

    window.clear();
    window.draw(hud_1);
    window.draw(bat.getShape());
    window.draw(ball.getShape());
    window.display();
}

/**
 * @brief Renders the multiplayer game screen.
 * Clears the window and draws both bats, the ball, and the HUD for both players.
 * @param window Reference to the render window.
 * @param bat1 Reference to the first player's bat.
 * @param bat2 Reference to the second player's bat.
 * @param ball Reference to the ball object.
 * @param score1 Current score of player 1.
 * @param lives1 Remaining lives of player 1.
 * @param score2 Current score of player 2.
 * @param lives2 Remaining lives of player 2.
 */
void DisplayManager::renderMultiplayer(sf::RenderWindow& window, const Bat& bat1, const Bat& bat2, const Ball& ball, int score1, int lives1, int score2, int lives2) {
    std::stringstream ss1, ss2;
    ss1 << "Score:" << score1 << " Lives:" << lives1;
    ss2 << "Score:" << score2 << " Lives:" << lives2;
    hud_1.setString(ss1.str());
    hud_2.setString(ss2.str());

    window.clear();
    window.draw(hud_1);
    window.draw(hud_2);
    window.draw(bat1.getShape());
    window.draw(bat2.getShape());
    window.draw(ball.getShape());
    window.display();
}
