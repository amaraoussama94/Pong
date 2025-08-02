/**
 * @file Pong.cpp
 * @brief Main entry point for the Pong game using SFML.
 * Handles game loop, rendering, input management, and transitions between menu, single-player, and multiplayer modes.
 * @author Oussama Amara
 * @date 2025-07-27
 */

#include "Bat.hpp"
#include "Ball.hpp"
#include "DisplayManager.hpp"
#include "Logger.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>

int main() {
    Logger log;
    log.info("Game starting...");
    int high_score_1 = 0;
    enum class State { MENU, SINGLEPLAYER, MULTIPLAYER };
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

    int score_1 = 0, lives_1 = 3;
    int score_2 = 0, lives_2 = 3;

    Bat bat_1(resolution.x / 2, resolution.y - 80);
    Bat bat_2(resolution.x / 2, 20);
    Ball ball(resolution.x / 2.f, 0.f, resolution);
// HUD setup (SFML 3.0.0 compliant)
    sf::Font font;
    if (!font.openFromFile("fonts/DS-DIGI.TTF")) {
        std::cerr << "Failed to load font\n";
        log.error("Failed to load font");
        return -1;
    }
    log.info("Font loaded successfully");

    DisplayManager display(font, resolution);
    sf::Clock clock;
    float Time_elapsed = 0;

    while (window.isOpen()) {
        /* **********************************
        ***** Handle the player input*****
        **********************************/
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                log.info("Window close event triggered");
                window.close();
            }
            if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent) {
                    auto key = keyEvent->scancode;
                    if (state == State::MENU) {
                        if (key == sf::Keyboard::Scancode::Num1) {
                            state = State::SINGLEPLAYER;
                            log.info("Switched to SINGLEPLAYER mode");
                        } else if (key == sf::Keyboard::Scancode::Num2) {
                            state = State::MULTIPLAYER;
                            log.info("Switched to MULTIPLAYER mode");
                        }
                    }
                    if (key == sf::Keyboard::Scancode::M) {
                        state = State::MENU;
                        log.info("Returned to MENU");
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
            log.info("Escape pressed — exiting");
            window.close();
        }

        sf::Time dt = clock.restart();
        Time_elapsed += dt.asSeconds();

        if (state == State::MENU) {
            log.info("Rendering menu");
            display.renderMenu(window);
            continue;
        }

        if (state == State::SINGLEPLAYER) {
            log.info("Singleplayer tick");

            auto batBounds = bat_1.getGlobalBounds();
            auto batPos = batBounds.position;
            auto batSize = batBounds.size;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
                bat_1.moveLeft();
                if (batPos.x < 0) bat_1.stopLeft();
            } else bat_1.stopLeft();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                bat_1.moveRight();
                if (batPos.x + batSize.x > window.getSize().x) bat_1.stopRight();
            } else bat_1.stopRight();

            bat_1.update(dt);
            ball.update(dt);

            auto ballBounds = ball.getGlobalBounds();
            auto ballPos = ballBounds.position;
            auto ballSize = ballBounds.size;

            if (ballPos.y > window.getSize().y) {
                ball.reboundBottom();
                lives_1--;
                log.info("Ball hit bottom — Player 1 lives left: " + std::to_string(lives_1));
                if (lives_1 < 1) {
                    if (score_1 > high_score_1) {
                        high_score_1 = score_1;
                        log.info("🎉 New High Score for Player 1: " + std::to_string(high_score_1));
                    }
                    ball = Ball(resolution.x / 2.f, resolution.y / 2.f, resolution);
                    Time_elapsed = 0;
                    state = State::MENU;
                    score_1 = 0;
                    lives_1 = 3;
                    continue;
                }
            }

            if (ballPos.y < 0) {
                ball.reboundBatOrTop();
                if (Time_elapsed > 1) {
                    score_1++;
                    log.info("Player 1 scored — Score: " + std::to_string(score_1));
                }
            }

            if (ballPos.x < 0 || ballPos.x + ballSize.x > window.getSize().x)
                ball.reboundSides();

            if (ball.getGlobalBounds().findIntersection(bat_1.getGlobalBounds()))
                ball.reboundBatOrTop();

            display.renderSingleplayer(window, bat_1, ball, score_1, lives_1,high_score_1);
        }

        if (state == State::MULTIPLAYER) {
            log.info("Multiplayer tick");

            auto bat1Bounds = bat_1.getGlobalBounds();
            auto bat2Bounds = bat_2.getGlobalBounds();
            auto bat1Pos = bat1Bounds.position;
            auto bat1Size = bat1Bounds.size;
            auto bat2Pos = bat2Bounds.position;
            auto bat2Size = bat2Bounds.size;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
                bat_1.moveLeft();
                if (bat1Pos.x < 0) bat_1.stopLeft();
            } else bat_1.stopLeft();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                bat_1.moveRight();
                if (bat1Pos.x + bat1Size.x > window.getSize().x) bat_1.stopRight();
            } else bat_1.stopRight();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
                bat_2.moveLeft();
                if (bat2Pos.x < 0) bat_2.stopLeft();
            } else bat_2.stopLeft();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
                bat_2.moveRight();
                if (bat2Pos.x + bat2Size.x > window.getSize().x) bat_2.stopRight();
            } else bat_2.stopRight();

            bat_1.update(dt);
            bat_2.update(dt);
            ball.update(dt);

            auto ballBounds = ball.getGlobalBounds();
            auto ballPos = ballBounds.position;
            auto ballSize = ballBounds.size;

            if (ballPos.y > window.getSize().y) {
                ball.reboundBottom();
                lives_1--;
                score_2++;
                log.info("Player 2 scored — Player 1 lives: " + std::to_string(lives_1));
                if (lives_1 < 1) {
                    ball = Ball(resolution.x / 2.f, resolution.y / 2.f, resolution);
                    Time_elapsed = 0;
                    state = State::MENU;
                    score_1 = score_2 = 0;
                    lives_1 = lives_2 = 3;
                    continue;
                }
            }

            if (ballPos.y < 0) {
                ball.reboundBatOrTopMultiplayer();
                score_1++;
                lives_2--;
                log.info("Player 1 scored — Player 2 lives: " + std::to_string(lives_2));
                if (lives_2 < 1) {
                    state = State::MENU;
                    score_1 = score_2 = 0;
                    lives_1 = lives_2 = 3;
                    continue;
                }
            }

            if (ballPos.x < 0 || ballPos.x + ballSize.x > window.getSize().x)
                ball.reboundSides();

            if (ball.getGlobalBounds().findIntersection(bat_1.getGlobalBounds()))
                ball.reboundBatOrTop();
            if (ball.getGlobalBounds().findIntersection(bat_2.getGlobalBounds()))
                ball.reboundBatOrTop();

            display.renderMultiplayer(window, bat_1, bat_2, ball, score_1, lives_1, score_2, lives_2);
        }
    }

    log.info("Game shutdown");
    return 0;
}
