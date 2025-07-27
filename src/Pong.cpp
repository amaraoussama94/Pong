/**
 * @file Pong.cpp
 * @brief Main entry point for the Pong game using SFML.
 * Handles game loop, rendering, input management, and transitions between menu, single-player, and multiplayer modes.
 * @author Oussama Amara
 * @date 2025-07-27
 */

#include "Bat.hpp"
#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <optional>
#include <iostream>
#include "Logger.hpp"

int main() {
    Logger log; // Initialize logger
    log.info("Game starting...");

    // The game will always be in one of three states
    enum class State { MENU, SINGLEPLAYER, MULTIPLAYER };
    // Start with the MENU state
    State state = State::MENU;
    log.info("Initial game state: MENU");

    // Create a video mode object based on desktop resolution
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().size.x;
    resolution.y = sf::VideoMode::getDesktopMode().size.y;

    // Create and open a window for the game
    sf::RenderWindow window;
    window.create(sf::VideoMode({static_cast<unsigned int>(resolution.x), static_cast<unsigned int>(resolution.y)}), "Pong");
    log.info("Render window created with resolution: " + std::to_string((int)resolution.x) + "x" + std::to_string((int)resolution.y));
    // Player 1
    int score_1 = 0;
    int lives_1 = 3;

    // Player 2
    int score_2 = 0;
    int lives_2 = 3;

    // Create bats and ball
    Bat bat_1(resolution.x / 2, resolution.y - 80); // Player 1 at bottom
    Bat bat_2(resolution.x / 2, 20);               // Player 2 at top
    Ball ball(resolution.x / 2.f, 0.f,resolution);

    // HUD setup (SFML 3.0.0 compliant)
    sf::Font font;
    if (!font.openFromFile("fonts/DS-DIGI.TTF")) {
        std::cerr << "Failed to load font: DS-DIGI.TTF" << std::endl;
        log.error("Failed to load font");
        return -1;
    }
    log.info("Font loaded successfully");
    sf::Text hud_1(font, "Score: 0", 25);
    sf::Text hud_2(font, "Lives: 3", 25);

    hud_1.setFillColor(sf::Color::White);
    hud_2.setFillColor(sf::Color::White);
    hud_1.setPosition(sf::Vector2f(20.f, resolution.y / 2.0f));
    hud_2.setPosition(sf::Vector2f(resolution.x - 200.f, resolution.y / 2.0f));

    // Clock for delta time
    sf::Clock clock;
    float Time_elapsed = 0;

    // Menu text
    sf::Text GameMode(font);
    GameMode.setCharacterSize(80);
    GameMode.setFillColor(sf::Color::White);
    GameMode.setPosition(sf::Vector2f(resolution.x / 2 - 400, resolution.y / 2 - 100));
    std::stringstream ssGameMode;
    ssGameMode << "1- Single player mode\n2- multiplayer mode";
    GameMode.setString(ssGameMode.str());

    while (window.isOpen()) {
        /*
        **********************************
        ***** Handle the player input*****
        **********************************
        */
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                log.info("Window close event triggered");
                window.close();
            }

    if (event->is<sf::Event::KeyPressed>()) {
        const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
        if (keyEvent) {
            auto key = keyEvent->scancode;
            if (state == State::MENU) {
                if (key == sf::Keyboard::Scancode::Num1){
                    state = State::SINGLEPLAYER; // change mode to single player
                    log.info("Switched to SINGLEPLAYER mode");
                }
                else if (key == sf::Keyboard::Scancode::Num2){
                    state = State::MULTIPLAYER; // change mode to multiplayer
                    log.info("Switched to MULTIPLAYER mode");
                }
            }

            if (key == sf::Keyboard::Scancode::M){
                state = State::MENU; // back to menu
                log.info("Returned to MENU");
            }
        }
}

        }

        // Handle the player quitting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            log.info("Escape pressed — exiting");
            window.close();
        }

        /******* MENU STATE *******/
        if (state == State::MENU) {
            log.info("Rendering menu");
            window.clear();
            window.draw(GameMode); // draw menu to the screen
            window.display();      // Required to display rendered content
            continue;
        }

        // Update the delta time
        sf::Time dt = clock.restart();
        Time_elapsed += dt.asSeconds();

        /******* SINGLE PLAYER MODE *******/
        if (state == State::SINGLEPLAYER) {
            log.info("Singleplayer tick");
            auto batBounds = bat_1.getGlobalBounds();
            auto batPos = batBounds.position;
            auto batSize = batBounds.size;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                bat_1.moveLeft();
                if (batPos.x < 0)
                    bat_1.stopLeft();
            } else {
                bat_1.stopLeft();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                bat_1.moveRight();
                if (batPos.x + batSize.x > window.getSize().x)
                    bat_1.stopRight();
            } else {
                bat_1.stopRight();
            }

            bat_1.update(dt);
            ball.update(dt);

            std::stringstream ss_1;
            ss_1 << "Score:" << score_1 << " Lives:" << lives_1;
            hud_1.setString(ss_1.str());

            auto ballBounds = ball.getGlobalBounds();
            auto ballPos = ballBounds.position;
            auto ballSize = ballBounds.size;

            if (ballPos.y > window.getSize().y) {
                ball.reboundBottom();
                lives_1--;
                log.info("Ball hit bottom wall — Player 1 lives left: " + std::to_string(lives_1));
                if (lives_1 < 1) {
                    log.info("Player 1 game over — returning to MENU");
                    ball = Ball(resolution.x / 2.f, resolution.y / 2.f,resolution); // Reset to center
                    Time_elapsed = 0; // Prevent immediate scoring
                    state = State::MENU;
                    score_1 = 0;
                    lives_1 = 3;
                }
            }

            if (ballPos.y < 0) {
                ball.reboundBatOrTop();
                if (Time_elapsed > 1)
                    log.info("Player 1 scored — Score: " + std::to_string(score_1));
                    score_1++;
            }

            if (ballPos.x < 0 || ballPos.x + ballSize.x > window.getSize().x)
                ball.reboundSides();

            if (ball.getGlobalBounds().findIntersection(bat_1.getGlobalBounds()))
                ball.reboundBatOrTop();

            window.clear();
            window.draw(hud_1);
            window.draw(bat_1.getShape());
            window.draw(ball.getShape());
            window.display();
        }

        /******* MULTIPLAYER MODE *******/
        if (state == State::MULTIPLAYER) {
            log.info("Multiplayer tick");
            auto bat1Bounds = bat_1.getGlobalBounds();
            auto bat1Pos = bat1Bounds.position;
            auto bat1Size = bat1Bounds.size;

            auto bat2Bounds = bat_2.getGlobalBounds();
            auto bat2Pos = bat2Bounds.position;
            auto bat2Size = bat2Bounds.size;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                bat_1.moveLeft();
                if (bat1Pos.x < 0)
                    bat_1.stopLeft();
            } else {
                bat_1.stopLeft();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                bat_1.moveRight();
                if (bat1Pos.x + bat1Size.x > window.getSize().x)
                    bat_1.stopRight();
            } else {
                bat_1.stopRight();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
                bat_2.moveLeft();
                if (bat2Pos.x < 0)
                    bat_2.stopLeft();
            } else {
                bat_2.stopLeft();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                bat_2.moveRight();
                if (bat2Pos.x + bat2Size.x > window.getSize().x)
                    bat_2.stopRight();
            } else {
                bat_2.stopRight();
            }

            bat_1.update(dt);
            bat_2.update(dt);
            ball.update(dt);

            std::stringstream ss_1, ss_2;
            ss_1 << "Score:" << score_1 << " Lives:" << lives_1;
            ss_2 << "Score:" << score_2 << " Lives:" << lives_2;
            hud_1.setString(ss_1.str());
            hud_2.setString(ss_2.str());

            auto ballBounds = ball.getGlobalBounds();
            auto ballPos = ballBounds.position;
            auto ballSize = ballBounds.size;

            if (ballPos.y > window.getSize().y) {
                log.info("Player 2 scored — Player 1 lives: " + std::to_string(lives_1));
                ball.reboundBottom();
                lives_1--;
                score_2++;
                if (lives_1 < 1) {
                     ball = Ball(resolution.x / 2.f, resolution.y / 2.f,resolution); // Reset to center
                    Time_elapsed = 0; // Prevent immediate scoring
                    state = State::MENU;
                    score_1 = score_2 = 0;
                    lives_1 = lives_2 = 3;
                }
            }

            if (ballPos.y < 0) {
                log.info("Player 1 scored — Player 2 lives: " + std::to_string(lives_2));
                ball.reboundBatOrTopMultiplayer();
                score_1++;
                lives_2--;
                if (lives_2 < 1) {
                    state = State::MENU;
                    score_1 = score_2 = 0;
                    lives_1 = lives_2 = 3;
                }
            }

            if (ballPos.x < 0 || ballPos.x + ballSize.x > window.getSize().x)
                ball.reboundSides();

            if (ball.getGlobalBounds().findIntersection(bat_1.getGlobalBounds()))
                ball.reboundBatOrTop();

            if (ball.getGlobalBounds().findIntersection(bat_2.getGlobalBounds()))
                ball.reboundBatOrTop();

            window.clear();
            window.draw(hud_1);
            window.draw(hud_2);
            window.draw(bat_1.getShape());
            window.draw(bat_2.getShape());
            window.draw(ball.getShape());
            window.display();
        }
    }

    log.info("Game shutdown");
    return 0;
}
