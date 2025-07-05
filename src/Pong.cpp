#include "Bat.hpp"
#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <optional>

int main() {
    // The game will always be in one of three states
    enum class State { MENU, SINGLEPLAYER, MULTIPLAYER };
    // Start with the MENU state
    State state = State::MENU;

    // Create a video mode object based on desktop resolution
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().size.x;
    resolution.y = sf::VideoMode::getDesktopMode().size.y;

    // Create and open a window for the game
    sf::RenderWindow window;
    window.create(sf::VideoMode({static_cast<unsigned int>(resolution.x), static_cast<unsigned int>(resolution.y)}), "Pong");

    // Player 1
    int score_1 = 0;
    int lives_1 = 3;

    // Player 2
    int score_2 = 0;
    int lives_2 = 3;

    // Create bats and ball
    Bat bat_1(resolution.x / 2, resolution.y - 80); // Player 1 at bottom
    Bat bat_2(resolution.x / 2, 20);               // Player 2 at top
    Ball ball(resolution.x / 2, 0);

    // HUD setup
    // HUD setup (SFML 3.0.0 compliant)
    sf::Font font;
    if (!font.openFromFile("fonts/DS-DIGI.TTF")) {
        std::cerr << "Failed to load font: DS-DIGI.TTF" << std::endl;
        return -1;
    }

    sf::Text hud_1("Score: 0", font, 25);
    sf::Text hud_2("Lives: 3", font, 25);

    hud_1.setFillColor(sf::Color::White);
    hud_2.setFillColor(sf::Color::White);
    hud_1.setPosition(20.f, resolution.y / 2.0f);
    hud_2.setPosition(resolution.x - 200.f, resolution.y / 2.0f);


    // Clock for delta time
    sf::Clock clock;
    float Time_elapsed = 0;

    // Menu text
    sf::Text GameMode;
    GameMode.setFont(font);
    GameMode.setCharacterSize(80);
    GameMode.setFillColor(sf::Color::White);
    GameMode.setPosition(resolution.x / 2 - 400, resolution.y / 2 - 100);
    std::stringstream ssGameMode;
    ssGameMode << "1- Single player mode\n2- multiplayer mode";
    GameMode.setString(ssGameMode.str());

    while (window.isOpen()) {
        /*
        **********************************
        ***** Handle the player input*****
        **********************************
        */
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.is<sf::Event::Closed>())
                window.close();

            if (event.is<sf::Event::KeyPressed>()) {
                auto key = event.get<sf::Event::KeyPressed>().scancode;
                if (state == State::MENU) {
                    if (key == sf::Keyboard::Scancode::Num1)
                        state = State::SINGLEPLAYER; // change mode to single player
                    else if (key == sf::Keyboard::Scancode::Num2)
                        state = State::MULTIPLAYER; // change mode to multiplayer
                }
                if (key == sf::Keyboard::Scancode::M)
                    state = State::MENU; // back to menu
            }
        }

        // Handle the player quitting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        /******* MENU STATE *******/
        if (state == State::MENU) {
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                bat_1.moveLeft();
                if (bat_1.getPosition().left < 0)
                    bat_1.stopLeft();
            } else {
                bat_1.stopLeft();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                bat_1.moveRight();
                if (bat_1.getPosition().left + bat_1.getPosition().width > window.getSize().x)
                    bat_1.stopRight();
            } else {
                bat_1.stopRight();
            }

            bat_1.update(dt);
            ball.update(dt);

            std::stringstream ss_1;
            ss_1 << "Score:" << score_1 << " Lives:" << lives_1;
            hud_1.setString(ss_1.str());

            if (ball.getPosition().top > window.getSize().y) {
                ball.reboundBottom();
                lives_1--;
                if (lives_1 < 1) {
                    state = State::MENU;
                    score_1 = 0;
                    lives_1 = 3;
                }
            }

            if (ball.getPosition().top < 0) {
                ball.reboundBatOrTop();
                if (Time_elapsed > 1)
                    score_1++;
            }

            if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
                ball.reboundSides();

            if (ball.getPosition().findIntersection(bat_1.getPosition()))
                ball.reboundBatOrTop();

            /*
            **********************************************
            ****** Draw the bat, the ball and the HUD*****
            **********************************************
            */
            window.clear();
            window.draw(hud_1);
            window.draw(bat_1.getShape());
            window.draw(ball.getShape());
            window.display();
        }

        /******* MULTIPLAYER MODE *******/
        if (state == State::MULTIPLAYER) {
            auto handleBat = [&](Bat& bat, sf::Keyboard::Key left, sf::Keyboard::Key right) {
                if (sf::Keyboard::isKeyPressed(left)) {
                    bat.moveLeft();
                    if (bat.getPosition().left < 0)
                        bat.stopLeft();
                } else {
                    bat.stopLeft();
                }

                if (sf::Keyboard::isKeyPressed(right)) {
                    bat.moveRight();
                    if (bat.getPosition().left + bat.getPosition().width > window.getSize().x)
                        bat.stopRight();
                } else {
                    bat.stopRight();
                }
            };

            handleBat(bat_1, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right);
            handleBat(bat_2, sf::Keyboard::Key::Q, sf::Keyboard::Key::D);

            bat_1.update(dt);
            bat_2.update(dt);
            ball.update(dt);

            std::stringstream ss_1, ss_2;
            ss_1 << "Score:" << score_1 << " Lives:" << lives_1;
            ss_2 << "Score:" << score_2 << " Lives:" << lives_2;
            hud_1.setString(ss_1.str());
            hud_2.setString(ss_2.str());

            if (ball.getPosition().top > window.getSize().y) {
                ball.reboundBottom();
                lives_1--;
                score_2++;
                if (lives_1 < 1) {
                    state = State::MENU;
                    score_1 = score_2 = 0;
                    lives_1 = lives_2 = 3;
                }
            }

            if (ball.getPosition().top < 0) {
                ball.reboundBatOrTopMultiplayer(); // for multiplayer mode
                score_1++;
                lives_2--;
                if (lives_2 < 1) {
                    state = State::MENU;
                    score_1 = score_2 = 0;
                    lives_1 = lives_2 = 3;
                }
            }

            if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
                ball.reboundSides();

            if (ball.getPosition().findIntersection(bat_1.getPosition()))
                ball.reboundBatOrTop();
            if (ball.getPosition().findIntersection(bat_2.getPosition()))
                ball.reboundBatOrTop();

            /*
            **********************************************
            ****** Draw the bat, the ball and the HUD*****
            **********************************************
            */
            window.clear();
            window.draw(hud_1);
            window.draw(hud_2);
            window.draw(bat_1.getShape());
            window.draw(bat_2.getShape());
            window.draw(ball.getShape());
            window.display();
        }
    }

    return 0;
}
